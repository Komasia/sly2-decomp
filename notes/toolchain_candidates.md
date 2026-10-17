# Toolchain candidates (diffs no C source can produce)

## (Claude agent) 2026-10-16 — RANKING.csv rows 2-30
None found. Every remaining diff in rows 2-30 (2-4 instructions) is an ordinary scheduling or register-allocation difference:
independent instructions in swapped order inside one basic block, or a different free register. No missing/extra nop, padding or
delay-slot pattern. Details per function are in notes/150000.md ("RANKING.csv rows 2-30 pass").

## (Claude agent) 2026-10-17 — __floatdisf (0x23C078): call slot not filled after a li.d
gcc -S (gnu-reorder-db) emits, in a reorder block right after label $L3:
    li.d  $16,6.5536e4      (expands to ori $s0,0x81E0 ; dsll32 $s0,$s0,15)
    dsra  $4,$17,32
    jal   litodp
GNU as moves the `dsra32 $a0,$s1,0` into the jal delay slot. Sony's assembler left it in place and put a `nop` in the
slot (target: ori; dsll32; dsra32; jal; nop). The existing pin_const_before_call rule only covers "li.d/dli directly
followed by jal"; this case has one ordinary instruction between the macro and the call. Candidate rule: Sony's as did
not fill a call's delay slot with the instruction right after a multi-instruction li.d/dli expansion (equivalently: it
looked back two instructions and refused when the one before the candidate came from a macro). Untested on other
SDK files; a fix would add a label after that single instruction when the next line is jal/jalr. Remaining 4 aligned
diffs of __floatdisf are all this one shift.
VERIFIED: with `// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111` (no SLY2_SAVES) the source in
build/hand_wip/__floatdisf.ee29.c becomes an exact MATCH when a label is inserted between `dsra $4,$17,32` and
`jal litodp` in the .s before gnu_reorder.assemble (tested from /tmp, tools untouched). So the rule above is the only
thing missing. (With ee-gcc2.95.3-114 the same hack leaves 2 diffs: arg-move order around the 2nd dpmul.)
Check __floatdidf and other libgcc2 converters for the same li.d; insn; jal shape.
