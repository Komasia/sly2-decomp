#!/usr/bin/env python3
"""perm_setup.py NAME [src.c]  -> build/perm/NAME/{base.c,target.o,compile.sh,settings.toml}
Default base.c is the m2c draft from build/automatch/NAME.c."""
import os, sys, re, json, shutil, stat
sys.path.insert(0, os.path.dirname(__file__))
import matchtool as M
import automatch as A

def target_relocs(asm_text):
    """Relocations of the original function, recovered from splat's symbolic asm."""
    rel = {}
    lines = [l for l in asm_text.split('\n') if re.match(r'\s*/\* [0-9A-F]+ [0-9A-F]{8} [0-9A-F]{8} \*/', l)]
    for i, l in enumerate(lines):
        body = l.split('*/', 1)[1]
        m = re.search(r'\b(jal|j)\s+([A-Za-z_][\w.$]*)\s*$', body)
        if m and not body.strip().startswith('jr'):
            rel[i] = [4, m.group(2), 0]; continue
        m = re.search(r'%(hi|lo|gp_rel)\(([A-Za-z_][\w.$]*)(?:\s*\+\s*(0x[0-9A-Fa-f]+|\d+))?\)', body)
        if m:
            t = {'hi': 5, 'lo': 6, 'gp_rel': 7}[m.group(1)]
            rel[i] = [t, m.group(2), int(m.group(3), 0) if m.group(3) else 0]
    return rel

def main():
    name = sys.argv[1]
    funcs = M.load_functions(); a, s = funcs[name]
    asm = A.split_asm()[name]
    words = M.target_words(a, s)
    rel = target_relocs(asm)
    # zero the relocated fields, then re-insert the addend the way REL objects carry it
    for i, (t, sym, add) in rel.items():
        w = words[i]
        if t == 4: w &= 0xFC000000
        elif t == 5: w = (w & 0xFFFF0000) | (((add + 0x8000) >> 16) & 0xFFFF)
        elif t in (6, 7): w = (w & 0xFFFF0000) | (add & 0xFFFF)
        words[i] = w
    while words and words[-1] == 0: words.pop()
    d = os.path.join(M.ROOT, 'build', 'perm', name); os.makedirs(d, exist_ok=True)
    elf_ident = b'\x7fELF\x01\x01\x01\x00' + b'\0' * 8 + b'\x01\x00\x08\x00'
    open(os.path.join(d, 'target.o'), 'wb').write(elf_ident + b'SLY2TGT\n' + json.dumps({'name': name, 'words': words, 'relocs': rel}).encode())
    src = sys.argv[2] if len(sys.argv) > 2 else os.path.join(M.ROOT, 'build', 'automatch', name + '.c')
    txt = open(src).read().replace('#include "m2c_prelude.h"\n', '')
    prelude = open(os.path.join(M.ROOT, 'include', 'm2c_prelude.h')).read().replace('#include "m2c_macros.h"', open('/home/claude/m2c/m2c_macros.h').read())
    open(os.path.join(d, 'base.c'), 'w').write(prelude + '\n' + txt)
    B = os.path.join(M.ROOT, 'tools/compilers/bundle/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3')
    cs = os.path.join(d, 'compile.sh')
    open(cs, 'w').write(f'#!/bin/bash\nINPUT="$(realpath "$1")"; OUTPUT="$(realpath -m "$3")"\ncd {M.ROOT} && timeout 30 {M.WIBO} {M.CC} -c -x c -O2 -G0 -ffast-math -B{B}/ "$INPUT" -o "$OUTPUT"\n')
    os.chmod(cs, 0o755)
    py = sys.executable
    open(os.path.join(d, 'settings.toml'), 'w').write(f'func_name = "{name}"\ncompiler_type = "gcc"\nobjdump_command = "env PYTHONPATH={os.environ.get("PYTHONPATH","")} {py} {os.path.join(M.ROOT, "tools", "fake_objdump.py")}"\n')
    print(d)

if __name__ == '__main__':
    main()
