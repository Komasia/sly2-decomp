#!/usr/bin/env python3
"""Second automatic pass: m2c with inferred-signature context (build/context.h), batched 50 functions
per m2c run, then per-function: fix stack slots, voidify, compile, compare. Skips matched functions.
Results: build/automatch2/results.csv ; matches -> src/auto/NAME.c"""
import os, re, sys, csv, json, subprocess, shutil, signal
from concurrent.futures import ThreadPoolExecutor
sys.path.insert(0, os.path.dirname(__file__))
import matchtool as M
import automatch as A
import quickfix as Q
import fix_sp
from c_rewrites import voidify

OUT = os.path.join(M.ROOT, 'build', os.environ.get('AM_DIR', 'automatch2'))
CTX = os.path.join(M.ROOT, 'build', 'context.h')

def matched_names():
    p = os.path.join(M.ROOT, 'build', 'progress_cache.json')
    s = set()
    if os.path.exists(p):
        for v in json.load(open(p)).values():
            for n, sc in (v['res'] or []):
                if sc == 1.0: s.add(n)
    for d in ('auto', 'splicewrap'):
        for f in os.listdir(os.path.join(M.ROOT, 'src', d)):
            s.add(f[:-2])
    return s

def split_output(c, names):
    """m2c prints, per function: decls + function. With multiple functions the decls for all are
    printed first (globals=used) followed by each function. Return {name: decls + function}."""
    out = {}
    # function bodies: start at a line '<type> NAME(...) {' and end at the matching closing '}' at col 0
    starts = []
    for n in names:
        m = re.search(r'^[^\n;{}]*\b%s\([^;{]*\) \{\n' % re.escape(n), c, re.M)
        if m: starts.append((m.start(), n))
    starts.sort()
    if not starts: return out
    head = c[:starts[0][0]]
    for i, (pos, n) in enumerate(starts):
        end = c.find('\n}\n', pos)
        body = c[pos:end + 3] if end >= 0 else c[pos:]
        out[n] = head + body
    return out

def one(args):
    n, c, addr, size = args
    r = fix_sp.rewrite(c)
    if r: c = r
    c = voidify(c)
    src = '#include "m2c_prelude.h"\n' + c
    open(os.path.join(OUT, n + '.c'), 'w').write(src)
    sc = Q.score_src(n, src)
    if sc is None: return n, addr, size // 4, 'cc_fail', 0.0
    if sc == 0:
        shutil.copy(os.path.join(OUT, n + '.c'), os.path.join(M.ROOT, 'src', 'auto', n + '.c'))
        return n, addr, size // 4, 'match', 1.0
    return n, addr, size // 4, 'diff', 1 - sc / max(1, size // 4)

def main():
    os.makedirs(OUT, exist_ok=True)
    funcs = M.load_functions(); asm = A.split_asm(); done_m = matched_names()
    res_path = os.path.join(OUT, 'results.csv')
    done = set()
    if os.path.exists(res_path):
        done = {r['name'] for r in csv.DictReader(open(res_path))}
    todo = [n for n in asm if n in funcs and n not in done_m and n not in done and funcs[n][1] >= 8]
    print(len(todo), 'to try', flush=True)
    f = open(res_path, 'a', newline=''); w = csv.writer(f)
    if not done: w.writerow(['name', 'addr', 'n_instr', 'status', 'score'])
    for i in range(0, len(todo), 50):
        chunk = todo[i:i + 50]
        sf = os.path.join(OUT, 'chunk.s')
        open(sf, 'w').write(A.HEADER + '\n'.join(asm[n] for n in chunk))
        rc, c, _ = A.run([sys.executable, A.M2C, '-t', 'mipsee-gcc-c', '--valid-syntax', '--globals=used', '--context', CTX, sf], 600)
        per = split_output(c, chunk)
        jobs = [(n, per[n], funcs[n][0], funcs[n][1]) for n in chunk if n in per]
        for n in chunk:
            if n not in per: w.writerow([n, f'0x{funcs[n][0]:06X}', funcs[n][1] // 4, 'm2c_fail', 0])
        with ThreadPoolExecutor(int(os.environ.get('JOBS', '1'))) as ex:
            for row in ex.map(one, jobs):
                w.writerow([row[0], f'0x{row[1]:06X}', row[2], row[3], f'{row[4]:.4f}'])
        f.flush()
        print(i + len(chunk), '/', len(todo), flush=True)

if __name__ == '__main__':
    main()
