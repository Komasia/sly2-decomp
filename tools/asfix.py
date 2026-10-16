#!/usr/bin/env python3
"""Reproduce Sly 2's R5900 short-loop padding in compiler output before assembling.

Sly 2's assembler pads every short backward loop (a conditional branch back to a label with no other
branch/jump in between) with nops placed right before the branch, until the loop is 6 instructions long
including the delay slot.  Our GNU as 2.9-ee-991111b pads differently (one nop more, and sometimes
pads 6-instruction loops to 7).  This filter inserts the nops itself and emits such branches as `.word`
so the assembler cannot add its own padding.

usage: asfix.py IN.s OUT.s
"""
import re, sys

LOOP_LEN = 6            # instructions including the delay slot

COND = {  # mnemonic: (kind, opcode or rt field)
    'beq': ('rs_rt', 4), 'bne': ('rs_rt', 5), 'beql': ('rs_rt', 20), 'bnel': ('rs_rt', 21),
    'blez': ('rs', 6), 'bgtz': ('rs', 7), 'blezl': ('rs', 22), 'bgtzl': ('rs', 23),
    'bltz': ('regimm', 0), 'bgez': ('regimm', 1), 'bltzl': ('regimm', 2), 'bgezl': ('regimm', 3),
    'beqz': ('z', 4), 'bnez': ('z', 5), 'beqzl': ('z', 20), 'bnezl': ('z', 21),
    'b': ('uncond', 4),
    'bc1f': ('cop1', 0), 'bc1t': ('cop1', 1), 'bc1fl': ('cop1', 2), 'bc1tl': ('cop1', 3),
}
JUMPY = re.compile(r'^(b\w*|j|jal|jr|jalr|bc\d\w*|syscall|break|eret)$')
REGNAMES = {'zero': 0, 'at': 1, 'v0': 2, 'v1': 3, 'a0': 4, 'a1': 5, 'a2': 6, 'a3': 7, 't0': 8, 't1': 9,
            't2': 10, 't3': 11, 't4': 12, 't5': 13, 't6': 14, 't7': 15, 's0': 16, 's1': 17, 's2': 18,
            's3': 19, 's4': 20, 's5': 21, 's6': 22, 's7': 23, 't8': 24, 't9': 25, 'k0': 26, 'k1': 27,
            'gp': 28, 'sp': 29, 'fp': 30, 's8': 30, 'ra': 31}

def reg(s):
    s = s.strip().lstrip('$')
    return int(s) if s.isdigit() else REGNAMES[s]

def encode(mn, ops, off):
    kind, code = COND[mn]
    off &= 0xFFFF
    if kind == 'rs_rt': return (code << 26) | (reg(ops[0]) << 21) | (reg(ops[1]) << 16) | off
    if kind == 'z': return (code << 26) | (reg(ops[0]) << 21) | off
    if kind == 'rs': return (code << 26) | (reg(ops[0]) << 21) | off
    if kind == 'regimm': return (1 << 26) | (reg(ops[0]) << 21) | (code << 16) | off
    if kind == 'uncond': return (4 << 26) | off
    if kind == 'cop1': return (17 << 26) | (8 << 21) | (code << 16) | off
    raise ValueError(mn)

def strip(line):
    return line.split('#', 1)[0].strip()

def classify(line):
    """('label', name) | ('insn', mnemonic, operands) | ('dir', text) | ('blank',)"""
    s = strip(line)
    if not s: return ('blank',)
    m = re.match(r'^([$\w.]+):\s*(.*)$', s)
    if m:
        return ('label', m.group(1)) if not m.group(2) else ('label+', m.group(1), m.group(2))
    if s.startswith('.'): return ('dir', s)
    parts = s.split(None, 1)
    return ('insn', parts[0], parts[1] if len(parts) > 1 else '')

# macros that may expand to more than one instruction; refuse to count across them
MULTI = re.compile(r'^(la|dla|dli|ulw|usw|div|divu|rem|remu|mul|abs|bge|bgt|ble|blt|sne|seq|sge|sgt|sle|sgeu|sgtu|sleu|rol|ror)$')

def multi(mn, ops):
    if mn == 'li':
        try: v = int(ops.split(',')[1].strip(), 0)
        except Exception: return True
        return not (-0x8000 <= v < 0x10000 or ((v & 0xFFFF) == 0 and -0x80000000 <= v < 0x80000000))
    return bool(MULTI.match(mn))



def isize(mn, ops):
    """Number of machine instructions a (possibly macro) instruction expands to, for block-position counting."""
    import struct
    if mn == 'li.s':
        try:
            bits = struct.unpack('<I', struct.pack('<f', float(ops.split(',')[1])))[0]
        except Exception:
            return 3
        if bits == 0: return 1                 # mtc1 $0
        return 2 if (bits & 0xFFFF) == 0 else 3   # lui [+ori] + mtc1
    if mn == 'li':
        return 2 if multi(mn, ops) else 1
    if mn in ('la', 'dla'): return 2
    return 1

# --- R5900 divide hazard: Sly 2's assembler puts two nops before div.s/sqrt.s/rsqrt.s/vdiv/vsqrt/vrsqrt when the
# instruction starts a basic block (function entry, a label, or the instruction after a branch/jump + delay slot;
# calls don't count).  Verified against every instance in the game code of SCUS_973.16.
DIVOPS = re.compile(r'^(div\.s|sqrt\.s|rsqrt\.s|vdiv|vsqrt|vrsqrt)$')
BR = re.compile(r'^(b\w*|bc\d\w*|j|jr)$')

def divfix(text):
    """The hazard rule: a divide/sqrt must be at least the 3rd instruction of its basic block.  At position 0
    the original assembler inserts two nops, at position 1 one nop (verified: all 11 position-1 sites in
    text.s have the nop, none lack it)."""
    lines = text.split('\n')
    out = []
    st = False            # .set noreorder state
    pos = 0               # index of the next instruction within its basic block
    pending = 0           # instructions left before the block boundary after a noreorder branch
    for l in lines:
        c = classify(l)
        if c[0] == 'dir':
            if re.match(r'\.set\s+noreorder', c[1]): st = True
            elif re.match(r'\.set\s+reorder', c[1]): st = False
            elif re.match(r'\.ent\b', c[1]): pos = 0; pending = 0
            out.append(l); continue
        if c[0] == 'label':
            pos = 0; pending = 0; out.append(l); continue
        if c[0] == 'label+':
            pos = 0; pending = 0
            c = ('insn',) + tuple(c[2].split(None, 1)) + ('',) if len(c[2].split(None, 1)) == 1 else ('insn',) + tuple(c[2].split(None, 1))
        if c[0] != 'insn':
            out.append(l); continue
        mn = c[1]
        if pos < 2 and DIVOPS.match(mn):
            indent = re.match(r'^\s*', l).group(0) or '\t'
            out.extend([f'{indent}nop'] * (2 - pos))
            pos = 2
        out.append(l)
        if pending:                     # this was a delay-slot instruction: the next one starts a block
            pending = 0; pos = 0
        elif BR.match(mn):
            if st: pending = 1; pos += 1       # explicit delay slot follows
            else: pos = 0                      # assembler supplies the delay slot
        else:
            pos += isize(mn, c[2] if len(c) > 2 else '')
    return '\n'.join(out)

def fix(text):
    text = divfix(text)
    lines = text.split('\n')
    out = list(lines)
    labels = {}           # label -> index in lines
    noreorder = []        # per line: inside .set noreorder
    st = False
    for i, l in enumerate(lines):
        c = classify(l)
        if c[0] in ('label', 'label+'): labels[c[1]] = i
        if c[0] == 'dir' and re.match(r'\.set\s+noreorder', c[1]): st = True
        if c[0] == 'dir' and re.match(r'\.set\s+reorder', c[1]): st = False
        noreorder.append(st)
    changed = 0
    # work from the end so inserted lines don't shift indices we still need
    for i in range(len(lines) - 1, -1, -1):
        c = classify(lines[i])
        if c[0] != 'insn' or c[1] not in COND: continue
        ops = [o.strip() for o in c[2].split(',')]
        tgt = ops[-1]
        if tgt not in labels or labels[tgt] >= i: continue
        uncond = c[1] == 'b'
        selfloop = uncond and not noreorder[i] and labels[tgt] == i - 1 - sum(
            1 for j in range(labels[tgt] + 1, i) if classify(lines[j])[0] in ('blank', 'dir'))
        if uncond and not noreorder[i] and not selfloop: continue
        # count instructions between the label and the branch
        n = 0; ok = True
        for j in range(labels[tgt] + 1, i):
            k = classify(lines[j])
            if k[0] == 'insn':
                if multi(k[1], k[2]): ok = False; break
                if JUMPY.match(k[1]) and not noreorder[j]:
                    # a call/jump in reorder mode: the assembler fills its delay slot from the preceding
                    # instruction if it can.  Only handle the case where it can't (first instruction of the
                    # loop): then it is the jump plus a nop.
                    if n == 0 and JUMPY.match(k[1]) and k[1] not in ('syscall', 'break', 'eret'):
                        n += 2; continue
                    ok = False; break
                n += 1
            elif k[0] == 'dir' and re.match(r'\.(p2align|align)\s+2\s*$', k[1]):
                pass                                                          # instructions are already 4-aligned
            elif k[0] == 'dir' and re.match(r'\.(p2align|align|space|skip|word|byte|half)', k[1]):
                ok = False; break
            elif k[0] == 'label+':
                ok = False; break
        if not ok or n + 2 > LOOP_LEN: continue
        # unconditional branches are not padded (only conditional loops trigger the R5900 errata), but are
        # still emitted as .word so the assembler can't add its own padding
        pad = 0 if (uncond and not selfloop and not noreorder[i]) else LOOP_LEN - 2 - n   # unconditional loops in noreorder blocks and `L: b L` are padded too
        if not noreorder[i]:
            # reorder mode: the assembler would fill the delay slot itself.  Only safe when padding is
            # inserted (then nothing can be moved into the slot and it gets a nop).
            if pad == 0:
                # the assembler fills the slot with a nop only if the previous instruction can't be moved
                # into it: require that it writes a register the branch reads
                prev = None
                for j in range(i - 1, labels[tgt], -1):
                    k = classify(lines[j])
                    if k[0] == 'insn': prev = k; break
                if prev is None: continue
                dst = prev[2].split(',')[0].strip()
                if not dst.startswith('$') or dst not in [o for o in ops[:-1]]: continue
            off = -(n + pad + 1)
            word = encode(c[1], ops[:-1], off)
            indent = re.match(r'^\s*', lines[i]).group(0)
            out[i:i + 1] = [f'{indent}.set noreorder'] + [f'{indent}nop' for _ in range(pad)] + \
                [f'{indent}.word 0x{word:08X}  # {c[1]} {c[2]}', f'{indent}nop', f'{indent}.set reorder']
            changed += 1
            continue
        off = -(n + pad + 1)
        word = encode(c[1], ops[:-1], off)
        indent = re.match(r'^\s*', lines[i]).group(0)
        repl = [f'{indent}nop' for _ in range(pad)] + [f'{indent}.word 0x{word:08X}  # {c[1]} {c[2]}']
        out[i:i + 1] = repl
        changed += 1
    return '\n'.join(out), changed

def main():
    src = open(sys.argv[1]).read()
    res, n = fix(src)
    open(sys.argv[2], 'w').write(res)

if __name__ == '__main__':
    main()
