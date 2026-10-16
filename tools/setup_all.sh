#!/bin/bash
# One-command setup for the Sly 2 decomp (Linux or WSL).  Downloads every compiler/tool the build uses into
# tools/ (none of them are stored in the repo), then extracts the game executable from YOUR OWN disc image.
#
#   bash tools/setup_all.sh "/path/to/Sly 2 - Band of Thieves (USA).iso"
#
# Needs: bash, curl, tar, xz, python3 (+ pip).  On Debian/Ubuntu/WSL it also installs the 32-bit C library
# (sudo apt) that the native PS2 compilers need.  Safe to re-run: anything already present is skipped.
set -e
ROOT="$(cd "$(dirname "$0")/.." && pwd)"; cd "$ROOT"
C=tools/compilers
REL=https://github.com/decompme/compilers/releases/download/compilers
mkdir -p $C/bundle $C/extra

get() {  # get URL DEST-DIR  (extracts .tar.xz / .tar.gz into DEST-DIR, skips if DEST-DIR is non-empty)
  local url=$1 dest=$2
  if [ -d "$dest" ] && [ -n "$(ls -A "$dest" 2>/dev/null)" ]; then echo "  have $dest"; return; fi
  echo "  fetching $(basename "$url")"
  mkdir -p "$dest"; local t; t=$(mktemp)
  curl -fsSL -o "$t" "$url"
  case "$url" in *.tar.xz) tar -xJf "$t" -C "$dest";; *.tar.gz) tar -xzf "$t" -C "$dest";; esac
  rm -f "$t"
}

echo "== wibo (runs the Windows compilers)"
[ -x tools/wibo-i686 ] || { curl -fsSL -o tools/wibo-i686 https://github.com/decompals/wibo/releases/download/1.0.0/wibo-i686; chmod +x tools/wibo-i686; }

echo "== PS2 compiler bundle (game code: ee-gcc 2.95.3-136, plus 2.95.x and Metrowerks builds)"
if [ ! -d $C/bundle/ee-gcc2.95.3-136 ]; then
  t=$(mktemp -d); curl -fsSL -o $t/b.tar.xz $REL/ps2_compilers.tar.xz; tar -xJf $t/b.tar.xz -C $t
  # the archive's top folder name varies; move every ee-gcc*/mwcps2* directory into bundle/
  for d in $(find $t -maxdepth 3 -mindepth 1 -type d \( -name 'ee-gcc*' -o -name 'mwcps2*' \) -prune); do mv -n "$d" $C/bundle/; done
  rm -rf $t
fi

echo "== ee-gcc 2.95.3-114 (its SN assembler ps2eeas assembles the game code)"
get $REL/ee-gcc2.95.3-114.tar.gz $C/2.95.3-114

echo "== ee-gcc 2.96 (Sony SDK library code, GNU as)"
get $REL/ee-gcc2.96.tar.xz $C/ee-gcc2.96

echo "== ee-gcc 2.9 / 3.2 (Sony SDK libraries: mult1, tail calls)"
for n in ee-gcc2.9-990721 ee-gcc2.9-991111 ee-gcc2.9-991111a ee-gcc2.9-991111-01 ee-gcc3.2-040921; do
  get $REL/$n.tar.xz $C/extra/$n; done
for n in ee-gcc2.9-991111-01-dtls13010 ee-gcc3.2-030926; do
  get $REL/$n.tar.gz $C/extra/$n; done

echo "== 32-bit C library for the native compilers"
if [ ! -e /lib/ld-linux.so.2 ]; then
  if command -v apt-get >/dev/null; then
    sudo dpkg --add-architecture i386 && sudo apt-get update -qq && sudo apt-get install -y -qq libc6:i386
  else
    echo "  !! install your distro's 32-bit glibc (libc6:i386 / glibc.i686) so tools/compilers/*/bin/ee-gcc can run"
  fi
fi

echo "== Python packages"
python3 -m pip install -q --user rabbitizer spimdisasm "splat64[mips]" 2>/dev/null \
  || python3 -m pip install -q --break-system-packages rabbitizer spimdisasm "splat64[mips]" \
  || echo "  !! pip install failed - install rabbitizer, spimdisasm and splat64[mips] yourself"
[ -d "$HOME/m2c" ] || git clone -q https://github.com/matt-kempster/m2c "$HOME/m2c" || echo "  !! couldn't clone m2c (only needed for tools/show.py)"

echo "== Game executable from your own disc"
if [ ! -f disc/SCUS_973.16 ]; then
  if [ -n "$1" ]; then python3 tools/extract_elf.py "$1"
  else echo "  !! run again with the path to your Sly 2 (USA) ISO to extract disc/SCUS_973.16"; fi
fi

echo "== Disassembly (used by tools/show.py for m2c drafts)"
[ -d asm ] || { [ -f disc/SCUS_973.16 ] && python3 -m splat split config/sly2.yaml >/dev/null && echo "  asm/ written"; }

echo "== Turn on the progress-graph hook"
git config core.hooksPath tools/hooks

echo
echo "Done. Check it works:  python3 tools/matchtool.py check src/P2/bis.cpp   (every function should say MATCH)"
