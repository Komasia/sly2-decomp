/* OnGuardUnregistered (0x2079A0): GUARD vt slot 22: the ALO's unregistration, the guard leaves the active guards'
 * list (D_003E1444), and tFF8 notes when. */
#include "stepguard.h"
#include "clock.h"
#include "dl.h"
extern struct DL D_003E1444;   /* the registered guards */
void func_001F3E00(struct GUARD *pguard);
void RemoveDlEntry__FP2DLPv(struct DL *pdl, void *pv);
// name: SafeHouse port (OnGuardUnregistered)
void OnGuardUnregistered__FP2LO(struct GUARD *pguard) { func_001F3E00(pguard); RemoveDlEntry__FP2DLPv(&D_003E1444, pguard); pguard->tFF8 = g_clock.t; }
