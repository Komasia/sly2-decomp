#!/bin/bash
# Run decomp-permuter (github.com/simonlindholm/decomp-permuter) on a plain-C draft (no inline asm, not C++).
#   bash tools/permute.sh build/hand_wip/func_XXXXXXXX.c [seconds=1200] [jobs=1]
# It randomly rewrites the C to find a version that compiles to the original bytes; improved versions are written
# to /tmp/perm/<func>/output-<score>-*/source.c - check them with matchtool before saving anything.
set -e
SRC=$1; SECS=${2:-1200}; JOBS=${3:-1}
ROOT="$(cd "$(dirname "$0")/.." && pwd)"
N=$(basename "$SRC"); N=${N%%.*}
P=${PERMUTER:-$HOME/permuter}
[ -d "$P" ] || git clone -q https://github.com/simonlindholm/decomp-permuter "$P"
D=/tmp/perm/$N; rm -rf "$D"; mkdir -p "$D"
# The permuter's C parser can't read __attribute__, so strip it, but remember the typedefs that need one
# (e.g. `typedef int qword __attribute__((mode(TI)))` - without it qword silently becomes a 32-bit int) and the
# file's // SLY2_* header (compiler choice for Sony code); compile.sh puts both back before every compile.
gcc -E -P -I"$ROOT/include" -x c "$SRC" > "$D/pre.c"
grep -E '^// SLY2_' "$SRC" > "$D/header.txt" || true
python3 - "$D/pre.c" "$D/base.c" "$D/attrs.txt" <<'PY'
import re, sys
s = open(sys.argv[1]).read(); keep = []
def strip_attrs(t):
    out = []; i = 0
    while True:
        j = t.find('__attribute__', i)
        if j < 0: out.append(t[i:]); return ''.join(out)
        out.append(t[i:j]); k = t.index('(', j); depth = 0
        for q in range(k, len(t)):
            if t[q] == '(': depth += 1
            elif t[q] == ')':
                depth -= 1
                if depth == 0: break
        i = q + 1
for m in re.finditer(r'typedef\s+([^;]*?)\s+(\w+)\s+(__attribute__\s*\(\(\s*mode\s*\(\s*\w+\s*\)\s*\)\))\s*;', s):
    keep.append('%s\t%s\t%s' % (m.group(2), ' '.join(m.group(1).split()), m.group(3)))
open(sys.argv[2], 'w').write(strip_attrs(s)); open(sys.argv[3], 'w').write('\n'.join(keep) + '\n')
PY
cat > "$D/compile.sh" <<EOS
#!/bin/bash
D="$D"
t=\$(mktemp "\$D/tmpXXXXXX").c
python3 - "\$1" "\$t" "\$D/header.txt" "\$D/attrs.txt" <<'PY'
import re, sys
body = open(sys.argv[1]).read(); hdr = open(sys.argv[3]).read()
for line in open(sys.argv[4]).read().splitlines():
    if not line.strip(): continue
    name, typ, attr = line.split('\t')
    body = re.sub(r'typedef\s+' + r'\\s+'.join(map(re.escape, typ.split())) + r'\s+' + name + r'\s*;', 'typedef %s %s %s;' % (typ, name, attr), body)
open(sys.argv[2], 'w').write(hdr + body)
PY
cd "$ROOT" && python3 -c "
import sys, shutil; sys.path.insert(0,'tools'); import matchtool as M
o = M.compile_src(sys.argv[1]); shutil.move(o, sys.argv[2])" "\$t" "\$3"
rc=\$?; rm -f "\$t"; exit \$rc
EOS
chmod +x "$D/compile.sh"
printf 'func_name = "%s"\ncompiler_type = "gcc"\nobjdump_command = "python3 %s/tools/perm_objdump.py -drz"\n' "$N" "$ROOT" > "$D/settings.toml"
"$D/compile.sh" "$D/base.c" -o "$D/base.o"; cp "$D/base.o" "$D/target.o"   # target.o is recognised by name
export PERM_FUNC=$N
cd "$P" && timeout "$SECS" python3 permuter.py "$D" -j"$JOBS" --best-only || true
ls -d "$D"/output-* 2>/dev/null || echo "no improvement found for $N"
