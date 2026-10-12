#!/usr/bin/env python3
"""SDK-library assembly path ('// SLY2_ASM: gnu-reorder').

Sony's SDK objects were produced by a gcc 2.9x code generator run without delay-slot filling, then assembled
by a GNU as in reorder mode, which fills each branch/jump delay slot with the preceding independent instruction.
That assembler did NOT fill the slot of a backward branch (loop branch) - those keep a nop.
This module rewrites a reorder-mode .s so loop branches are emitted in noreorder with an explicit nop, then
assembles with the GNU as from ee-gcc 2.96 (tools/compilers/ee-gcc2.96)."""
import re, os, subprocess, sys

BRANCH = re.compile(r'^\s+(b|beq|bne|beqz|bnez|blez|bgtz|bltz|bgez|beql|bnel|beqzl|bnezl|blezl|bgtzl|bltzl|bgezl|bc1t|bc1f|bc1tl|bc1fl)\s+(.*),?\s*(\$L\d+|\.L\w+|[A-Za-z_]\w*)\s*$')

def pin_loop_branches(text):
    lines = text.split('\n')
    labels = {}
    for i, l in enumerate(lines):
        m = re.match(r'^(\$L\d+|\.L\w+):', l)
        if m: labels[m.group(1)] = i
    out = []
    for i, l in enumerate(lines):
        m = re.match(r'^\s+(\w+)\s+(.*)$', l)
        if m and m.group(1).startswith('b') and m.group(1) not in ('break',):
            target = m.group(2).split(',')[-1].strip()
            if target in labels and labels[target] < i:     # backward branch = loop branch
                # a label right before the branch stops GNU as moving the previous insn into its slot
                out += ['$Lgr_pin%d:' % i, l]
                continue
        out.append(l)
    return '\n'.join(out)

def assemble(s_path, obj, root):
    g = os.path.join(root, 'tools', 'compilers', 'ee-gcc2.96')
    txt = pin_loop_branches(open(s_path).read())
    s2 = s_path + '.gr.s'
    open(s2, 'w').write(txt)
    p = subprocess.run([os.path.join(g, 'ee', 'bin', 'as'), '-G0', '-EL', '-mabi=eabi', '-o', obj, s2],
                       capture_output=True, text=True)
    if p.returncode:
        sys.stderr.write(p.stderr)
    return p.returncode
