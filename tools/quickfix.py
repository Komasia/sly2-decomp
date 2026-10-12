#!/usr/bin/env python3
"""Greedy fixer for near-miss C drafts (m2c output that compiles but differs slightly).

Transforms tried on each round (each a single local edit):
  * swap the operands of one comparison:  (A < B) -> (B > A)
  * swap two adjacent simple statements at the same indent
  * negate an if/else:  if (C) {X} else {Y}  ->  if (!(C)) {Y} else {X}   (single-level, brace style of m2c)
Keeps any edit that lowers the number of differing instructions; stops at a match or no improvement.

usage: quickfix.py NAME [--src FILE] [--rounds N]     (default src: build/automatch/NAME.c)
On success writes src/auto/NAME.c
"""
import os, sys, re, subprocess, tempfile, argparse, shutil, signal
sys.path.insert(0, os.path.dirname(__file__))
import matchtool as M
from c_rewrites import voidify, inline_ctor, inline_ctor_return

B = os.path.join(M.ROOT, 'tools/compilers/bundle/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3')
FLAGS = ['-x', 'c', '-O2', '-G0', '-ffast-math', '-mvu0-use-vf0-vf31', '-B' + B + '/']

def score_src(name, src):
    t = tempfile.mkdtemp(); cf = os.path.join(t, 'f.c'); of = os.path.join(t, 'f.o')
    open(cf, 'w').write(src)
    cmd = [M.WIBO, M.CC, '-c'] + M.INCLUDES + ['-I/home/claude/m2c'] + FLAGS + [cf, '-o', of]
    p = subprocess.Popen(cmd, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, cwd=M.ROOT, start_new_session=True)
    try:
        p.wait(timeout=30)
    except subprocess.TimeoutExpired:
        os.killpg(p.pid, signal.SIGKILL); p.wait()
    if not os.path.exists(of):
        shutil.rmtree(t, ignore_errors=True); return None
    fns = M.obj_functions(of); shutil.rmtree(t, ignore_errors=True)
    if name not in fns: return None
    w, r = fns[name]
    a, s = M.load_functions()[name]
    tgt = M.target_words(a, s)
    while len(tgt) > len(w) and tgt[-1] == 0: tgt.pop()
    n = max(len(tgt), len(w)); bad = 0
    for i in range(n):
        x = tgt[i] if i < len(tgt) else None; y = w[i] if i < len(w) else None
        rr = r.get(i)
        if x is None or y is None or (M.mask(x, rr) != M.mask(y, rr) if rr is not None else x != y): bad += 1
    return bad

FLIP = {'<': '>', '>': '<', '<=': '>=', '>=': '<=', '==': '==', '!=': '!='}
CMP = re.compile(r'(<=|>=|==|!=|(?<![<>\-])<(?![<=])|(?<![<>\-])>(?![>=]))')

def matching_paren(s, i, step):
    depth = 0; j = i
    open_c, close_c = ('(', ')') if step > 0 else (')', '(')
    while 0 <= j < len(s):
        if s[j] == open_c: depth += 1
        elif s[j] == close_c:
            depth -= 1
            if depth == 0: return j
        j += step
    return None

def comparison_swaps(src):
    out = []
    for m in CMP.finditer(src):
        i = m.start()
        # find enclosing parens
        depth = 0; L = i - 1
        while L >= 0:
            if src[L] == ')': depth += 1
            elif src[L] == '(':
                if depth == 0: break
                depth -= 1
            elif src[L] in ';{}' and depth == 0: L = -1; break
            L -= 1
        if L < 0: continue
        R = matching_paren(src, L, 1)
        if R is None: continue
        inner = src[L + 1:R]
        rel = i - (L + 1)
        a, op, b = inner[:rel].strip(), m.group(0), inner[rel + len(m.group(0)):].strip()
        if re.search(r'&&|\|\||\?|=(?!=)', a.replace('==', '').replace('<=', '').replace('>=', '').replace('!=', '')) or \
           re.search(r'&&|\|\||\?', b): continue
        out.append(src[:L + 1] + f'{b} {FLIP[op]} {a}' + src[R:])
    return out

STMT = re.compile(r'^(\s+)([^\s{}][^{}]*;)\s*$')
def statement_swaps(src):
    lines = src.split('\n'); out = []
    for i in range(len(lines) - 1):
        a, b = STMT.match(lines[i]), STMT.match(lines[i + 1])
        if not a or not b or a.group(1) != b.group(1): continue
        if any(re.match(r'(return|goto|break|continue|case|default)\b', x.group(2)) for x in (a, b)): continue
        if re.match(r'^[A-Za-z_][\w\s\*]*\s\**\w+(\[\w*\])?;$', a.group(2)) or re.match(r'^[A-Za-z_][\w\s\*]*\s\**\w+(\[\w*\])?;$', b.group(2)):
            continue  # declarations
        l2 = lines[:]; l2[i], l2[i + 1] = l2[i + 1], l2[i]
        out.append('\n'.join(l2))
    return out

IFELSE = re.compile(r'(\n(\s*))if \((.*)\) \{\n((?:\2    .*\n|\n)*?)\2\} else \{\n((?:\2    .*\n|\n)*?)\2\}\n')
def ifelse_flips(src):
    out = []
    for m in IFELSE.finditer(src):
        ind, cond, x, y = m.group(2), m.group(3), m.group(4), m.group(5)
        new = f'{m.group(1)}if (!({cond})) {{\n{y}{ind}}} else {{\n{x}{ind}}}\n'
        out.append(src[:m.start()] + new + src[m.end():])
    return out

COMM = re.compile(r'(?<![\w\]\)])(\(?)([A-Za-z_][\w.>-]*|\d+|0x[0-9A-Fa-f]+) ([+*&|^]) ([A-Za-z_][\w.>-]*|\d+|0x[0-9A-Fa-f]+)(?![\w(\[])')
def commutative_swaps(src):
    out = []
    for m in COMM.finditer(src):
        a, op, b = m.group(2), m.group(3), m.group(4)
        if a == b: continue
        out.append(src[:m.start()] + m.group(1) + f'{b} {op} {a}' + src[m.end():])
    return out[:40]

def voidptr_locals(src):
    """m2c sometimes types a temp as T* and then adds byte offsets to it; make such temps void*."""
    out = []
    for m in re.finditer(r'^(\s+)((?:s|u)(?:8|16|32|64)|f32|M2C_UNK(?:8|16|32|64)?) \*(temp_\w+|var_\w+);\s*$', src, re.M):
        v = m.group(3)
        if re.search(r'\b%s \+ ' % v, src) or re.search(r'\b%s - ' % v, src):
            out.append(src[:m.start()] + f'{m.group(1)}void *{v};' + src[m.end():])
    if len(out) > 1:
        allv = src
        for m in re.finditer(r'^(\s+)((?:s|u)(?:8|16|32|64)|f32|M2C_UNK(?:8|16|32|64)?) \*(temp_\w+|var_\w+);\s*$', src, re.M):
            allv = allv.replace(m.group(0), f'{m.group(1)}void *{m.group(3)};')
        out.append(allv)
    return out

def main():
    ap = argparse.ArgumentParser(); ap.add_argument('name'); ap.add_argument('--src'); ap.add_argument('--rounds', type=int, default=6)
    a = ap.parse_args()
    src = open(a.src or os.path.join(M.ROOT, 'build', 'automatch', a.name + '.c')).read()
    best = score_src(a.name, src)
    if best is None: print(a.name, 'does not compile'); return 1
    print(a.name, 'start', best, flush=True)
    for rnd in range(a.rounds):
        if best == 0: break
        improved = False
        v = voidify(src)
        extra = [v] if v != src else []
        ic = inline_ctor_return(src)
        if ic != src: extra.append(ic)
        if ic != src and voidify(ic) != ic: extra.append(voidify(ic))
        for cand in extra + voidptr_locals(src) + comparison_swaps(src) + commutative_swaps(src) + statement_swaps(src) + ifelse_flips(src):
            sc = score_src(a.name, cand)
            if sc is not None and sc < best:
                best, src, improved = sc, cand, True
                print(a.name, 'round', rnd, '->', best, flush=True)
                if best == 0: break
        if not improved: break
    if best == 0:
        os.makedirs(os.path.join(M.ROOT, 'src', 'auto'), exist_ok=True)
        open(os.path.join(M.ROOT, 'src', 'auto', a.name + '.c'), 'w').write(src)
        print(a.name, 'MATCH'); return 0
    open(os.path.join(M.ROOT, 'build', 'automatch', a.name + '.best.c'), 'w').write(src)
    print(a.name, 'best', best); return 2

if __name__ == '__main__':
    sys.exit(main())
