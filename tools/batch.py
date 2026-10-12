#!/usr/bin/env python3
"""batch.py START END [maxinstr]: unmatched functions in [START,END) with compact asm + best draft."""
import os, sys, csv, json, re
sys.path.insert(0, os.path.dirname(__file__))
import matchtool as M
lo, hi = int(sys.argv[1], 16), int(sys.argv[2], 16)
maxi = int(sys.argv[3]) if len(sys.argv) > 3 else 120
_cp = os.path.join(M.ROOT, 'build', 'progress_cache.json')
if not os.path.exists(_cp): _cp = os.path.join(M.ROOT, 'build', 'progress_cache_preasfix.json')
cache = json.load(open(_cp))
matched = {n for v in cache.values() for n, s in (v['res'] or []) if s == 1.0}
funcs = M.load_functions()
maddr = {funcs[n][0] for n in matched if n in funcs}
seen_a = set()
for n, (a, s) in sorted(funcs.items(), key=lambda x: x[1][0]):
    if not (lo <= a < hi) or a in maddr or a in seen_a: continue
    seen_a.add(a)
    w = M.target_words(a, s)
    if all(x == 0 for x in w) or s // 4 > maxi: 
        if s // 4 > maxi: print(f'##### {n} @{a:06X} ({s//4} instr) -- skipped (large)')
        continue
    print(f'##### {n} @{a:06X} ({s//4} instr)')
    print(' ; '.join(re.sub(r'\s+', ' ', M.disasm(x, a + 4 * i)) for i, x in enumerate(w)))
    for d in ('automatch2', 'automatch'):
        p = os.path.join(M.ROOT, 'build', d, n + '.c')
        if os.path.exists(p):
            t = open(p).read().replace('#include "m2c_prelude.h"\n', '')
            body = t[t.find(n + '('):] if (n + '(') in t else t
            # find the line start of the definition
            i = t.rfind('\n', 0, t.find(n + '(')) + 1
            print('--- draft (' + d + '):'); print(t[i:].strip()); break
