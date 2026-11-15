/* UpdateBentleyHold: the mine's phases until they settle: the summon ends with its animation; held or falling, a
 * landed mine (+0x158 2) lands, one in state 4 or the ability's button let go releases it (vt slot 76) and ends the
 * hold into a jump state 0xB; else falling once airborne for 0.1 s. Layout: SafeHouse port (gang.h BENTLEY). */
#include "vtbl.h"
struct CARRY { char pad[0xC]; VTENT *vt; char pad1[0x158 - 0x10]; int state; char pad2[0x1A0 - 0x15C]; int n1A0; };   /* the carried object (cid 0x64, SafeHouse CARRY: +0x158 its state) */
struct ABILITY { int id; };   /* field: SafeHouse port */
struct BENTLEY { char pad[0x150]; void *ppadctl; char pad0[0x20C - 0x154]; float tJump20C; char padA[0x2C0 - 0x210]; char jump[0x1030 - 0x2C0]; void *pasega1030;
    char pad1[0x13D0 - 0x1034]; int state; char pad2[0x16B0 - 0x13D4]; int n16B0; struct ABILITY *pabil16B4; char pad3[0x186C - 0x16B8]; struct CARRY *ploCarried; };
#include "clock.h"
int FAsegaRetracted(void *pv) asm("FAsegaRetracted__FP5ASEGA");
void SetBentleyHold__FP7BENTLEYi(struct BENTLEY *pbentley, int n);
void LandCarry__FP2LOT0(struct CARRY *pcarry, int n);
int GrfAbilityButton__FP5ACTORi(struct BENTLEY *pbentley, int n);
int func_001C4728(void *pv, int n);
void ReleaseBentleyCarried__FP7BENTLEY(struct BENTLEY *pbentley);
void SetJumpKind__FP4JUMPiiP2LO(void *pv, int a, int b, int c);
// name: SafeHouse port (UpdateBentleyHold)
void UpdateBentleyHold__FP7BENTLEY(struct BENTLEY *pbentley)
{
    int n16B0Old;
    for (;;) {
        n16B0Old = pbentley->n16B0;
        switch (n16B0Old) {
        case 0:
            if (FAsegaRetracted(pbentley->pasega1030))
                SetBentleyHold__FP7BENTLEYi(pbentley, 1);
            break;
        case 1:
        case 2: {
            struct CARRY *pcarry = pbentley->ploCarried;
            if (pcarry->state == 2) {
                LandCarry__FP2LOT0(pcarry, pcarry->n1A0);
                goto common;
            }
            if (pcarry->state == 4 || !func_001C4728(pbentley->ppadctl, GrfAbilityButton__FP5ACTORi(pbentley, pbentley->pabil16B4->id) | 0x10)) {
                ((void (*)(void *, int))pcarry->vt[76].pfn)(VT_THIS(pcarry, &pcarry->vt[76]), 1);
            common:
                ReleaseBentleyCarried__FP7BENTLEY(pbentley);
                SetJumpKind__FP4JUMPiiP2LO(pbentley->jump, 0xB, 0, 0);
            } else if (0.1f < g_clock.t - pbentley->tJump20C) {
                SetBentleyHold__FP7BENTLEYi(pbentley, 2);
            } else {
                SetBentleyHold__FP7BENTLEYi(pbentley, 1);
            }
            break;
        }
        }
        if (pbentley->n16B0 == n16B0Old || pbentley->state != 6)
            break;
    }
}
