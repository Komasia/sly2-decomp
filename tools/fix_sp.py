#!/usr/bin/env python3
"""Rewrite m2c drafts that use raw stack slots (`sp`, `sp10`, `&sp10`) into a frame struct whose
members sit at exactly the original offsets.   fix_sp.py IN.c OUT.c  (exit 0 if rewritten)"""
import re, sys

SIZES = {'s8': 1, 'u8': 1, 'M2C_UNK8': 1, 's16': 2, 'u16': 2, 'M2C_UNK16': 2, 's32': 4, 'u32': 4, 'f32': 4,
         'M2C_UNK': 4, 'M2C_UNK32': 4, 's64': 8, 'u64': 8, 'f64': 8, 'M2C_UNK64': 8, 's128': 16, 'u128': 16}

def size_of(t):
    t = t.strip()
    if t.endswith('*'): return 4
    return SIZES.get(t, 4)

def rewrite(src):
    m = re.search(r'\n([^\n]*?)\b(\w+)\(([^)]*)\) \{\n', src)
    if not m: return None
    head_end = m.end()
    body = src[head_end:]
    if not re.search(r'(?<![\w.])sp([0-9A-F]+)?\b', body): return None
    types = {}
    for d in re.finditer(r'^\s*([\w\s]+?\s*\**)\s*sp([0-9A-F]+);\s*$', body, re.M):
        types[int(d.group(2), 16)] = d.group(1).strip()
    body = re.sub(r'^\s*[\w\s]+?\s*\**\s*sp[0-9A-F]+;\s*\n', '', body, flags=re.M)
    offs = set(types)
    for x in re.finditer(r'(?<![\w.])sp([0-9A-F]+)\b', body): offs.add(int(x.group(1), 16))
    if re.search(r'(?<![\w.&])sp\b', body): offs.add(0)
    members = []; cur = 0; pad = 0
    for o in sorted(offs):
        if o < cur: continue           # overlapping view of an earlier slot; leave as is
        if o > cur:
            members.append(f'        char pad{pad}[0x{o - cur:X}];'); pad += 1
        t = types.get(o, 'M2C_UNK')
        members.append(f'        {t} m{o:X};'); cur = o + size_of(t)
    frame = '    struct {\n' + '\n'.join(members) + '\n    } fr;\n'
    body = re.sub(r'&sp([0-9A-F]+)\b', lambda x: f'&fr.m{int(x.group(1), 16):X}', body)
    body = re.sub(r'(?<![\w.])sp([0-9A-F]+)\b', lambda x: f'fr.m{int(x.group(1), 16):X}', body)
    body = re.sub(r'(?<![\w.&])sp\b', '(void *)&fr', body)
    return src[:head_end] + frame + body

def main():
    out = rewrite(open(sys.argv[1]).read())
    if out is None: return 1
    open(sys.argv[2], 'w').write(out)
    return 0

if __name__ == '__main__':
    sys.exit(main())
