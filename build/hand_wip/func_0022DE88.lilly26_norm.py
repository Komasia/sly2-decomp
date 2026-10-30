import sys, os, difflib, re
sys.path.insert(0, os.path.expanduser('~/sly2-decomp/tools'))
import matchtool as M
src=os.path.abspath(sys.argv[1]); mode=sys.argv[2] if len(sys.argv)>2 else 'vf'
of=M.compile_src(src); words,rel=M.obj_functions(of)['func_0022DE88']
addr,size=M.load_functions()['func_0022DE88']; tgt=M.target_words(addr,size)
def norm(w,va):
    s=M.disasm(w,va)
    if 'vf' in mode: s=re.sub(r'\$vf\d+','$vfN',s)
    if 'f' in mode.replace('vf',''): s=re.sub(r'\$f\d+','$fN',s)
    if 'g' in mode: s=re.sub(r'\$(v0|v1|a0|a1|a2|a3|t0|t1|t2|s0|s1|s2|s3|s4|s5|s7|fp)\b','$R',s)
    s=re.sub(r'\. \+ 4 \+ \(.*?\)','BR',s)
    s=re.sub(r'func_\w+','F',s)
    s=re.sub(r'0x[0-9A-Fa-f]+\(\$(?!sp)','X($',s)  # non-sp offsets
    s=re.sub(r'(lui|addiu|ori)\s+(\$\w+), (\$\w+, )?-?0x[0-9A-Fa-f]+',r'\1 \2',s)
    return s
a=[norm(w,0) for w in tgt]; b=[norm(w,0) for w in words]
sm=difflib.SequenceMatcher(None,a,b,autojunk=False)
m=sum(x.size for x in sm.get_matching_blocks())
print(mode,'norm-aligned',max(len(a),len(b))-m)
