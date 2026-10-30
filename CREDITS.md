# Credits

Sly 2: Band of Thieves (`SCUS_973.16`, NTSC-U) was fully matched on **2026-10-30**: all 6,662 functions compile to
code that is byte-identical to the original game, with every call and data reference pointing at the right target.

## Who did what

Counted by who first committed each matched source file (the "Dimitri + Claude" row includes the work done before the
GitHub repo existed, which was imported in one commit). Everyone worked with AI assistants: Dimitri with Claude agents,
NaGa with Claude and ChatGPT, and Lilly with Claude.

| Who | Functions matched | Instructions | Main areas |
|---|---|---|---|
| **Dimitri** (Komasia) + **Claude** agents | ~6,240 | ~251,000 | Project setup, toolchain identification, engine core 0x100000–0x190000, the bulk of the early matching, final relocation audit |
| **NaGa** (with Claude and ChatGPT) | 343 | ~56,600 | Engine 0x190000–0x1F0000 |
| **Lilly** (lillyflower648, with Claude) | 107 | ~42,400 | Engine 0x1F0000–0x230000 and the Sony SDK libraries (0x234F48–0x2550A0) |

## Timeline
- **Before 2026-10-12** — Dimitri and Claude identify the compiler (ee-gcc 2.95.3 build 136 with the SN assembler from
  build 114) and match most of the small and medium functions, partly by reusing Sly 1 decomp code.
- **2026-10-12** — GitHub repo created; NaGa joins and takes 0x190000–0x1F0000.
- **2026-10-24** — Lilly joins; ranges re-split (99.05% of functions matched at this point).
- **2026-10-30** — last functions matched (6,662 / 6,662). A full relocation-aware audit then found 16 functions that
  had matched with the right bytes but referred to the wrong global or callee; they were fixed in `e0aacd4`.

## Tools and references
- [decomp.me compilers](https://github.com/decompme/compilers) (ee-gcc builds, SN `ps2eeas`)
- [wibo](https://github.com/decompals/wibo), [m2c](https://github.com/matt-kempster/m2c),
  [rabbitizer / spimdisasm / splat](https://github.com/Decompollaborate),
  [decomp-permuter](https://github.com/simonlindholm/decomp-permuter)
- The Sly 1 decompilation, used as a reference for shared engine code
