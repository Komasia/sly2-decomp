#!/usr/bin/env python3
"""Compile every Sly 1 decomp source file (INCLUDE_ASM stripped) and find Sly 2 functions that
are byte-identical (after relocation masking). Output: config/harvest_sly1.csv"""
import os, sys, glob, re, csv, subprocess, tempfile, struct
from concurrent.futures import ThreadPoolExecutor
sys.path.insert(0, os.path.dirname(__file__))
import matchtool as M

SLY1 = '/home/claude/sly1'
INC = ['-I' + SLY1 + '/include', '-I' + SLY1 + '/src/P2', '-isystem', SLY1 + '/include/sdk/ee', '-isystem', SLY1 + '/include/gcc']

def build(src):
    t = tempfile.mkdtemp()
    stripped = os.path.join(t, os.path.basename(src))
    txt = open(src, errors='ignore').read()
    txt = '\n'.join(l for l in txt.split('\n') if 'INCLUDE_ASM' not in l and 'INCLUDE_RODATA' not in l)
    open(stripped, 'w').write(txt)
    out = os.path.join(t, 'o.o')
    cmd = [M.WIBO, M.CC, '-c'] + INC + M.CFLAGS + [stripped, '-o', out]
    p = subprocess.run(cmd, capture_output=True, text=True, cwd=M.ROOT)
    if not os.path.exists(out):
        return src, None, p.stderr[-400:]
    return src, M.obj_functions(out), ''

def main():
    funcs = M.load_functions()
    elf = open(M.ELF, 'rb').read()
    by_len = {}
    tgt = {}
    for n, (a, s) in funcs.items():
        if not (M.TEXT_VA <= a < M.TEXT_VA + M.TEXT_SIZE): continue
        w = M.target_words(a, s)
        while w and w[-1] == 0: w.pop()
        tgt[a] = (n, w)
        by_len.setdefault(len(w), []).append(a)
    srcs = sorted(glob.glob(SLY1 + '/src/**/*.c', recursive=True) + glob.glob(SLY1 + '/src/**/*.cpp', recursive=True))
    rows = []; fails = []; total = 0
    with ThreadPoolExecutor(2) as ex:
        for src, fns, err in ex.map(build, srcs):
            if fns is None: fails.append((src, err)); continue
            for name, (words, rel) in fns.items():
                total += 1
                L = len(words)
                while L and words[L-1] == 0: L -= 1
                hits = []
                for a in by_len.get(L, []):
                    tw = tgt[a][1]
                    if all((M.mask(tw[i], rel[i]) == M.mask(words[i], rel[i])) if i in rel else tw[i] == words[i] for i in range(L)):
                        hits.append(a)
                if len(hits) >= 1 and L >= 2:
                    for a in hits:
                        rows.append((f'0x{a:06X}', tgt[a][0], name, os.path.relpath(src, SLY1), L, len(hits)))
    with open(os.path.join(M.ROOT, 'config', 'harvest_sly1.csv'), 'w', newline='') as f:
        w = csv.writer(f); w.writerow(['sly2_addr', 'sly2_name', 'sly1_symbol', 'sly1_source', 'n_instr', 'n_candidates']); w.writerows(rows)
    print(f'compiled functions: {total}, source files failed: {len(fails)}')
    for s, e in fails[:10]: print('FAIL', os.path.relpath(s, SLY1), e.strip().split('\n')[-1][:200])
    uniq = {r[0] for r in rows}
    print(f'sly2 functions with a byte-identical sly1 C body: {len(uniq)}  (unique-candidate: {len({r[0] for r in rows if r[5]==1})})')

if __name__ == '__main__':
    main()
