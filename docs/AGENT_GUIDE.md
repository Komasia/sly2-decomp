# Sly 2 matching decomp — guide for decompilation agents

Goal: write C/C++ source that compiles to **byte-identical** code for functions of Sly 2 (SCUS_973.16).
Project root: `/home/claude/decomp`. Always run tools from the root.

## Your loop
1. `python3 tools/worklist.py LO HI [MAXINSTR]` — unmatched functions in your hex address range, smallest first.
   Re-run it now and then: other processes add matches to `src/auto/` and you must skip those.
2. `python3 tools/show.py NAME` — target disassembly, the best m2c draft (if any), and Sly 1 reference C if known.
   `python3 tools/matchtool.py target NAME` prints just the target asm.
3. Write `src/hand/NAME.c` (or `.cpp`, see below) and check it:
   `python3 tools/matchtool.py check src/hand/NAME.c NAME`
   It prints `MATCH` or a side-by-side diff (`!!` marks differing lines; left = target, right = yours).
   Relocated operands (addresses of calls/globals) are masked, so `jal func_X` matches any symbol.
4. Iterate until MATCH. If after a real effort (~10–15 attempts) it still differs, move the best attempt to
   `build/hand_wip/NAME.c` (create the dir), note the remaining diff in your notes file, and move on.
   **Only matching files may stay in `src/hand/`.**
5. Never run `tools/progress.py`, `automatch*.py`, `quickfix.py`, or edit anything in `tools/`, `include/`,
   `config/`, `src/P2/`, `src/auto/`. Other agents work at the same time. Write only `src/hand/*`,
   `build/hand_wip/*`, and your notes file `notes/<your-range>.md`.

## Compiler facts
- ee-gcc 2.95.3 (build 136), `-O2 -G0 -ffast-math -mvu0-use-vf0-vf31`. `.c` files compile as C, `.cpp` as C++.
- The original is C++. Use `.cpp` when the symbol is a mangled name (e.g. `Free__9CDynArray`): declare the class
  locally in your file with the right member offsets and define the method. g++ 2.95 mangling: `Name__ClassArgs`,
  e.g. `Foo__4CBarii` = `CBar::Foo(int,int)`, `__4CBar` = ctor, `_$_4CBar` = dtor, free function
  `Foo__FP4CBari` = `Foo(CBar*, int)`. Arg codes: i int, Ui uint, f float, c char, Uc uchar, s short, l long
  (64-bit on EE: use `long`), Ul ulong, v void, P pointer, R reference, C const, `Q2..` nested.
- For `func_XXXXXXXX` names (unknown), write plain C with that exact function name. Types are free to choose.
- Shared headers you may `#include` (read-only): `common.h` (byte/uchar/ushort/uint/ulong(64-bit)),
  `vec.h` (VECTOR/VECTOR4), `mat.h` (MATRIX3/4), `qw.h` (QW), `bis.h`, `dmas.h`, `vifs.h`, `gifs.h`, `heap.h`.
  For anything else declare structs/externs locally in your file.
- Declare called functions with prototypes; an undeclared function returning int changes codegen.
  A call whose result is unused should be declared `void` (or cast the call to void).
- `$ra` saved with `sd`; callee-saved `$s` regs with `sq`. Struct returns use a hidden pointer in `$a0`.
- vtables: entries are 8 bytes `{short delta; short pad; fn}`. A virtual call loads `lh 8N(vt)` and `lw 8N+4(vt)`
  for slot N (slot 0 unused). vptr is placed after the data members of the class that first declares virtuals
  (offset 0 if that class has no data). Constructors return `this`.
- `ulong` (64-bit) ops appear as `dsll32`, `dsra32`, `daddu` etc. `daddu $x, $y, $zero` is just a move.
- Float constants come from `lui`+`mtc1`; `lwc1 f, %gp_rel` / absolute addresses are globals.

## Toolchain status (things the build now reproduces — don't fight them)
- Assembly goes through SN's `ps2eeas` (via tools/wibo_cc.py): FPU hazard nops (mtc1→use, c.cond→bc1x),
  64-bit constant expansion (`addiu -1; dsll32`), and short backward branch padding (tools/asfix.py) all
  match the original now. If you believe a remaining diff is a toolchain issue, write it in your notes with
  the function name instead of working around it.
- C++ is compiled with exceptions disabled (-fno-exceptions), so C++ objects with destructors and
  temporaries can be used naturally.

## Knowledge from earlier agents (read notes/*.md for details)
- 128-bit by-value arguments/returns (VECTOR passed in one GPR, `qword` params): use
  `typedef int qword __attribute__((mode(TI)));`.
- Allocation: func_001AE4F8 = operator new / alloc(cb). memcpy = func_0023320C, memset = func_002333B4:
  declare them under their func_ names (a prototype named memcpy/memset becomes a builtin).
- CRef = {int m_tagk; int m_tag}; tagk 0x15 int, 0x16 float, 0x17 bool, 0x24 void. func_00129EC8 = ~CRef,
  func_001291A8 = CRef copy ctor. Splice wrappers: see src/splicewrap/ and notes/120000.md.
- DL list {pvFirst, pvLast, ibDle}, DLE {pvNext, pvPrev}; DLI iterator {pdl, ppv, ibDle, pdliNext},
  g_pdliFirst = D_002DD2FC (notes/130000.md has inline InitDli/PvNextDli that match).
- g_clock = D_002DDED0 {float t; float dt; ...} (notes/140000.md). Big game-state global D_003DD490.
- LO-style objects have the vptr at +0xC.
- Unsolved patterns (skip unless you have a new idea): "factory" functions `p = alloc(cb); p->vtbl = X; ...`
  where the target keeps the vtable address in $v1 (notes/110000.md); returning a float VECTOR in $v0 with
  pextuw/prot3w (notes/140000.md).

## Matching techniques that worked here
- **Store order**: gcc keeps source order of stores, except it sometimes rotates the last store to the front.
  If the target stores A,B,C try source order B,C,A.
- **Register allocation** differences: change declaration order of locals, merge/split temporaries,
  introduce a block-scoped temp, reuse a variable vs. new one, write `x = a; x |= b;` vs `x = a | b;`,
  swap operands of commutative ops / comparisons, `if (!c) {B} else {A}` vs `if (c) {A} else {B}`.
- Building a value in a temporary (`ulong tag = ...; tag |= ...; p->x = tag;`) vs inline expression changes
  instruction scheduling.
- `for` vs `while` vs `do-while`; `i++` vs pre-increment; pointer walking vs indexing; `x != 0` vs `x`.
- `beql`/`bnel` (branch-likely) come from loops/ifs the compiler optimised; you don't write them directly.
- Short backward loops are padded with `nop`s by the build (tools/asfix.py) — don't try to reproduce those nops.
- `pv->x = pv->y = pv->z = 0` (chained) gives a different store order / keeps 0.0f in an FPU reg.
- Non-rotated loops: `for (i = 0; ; i++) { if (i >= n) break; ... }`; `do { ... } while (1)` with breaks.
- `(a == b) & (c == d)` gives the movn/sltiu forms; `switch` for set-membership tests.
- Taking a global's address into a local first (`G *pg = &g;`) when the target keeps it in an $s register.
- An unused local struct can reproduce an otherwise unexplained stack frame size.
- Inline functions in headers (e.g. a small accessor) can explain duplicated code sequences.
- Switch statements produce jump tables (`lw` from a table in .rodata + `jr`).
- Functions using VU0 macro-mode (`vadd.xyz`, `qmtc2`, `lqc2`…) are hard; skip them (note them) unless small.

## Notes file
Keep `notes/<range>.md` with: struct layouts / class names you inferred (with offsets and evidence),
real names you are confident about (from Sly 1 counterparts, strings, vtables), and near-misses left in
`build/hand_wip/`. These get merged into shared headers later.

## Round-3 discoveries (from notes/1E0000.md and notes/200000.md — read those for details)
- Parameter order with floats changes integer register assignment: try moving float params (e.g. `(p, int, float, int, float, int, int)`).
- A separate counter per loop (`i`, then `j`) can fix saved-register priority.
- Declare callees with their real return type (memset/memmove return `void *`, constructors return `this`) — fixes $v0/$v1 choice.
- `qword` locals get a stack slot when their address is first taken; wrap in a union/struct to place at declaration.
- VU0: one inline-asm statement per VU op (vsub / dot / sqrt / qmfc2) lets gcc allocate VF regs like the original.
- EE varargs: `__builtin_next_arg` / `__builtin_args_info(2)` for va_start, `*(T*)((ap += 8) - 8)` for va_arg.
- `extern const float` lets a global float load be hoisted from a loop; `int unused[4]` explains a frame with ra at sp+0x10;
  `while (f(p), cond)` reproduces calls inside a loop test; an empty `case 0:` can reproduce a switch tree.
- Jump tables: read from disc/SCUS_973.16 at file offset 0x80 + (addr - 0x100000).

## Sony SDK library code (0x234F48–0x2550A0)
- Built by Sony with a modified 2.95.x compiler we do NOT have (see notes/234F48.md, notes/245000.md). ee-gcc 2.96 is NOT it
  (always keeps a frame around tail calls, mis-rounds float constants).
- Best available: `// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136` + `// SLY2_CFLAGS: -O2 -G0` in src/lib/NAME.c.
  Matches leaf functions and functions whose frame only holds $ra + locals (no saved $s regs, no tail calls,
  no mult1, no padded short loops, no float compare-branch, no assembler-built 64-bit constants).
- `long long` is 128-bit on the EE; use `long` for 64-bit values.

## Toolchain fix (round 5)
- tools/asfix.py now pads `L: b L` (while(1);) and short loops that start with a `jal` (call + empty delay slot)
  to 6 instructions like the original. Re-verified: no regressions. If you see one extra nop before a short
  backward branch, report it in your notes with the function name.
- `_start` (crt0) is hand-written asm in the original; it is kept as a top-level `__asm__` block in src/hand/_start.c.

## Toolchain fixes (round 6) — IMPORTANT, supersedes earlier "nop before div" advice
- The build now inserts the two nops Sly 2's assembler put before div.s / sqrt.s / rsqrt.s / vdiv / vsqrt / vrsqrt
  when that instruction starts a basic block (function entry, branch target, or right after a branch + delay slot;
  calls don't count). Do NOT write `__asm__("nop\n\tnop")` anymore — write the plain C division / sqrt.
- Unconditional backward `b` loops in noreorder blocks, and loops whose first instruction is any branch/jump,
  are now padded like the original (UpdateJoy, func_001974C8 match without hacks).
- Kernel syscall stubs (`addiu v1,$zero,N; syscall; jr ra; nop`) are done as asm blocks in src/lib/syscall/.

## SDK assembler mode: `// SLY2_ASM: gnu-reorder`  (added after round 8 — use it for Sony SDK code)
- Sony's SDK objects = gcc code generator WITHOUT delay-slot filling + GNU as in reorder mode, which fills every
  branch/jump delay slot with the preceding independent instruction, EXCEPT loop (backward) branches, which keep a nop.
- Header for SDK files:   // SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
                          // SLY2_CFLAGS: -O2 -G0
                          // SLY2_ASM: gnu-reorder
  (tools/gnu_reorder.py adds -fno-delayed-branch, pins loop branches, assembles with ee-gcc2.96's GNU as.)
  Verified: kCopy, kCopy_00239898, kputchar, memclr match this way. Also try SLY2_CC: tools/compilers/ee-gcc2.96 with it.
- Do NOT add your own `nop`s for delay slots or short-loop padding in this mode; the assembler handles them.

## SDK build modes (round 10) — pick per library, all with SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
| `// SLY2_ASM:` | Model | Libraries seen so far (verified matches) |
|---|---|---|
| `gnu-reorder`    | gcc delay-slot filling OFF, GNU as fills slots, loop slots stay nop | libkernel: kCopy*, memclr, kputchar, DIntr, _sceIDC |
| `gnu-reorder-db` | gcc reorg fills slots (incl. from branch targets, beql), GNU as fills what's left | libmpeg/libipu (sceMpegInit, sceIpuSync), libm (floorf), libgraph/libdma (sceDmaPutEnv), libgcc fp-bit (__pack_d) |
| `gnu-reorg`      | as gnu-reorder-db, but slots of short (<=5 insn) single-block loops are emptied | libgcc dp-bit (litodp) |
- Try `-fstrict-aliasing` in SLY2_CFLAGS: Sony's lib build had it on for some files (sceDmaPutEnv, iAllocTimerCounter).
- Still unsolved toolchain issues (skip these functions): `$s` regs saved with `sd` into 16-byte slots; frameless `j` tail calls;
  `mult1`/`mult` constant strides (scePad); the mfc1->branch hazard nop in libm.
