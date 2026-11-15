/* UpdateBentleySub: the sub-object's swing mode by Bentley's state: a retracted swing animation ends the mode, a new
 * mode replaces a running one, and square (within 0.1 s, when ability 2 is allowed: vt slot 99) restarts the swing
 * when none runs or it may chain (+0xC); square let go is noted (+0x14). Layout: SafeHouse port (gang.cpp). */
#include "vtbl.h"
struct PADCTL { char pad[0x30]; int grfbtnHeld; };
struct BENTLEY { char pad[0xC]; VTENT *pvt; char pad2[0x150 - 0x10]; struct PADCTL *ppadctl; };
struct BENTLEYSUB { struct BENTLEY *pbentley; int state; int n8; int nC; int n10; int n14; char pad[0xE0 - 0x18]; void *pasega; };   /* field: SafeHouse port (gang.h BENTLEYSUB) */
int FAsegaRetracted(void *psub) asm("FAsegaRetracted__FP5ASEGA");
void SetBentleySubMode__FP7BENTLEYi(struct BENTLEYSUB *psub, int mode);
#define PADBTN_Square 0x80   /* the pad controller's square (SafeHouse gang.cpp) */
int GrfPadctlPressedWithin__FP6PADCTLUif(struct PADCTL *ppadctl, float g, int n);
void ForgetPadctlPresses__FP6PADCTLUi(struct PADCTL *ppadctl, int n);
// name: SafeHouse port (UpdateBentleySub)
void UpdateBentleySub__FP7BENTLEYi(struct BENTLEYSUB *psub, int mode)
{
    if (psub->pasega && FAsegaRetracted(psub->pasega))
        SetBentleySubMode__FP7BENTLEYi(psub, -1);
    if (mode != psub->state && psub->state != -1)
        SetBentleySubMode__FP7BENTLEYi(psub, mode);
    if (mode != -1 && (psub->state == -1 || psub->nC)) {
        if (GrfPadctlPressedWithin__FP6PADCTLUif(psub->pbentley->ppadctl, 0.1f, PADBTN_Square)) {
            struct BENTLEY *pbentley = psub->pbentley;
            if (((int (*)(void *, int))pbentley->pvt[99].pfn)(VT_THIS(pbentley, &pbentley->pvt[99]), 2)) {
                ForgetPadctlPresses__FP6PADCTLUi(psub->pbentley->ppadctl, PADBTN_Square);
                SetBentleySubMode__FP7BENTLEYi(psub, -1);
                SetBentleySubMode__FP7BENTLEYi(psub, mode);
            }
        }
    }
    if (!(psub->pbentley->ppadctl->grfbtnHeld & PADBTN_Square))
        psub->n14 = 1;
}
