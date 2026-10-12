#!/usr/bin/env python3
"""qdiff.py NAME [file.c]: compile a C draft (default build/automatch/NAME.best.c or NAME.c) and print only diff lines with 1 line of context."""
import os, sys, subprocess, tempfile
sys.path.insert(0, os.path.dirname(__file__))
import matchtool as M, quickfix as Q
name = sys.argv[1]
f = sys.argv[2] if len(sys.argv) > 2 else next(p for p in [f'build/automatch/{name}.best.c', f'build/automatch/{name}.c'] if os.path.exists(os.path.join(M.ROOT, p)))
src = os.path.join(M.ROOT, f) if not os.path.isabs(f) else f
t = tempfile.mkdtemp(); of = os.path.join(t, 'f.o')
cmd = [M.WIBO, M.CC, '-c'] + M.INCLUDES + ['-I/home/claude/m2c'] + Q.FLAGS + ([] if src.endswith('.c') else []) + [src, '-o', of]
if src.endswith('.cpp'): cmd = [M.WIBO, M.CC, '-c'] + M.INCLUDES + M.CFLAGS + [src, '-o', of]
p = subprocess.run(cmd, capture_output=True, text=True, cwd=M.ROOT)
if not os.path.exists(of): print(p.stderr[-1500:]); sys.exit(1)
fns = M.obj_functions(of)
score, (hdr, lines) = M.compare(name, *fns[name])
print(hdr)
show = set()
for i, l in enumerate(lines):
    if l.startswith('!!'): show.update({i - 1, i, i + 1})
for i in sorted(show):
    if 0 <= i < len(lines): print(lines[i][:118])
