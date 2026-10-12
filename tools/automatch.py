#!/usr/bin/env python3
"""Bulk pass: for each function, m2c --valid-syntax -> ee-gcc -> compare with the original.
Results: build/automatch/results.csv (name, addr, n_instr, status, score) and
         build/automatch/<name>.c for every attempt; matches copied to src/auto/<name>.c

usage: automatch.py [--jobs N] [--only NAME ...] [--min-instr N] [--max-instr N]
"""
import os, re, sys, csv, subprocess, tempfile, argparse, shutil, signal
from concurrent.futures import ThreadPoolExecutor
sys.path.insert(0, os.path.dirname(__file__))
import matchtool as M

M2C = os.environ.get('M2C', '/home/claude/m2c/m2c.py')
ASM = os.path.join(M.ROOT, 'asm', 'text.s')
OUT = os.path.join(M.ROOT, 'build', os.environ.get('AM_OUT', 'automatch'))
CTX = os.environ.get('AM_CONTEXT')

def split_asm():
    src = open(ASM).read()
    body = src.split('\n.align 3\n', 1)[1]
    parts = re.split(r'\n(?=\.align 3\n)', '.align 3\n' + body)
    out = {}
    for p in parts:
        m = re.search(r'^glabel (\S+)', p, re.M)
        if m: out[m.group(1)] = p
    return out

def run(cmd, timeout, **kw):
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True, start_new_session=True, **kw)
    try:
        out, err = p.communicate(timeout=timeout)
        return p.returncode, out, err
    except subprocess.TimeoutExpired:
        os.killpg(p.pid, signal.SIGKILL); p.communicate()
        return -999, '', 'timeout'

HEADER = '.set noat\n.set noreorder\n.section .text\n'

def attempt(args):
    name, asm, addr, size = args
    d = os.path.join(OUT, 'tmp', name); os.makedirs(d, exist_ok=True)
    sf = os.path.join(d, 'f.s'); open(sf, 'w').write(HEADER + asm)
    rc, c, _ = run([sys.executable, M2C, '-t', 'mipsee-gcc-c', '--valid-syntax', '--globals=used'] + (['--context', CTX] if CTX else []) + [sf], 60)
    if rc == -999 or (rc != 0 and 'Decompilation failure' in c) or not c.strip():
        return name, addr, size // 4, 'm2c_fail', 0.0
    cf = os.path.join(OUT, name + '.c')
    if CTX:
        import fix_sp
        from c_rewrites import voidify
        r = fix_sp.rewrite(c)
        if r: c = r
        c = voidify(c)
    open(cf, 'w').write('#include "m2c_prelude.h"\n' + c)
    obj = os.path.join(d, 'f.o')
    cmd = [M.WIBO, M.CC, '-c'] + M.INCLUDES + ['-I/home/claude/m2c'] + ['-x', 'c', '-O2', '-G0', '-ffast-math', '-mvu0-use-vf0-vf31', '-B' + os.path.join(M.ROOT, 'tools/compilers/bundle/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3') + '/', cf, '-o', obj]
    rc, _, err = run(cmd, 30, cwd=M.ROOT)
    if rc == -999 or not os.path.exists(obj):
        open(cf + '.err', 'w').write(err)
        return name, addr, size // 4, 'cc_fail', 0.0
    fns = M.obj_functions(obj)
    if name not in fns:
        return name, addr, size // 4, 'no_symbol', 0.0
    score, res = M.compare(name, *fns[name], verbose=False)
    shutil.rmtree(d, ignore_errors=True)
    return name, addr, size // 4, 'match' if score == 1.0 else 'diff', score

def safe_attempt(t):
    try:
        return attempt(t)
    except Exception as e:
        return t[0], t[2], t[3] // 4, 'error', 0.0

MATCHED = set()
def load_matched():
    import json
    p = os.path.join(M.ROOT, 'build', 'progress_cache.json')
    if os.path.exists(p):
        for v in json.load(open(p)).values():
            for n, sc in (v['res'] or []):
                if sc == 1.0: MATCHED.add(n)

def main():
    load_matched()
    ap = argparse.ArgumentParser(); ap.add_argument('--jobs', type=int, default=2)
    ap.add_argument('--only', nargs='*'); ap.add_argument('--min-instr', type=int, default=0); ap.add_argument('--max-instr', type=int, default=10**9)
    a = ap.parse_args()
    os.makedirs(OUT, exist_ok=True); os.makedirs(os.path.join(M.ROOT, 'src', 'auto'), exist_ok=True)
    funcs = M.load_functions(); asm = split_asm()
    todo = []
    for n, s in asm.items():
        if n not in funcs: continue
        addr, size = funcs[n]
        if a.only and n not in a.only: continue
        if os.environ.get('AM_SKIP_MATCHED') and n in MATCHED: continue
        if not (a.min_instr <= size // 4 <= a.max_instr): continue
        todo.append((n, s, addr, size))
    res_path = os.path.join(OUT, 'results.csv')
    done = {}
    if os.path.exists(res_path) and not a.only:
        for r in csv.DictReader(open(res_path)): done[r['name']] = r
    todo = [t for t in todo if t[0] not in done]
    print(f'{len(todo)} functions to try ({len(done)} already done)', flush=True)
    new = open(res_path, 'a', newline=''); w = csv.writer(new)
    if not done: w.writerow(['name', 'addr', 'n_instr', 'status', 'score'])
    n = 0
    with ThreadPoolExecutor(a.jobs) as ex:
        for name, addr, ni, st, sc in ex.map(safe_attempt, todo):
            w.writerow([name, f'0x{addr:06X}', ni, st, f'{sc:.4f}']); new.flush(); n += 1
            if st == 'match':
                shutil.copy(os.path.join(OUT, name + '.c'), os.path.join(M.ROOT, 'src', 'auto', name + '.c'))
            if n % 200 == 0: print(f'{n}/{len(todo)}', flush=True)
    new.close()

if __name__ == '__main__':
    main()
