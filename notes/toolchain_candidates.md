# Toolchain candidates (diffs no C source can produce)

## (Claude agent) 2026-10-16 — RANKING.csv rows 2-30
None found. Every remaining diff in rows 2-30 (2-4 instructions) is an ordinary scheduling or register-allocation difference:
independent instructions in swapped order inside one basic block, or a different free register. No missing/extra nop, padding or
delay-slot pattern. Details per function are in notes/150000.md ("RANKING.csv rows 2-30 pass").
