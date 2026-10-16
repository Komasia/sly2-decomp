# Sly 2: Band of Thieves — matching decompilation (work in progress)

**New here? Start with [SETUP.md](SETUP.md).** This repo contains no game data; bring your own disc.

Target: `SCUS_973.16` (NTSC-U, SHA-1 de2af92a54de71e33edc8a160c31c0337a95e6f5)

## Progress

![Decompilation progress](docs/progress.svg)

The graph updates automatically every time `tools/progress.py` runs. Only functions whose compiled bytes are
identical to the original game count. Ranges: orange = Dimitri + Claude, purple = NaGa (see `ASSIGNMENTS.md`).

## Toolchain (confirmed)
- **Compiler: ee-gcc 2.95.3 build 136**, flags `-O2 -G0 -ffast-math`, sources are C++ (`-x c++`).
  (Sly 1 used SN ee-gcc 2.95.2 v2.73a; Sly 2 differs — it saves `$ra` with `sd`, not `sq`.)
- Runs on Linux through `tools/wibo-i686`. Compilers live in `tools/compilers/` (from decomp.me's collection).

## Layout
- `src/P2/*.cpp` — hand-decompiled engine code with real types/names (e.g. `bis.cpp`, the binary input stream)
- `src/auto/*.c` — functions matched from m2c output (raw C, unknown types as `M2C_FIELD` macros). They are
  byte-identical but still need cleanup into proper types/names.
- `include/` — headers (`bis.h`, `vec.h`, `mat.h`, `common.h`, `m2c_prelude.h`)
- `config/symbol_addrs.txt` — names; `config/functions.csv` — every function's address/size;
  `config/matched.csv` — current verified match list (generated)
- `asm/text.s` — full disassembly

## Tools
- `tools/matchtool.py check FILE [func...]` — compile and compare against the original, per function
- `tools/show.py NAME` — target asm + m2c draft + Sly 1 reference C side by side
- `tools/automatch.py` — bulk m2c→compile→compare pass
- `tools/quickfix.py NAME` / `batch_quickfix.py` — greedy fixer for near-misses
- `tools/perm_setup.py NAME` + decomp-permuter (`tools/fake_objdump.py` stands in for mips objdump)
- `tools/progress.py` — rebuild the matched list and print totals
- `tools/harvest_sly1.py` — find Sly 2 functions identical to matched Sly 1 C

Env for the tools: PYTHONPATH must include rabbitizer (pip install rabbitizer spimdisasm splat64).
