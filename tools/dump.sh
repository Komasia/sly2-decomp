#!/bin/sh
# Compile a draft with gcc pass dumps (-da, -fsched-verbose-5, ...) WITHOUT littering the repo root.
# usage: tools/dump.sh <workdir> <src.c|src.cpp> [extra gcc flags, e.g. -da -fsched-verbose-5]
# Dumps and d.s land in <workdir>. (matchtool.py compiles in the repo root, so never pass -da through it.)
R=$(cd "$(dirname "$0")/.." && pwd)
W=$1; src=$(cd "$(dirname "$2")" && pwd)/$(basename "$2"); shift 2
mkdir -p "$W" && cd "$W" || exit 1
case "$src" in *.c) ext=c; lang=c;; *) ext=cpp; lang=c++;; esac
cp "$src" "d.$ext"
"$R/tools/wibo-i686" "$R/tools/compilers/bundle/ee-gcc2.95.3-136/bin/ee-gcc.exe" -S -I"$R/include" -x $lang -O2 -G0 \
  -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -B"$R/tools/compilers/bundle/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3/" \
  "$@" "d.$ext" -o d.s
