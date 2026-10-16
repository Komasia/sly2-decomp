# Setting up the Sly 2 decomp

This repository contains **only our own source code and tools**. It does not contain the game, its code, or any
compiler binaries. You need your own copy of *Sly 2: Band of Thieves* (USA, SCUS-97316) and a Linux (or WSL) machine.

## 1. Game executable (from your own disc)
```
python3 tools/extract_elf.py "/path/to/Sly 2 - Band of Thieves (USA).iso"
```
It writes `disc/SCUS_973.16` and checks SHA-1 `de2af92a54de71e33edc8a160c31c0337a95e6f5`.

## 2. Python packages
```
pip install rabbitizer spimdisasm splat64[mips]
git clone https://github.com/matt-kempster/m2c ~/m2c     # only needed for automatch/show drafts
```
`tools/matchtool.py` needs `rabbitizer` on PYTHONPATH.

## 3. Compilers (put them under `tools/`)
| What | Where it goes | Get it from |
|---|---|---|
| wibo (runs the Windows compilers on Linux) | `tools/wibo-i686` (chmod +x) | https://github.com/decompals/wibo/releases/download/1.0.0/wibo-i686 |
| PS2 compiler bundle (game code: **ee-gcc 2.95.3-136**) | extract to `tools/compilers/bundle/` | https://github.com/decompme/compilers/releases/download/compilers/ps2_compilers.tar.xz |
| ee-gcc 2.95.3-114 (only for its SN assembler `ps2eeas.exe`) | extract to `tools/compilers/2.95.3-114/` | https://github.com/decompme/compilers/releases/download/compilers/ee-gcc2.95.3-114.tar.gz |
| ee-gcc 2.96 (Sony SDK library code, GNU as) | extract to `tools/compilers/ee-gcc2.96/` | https://github.com/decompme/compilers/releases/download/compilers/ee-gcc2.96.tar.xz |
| More PS2 compilers (Sony SDK libraries: ee-gcc 2.9 does `mult1` and tail calls) | extract each to `tools/compilers/extra/<name>/` | `https://github.com/decompme/compilers/releases/download/compilers/<name>.tar.xz` for ee-gcc2.9-990721, ee-gcc2.9-991111, ee-gcc2.9-991111a, ee-gcc2.9-991111-01, ee-gcc3.2-040921; `.tar.gz` for ee-gcc2.9-991111-01-dtls13010, ee-gcc3.2-030926 |

ee-gcc 2.96 is a 32-bit Linux program: on Ubuntu/Debian `sudo dpkg --add-architecture i386 && sudo apt install libc6:i386`
(or use `tools/setup_i386.sh` with Ubuntu's `libc6_*_i386.deb`).

## 4. Optional: disassembly for drafts
```
python3 -m splat split config/sly2.yaml      # writes asm/ (used by tools/show.py and tools/automatch.py)
```

## 5. Check it works
```
export PYTHONPATH=<path to rabbitizer etc.>
python3 tools/matchtool.py check src/P2/bis.cpp      # every function should print MATCH
python3 tools/progress.py                            # rebuilds config/matched.csv and prints totals
```

## 6. Turn on the progress-graph hook (once per clone)
```
git config core.hooksPath tools/hooks
```
After this, every `git push` that adds or changes code under `src/` automatically re-runs `tools/progress.py` and
commits the updated README graph. The first push stops after updating the graph, so run `git push` once more.
To skip it for one push: `git push --no-verify`.

## How we work
- Read `docs/AGENT_GUIDE.md` (rules, compiler facts, matching tricks) and the `notes/<range>.md` for your range.
- `python3 tools/worklist.py LO HI [MAXINSTR]` lists unmatched functions in an address range, smallest first.
- One function per file: `src/hand/NAME.c` (or `.cpp`), checked with `python3 tools/matchtool.py check FILE NAME`.
  **Only byte-identical functions are committed to `src/`**; near-misses go in `build/hand_wip/` with a note.
- Sony SDK library code goes in `src/lib/` with per-file compiler headers (see the end of `docs/AGENT_GUIDE.md`).
- To avoid overlap, claim an address range (e.g. in an issue or on Discord) before starting on it.
