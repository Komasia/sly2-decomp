#!/usr/bin/env python3
"""Re-score existing drafts (build/automatch*/NAME[.best].c) for the given functions (file of names or
all unmatched); copy any exact match to src/auto/NAME.c.   rescore.py [NAMES_FILE]"""
import os, sys, glob, json
from concurrent.futures import ThreadPoolExecutor
sys.path.insert(0, os.path.dirname(__file__))
import matchtool as M, quickfix as Q

def matched():
    c = json.load(open(os.path.join(M.ROOT, 'build', 'progress_cache.json')))
    s = {n for v in c.values() for n, sc in (v['res'] or []) if sc == 1.0}
    s |= {f[:-2] for f in os.listdir(os.path.join(M.ROOT, 'src', 'auto'))}
    return s

def one(n):
    for p in sorted(glob.glob(os.path.join(M.ROOT, 'build', 'automatch*', n + '.best.c')) + glob.glob(os.path.join(M.ROOT, 'build', 'automatch*', n + '.c'))):
        src = open(p).read()
        if Q.score_src(n, src) == 0:
            open(os.path.join(M.ROOT, 'src', 'auto', n + '.c'), 'w').write(src)
            return n, p
    return n, None

def main():
    funcs = M.load_functions(); done = matched()
    names = open(sys.argv[1]).read().split() if len(sys.argv) > 1 else list(funcs)
    names = [n for n in names if n not in done and n in funcs]
    print(len(names), 'to rescore', flush=True)
    k = 0
    with ThreadPoolExecutor(int(os.environ.get('JOBS', '2'))) as ex:
        for n, p in ex.map(one, names):
            if p: k += 1; print('MATCH', n, os.path.relpath(p, M.ROOT), flush=True)
    print(k, 'new matches')

if __name__ == '__main__':
    main()
