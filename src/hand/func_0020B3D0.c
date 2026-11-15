/* NGuardStatus (0x20B3D0): 2 in state 7, 1 in state 5 or 6, else 0. */
unsigned long func_00207A20(int st);   /* the state's mask bit */
struct GUARD { char pad[0x2C0]; unsigned long grfState; };
// name: SafeHouse port (NGuardStatus)
int NGuardStatus__FP5GUARD(struct GUARD *pguard) { if (pguard->grfState & func_00207A20(7)) return 2; if (pguard->grfState & (func_00207A20(5) | func_00207A20(6))) return 1; return 0; }
