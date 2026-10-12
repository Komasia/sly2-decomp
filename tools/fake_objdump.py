#!/usr/bin/env python3
"""Stand-in for `mips-linux-gnu-objdump -drz` (not installable here), good enough for decomp-permuter.

Handles two inputs:
  * real ELF .o files from ee-gcc (relocations read from .rel.text)
  * "target" files written by perm_setup.py: a 20-byte ELF ident prefix (so permuter detects MIPS)
    followed by b'SLY2TGT\\n' and JSON {"name", "words", "relocs": {idx: [type, sym, addend]}}
Output format mirrors GNU objdump closely enough for permuter's simplify_objdump().
"""
import sys, os, re, json, struct
sys.path.insert(0, os.path.dirname(__file__))
import rabbitizer
import matchtool as M

RTYPES = {4: 'R_MIPS_26', 5: 'R_MIPS_HI16', 6: 'R_MIPS_LO16', 7: 'R_MIPS_GPREL16'}
BRANCH = re.compile(r'\. \+ 4 \+ \((-?0x[0-9A-Fa-f]+) << 2\)')
HEX = re.compile(r'(?<![\w.])(-?)0x([0-9A-Fa-f]+)')

def fmt(word, idx):
    ins = rabbitizer.Instruction(word, vram=idx * 4, category=rabbitizer.InstrCategory.R5900)
    text = ins.disassemble()
    m = BRANCH.search(text)
    if m:
        tgt = idx * 4 + 4 + (int(m.group(1), 16) << 2)
        text = text[:m.start()] + format(tgt, 'x')
    parts = text.split(None, 1)
    mnem = parts[0]; args = parts[1] if len(parts) > 1 else ''
    if mnem in ('jal', 'j') and not m:
        args = '0'
    args = args.replace('$', '').replace(', ', ',').replace(' ', '')
    if not m:
        args = HEX.sub(lambda h: str(int(h.group(1) + h.group(2), 16)), args)
    return mnem, args

def emit(name, words, relocs):
    print(f'\n00000000 <{name}>:')
    for i, w in enumerate(words):
        mnem, args = fmt(w, i)
        print(f'{i*4:8x}:\t{w:08x} \t{mnem}\t{args}')
        r = relocs.get(i)
        if r:
            rtype, sym = r[0], r[1]
            print(f'\t\t\t{i*4:x}: {RTYPES.get(rtype, "R_MIPS_NONE")}\t{sym}')

def main():
    path = sys.argv[-1]
    data = open(path, 'rb').read()
    print(f'\n{path}:     file format elf32-tradlittlemips\n\n\nDisassembly of section .text:')
    if data[20:28] == b'SLY2TGT\n':
        j = json.loads(data[28:])
        emit(j['name'], j['words'], {int(k): v for k, v in j['relocs'].items()})
        return
    d, secs, syms, relocs = M.read_obj(path)
    # symbol names for relocations
    symtab = next(s for s in secs if s['type'] == 2)
    strtab = secs[symtab['link']]
    def symname(i):
        nm, = struct.unpack_from('<I', d, symtab['off'] + i * 16)
        return d[strtab['off'] + nm:d.index(b'\0', strtab['off'] + nm)].decode()
    for s in secs:
        if s['type'] == 9 and secs[s['info']]['name'] == '.text':
            rel = {}
            for i in range(s['size'] // 8):
                off, inf = struct.unpack_from('<II', d, s['off'] + i * 8)
                rel.setdefault(off, (inf & 0xff, symname(inf >> 8)))
            break
    else:
        rel = {}
    for sy in syms:
        if sy['type'] == 2 and sy['size'] > 0 and secs[sy['shndx']]['name'] == '.text':
            sec = secs[sy['shndx']]
            words = list(struct.unpack_from('<%dI' % (sy['size'] // 4), d, sec['off'] + sy['value']))
            rr = {(o - sy['value']) // 4: list(v) for o, v in rel.items() if sy['value'] <= o < sy['value'] + sy['size']}
            # static symbols (e.g. .rodata section) show as section names; keep as-is
            emit(sy['name'], words, rr)

if __name__ == '__main__':
    main()
