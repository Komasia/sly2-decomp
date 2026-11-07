/* func_001E1B68: drops a reference on a relay script (JSG); the last one releases its frame and sidebag
 * references, tears the BASIC part down and returns the JSG to its slot heap. */
#include "relay.h"
#include "slotheap.h"

extern SLOTHEAP D_003E1560;   /* JSG slot heap (PrunNew__FP2LOPvP3RUN allocates from it) */

void func_00256EE0(void *ppframe, void *pframe);       /* CRefPtr<CFrame> assignment */
void func_002580A8(void *ppsidebag, void *psidebag);   /* CRefPtr<CSidebag> assignment */
void func_001334A8(void *pbasic);
void func_0011CD98(SLOTHEAP *pslotheap, void *pv);     /* free a slot */

void func_001E1B68(JSG *pjsg)
{
    int cref = pjsg->cref - 1;

    pjsg->cref = cref;
    if (cref <= 0) {
        func_00256EE0(&pjsg->basic.pframe, 0);
        func_002580A8(&pjsg->basic.psidebag, 0);
        func_001334A8(pjsg);
        func_0011CD98(&D_003E1560, pjsg);
    }
}
