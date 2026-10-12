"""Shared source rewrites for m2c drafts."""
import re

def voidify(src):
    """Calls whose result is never used: declare them returning void (affects register allocation)."""
    out = src
    # virtual / indirect calls used as statements
    out = re.sub(r'^(\s*)M2C_FIELD\(([^;\n]*?), M2C_UNK \(\*\*\)\(', r'\1M2C_FIELD(\2, void (**)(', out, flags=re.M)
    # direct calls: find functions only ever called as statements
    decl = re.compile(r'^(M2C_UNK|s32|u32|s16|u16|s8|u8|void \*|f32|s64) (\w+)\(([^;]*)\);(\s*/\* extern \*/)?\s*$', re.M)
    for m in list(decl.finditer(out)):
        fn = m.group(2)
        uses = re.findall(r'(.)\s*\b%s\(' % re.escape(fn), out.split(m.group(0), 1)[1] if m.group(0) in out else out)
        body_calls = [mm for mm in re.finditer(r'^\s*(.*?)\b%s\(' % re.escape(fn), out, re.M) if not mm.group(0).lstrip().startswith(m.group(1))]
        stmt_only = all(mm.group(1).strip() == '' for mm in body_calls) and body_calls
        if stmt_only and m.group(1) != 'void':
            out = out.replace(m.group(0), f'void {fn}({m.group(3)});{m.group(4) or ""}')
    return out

ALLOC = re.compile(r'^(\s*)(\w+) = (\(?[\w *]*\)?\s*)?(func_001AE4F8|__builtin_new\w*)\(([^;]*)\);\s*$', re.M)
def inline_ctor(src):
    """After `p = operator_new(n);` move the following run of stores into p (constant/global RHS only)
    into a static inline 'constructor' that returns p, mirroring an inlined C++ ctor."""
    out = src; k = 0
    for m in list(ALLOC.finditer(src)):
        ind, var = m.group(1), m.group(2)
        after = src[m.end():].split('\n')[1:]
        moved = []
        for line in after:
            mm = re.match(r'^\s*M2C_FIELD\(%s, ([^)]*\)?[^)]*), (0x[0-9A-Fa-f]+|\d+)\) = (.*);\s*$' % re.escape(var), line)
            if not mm: break
            rhs = mm.group(3)
            if not re.fullmatch(r'\(?[\w *]*\)?\s*(&?D_[0-9A-Fa-f]+|-?0x[0-9A-Fa-f]+|-?\d+(\.\d+f?)?|NULL)', rhs.strip()): break
            moved.append(line)
        if not moved: continue
        name = f'm2c_ctor_{k}'; k += 1
        body = '\n'.join('    ' + l.strip().replace(f'M2C_FIELD({var},', 'M2C_FIELD(p,') for l in moved)
        fn = f'static inline void *{name}(void *p)\n{{\n{body}\n    return p;\n}}\n'
        block = m.group(0) + '\n' + '\n'.join(moved)
        new = f'{ind}{var} = {m.group(3) or ""}{name}({m.group(4)}({m.group(5)}));'
        if block not in out: continue
        out = out.replace(block, new, 1)
        # insert the inline fn before the function definition that contains it
        fdef = re.search(r'\n[^\n;{}]*\([^;{}]*\) \{\n', out)
        out = out[:fdef.start() + 1] + fn + '\n' + out[fdef.start() + 1:] if fdef else fn + out
    return out

def inline_ctor_return(src):
    """inline_ctor, and if the allocated object is the last thing touched in a void function, return it."""
    out = inline_ctor(src)
    if out == src: return out
    m = re.search(r'^(\s*)(\w+) = (m2c_ctor_\d+\([^;]*\));\s*\n(\s*)\}', out, re.M)
    if m:
        out = out[:m.start()] + f'{m.group(1)}return {m.group(3)};\n{m.group(4)}}}' + out[m.end():]
        out = re.sub(r'\nvoid (func_\w+|\w+__\w*)\(', r'\nvoid *\1(', out, count=1) if False else out
        # make the enclosing function return void*
        fdef = list(re.finditer(r'\n(void) (\w+)\(([^)]*)\) \{\n', out))
        if fdef:
            f = fdef[-1]
            out = out[:f.start()] + f'\nvoid *{f.group(2)}({f.group(3)}) {{\n' + out[f.end():]
    return out
