#!/usr/bin/env python3
"""Run quickfix over all near-miss drafts (best score first); log to build/quickfix.csv. Resumable."""
import csv, os, subprocess, sys
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
res = os.path.join(ROOT, 'build', 'quickfix_' + os.environ.get('QF_DRAFTS', 'automatch') + '.csv')
done = set()
if os.path.exists(res):
    done = {r['name'] for r in csv.DictReader(open(res))}
DRAFTS = os.environ.get('QF_DRAFTS', 'automatch')
rows = [r for r in csv.DictReader(open(os.path.join(ROOT, 'build', DRAFTS, 'results.csv'))) if r['status'] == 'diff']
rows.sort(key=lambda r: -float(r['score']))
min_score = float(sys.argv[1]) if len(sys.argv) > 1 else 0.5
f = open(res, 'a', newline=''); w = csv.writer(f)
if not done: w.writerow(['name', 'start_score', 'result'])
for r in rows:
    if r['name'] in done or float(r['score']) < min_score: continue
    if os.path.exists(os.path.join(ROOT, 'src', 'auto', r['name'] + '.c')): continue
    p = subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'quickfix.py'), r['name'], '--rounds', '4', '--src', os.path.join(ROOT, 'build', DRAFTS, r['name'] + '.c')], capture_output=True, text=True, timeout=3600)
    last = (p.stdout.strip().split('\n') or [''])[-1]
    w.writerow([r['name'], r['score'], last]); f.flush()
