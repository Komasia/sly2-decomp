struct O { char pad[0x58]; int n; };
int FGuardState(void *p, int n) asm("FGuardState__FP5GUARDi");
struct O *func_00205458(void *p, int oid);
int func_0020A010(void *p) { if (FGuardState(p, 0x17)) return func_00205458(p, 0xB1)->n; return 0; }
