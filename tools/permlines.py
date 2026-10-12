#!/usr/bin/env python3
"""permlines.py FILE FUNC 'line A' 'line B' ... : try all orders of the given (exact, consecutive) source lines."""
import sys, os, itertools, subprocess, tempfile, shutil
sys.path.insert(0, os.path.dirname(__file__))
import matchtool as M
f, func, lines = sys.argv[1], sys.argv[2], sys.argv[3:]
src = open(f).read()
block = '\n'.join(lines)
assert block in src, 'block not found verbatim'
best = None
for perm in itertools.permutations(lines):
    cand = src.replace(block, '\n'.join(perm))
    t = tempfile.mkdtemp(); p = os.path.join(t, os.path.basename(f)); open(p, 'w').write(cand)
    try:
        obj = M.compile_src(p)
    except SystemExit:
        continue
    fns = M.obj_functions(obj)
    if func not in fns: continue
    sc, res = M.compare(func, *fns[func], verbose=False)
    if best is None or sc > best[0]: best = (sc, perm)
    if sc == 1.0:
        open(f, 'w').write(cand); print('MATCH with order:'); print('\n'.join(perm)); sys.exit(0)
print('no match; best', best)
