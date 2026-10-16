#!/usr/bin/env python3
"""undrafted.py LO HI: unmatched functions in [LO,HI) (hex) that have NO draft in build/hand_wip/ yet,
smallest first: NAME ADDR NINSTR.  Uses config/matched.csv (run progress.py to refresh it)."""
import sys, os, csv, glob, re
sys.path.insert(0, os.path.dirname(__file__))
import matchtool as M, progress as P
lo, hi = int(sys.argv[1], 16), int(sys.argv[2], 16)
real = P.real_functions(M.load_functions())
done = {int(r['addr'], 16) for r in csv.DictReader(open(os.path.join(M.ROOT, 'config', 'matched.csv'))) if r['status'] == 'match'}
srcs = {os.path.basename(f).rsplit('.', 1)[0] for f in glob.glob(os.path.join(M.ROOT, 'src', '*', '*.c*'))}
wip = {re.split(r'[._]v\d|\.', os.path.basename(f))[0] for f in glob.glob(os.path.join(M.ROOT, 'build', 'hand_wip', '*'))}
out = sorted((s // 4, a, n) for a, (n, s) in real.items()
             if lo <= a < hi and a not in done and n not in wip and n not in srcs)
for k, a, n in out: print(n, f'0x{a:06X}', k)
