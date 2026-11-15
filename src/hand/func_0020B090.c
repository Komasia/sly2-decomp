#include "vtbl.h"
struct AIJOB { char pad[0xC]; VTENT *pvt; };
struct GUARD { char pad[0x2C0]; long grfState; char pad2[0xFD0 - 0x2C8]; struct AIJOB *pjobMove; };
long func_00207A20(int st);   /* the state's mask bit */
int func_002040F8(struct GUARD *pguard);   /* STEP vt slot 85 */
/* GrfGuardXp (0x20B090): GUARD vt slot 85, which contacts the guard makes: all (1) in state 0x14, none while held
 * (states 0x12 / 0x13 / 0x16); otherwise its current move job's (vt slot 12), or the STEP's (0x2040F8). */
// name: SafeHouse port (GrfGuardXp)
int GrfGuardXp__FP3ALO(struct GUARD *pguard)
{
    long grfHeld;
    if (pguard->grfState & func_00207A20(0x14))
        return 1;
    grfHeld = func_00207A20(0x12) | func_00207A20(0x13) | func_00207A20(0x16);
    if (pguard->grfState & grfHeld)
        return 0;
    if (pguard->pjobMove)
        return ((int (*)(void *))pguard->pjobMove->pvt[12].pfn)(VT_THIS(pguard->pjobMove, &pguard->pjobMove->pvt[12]));
    return func_002040F8(pguard);
}
