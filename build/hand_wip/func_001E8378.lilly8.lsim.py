# local-alloc simulator for VU qtys of one basic block (gcc 2.95 local-alloc.c), from a .lreg dump
import re,sys,math
dump=sys.argv[1]; bb=int(sys.argv[2])
txt=open(dump).read()
info={}
for m in re.finditer(r'^Register (\d+) used (\d+) times across (\d+) insns( in block (\d+))?;(.*)$',txt,re.M):
    r=int(m.group(1)); info[r]=dict(refs=int(m.group(2)),blk=int(m.group(5)) if m.group(5) else -1,vu='VU_REGS' in m.group(6),deaths=(2 if 'dies in 2' in m.group(6) else 1), rest=m.group(6))
disp={}
g=open(dump.replace('.lreg','.greg')).read()
d=g[g.index(';; Register dispositions:'):]
d=d[:d.index('\n\n')]
for a,b in re.findall(r'(\d+) in (\d+)',d): disp[int(a)]=int(b)
s=txt.index('[bb %d] NOTE_INSN_BASIC_BLOCK'%bb); e=txt.index('[bb %d] NOTE_INSN_BASIC_BLOCK'%(bb+1))
s=txt.rindex('\n\n',0,s)
items=re.split(r'\n\n+',txt[s:e])
REG=r'\(reg(?:/\w)?(?::\w+)? (\d+)\)'
n=0; qty={}; regq={}; qn=0; order=[]
def born(r,t):
    global qn
    regq[r]=qn; qty[qn]=dict(regs=[r],birth=t,death=None,refs=info[r]['refs']); qn+=1
for it in items:
    it=it.strip()
    m=re.match(r'\((\w+)(?:/\w+)? (\d+)',it)
    if not m or m.group(1) in ('note','barrier','code_label') and m.group(1)!='code_label': continue
    kind=m.group(1)
    if kind=='note': continue
    n+=1
    body=it.split('(expr_list:REG')[0]
    body=re.sub(r'\(insn_list.*$','',body,flags=re.S)
    # operands
    if 'asm_operands' in body:
        outs=[int(x) for x in re.findall(r'\(set '+REG+r'\s*\(asm_operands',body)]
        am=re.search(r'asm_operands \("(?:[^"\\]|\\.)*"\) \("[^"]*"\) \d+\[(.*?)\]\s*\[',body,re.S)
        ins=[]
        if am:
            for op in re.split(r'\n\s*(?=\()',am.group(1).strip()):
                mm=re.match(REG,op.strip()); ins.append(int(mm.group(1)) if mm else None)
        ops=outs+ins; earlyc=False
        cons=re.search(r'asm_operands \("(?:[^"\\]|\\.)*"\) \("([^"]*)"',body).group(1)
        earlyc='&' in cons
    else:
        sm=re.match(r'\(\w+(?:/\w+)? \d+ \d+ \d+ \(set '+REG+r'\s*(.*)',body,re.S)
        if sm:
            src=sm.group(2).strip()
            mm=re.match(REG,src)
            ops=[int(sm.group(1)), int(mm.group(1)) if mm else None]
            if not mm:
                ops+= [int(x) for x in re.findall(REG,src)]
        else: ops=[]
        earlyc=False
    dead=[int(x) for x in re.findall(r'REG_DEAD '+REG,it)]
    unused=[int(x) for x in re.findall(r'REG_UNUSED '+REG,it)]
    sets=[int(x) for x in re.findall(r'\(set '+REG,body)]
    tied=None
    if len(ops)>1 and ops[0] is not None and ops[0] in info and info[ops[0]]['vu'] and not earlyc:
        for o in ops[1:]:
            if o is None or o not in regq or o==ops[0]: continue
            if o in dead and ops[0] not in regq and info[ops[0]]['blk']==bb and info[ops[0]]['deaths']==1:
                q=regq[o]; regq[ops[0]]=q; qty[q]['regs'].append(ops[0]); qty[q]['refs']+=info[ops[0]]['refs']; tied=o; break
    # deaths (inputs) at 2n
    for r in dead:
        if r in regq and r!=tied: qty[regq[r]]['death']=2*n
    for r in sets:
        if r in info and info[r]['vu'] and info[r]['blk']==bb and r not in regq: born(r,2*n)
    for r in unused:
        if r in regq: qty[regq[r]]['death']=2*n+1
    order.append((n,m.group(2),ops,sets,dead))
res=[]
for q,v in qty.items():
    L=(v['death'] or 0)-v['birth']
    pri=int(math.floor(math.log2(v['refs']))*v['refs']*2/L*10000) if L>0 else 0
    res.append((pri,q,v))
res.sort(key=lambda x:(-x[0],x[1]))
live={}
for pri,q,v in res:
    regs=v['regs']; hr=[disp.get(r) for r in regs]
    print('q%-3d pri=%-7d refs=%-3d [%d,%s) regs=%s -> %s'%(q,pri,v['refs'],v['birth'],v['death'],regs,['vf%d'%(h-79) if h else None for h in hr]))
