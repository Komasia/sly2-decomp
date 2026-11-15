/* func_0020A010 (0x20A010): while carried (state 0x17), the carry job's +0x58; otherwise 0. */
struct JOBB1 { char pad[0x58]; int n58; };
int FGuardState(void *pguard, int st) asm("FGuardState__FP5GUARDi");
struct JOBB1 *func_00205458(void *pguard, int cid);   /* PjobFind */
int func_0020A010(void *pguard) { if (FGuardState(pguard, 0x17)) return func_00205458(pguard, 0xB1)->n58; return 0; }
