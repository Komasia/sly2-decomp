#!/usr/bin/env python3
# usage: rtl.py dumpfile [uid_lo uid_hi]   compact insn listing with pseudo->hard assignments from ";; Register N in R."
import sys, re
fn=sys.argv[1]
txt=open(fn).read()
assign={}
for m in re.finditer(r'^;; Register (\d+) in (\d+)\.',txt,re.M):
    assign[int(m.group(1))]=int(m.group(2))
# split top-level forms
forms=[];i=0;n=len(txt)
while i<n:
    if txt[i]=='(':
        d=0;j=i
        while j<n:
            c=txt[j]
            if c=='(':d+=1
            elif c==')':
                d-=1
                if d==0:break
            elif c=='"':
                j+=1
                while txt[j]!='"':
                    if txt[j]=='\\':j+=1
                    j+=1
            j+=1
        forms.append(txt[i:j+1]);i=j+1
    else:i+=1
HN={}
def reg(m):
    num=int(m.group(2));name=m.group(3)
    if num>=76 and num in assign: return f'p{num}[{assign[num]}]'
    if num>=76: return f'p{num}'
    return name or f'h{num}'
def compact(s):
    s=re.sub(r'\(reg(/\w)*:(\w+) (\d+)(?: ([\$\w]+))?\)',lambda m:(f"p{m.group(3)}[{assign[int(m.group(3))]}]" if int(m.group(3))>=76 and int(m.group(3)) in assign else (f"p{m.group(3)}" if int(m.group(3))>=76 else (m.group(4) or 'h'+m.group(3)))),s)
    s=re.sub(r'\s+',' ',s)
    return s
lo=int(sys.argv[2]) if len(sys.argv)>2 else 0
hi=int(sys.argv[3]) if len(sys.argv)>3 else 10**9
for f in forms:
    m=re.match(r'\((insn/?\w*|jump_insn|call_insn/?\w*|code_label|barrier|note\S*) (\d+)',f)
    if not m: continue
    uid=int(m.group(2))
    if uid<lo or uid>hi: continue
    kind=m.group(1)
    if kind.startswith('note'): continue
    c=compact(f)
    c=re.sub(r'\(const_double[^)]*\)\)?','CD',c)
    c=re.sub(r'\(insn_list[^)]*\)','',c)
    c=re.sub(r'\(expr_list:REG_\w+ [^()]*(\([^()]*\)[^()]*)*\)','',c)
    c=c[:260]
    print(c)
