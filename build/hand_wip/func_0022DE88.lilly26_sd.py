#!/usr/bin/env python3
# usage: sd.py draft.cpp [ctx]  -> aligned diff blocks (target | ours)
import sys, os, subprocess, tempfile, difflib
sys.path.insert(0, os.path.expanduser('~/sly2-decomp/tools'))
import matchtool as M
src = os.path.abspath(sys.argv[1])
of = M.compile_src(src)
fns = M.obj_functions(of)
name = 'func_0022DE88'
words, rel = fns[name]
addr, size = M.load_functions()[name]
tgt = M.target_words(addr, size)
def d(w, va): return M.disasm(w, va)
def key(w):
    op = w >> 26
    if op in (2, 3): return w & 0xFC000000
    if op in M.IMM_OPS: return w & 0xFFFF0000
    return w
def skey(w):
    op = w >> 26
    if op in (2, 3): return w & 0xFC000000
    if op in (1,4,5,6,7,0x14,0x15,0x16,0x17) : return w & 0xFFFF0000
    if op in M.IMM_OPS and ((w >> 21) & 31) != 29: return w & 0xFFFF0000
    return w
sa=[skey(w) for w in tgt]; sb=[skey(w) for w in words]
sm2=difflib.SequenceMatcher(None, sa, sb, autojunk=False)
strict = max(len(sa),len(sb))-sum(bl.size for bl in sm2.get_matching_blocks())
import re as _re
def nkey(w):
    t=d(w,0)
    t=_re.sub(r'\$vf\d+','$vfN',t); t=_re.sub(r'\$f\d+','$fN',t)
    t=_re.sub(r'\$(v0|v1|a0|a1|a2|a3|t0|t1|t2|s0|s1|s2|s3|s4|s5|s7|fp)\b','$R',t)
    t=_re.sub(r'\. \+ 4 \+ \(.*?\)','BR',t); t=_re.sub(r'func_\w+','F',t)
    t=_re.sub(r'(?<!sp)\b(lui|addiu|ori)\s+(\$\w+), (\$\w+, )?-?0x[0-9A-Fa-f]+',r'\1 \2',t)
    t=_re.sub(r'0x[0-9A-Fa-f]+\(\$(?!sp)','X($',t)
    return t
if os.environ.get('NORM'):
    a=[nkey(w) for w in tgt]; b=[nkey(w) for w in words]
else:
    a = [key(w) for w in tgt]; b = [key(w) for w in words]
sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
out = []
nd = 0
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    if tag == 'equal':
        # still show immediate diffs
        for k in range(i2 - i1):
            if tgt[i1+k] != words[j1+k] and False: pass
        continue
    nd += max(i2 - i1, j2 - j1)
    out.append(f'--- {tag} T[{i1}:{i2}] (0x{addr+4*i1:X}) O[{j1}:{j2}]')
    for k in range(max(i2 - i1, j2 - j1)):
        l = d(tgt[i1+k], addr+4*(i1+k)) if i1+k < i2 else '-'
        r = d(words[j1+k], 0) if j1+k < j2 else '-'
        out.append(f'  {l:44s} | {r}')
print('frame ours', hex(-(words[0]&0xFFFF|~0xFFFF)), 'tgt', hex(-(tgt[0]&0xFFFF|~0xFFFF)))
open('/tmp/w22/sd.out', 'w').write('\n'.join(out))
m=sum(bl.size for bl in sm.get_matching_blocks()); print('STRICT', strict, 'target', len(tgt), 'ours', len(words), 'aligned', max(len(a),len(b))-m)
