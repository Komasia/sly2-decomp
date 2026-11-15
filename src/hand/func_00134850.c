/* UpdateBentleyTransitions: Bentley's state changes until they settle: from the ground states (0 stand, 1 walk with R1,
 * 7 run, 5 near a target) the target in reach, a jump (cross), the binocucom (R3), triangle's ability (state 6), an
 * interaction (circle) or the stick's state; the jump, interaction, damage, climb, hold, carry (8), throw (12) and
 * animation (10) states' own transitions; state 14 ends after D_002BC930 s; the second state machine each round.
 * Layout: SafeHouse port (gang.h BENTLEY, actor.h ACTOR); n/g/p + offset names where SafeHouse has none. */
#include "vtbl.h"
struct PADCTL { char pad[0x1C]; float uStick; char pad1[0x30 - 0x20]; int grfbtnHeld; };   /* the stick's deflection, the buttons held */
struct BENTLEY {
    char pad[0xC]; VTENT *vt; char pad0[0x150 - 0x10]; struct PADCTL *ppadctl;
    char pad1[0x20C - 0x154]; float tJump20C; char pad2[0x2C0 - 0x210]; char jump[0x4C0 - 0x2C0];
    int interact; char pad3[0x4C8 - 0x4C4]; int n4C8; char pad4[0xDF0 - 0x4CC]; char damage[0xF00 - 0xDF0];
    char binoc[0xF50 - 0xF00]; char climb[0x1030 - 0xF50]; void *pasega1030; void *psma1034; char pad5[0x11B0 - 0x1038];
    char jtthrow[0x13D0 - 0x11B0]; int state; float tState; char pad6[0x16B4 - 0x13D8]; int pabil16B4;
    char pad7[0x1870 - 0x16B8]; int n1870;
};
#include "clock.h"
extern float D_002BC930;
void SetJumpKind__FP4JUMPiiP2LO(void *pv, int a, int b, int c);
int FActorTargetInReach__FP5ACTORi(struct BENTLEY *pbentley, int n);
void SetBentleyState__FP7BENTLEYi(struct BENTLEY *pbentley, int n);
int GrfPadctlTakePressed__FP6PADCTL(struct PADCTL *ppadctl, int grf, float g);
int GrfPadctlPressedWithin__FP6PADCTLUif(struct PADCTL *ppadctl, int grf, float g);
void ForgetPadctlPresses__FP6PADCTLUi(struct PADCTL *ppadctl, int grf);
void UpdateJumpTransitions__FP4JUMP(void *pv);
void UpdateInteractTransitions__FP5ACTOR(void *pv);
void UpdateDamageTransitions__FP5ACTOR(void *pv);
void OpenBinoc__FP5ACTORiP2LOT2(void *pv, int a, int b, int c);
void FInteractCircle__FP5ACTOR(void *pv, int a, int b);
int CbFromSaak(struct BENTLEY *pbentley, int n) asm("CbFromSaak__F4SAAK");   /* SafeHouse: PabilFind, the ability of id n */
void UpdateClimbTransitions__FP5ACTOR(void *pv);
void UpdateBentleyHold__FP7BENTLEY(struct BENTLEY *pbentley);
void func_001367D8(struct BENTLEY *pbentley);
void UpdateJtThrow__FP7JTTHROW(void *pv);
int FAsegaRetracted(void *pv) asm("FAsegaRetracted__FP5ASEGA");
int FSmaRetracted(void *pv) asm("FSmaRetracted__FP3SMA");
void UpdateBentleyState2__FP7BENTLEY(struct BENTLEY *pbentley);

/* the pad controller's buttons (SafeHouse gang.cpp / jump.cpp) */
#define PADBTN_R1 0x8
#define PADBTN_Triangle 0x10
#define PADBTN_Circle 0x20
#define PADBTN_Cross 0x40
#define PADBTN_R3 0x400
/* vt slot 99: may Bentley start the action n (0x136870) */
#define VCALL99(pbentley, a) ((int (*)(void *, int))(pbentley)->vt[99].pfn)(VT_THIS((pbentley), &(pbentley)->vt[99]), a)

// name: SafeHouse port (UpdateBentleyTransitions)
void UpdateBentleyTransitions__FP7BENTLEY(struct BENTLEY *pbentley)
{
    int s;
    do {
        s = pbentley->state;
        switch (s) {
        case 2:
        case 4:
        case 6:
        case 8:
        case 9:
        case 10:
        case 11:
        case 13:
        case 14:
            break;
        case 3:
            if (pbentley->n4C8 == 1 || pbentley->n4C8 == 12)
                break;
            if (0.1f < g_clock.t - pbentley->tJump20C)
                SetJumpKind__FP4JUMPiiP2LO(pbentley->jump, 0, 0, 0);
            break;
        case 5:
        case 7:
        case 12:
        default:
            if (0.1f < g_clock.t - pbentley->tJump20C)
                SetJumpKind__FP4JUMPiiP2LO(pbentley->jump, 0, 0, 0);
            break;
        }
        switch (pbentley->state) {
        case 0:
        case 1:
        case 7:
            if (!(pbentley->ppadctl->grfbtnHeld & PADBTN_R1) && FActorTargetInReach__FP5ACTORi(pbentley, 0)) {
                SetBentleyState__FP7BENTLEYi(pbentley, 5);
            } else if (GrfPadctlTakePressed__FP6PADCTL(pbentley->ppadctl, PADBTN_Cross, 0.1f)) {
                SetJumpKind__FP4JUMPiiP2LO(pbentley->jump, 1, 0, 0);
            } else if (GrfPadctlPressedWithin__FP6PADCTLUif(pbentley->ppadctl, PADBTN_R3, 0.15f) && VCALL99(pbentley, 3)) {
                ForgetPadctlPresses__FP6PADCTLUi(pbentley->ppadctl, PADBTN_R3);
                OpenBinoc__FP5ACTORiP2LOT2(pbentley->binoc, 0, 0, 0);
            } else if (GrfPadctlPressedWithin__FP6PADCTLUif(pbentley->ppadctl, PADBTN_Triangle, 0.15f) && VCALL99(pbentley, pbentley->n1870)) {
                ForgetPadctlPresses__FP6PADCTLUi(pbentley->ppadctl, PADBTN_Triangle);
                pbentley->pabil16B4 = CbFromSaak(pbentley, pbentley->n1870);
                SetBentleyState__FP7BENTLEYi(pbentley, 6);
            } else if (GrfPadctlTakePressed__FP6PADCTL(pbentley->ppadctl, PADBTN_Circle, 0.2f)) {
                FInteractCircle__FP5ACTOR(&pbentley->interact, 0xF8FE, 0);
            } else {
                float g = pbentley->ppadctl->uStick;
                if ((pbentley->state == 0 && 0.1f < g) || (pbentley->state != 0 && 0.0f < g)) {
                    if (pbentley->ppadctl->grfbtnHeld & PADBTN_R1)
                        SetBentleyState__FP7BENTLEYi(pbentley, 1);
                    else
                        SetBentleyState__FP7BENTLEYi(pbentley, 7);
                } else {
                    SetBentleyState__FP7BENTLEYi(pbentley, 0);
                }
            }
            break;
        case 2:
            UpdateJumpTransitions__FP4JUMP(pbentley->jump);
            if (GrfPadctlPressedWithin__FP6PADCTLUif(pbentley->ppadctl, PADBTN_Triangle, 0.15f) && VCALL99(pbentley, pbentley->n1870)) {
                ForgetPadctlPresses__FP6PADCTLUi(pbentley->ppadctl, PADBTN_Triangle);
                pbentley->pabil16B4 = CbFromSaak(pbentley, pbentley->n1870);
                SetBentleyState__FP7BENTLEYi(pbentley, 6);
            }
            break;
        case 3:
            UpdateInteractTransitions__FP5ACTOR(&pbentley->interact);
            break;
        case 4:
            UpdateDamageTransitions__FP5ACTOR(pbentley->damage);
            break;
        case 5:
            if ((pbentley->ppadctl->grfbtnHeld & PADBTN_R1) || !FActorTargetInReach__FP5ACTORi(pbentley, 1)) {
                SetBentleyState__FP7BENTLEYi(pbentley, 0);
            } else if (GrfPadctlTakePressed__FP6PADCTL(pbentley->ppadctl, PADBTN_Cross, 0.1f)) {
                SetJumpKind__FP4JUMPiiP2LO(pbentley->jump, 1, 0, 0);
            } else if (GrfPadctlPressedWithin__FP6PADCTLUif(pbentley->ppadctl, PADBTN_R3, 0.15f) && VCALL99(pbentley, 3)) {
                ForgetPadctlPresses__FP6PADCTLUi(pbentley->ppadctl, PADBTN_R3);
                OpenBinoc__FP5ACTORiP2LOT2(pbentley->binoc, 0, 0, 0);
            } else if (GrfPadctlTakePressed__FP6PADCTL(pbentley->ppadctl, PADBTN_Circle, 0.2f)) {
                FInteractCircle__FP5ACTOR(&pbentley->interact, 0xF8FE, 0);
            } else if (GrfPadctlPressedWithin__FP6PADCTLUif(pbentley->ppadctl, PADBTN_Triangle, 0.15f) && VCALL99(pbentley, pbentley->n1870)) {
                ForgetPadctlPresses__FP6PADCTLUi(pbentley->ppadctl, PADBTN_Triangle);
                pbentley->pabil16B4 = CbFromSaak(pbentley, pbentley->n1870);
                SetBentleyState__FP7BENTLEYi(pbentley, 6);
            }
            break;
        case 13:
            UpdateClimbTransitions__FP5ACTOR(pbentley->climb);
            break;
        case 6:
            UpdateBentleyHold__FP7BENTLEY(pbentley);
            break;
        case 8:
            func_001367D8(pbentley);
            break;
        case 12:
            UpdateJtThrow__FP7JTTHROW(pbentley->jtthrow);
            break;
        case 10:
            if (pbentley->pasega1030 && FAsegaRetracted(pbentley->pasega1030))
                SetBentleyState__FP7BENTLEYi(pbentley, 0);
            else if (pbentley->psma1034 && FSmaRetracted(pbentley->psma1034))
                SetBentleyState__FP7BENTLEYi(pbentley, 0);
            break;
        case 14:
            if (D_002BC930 < g_clock.t - pbentley->tState)
                SetBentleyState__FP7BENTLEYi(pbentley, 0);
            break;
        }
        UpdateBentleyState2__FP7BENTLEY(pbentley);
    } while (pbentley->state != s);
}
