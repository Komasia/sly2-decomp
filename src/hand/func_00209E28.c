/* ReactGuardHeld (0x209E28): the guard is picked up: its reaction job (0x9C) reacts to message kind 6 with the
 * holder. */
struct AIMSG { int an[0x1C]; };   /* +0x0 the kind, +0x10 the object argument */
void *func_00205458(void *pguard, int cid);   /* PjobFind */
void *s1_memset(void *pv, int c, int cb) asm("memset");
void React__8JOBREACTP5AIMSG(void *pjobreact, struct AIMSG *pmsg);
#define AIMSGK_Held 6
// name: SafeHouse port (ReactGuardHeld)
void ReactGuardHeld__FP2LOi(void *pguard, int ploHolder) { void *pjobreact = func_00205458(pguard, 0x9C); struct AIMSG msg; s1_memset(&msg, 0, sizeof msg); msg.an[0] = AIMSGK_Held; msg.an[4] = ploHolder; React__8JOBREACTP5AIMSG(pjobreact, &msg); }
