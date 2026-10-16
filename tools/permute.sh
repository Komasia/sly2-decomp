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
gcc -E -P -I"$ROOT/include" -D'__attribute__(x)=' -x c "$SRC" > "$D/base.c"
cat > "$D/compile.sh" <<EOS
#!/bin/bash
cd "$ROOT" && python3 -c "
import sys, shutil; sys.path.insert(0,'tools'); import matchtool as M
o = M.compile_src(sys.argv[1]); shutil.move(o, sys.argv[2])" "\$1" "\$3"
EOS
chmod +x "$D/compile.sh"
printf 'func_name = "%s"\ncompiler_type = "gcc"\nobjdump_command = "python3 %s/tools/perm_objdump.py -drz"\n' "$N" "$ROOT" > "$D/settings.toml"
"$D/compile.sh" "$D/base.c" -o "$D/base.o"; cp "$D/base.o" "$D/target.o"   # target.o is recognised by name
export PERM_FUNC=$N
cd "$P" && timeout "$SECS" python3 permuter.py "$D" -j"$JOBS" --best-only || true
ls -d "$D"/output-* 2>/dev/null || echo "no improvement found for $N"
