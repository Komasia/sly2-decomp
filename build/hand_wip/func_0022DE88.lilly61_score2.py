#!/usr/bin/env python3
# score2: aligned count restricted to target index range [LO,HI) (env), plus overall
import sys, os, difflib
sys.path.insert(0, os.path.expanduser('~/sly2-decomp/tools'))
import matchtool as M
name='func_0022DE88'
addr,size=M.load_functions()[name]
tgt=M.target_words(addr,size)
def key(w):
    op=w>>26
    if op in (2,3): return w&0xFC000000
    if op in M.IMM_OPS: return w&0xFFFF0000
    return w
ta=[key(w) for w in tgt]
def score(path, lo=None, hi=None):
    try:
        of=M.compile_src(os.path.abspath(path)); fns=M.obj_functions(of)
        words,rel=fns[name]
    except BaseException as e:
        return None
    b=[key(w) for w in words]
    sm=difflib.SequenceMatcher(None,ta,b,autojunk=False)
    tot=max(len(ta),len(b))-sum(bl.size for bl in sm.get_matching_blocks())
    rng=None
    if lo is not None:
        eq=set()
        for bl in sm.get_matching_blocks():
            for k in range(bl.size): eq.add(bl.a+k)
        rng=sum(1 for i in range(lo,hi) if i not in eq)
    return tot,len(words),rng
if __name__=='__main__':
    lo=int(os.environ.get('LO','0')); hi=int(os.environ.get('HI','0'))
    for p in sys.argv[1:]:
        print(p, score(p,lo,hi) if hi else score(p))
