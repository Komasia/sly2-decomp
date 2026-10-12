#!/usr/bin/env python3
"""worklist.py LO HI [MAXINSTR]: unmatched functions in [LO,HI) (hex), smallest first, one per line:
NAME ADDR NINSTR.  'Matched' = in build/progress_cache.json or a file exists in src/auto, src/hand, src/splicewrap."""
import os, sys, json, glob
sys.path.insert(0, os.path.dirname(__file__))
import matchtool as M
lo, hi = int(sys.argv[1], 16), int(sys.argv[2], 16)
mx = int(sys.argv[3]) if len(sys.argv) > 3 else 10**9
funcs = M.load_functions()
c = json.load(open(os.path.join(M.ROOT, 'build', 'progress_cache.json')))
done = {n for v in c.values() for n, s in (v['res'] or []) if s == 1.0}
for d in ('auto', 'hand', 'splicewrap', 'lib'):
    for f in glob.glob(os.path.join(M.ROOT, 'src', d, '*.c*')):
        done.add(os.path.basename(f).rsplit('.', 1)[0])
daddr = {funcs[n][0] for n in done if n in funcs}
seen = set(); out = []
for n, (a, s) in funcs.items():
    if not (lo <= a < hi) or a in daddr or a in seen: continue
    if not (M.TEXT_VA <= a < M.TEXT_VA + M.TEXT_SIZE): continue
    w = M.target_words(a, s)
    if all(x == 0 for x in w) or s // 4 > mx: continue
    seen.add(a)
    # prefer a real name over func_XXXXXXXX when both exist
    alts = [m for m, (b, _) in funcs.items() if b == a]
    nm = sorted(alts, key=lambda x: x.startswith('func_'))[0]
    out.append((s // 4, a, nm))
for k, a, n in sorted(out): print(n, f'0x{a:06X}', k)
