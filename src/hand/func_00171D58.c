/* func_00171D58: send a guard's reactions job (CID_JOBREACT) reaction message 1 (no argument). */
#include "cid.h"
struct AIMSG { int a[0x1C]; };
void *func_00205458(void *pguard, int cid);
void *s1_memset(void *pv, int b, int cb) asm("memset");
void React__8JOBREACTP5AIMSG(void *pjob, struct AIMSG *paimsg);
void func_00171D58(void *pguard) { struct AIMSG aimsg; void *pjob = func_00205458(pguard, CID_JOBREACT); if (pjob) { s1_memset(&aimsg, 0, sizeof(aimsg)); aimsg.a[0] = 1; React__8JOBREACTP5AIMSG(pjob, &aimsg); } }
