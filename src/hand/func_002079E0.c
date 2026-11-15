/* OnGuardRegistered (0x2079E0): GUARD registration: the ALO's registration, the guard joins the active guards' list
 * (D_003E1444), and tFF8 is reset to D_002A8868. */
#include "stepguard.h"
#include "dl.h"
extern float D_002A8868;
extern struct DL D_003E1444;   /* the registered guards */
void func_001F3EA8(struct GUARD *pguard);
void AppendDlEntry__FP2DLPv(struct DL *pdl, void *pv);
// name: SafeHouse port (OnGuardRegistered)
void OnGuardRegistered__FP2LO(struct GUARD *pguard) { func_001F3EA8(pguard); AppendDlEntry__FP2DLPv(&D_003E1444, pguard); pguard->tFF8 = D_002A8868; }
