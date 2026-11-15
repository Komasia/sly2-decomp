/* TellGuardCommands: tell a guard's reactions job (CID_JOBREACT) to run a command list: reaction message 5 with it. */
#include "cid.h"
struct AIMSG { int a[0x1C]; };   /* +0: the kind, +0x10: the argument */
void *func_00205458(void *pguard, int cid);   /* the guard's job of a class */
void *s1_memset(void *pv, int b, int cb) asm("memset");
void React__8JOBREACTP5AIMSG(void *pjob, struct AIMSG *paimsg);
// name: SafeHouse port (TellGuardCommands)
void TellGuardCommands__FP2LOi(void *pguard, int pcmdlist) { struct AIMSG aimsg; void *pjob = func_00205458(pguard, CID_JOBREACT); if (pjob) { s1_memset(&aimsg, 0, sizeof(aimsg)); aimsg.a[4] = pcmdlist; aimsg.a[0] = 5; React__8JOBREACTP5AIMSG(pjob, &aimsg); } }
