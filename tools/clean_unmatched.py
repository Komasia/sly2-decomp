#!/usr/bin/env python3
"""Move source files in src/hand and src/lib (recursively) that contain no exactly-matching function
into build/hand_wip/. Run after tools/progress.py (uses config/matched.csv)."""
import csv, os, shutil
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)
rows = list(csv.DictReader(open('config/matched.csv')))
good = set(r['source'] for r in rows if r['status'] == 'match')
moved = []
for top in ('src/hand', 'src/lib'):
    for dp, dn, fn in os.walk(top):
        for f in fn:
            if not f.endswith(('.c', '.cpp')): continue
            p = os.path.join(dp, f)
            if p in good: continue
            dst = os.path.join('build/hand_wip', f)
            while os.path.exists(dst): dst += '.dup'
            shutil.move(p, dst); moved.append(p)
print('moved non-matching to wip:', len(moved), moved)
