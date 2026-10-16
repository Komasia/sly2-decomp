#!/usr/bin/env python3
"""rank_drafts.py [LO HI]: compile every draft in build/hand_wip/ for an unmatched function and write
build/hand_wip/RANKING.csv (name,addr,diffs,total,file) sorted by diffs - the best version of each function."""
import sys, os, re, csv, glob, subprocess
sys.path.insert(0, os.path.dirname(__file__))
import matchtool as M
lo, hi = (int(sys.argv[1], 16), int(sys.argv[2], 16)) if len(sys.argv) > 2 else (0, 1 << 32)
funcs = M.load_functions()
done = {r['name'] for r in csv.DictReader(open(os.path.join(M.ROOT, 'config', 'matched.csv'))) if r['status'] == 'match'}
best = {}
for f in sorted(glob.glob(os.path.join(M.ROOT, 'build', 'hand_wip', '*.c*'))):
    name = re.split(r'[._]v\d|\.(?=[^.]*$)|\.la|\.ee29', os.path.basename(f))[0]
    if name not in funcs or name in done: continue
    a, s = funcs[name]
    if not (lo <= a < hi): continue
    try:
        out = subprocess.run([sys.executable, os.path.join(M.ROOT, 'tools', 'matchtool.py'), 'check', f, name],
                             capture_output=True, text=True, timeout=180).stdout
    except subprocess.TimeoutExpired:
        continue
    m = re.search(r'(\d+)/(\d+) instructions differ', out)
    d, t = (int(m.group(1)), int(m.group(2))) if m else ((0, s // 4) if ': MATCH' in out else (None, None))
    if d is None: continue
    if name not in best or d < best[name][2]:
        best[name] = (name, f'0x{a:06X}', d, t, os.path.relpath(f, M.ROOT))
rows = sorted(best.values(), key=lambda r: (r[2], r[1]))
with open(os.path.join(M.ROOT, 'build', 'hand_wip', 'RANKING.csv'), 'w', newline='') as fo:
    w = csv.writer(fo); w.writerow(['name', 'addr', 'diffs', 'total', 'file']); w.writerows(rows)
print(len(rows), 'drafts ranked;', sum(1 for r in rows if r[2] <= 5), 'within 5 diffs,', sum(1 for r in rows if r[2] <= 15), 'within 15')
