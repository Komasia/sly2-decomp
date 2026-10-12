#!/usr/bin/env python3
"""Remove src/auto and src/splicewrap drafts for functions now matched by hand-written src/P2 code."""
import os, json, sys
sys.path.insert(0, os.path.dirname(__file__))
import matchtool as M
cache = json.load(open(os.path.join(M.ROOT, 'build', 'progress_cache.json')))
funcs = M.load_functions()
hand = set()
for src, v in cache.items():
    if '/src/auto/' in src or '/src/splicewrap/' in src or not v['res']: continue
    for n, s in v['res']:
        if s == 1.0: hand.add(funcs[n][0])
removed = 0
for d in ('auto', 'splicewrap'):
    for f in os.listdir(os.path.join(M.ROOT, 'src', d)):
        n = f[:-2]
        if n in funcs and funcs[n][0] in hand:
            os.remove(os.path.join(M.ROOT, 'src', d, f)); removed += 1
print('removed', removed, 'auto drafts superseded by hand-written code')
