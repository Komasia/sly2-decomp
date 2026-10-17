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

## Housekeeping rules
- Never `mv`/`cp` anything to /dev/null or other system paths. To set a file aside, move it to build/hand_wip/.
- Never run git. The coordinator commits and pushes.
- Ranges 0x190000–0x230000 normally belong to NaGa (see ASSIGNMENTS.md). While NaGa is on break (from 2026-10-16) Dimitri has opened them to Claude agents: work there, but never overwrite NaGa's drafts (use new version names). Check ASSIGNMENTS.md: when the "on break" note is gone, stay out again.

## Divide/sqrt hazard padding (2026-10-16)
`tools/asfix.py` now pads div.s/sqrt.s/rsqrt.s/vdiv/vsqrt/vrsqrt to be at least the 3rd instruction of its basic
block: 2 nops at block position 0, 1 nop at position 1. Positions count real machine instructions (`li.s` = 1–3,
`li`/`la` = 1–2) and the padding nops themselves. Verified on a full uncached rebuild (no regressions; +func_0011D018).

## `// SLY2_SAVES: sd` (Sony SDK register saves, 2026-10-16)
Sony's SDK compiler saved/restored callee-saved registers with 64-bit `sd`/`ld` (still in 16-byte stack slots);
the ee-gcc builds we have emit 128-bit `sq`/`lq`. Add `// SLY2_SAVES: sd` (only together with `SLY2_ASM:`) and
matchtool rewrites sq/lq to sd/ld at assembly time. This emulates the compiler difference, like asfix.py does for
the game's assembler; do not put the macro in the C source. Typical SDK header set:
`SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114` / `SLY2_CFLAGS: -O2 -G0` / `SLY2_ASM: gnu-reorder-db` / `SLY2_SAVES: sd`.

## Short loops with an inner forward branch (2026-10-16)
asfix.py now also pads short loops that contain a forward conditional branch in reorder mode, when the
instruction before that branch writes a register the branch tests (so its delay slot is certainly a nop): the branch
counts as 2 instructions. A branch that is the loop's first instruction keeps the older rule. Fixed strchr
(func_0021EDF8) and func_001A6260; full uncached rebuild shows no regressions.

## Dead-code scraps: config/junk.csv (2026-10-16)
The original linker left small scraps of dead code between functions: orphan `addiu $sp,$sp,+N` / `nop` epilogue
pieces and lone delay-slot instructions with no return. 141 such ranges are listed in `config/junk.csv`; they are
not functions, so progress.py, the graph and worklist.py skip them (their bytes are still part of .text for a full
rebuild). Three entries that were a scrap followed by a real tiny function were split, so the function now starts
at the real address (func_00119BC8, func_0014C1F0, func_00259D60, and 9 more in a second pass that also treats
a leading "orphan instruction + nop" pair as scrap). Totals dropped from 6,813 to 6,661 functions.
If you find another scrap, add its range to junk.csv with a reason rather than "matching" it.

## Callee return types matter (2026-10-16)
Declare callees with their real return type even when the result is ignored: constructors, copy constructors and
CRef::operator= (func_00129658 returns CRef*, func_001291A8 returns void*) return `this`. Declaring them `void`
changes scheduling/argument order across the *whole* caller. This finished func_00200DA0, func_00200F58,
func_001D54B8 and func_001DE008. (The reverse also happens: func_0011B500's result is unused in one caller, and there
`void` matched — try both.)

## Empty asm barriers (policy, 2026-10-16)
`__asm__ __volatile__("")` emits no instructions; it only stops gcc moving code across it. It is accepted in matched
files when it stands in for a known difference between our compiler builds and the ones the game was built with
(e.g. Sony's SDK scheduler keeps the use of a call's return value right after the jal). Prefer natural C when it
exists, and leave a one-line comment saying what the barrier emulates.

## SDK modes: FPU compare -> branch nop and mfc1 -> branch nop (2026-10-16)
Also: labels between c.cond.s and the bc1 are skipped (the nop still goes after the compare), and `mfc1 $r,$fN`
followed by a gcc-scheduled branch reading $r gets a nop (Sony kept the coprocessor-move delay). Matched
__kernel_rem_pio2f, __kernel_sinf, __kernel_cosf; all 272 SDK-mode files re-verified.
gnu_reorder.py also inserts a nop between `c.cond.s` and a following bc1t/bc1f when gcc emitted the branch in a
noreorder block (Sony assembler hazard rule; matched acosf/asinf/atan2f, floorf unaffected). SLY2_SAVES now only
rewrites $sp-based sq/lq (real 128-bit data stores stay sq). All 113 SDK-mode files re-verified.

## SDK modes: constant expansion before a call (2026-10-16)
tools/gnu_reorder.py now also stops GNU as from moving the tail of a multi-instruction constant (`li.d`, `dli`) into
the delay slot of an immediately following `jal`/`jalr`; Sony's assembler left a nop there. All 101 SDK-mode files
re-verified; this finished newlib scalbn (func_00249EE0).

## GSmooth prototype (2026-10-16)
func_0011D018 is Sly 1's GSmooth: `float GSmooth(float gCur, float gTarget, float dt, SMP *psmp, float *pdgNext)`.
Declaring it with that argument order fixes argument-setup order in its callers (it alone matched func_00150160).
Check other drafts that call 0x11D018 with a different prototype.

## `// SLY2_DIVNOP` (Sony libm divisions, 2026-10-16)
Sony's libm compiler emitted every `div.s` as a `nop; nop; div.s` unit, even mid-block, and never put a division in
a delay slot. Opt-in header `// SLY2_DIVNOP` (with SLY2_ASM) makes gnu_reorder.py reproduce that (and moves a div.s
that gcc placed in a delay slot in front of its branch). Matched __ieee754_atan2f; atanf also needs the source tweak
in notes/245000.md. Use only for libm files that show the pattern.

## Junk list correction
Two `nop`s directly before a `div.s` at a function's start are the divide-hazard padding, not scrap: 0x117120 was
wrongly listed and is fixed (func_00117120 now matches).

## New compilers: ee-gcc 2.9 and 3.2 (2026-10-16)
`tools/compilers/extra/` now has ee-gcc2.9-990721, 2.9-991111, 2.9-991111a, 2.9-991111-01, 2.9-991111-01-dtls13010,
3.2-030926, 3.2-040921 (native Linux; use with `// SLY2_CC: tools/compilers/extra/<name>`). ee-gcc 2.9 emits `mult1`
and frame-teardown `j` tail calls and saves registers with `sd` natively (no SLY2_SAVES needed) — it is at least one
of Sony's SDK compilers: setD3_CHCR matched with `SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111`,
`SLY2_CFLAGS: -O2 -G0`, `SLY2_ASM: gnu-reorder-db`. The "mult1" and "j tail call" blockers in notes/23C000.md are
therefore probably solvable: retry them with ee-gcc 2.9 first. ee-gcc 3.2 also emits both but laid out setD3_CHCR differently.

## Real compiler instead of emulation (2026-10-16)
71 Sony SDK files that matched with ee-gcc 2.95.3-114 + `SLY2_SAVES: sd` emulation also match with the real Sony
compiler ee-gcc 2.9-991111 (or 991111-01) with no emulation, so they were switched to it. 25 still need the 114 +
SLY2_SAVES form (their source was tuned for it). New SDK work should start with ee-gcc 2.9.

## decomp-permuter for plain-C near-misses (2026-10-16)
`bash tools/permute.sh build/hand_wip/NAME.c [seconds] [jobs]` runs decomp-permuter (random source rewrites scored
against the original bytes; tools/perm_objdump.py stands in for MIPS objdump). Works only on plain C drafts without
inline asm (pycparser). Candidates land in /tmp/perm/NAME/output-*/source.c; ALWAYS verify a candidate with
matchtool and then clean it up into readable C before saving it to src/. Use at most 1 job per agent (2 cores total).

## FPU compare → short-loop branch (asfix, 2026-10-16)
When a short loop ends `c.cond.s; bc1x`, SN's assembler inserts its compare→branch hazard nop, which makes the loop one
instruction longer (often long enough that it is no longer padded). asfix now counts that nop. If a loop that ends in an
FPU compare/branch used to be off by one nop, recheck it: func_001E7538 matched with no source change.

## Allocation-only asm operands (policy, 2026-10-16)
In a function that already uses inline VU asm, an extra *unused* operand on an existing asm statement (e.g. listing
`"j"(dv)` twice) is accepted the same way register pins are. It emits no instructions and only changes the
register-allocation heuristics. Say so in a comment on that line. Don't add new asm statements just for this.
First example: src/hand/func_0012DA30.c.

## Float vs. int parameter order is invisible in the callee (2026-10-16)
In the EE EABI, float arguments go in $f12.. and integer/pointer arguments go in $a0.., each counted separately. So
`f(int *p, float g)` and `f(float g, int *p)` compile to identical callee code, and a matched callee's prototype
order is only a guess. The caller is where the order shows: gcc evaluates arguments in prototype order, which changes
scheduling, e.g. whether `&hit` is formed before or after a float argument that contains a call. When a caller
matches only with a different float/int order, use that order (it's the real one). If you can, update the shared
prototype and re-check the callee and its other callers. Examples: func_00117120 (floats first, func_0012E060) and
func_001A93C8 (float before HIT*, func_0013B5E8).

## Sony code: constants held in locals (2026-10-16)
When the original keeps a small constant (0/1/2/0x20…) in a callee-saved register ($s3/$s5) for a whole function, the
Sony source declared it as a local variable, e.g. `int one = 1;`, `int two = 2;`, or a reused flag like `sel`.
Write that local and use it in every place the original reads the register. This matched sceIoctl and _getAllRefs.

## Matrix-returning callees: by-value inline helper (2026-10-16)
If a function passes an M3 (3x3 matrix) returned by one call straight into another, write a `static inline` helper that
takes the M3 by value, and call it directly with the call that returns it: `Helper(GetMat(...), ...)`. This removes
the extra stack copy and matched func_00231300 and func_0014E1A8.

## Aligned difference count (2026-10-17)
`matchtool.py check` now also prints `aligned N`: the number of differences after lining up the two instruction
streams. With a positional count, one extra or missing instruction shifts every later instruction, so a draft that
is really 5 instructions off can show as 100+. RANKING.csv is sorted by the aligned count (column `aligned`). Use it
to judge how close a draft really is. Only an exact MATCH counts.

## Block-scoped locals change register assignment (2026-10-17)
Declaring a temporary inside the `if`/loop block that uses it, instead of at function scope, changes gcc's register
allocation and can fix saved-register swaps. This matched _sceCd_cd_read_intr. Related Sony libcdvd patterns: a
`static inline nopdelay()` helper and a `while(1){...continue;...break;}` retry loop (matched _sceCd_*_prechk).

## li.d / dli then one instruction then a call (gnu_reorder, 2026-10-17)
Sony's assembler also left the instruction right after a multi-instruction constant (li.d/dli) out of a following
call's delay slot. gnu_reorder now pins it, which matched libgcc __floatdisf. Check other libgcc converters
(__floatdidf etc.) with the same `li.d; insn; jal` shape.

## A target nop just before a loop head = a real loop in the source (2026-10-17)
If the target has a `nop` right before a backward-branch target that sits on an 8-byte boundary, and our build doesn't,
that nop is gcc's loop-head alignment (`.p2align 3`). gcc emits it only for real `for`/`while`/`do` loops, not for
loops built from gotos (and not after a loop rotation that gcc doesn't recognise as a loop). It is NOT an assembler
rule. Rewrite that loop as a real loop. If gcc then hoists constants out of it (loop.c), work on that next. Seen in
func_001F2500 and func_0012D508.

## SLY2_NOLOOPFIX: Sony code whose short loops are NOT padded (2026-10-17)
On the SDK assembly path, GNU as pads every short loop it assembles in reorder mode (the R5900 erratum fix). It has no
option to turn that off, and it rejects such a loop in noreorder. Sony's assembler didn't pad some loops (libmpeg
_motionComp0's IPU wait loop). Add `// SLY2_NOLOOPFIX` to the file header: gnu_reorder then emits each backward branch
whose loop body is plain single instructions as a raw `.word` in a noreorder block with a nop slot, so nothing is
padded. It's opt-in per file, so use it only when the target shows an unpadded short loop where ours has 1–2 extra
nops before the branch.

## One shared `return 0` vs several (gcc setcc) (2026-10-17)
When the target branches to a single shared `return 0` block but ours computes the result with slt/sltu/xori (a
setcc) or repeats the return, write the early exits as `goto fail;` (or `break` out of the loop) to one shared
`fail: return 0;`. That gave big drops on func_00136870, func_00154770 and func_00126A18.

## Let gcc emit qmfc2/qmtc2/mfc1 moves itself (2026-10-17)
gcc's reorg never puts an inline-asm instruction in a branch delay slot. If the target has a `qmfc2`/`qmtc2`/`mfc1`
in a delay slot (or scheduled across a branch) and ours has it as an asm statement, write the move as plain C (a
union/cast between the vector, qword and float views, or a plain assignment) so gcc emits it and can schedule it.
This matched func_0011EE08 and func_00151700.
