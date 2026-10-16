#!/usr/bin/env python3
"""objdump stand-in for decomp-permuter (no MIPS binutils needed).  Usage (as permuter's objdump_command):
perm_objdump.py -drz FILE.  FILE is either a compiled .o (function named by $PERM_FUNC) or a text file
'TARGET:<name>' meaning the original game's bytes.  Relocated fields are masked on the compiled side (jal targets,
%hi/%lo); on the target side jal targets and lui of game-address range are masked the same way."""
import sys, os
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import matchtool as M
path = sys.argv[-1]
name = os.environ['PERM_FUNC']
data = open(path, 'rb').read()
if data.startswith(b'TARGET:') or os.path.basename(path) == 'target.o':
    a, s = M.load_functions()[name]
    words = M.target_words(a, s); va = a
    base = os.path.join(os.path.dirname(os.path.abspath(path)), 'base.o')
    brel = M.obj_functions(base).get(name, ([], {}))[1] if os.path.exists(base) else {}
    words = [M.mask(w, brel[i]) if i in brel else w for i, w in enumerate(words)]   # same fields as base.o's relocs
    out = []
    for w in words:
        op = w >> 26
        if op in (2, 3): w &= 0xFC000000                               # j/jal target
        elif op == 0x0F and 0x0010 <= (w & 0xFFFF) <= 0x0050: w &= 0xFFFF0000   # lui %hi(game address)
        out.append(w)
    words = out
else:
    fns = M.obj_functions(path)
    words, rel = fns.get(name, ([], {}))
    words = [M.mask(w, rel[i]) if i in rel else w for i, w in enumerate(words)]
    va = 0
print(f'{path}:     file format elf32-tradlittlemips\n')
print(f'Disassembly of section .text:\n\n00000000 <{name}>:')
for i, w in enumerate(words):
    d = M.disasm(w, va + 4 * i).strip()
    parts = d.split(None, 1)
    mn = parts[0] if parts else 'nop'
    args = parts[1].replace(' ', '') if len(parts) > 1 else ''
    print(f'{4*i:8x}:\t{w:08x} \t{mn}\t{args}')
