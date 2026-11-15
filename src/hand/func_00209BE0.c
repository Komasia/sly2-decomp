/* func_00209BE0 (0x209BE0): the guard's kind table entry for exactly the state mask grfKind, or 0. */
struct KINDEM { char pad[0x10]; long grfKind; char pad2[8]; };   /* a KINDE, then its state mask */
struct GUARD { char pad[0x4C0]; int ckindem; char pad2[0xC]; struct KINDEM akindem[1]; };
struct KINDEM *func_00209BE0(struct GUARD *pguard, long grfKind) { int i; for (i = 0; i < pguard->ckindem; i++) { struct KINDEM *pkindem = &pguard->akindem[i]; if (pkindem->grfKind == grfKind) return pkindem; } return 0; }
