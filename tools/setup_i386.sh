#!/bin/bash
# Make the native 32-bit ee-gcc 2.96 (tools/compilers/ee-gcc2.96, Sony SDK library compiler) runnable.
# Needs libc6_2.39-0ubuntu8_i386.deb (kept in D:\Roms\PS2\Sly2Decomp) and a zstd binary (built from github.com/facebook/zstd).
set -e
DEB=${1:-/mnt/user-data/uploads/PS2/Sly2Decomp/libc6_2.39-0ubuntu8_i386.deb}
ZSTD=${ZSTD:-/home/claude/zstd/programs/zstd}
T=$(mktemp -d); cd $T; ar x "$DEB"; $ZSTD -dc data.tar.zst | tar x
cp -a usr/lib/i386-linux-gnu /usr/lib/
ln -sf /usr/lib/i386-linux-gnu/ld-linux.so.2 /lib/ld-linux.so.2
echo "ok: ee-gcc 2.96 runnable"
