struct S { char pad[0x298]; int a; char pad2[0x90]; int b; };
int FGuardState(struct S *p, int n) asm("FGuardState__FP5GUARDi");
int func_00207598(struct S *p) { if (p->b || p->a) return 1; return FGuardState(p, 0x2A) != 0; }
