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
    noreorder = False
    for i, l in enumerate(lines):
        st = l.strip()
        if st == '.set\tnoreorder' or st == '.set noreorder': noreorder = True
        elif st == '.set\treorder' or st == '.set reorder': noreorder = False
        m = re.match(r'^\s+(\w+)\s+(.*)$', l)
        if m and not noreorder and m.group(1).startswith('b') and m.group(1) not in ('break',):
            target = m.group(2).split(',')[-1].strip()
            if target in labels and labels[target] < i:     # backward branch = loop branch
                # a label right before the branch stops GNU as moving the previous insn into its slot
                out += ['$Lgr_pin%d:' % i, l]
                continue
        out.append(l)
    return '\n'.join(out)

def unfill_short_loops(text, loopmax=5):
    """gcc reorg filled every slot; Sony's toolchain left the slot of a short single-block loop empty (nop).
    Move the slot instruction of such loop branches back in front of the branch (agents' gnu-reorg model)."""
    L = text.split('\n'); labels = {}
    for i, l in enumerate(L):
        m = re.match(r'^(\$L\d+):', l)
        if m: labels[m.group(1)] = i
    out = []; i = 0
    def isloop(a, b):
        for q in range(a, b):
            if re.match(r'^\s+(j\w*|b\w*)\s', L[q]) and not re.match(r'^\s+(jal|break)\s', L[q]): return False
        n = sum(1 for q in range(a, b) if re.match(r'^\s+[a-z]', L[q]) and not L[q].strip().startswith('.'))
        return n <= loopmax
    while i < len(L):
        l = L[i]
        if l.strip() == '.set\tnoreorder' and i + 5 < len(L) and L[i+1].strip() == '.set\tnomacro':
            br = L[i+2]; slot = L[i+3]
            m = re.match(r'^\s+(b\w*)\s+(.*)$', br)
            if m and not m.group(1).endswith('l') and L[i+4].strip() == '.set\tmacro' and L[i+5].strip() == '.set\treorder':
                tgt = m.group(2).split(',')[-1].strip()
                sm = re.match(r'^\s+\w+\s+(\$\w+)', slot)
                regs = set(re.findall(r'\$\w+', m.group(2)))
                wr_br = sm and sm.group(1) in regs
                if tgt in labels and labels[tgt] < i and isloop(labels[tgt], i) and not wr_br:
                    if slot.strip() != 'nop':
                        k = len(out) - 1
                        while k >= 0 and (out[k].strip() == '' or out[k].strip().startswith('#')): k -= 1
                        pm = re.match(r'^\s+\w+\s+(\$\w+)', out[k]) if k >= 0 else None
                        if pm and pm.group(1) in regs: out.insert(k, slot)
                        else: out.append(slot)
                    out.append(br); i += 6; continue
        out.append(l); i += 1
    return '\n'.join(out)

def assemble(s_path, obj, root, mode='gnu-reorder'):
    g = os.path.join(root, 'tools', 'compilers', 'ee-gcc2.96')
    txt = open(s_path).read()
    if mode == 'gnu-reorg':
        txt = unfill_short_loops(txt)
    txt = pin_loop_branches(txt)
    s2 = s_path + '.gr.s'
    open(s2, 'w').write(txt)
    p = subprocess.run([os.path.join(g, 'ee', 'bin', 'as'), '-G0', '-EL', '-mabi=eabi', '-o', obj, s2],
                       capture_output=True, text=True)
    if p.returncode:
        sys.stderr.write(p.stderr)
    return p.returncode
