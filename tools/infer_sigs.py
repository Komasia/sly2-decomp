#!/usr/bin/env python3
"""Infer a C prototype for every function from the binary and write build/context.h for m2c --context.

  args   : integer arg regs (a0-a3, t0-t3) and float arg regs (f12-f19) read before written, in order
           (EABI assigns int and float registers independently, so ints-then-floats is register-exact)
  return : int if some caller reads $v0 after the call, float if some caller reads $f0, else void
"""
import os, sys, re, csv
sys.path.insert(0, os.path.dirname(__file__))
import matchtool as M
import rabbitizer

INT_ARGS = ['a0', 'a1', 'a2', 'a3', 't0', 't1', 't2', 't3']
FP_ARGS = ['f12', 'f13', 'f14', 'f15', 'f16', 'f17', 'f18', 'f19']

def instrs(a, s):
    for i, w in enumerate(M.target_words(a, s)):
        yield rabbitizer.Instruction(w, vram=a + 4 * i, category=rabbitizer.InstrCategory.R5900)

def regs_of(ins):
    """(reads, writes) as register-name sets using rabbitizer's operand info."""
    text = ins.disassemble()
    ops = re.findall(r'\$(\w+)', text)
    if not ops: return set(), set()
    mn = text.split()[0]
    # stores, branches, jr, mt* only read; most others write first operand
    read_only = mn.startswith(('s', 'b', 'j', 'mt', 'c.', 'ctc')) and not mn.startswith(('sub', 'sll', 'srl', 'sra', 'slt', 'seb', 'seh', 'sq')) or mn in ('jr', 'jalr')
    if mn in ('sq', 'swc1', 'sdc1', 'sqc2'): read_only = True
    if mn.startswith(('mfc', 'cfc')):
        return set(ops[1:]), {ops[0]}
    if mn.startswith('mtc'):
        return {ops[0]}, set(ops[1:])
    if read_only:
        return set(ops), set()
    return set(ops[1:]), {ops[0]}

SIGS = {}   # addr -> (ni, nf) from the previous fixed-point iteration

def call_target(ins):
    t = ins.disassemble()
    m = re.search(r'func_([0-9A-Fa-f]+)', t)
    return int(m.group(1), 16) if m else None

PTRS = {}   # addr -> set of int arg regs used as a load/store base before being written

def analyse_args(a, s):
    written = set(); ints = set(); fps = set(); pending_call = False; ptrs = set()
    for ins in instrs(a, s):
        r, w = regs_of(ins)
        t = ins.disassemble()
        mb = re.search(r'\(\$(\w+)\)', t)
        if mb and mb.group(1) in INT_ARGS and mb.group(1) not in written: ptrs.add(mb.group(1))
        if t.startswith('jal '):
            tg = call_target(ins)
            ni, nf = SIGS.get(tg, (0, 0))
            r = set(r) | set(INT_ARGS[:ni]) | set(FP_ARGS[:nf])
        elif t.startswith('jalr'):
            r = set(r) | {'a0'}
        for x in r:
            if x not in written:
                if x in INT_ARGS: ints.add(x)
                if x in FP_ARGS: fps.add(x)
        written |= w
        if t.startswith(('jal ', 'jalr')):
            pending_call = True
        elif pending_call:
            # the delay slot executed; now the call clobbers all arg regs
            written |= set(INT_ARGS) | set(FP_ARGS); pending_call = False
    ni = max([INT_ARGS.index(x) + 1 for x in ints], default=0)
    nf = max([FP_ARGS.index(x) + 1 for x in fps], default=0)
    PTRS[a] = ptrs
    return ni, nf

def main():
    funcs = M.load_functions()
    by_addr = {a: n for n, (a, s) in funcs.items()}
    real = {a: (n, s) for n, (a, s) in funcs.items() if M.TEXT_VA <= a < M.TEXT_VA + M.TEXT_SIZE}
    ret_int = set(); ret_fp = set()
    for a, (n, s) in real.items():
        seq = list(instrs(a, s))
        for i, ins in enumerate(seq):
            t = ins.disassemble()
            if not t.startswith('jal '): continue
            m = re.search(r'func_([0-9A-Fa-f]+)', t)
            tgt = ins.getInstrIndexAsVram() if hasattr(ins, 'getInstrIndexAsVram') else None
            if tgt is None and m: tgt = int(m.group(1), 16)
            if tgt is None: continue
            # look at instructions after the delay slot until v0/f0 is overwritten or control flow
            vdead = fdead = False
            for nxt in seq[i + 2:i + 30]:
                r, w = regs_of(nxt)
                nt = nxt.disassemble()
                if 'v0' in r and not vdead: ret_int.add(tgt)
                if 'f0' in r and not fdead: ret_fp.add(tgt)
                vdead |= 'v0' in w; fdead |= 'f0' in w
                if vdead and fdead: break
                if nt.startswith(('jal', 'jr', 'b ', 'beq', 'bne', 'j ', 'bgez', 'blez', 'bgtz', 'bltz', 'bc1')): break
    # functions with no direct callers (virtuals, callbacks): decide the return type from the body:
    # a write to v0 / f0 within the last two instructions before each `jr $ra` means it returns a value
    called = set()
    for a, (n, s_) in real.items():
        for ins in instrs(a, s_):
            t = ins.disassemble()
            if t.startswith('jal '):
                tg = call_target(ins)
                if tg: called.add(tg)
    for a, (n, s_) in real.items():
        pass
        seq = list(instrs(a, s_))
        for i, ins in enumerate(seq):
            if ins.disassemble().startswith('jr') and '$ra' in ins.disassemble():
                window = [x for x in seq[max(0, i - 6):i + 2] if not x.disassemble().startswith(("lq", "ld ", "lwc1", "addiu       $sp"))]
                ws = set()
                for x in window: ws |= regs_of(x)[1]
                if 'v0' in ws: ret_int.add(a)
                if 'f0' in ws and 'v0' not in ws: ret_fp.add(a)
    for it in range(6):
        new = {a: analyse_args(a, s) for a, (n, s) in real.items()}
        changed = sum(1 for a in new if new[a] != SIGS.get(a))
        SIGS.clear(); SIGS.update(new)
        if not changed: break
    out = ['/* generated by tools/infer_sigs.py */', 'typedef int s32; typedef float f32;']
    rows = []
    for a, (n, s) in sorted(real.items()):
        ni, nf = SIGS[a]
        ret = 'f32' if a in ret_fp else ('s32' if a in ret_int else 'void')
        args = [('void *' if INT_ARGS[k] in PTRS.get(a, ()) else 's32') for k in range(ni)] + ['f32'] * nf
        if not re.match(r'^[A-Za-z_]\w*$', n): continue
        proto = f'({", ".join(args) if args else "void"});'
        out.append(f'{ret} {n}{proto}')
        alias = f'func_{a:08X}'
        if alias != n: out.append(f'{ret} {alias}{proto}')
        rows.append((n, f'0x{a:06X}', ret, ni, nf))
    open(os.path.join(M.ROOT, 'build', 'context.h'), 'w').write('\n'.join(out) + '\n')
    with open(os.path.join(M.ROOT, 'build', 'signatures.csv'), 'w', newline='') as f:
        w = csv.writer(f); w.writerow(['name', 'addr', 'ret', 'n_int', 'n_float']); w.writerows(rows)
    print(len(rows), 'prototypes;', sum(1 for r in rows if r[2] == 'void'), 'void,', sum(1 for r in rows if r[2] == 'f32'), 'float returns')

if __name__ == '__main__':
    main()
