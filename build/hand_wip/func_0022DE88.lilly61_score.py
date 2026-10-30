#!/usr/bin/env python3
# score.py file... -> prints strict, aligned (target-order difflib) per file; importable score(path)
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
def score(path):
    try:
        of=M.compile_src(os.path.abspath(path)); fns=M.obj_functions(of)
        words,rel=fns[name]
    except BaseException as e:
        return None
    b=[key(w) for w in words]
    sm=difflib.SequenceMatcher(None,ta,b,autojunk=False)
    m=sum(bl.size for bl in sm.get_matching_blocks())
    return max(len(ta),len(b))-m, len(words), sum(1 for x,y in zip(tgt,words) if x!=y)
if __name__=='__main__':
    for p in sys.argv[1:]:
        print(p, score(p))
