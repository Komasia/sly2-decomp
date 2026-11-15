/* SetBentleyState: Bentley leaves his state (records' modes, the jump's / interaction's / damage's / climb's / hold's /
 * carry's / throw's end; leaving the jump into a stand, walk or interaction fires the landing explosion +0x16D0 / +0x16D4;
 * the gaits keep their phase) and enters the new one: its animation (an ASEG applied over the old one, or a state of the
 * idle state machine +0x1028 / +0x102C) with its apply flags, time and speed, the look mask, the gaits' feet reset.
 * Layout: SafeHouse port (gang.h BENTLEY, actor.h ACTOR); offset names where SafeHouse has none. */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct VO { char pad[0xC]; VTENT *vt; };
struct ASEG { char pad[0x74]; float tMax; };   /* field: SafeHouse port */
struct GAITA { int x0; struct ASEG *paseg; };   /* a gait's head: its ASEG at +4 */
struct ASEGA { char pad[0x14]; struct ASEG *paseg; char pad1[0x1C - 0x18]; float t; };   /* field: SafeHouse port (asega.h) */
struct BENTLEY {
    char pad[0xC]; VTENT *vt; char pad0[0x58 - 0x10]; void *pxfPos; void *pxfRot;
    char pad1[0x190 - 0x60]; qword vel; float uGaitPhase; char pad2[0x2C0 - 0x1A4]; char jump[0x4C0 - 0x2C0];
    char interact[8]; int n4C8; char pad3[0xDF0 - 0x4CC]; char damage[0xF00 - 0xDF0]; char binoc[0xF50 - 0xF00];
    char climb[0x1028 - 0xF50]; void *psmIdle; void *psm102C; struct ASEGA *pasega1030; int psma1034;
    char pad4[0x108C - 0x1038]; int n108C; char pad5[0x11B0 - 0x1090]; char jtthrow[0x1320 - 0x11B0];
    struct GAITA gaitWalk; char pad6[0x1374 - 0x1328]; struct ASEG *paseg1374; char pad7[0x13D0 - 0x1378];
    int state; float tState; char pad8[0x14E0 - 0x13D8]; struct ASEG *paseg14E0; char pad9[0x1600 - 0x14E4];
    struct GAITA gaitRun; char pad10[0x16D0 - 0x1608]; struct VO *pexpl16D0; struct VO *pexpl16D4;
    char pad11[0x181C - 0x16D8]; int f181C; struct ASEG *paseg1820; char pad12[0x186C - 0x1824]; struct VO *ploCarried;
    char pad13[0x1878 - 0x1870]; struct ASEG *paseg1878;
};
#include "clock.h"
extern qword D_002A2DD0;
void SetXfMode__FP3ALOP2XFi(struct BENTLEY *, void *, int);
void ActorNextLookTime(struct BENTLEY *) asm("ActorNextLookTime__FP5ACTOR");
void ExplodeExpl__FP4EXPL(struct VO *);
void SetJumpAnimState__FP4JUMPiP2LO(void *, int, int);
void SetInteractState__FP5ACTORi(void *, int);
void SetDamageState__FP5ACTORi(void *, int);
void SetClimbState__FP5ACTORi(void *, int);
void ReleaseBentleyCarried__FP7BENTLEY(struct BENTLEY *);
void SetBentleyHold__FP7BENTLEYi(struct BENTLEY *, int);
void SetBentleyCarried__FP7BENTLEYi(struct BENTLEY *, int);
void SetJtThrowState__FP7JTTHROWi(void *, int);
int IsmsFindSmOptional(void *, int) asm("IsmsFindSmOptional__FP2SM3OID");
int GrfActorLookMask__FP5ACTOR(struct BENTLEY *);
void ActorSetLookFlag__FP5ACTORi(struct BENTLEY *, int);
void ResetGaitFeet__FP4GAIT(struct GAITA *);
void SetBinocState__FP5ACTORi(void *, int);
void RetractAsegaPp__FPP5ASEGA(void *);
void ClearSmaHandle__FPP3SMA(void *);
void ApplyAsegCur(struct ASEG *, struct BENTLEY *, int, void *, float, float) asm("ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA");
void ReplaceSmaHandleMask__FP2SMi3OIDiUiPP3SMA(void *, struct BENTLEY *, int, int, int, void *);

#define VCALL0(pbentley, grfapl) ((void (*)(void *))(pbentley)->vt[grfapl].pfn)(VT_THIS((pbentley), &(pbentley)->vt[grfapl]))
#define VCALL1(pbentley, grfapl, a) ((void (*)(void *, int))(pbentley)->vt[grfapl].pfn)(VT_THIS((pbentley), &(pbentley)->vt[grfapl]), a)

// name: SafeHouse port (SetBentleyState)
void SetBentleyState__FP7BENTLEYi(struct BENTLEY *pbentley, int stateNew)
{
    int stateOld;
    struct ASEG *paseg;
    void *psm;
    int grfLook;
    int oidState;
    int grfapl;
    float t;
    float svt;
    struct GAITA *pgait;

    if (stateNew == pbentley->state)
        return;
    switch (pbentley->state) {
    case 0:
        SetXfMode__FP3ALOP2XFi(pbentley, pbentley->pxfPos, 2);
        SetXfMode__FP3ALOP2XFi(pbentley, pbentley->pxfRot, 2);
        ActorNextLookTime(pbentley);
        break;
    case 9:
    case 10:
    case 11:
        SetXfMode__FP3ALOP2XFi(pbentley, pbentley->pxfPos, 2);
        SetXfMode__FP3ALOP2XFi(pbentley, pbentley->pxfRot, 2);
        break;
    case 2:
        if (pbentley->n108C == 0) {
            struct VO *po = 0;
            if (stateNew >= 0) {
                if (stateNew < 2) {
                    po = pbentley->pexpl16D0;
                } else if (stateNew == 3) {
                    switch (pbentley->n4C8) {
                    case 1:
                        break;
                    case 3:
                    case 4:
                        po = pbentley->pexpl16D4;
                        break;
                    default:
                        po = pbentley->pexpl16D0;
                        break;
                    }
                }
            }
            if (po) {
                VCALL0(po, 8);
                ExplodeExpl__FP4EXPL(po);
                VCALL0(po, 9);
            }
        }
        SetJumpAnimState__FP4JUMPiP2LO(pbentley->jump, -1, 0);
        break;
    case 3:
        SetInteractState__FP5ACTORi(pbentley->interact, -1);
        break;
    case 4:
        SetDamageState__FP5ACTORi(pbentley->damage, -1);
        break;
    case 13:
        SetClimbState__FP5ACTORi(pbentley->climb, -1);
        break;
    case 6:
        if (pbentley->ploCarried) {
            VCALL1(pbentley->ploCarried, 76, 1);
            ReleaseBentleyCarried__FP7BENTLEY(pbentley);
        }
        SetBentleyHold__FP7BENTLEYi(pbentley, -1);
        break;
    case 8:
        SetBentleyCarried__FP7BENTLEYi(pbentley, -1);
        VCALL1(pbentley, 79, 1);
        break;
    case 1:
    case 7:
        pbentley->uGaitPhase = pbentley->pasega1030->t / pbentley->pasega1030->paseg->tMax;
        break;
    case 12:
        SetJtThrowState__FP7JTTHROWi(pbentley->jtthrow, -1);
        break;
    }
    stateOld = pbentley->state;
    pbentley->state = stateNew;
    paseg = 0;
    psm = 0;
    grfapl = 1;
    oidState = -1;
    grfLook = 4;
    t = 0.0f;
    svt = 1.0f;
    pbentley->tState = g_clock.t;
    switch (stateNew) {
    case 0:
        SetXfMode__FP3ALOP2XFi(pbentley, pbentley->pxfPos, 1);
        SetXfMode__FP3ALOP2XFi(pbentley, pbentley->pxfRot, 1);
        if (pbentley->f181C) {
            paseg = pbentley->paseg1820;
            grfapl = 9;
        } else {
            psm = pbentley->psmIdle;
            if (stateOld != 2)
                oidState = stateOld != 7 ? 0x175 : 0x176;
            else
                oidState = 0x178;
            if (IsmsFindSmOptional(psm, oidState) < 0)
                oidState = -1;
        }
        pbentley->vel = D_002A2DD0;
        grfLook = GrfActorLookMask__FP5ACTOR(pbentley);
        ActorSetLookFlag__FP5ACTORi(pbentley, 1);
        break;
    case 1:
        paseg = pbentley->gaitWalk.paseg;
        pgait = &pbentley->gaitWalk;
        goto L1;
    case 7:
        paseg = pbentley->gaitRun.paseg;
        pgait = &pbentley->gaitRun;
    L1:
        grfapl = 9;
        t = pbentley->uGaitPhase * paseg->tMax;
        ResetGaitFeet__FP4GAIT(pgait);
        break;
    case 4:
        SetBinocState__FP5ACTORi(pbentley->binoc, -1);
        break;
    case 5:
        paseg = pbentley->paseg14E0;
        grfapl = 9;
        break;
    case 13:
        SetClimbState__FP5ACTORi(pbentley->climb, 0);
        return;
    case 6:
        SetBentleyHold__FP7BENTLEYi(pbentley, 0);
        return;
    case 8:
        SetBentleyCarried__FP7BENTLEYi(pbentley, 0);
        return;
    case 9:
        psm = pbentley->psm102C;
    case 10:
    case 11:
        SetXfMode__FP3ALOP2XFi(pbentley, pbentley->pxfPos, 1);
        SetXfMode__FP3ALOP2XFi(pbentley, pbentley->pxfRot, 1);
        pbentley->vel = D_002A2DD0;
        break;
    case 14:
        paseg = pbentley->paseg1878;
        if (!paseg) {
            paseg = pbentley->paseg1374;
            svt = 1.5f;
        }
        grfapl = 9;
        break;
    case 12:
        return;
    }
    RetractAsegaPp__FPP5ASEGA(&pbentley->pasega1030);
    ClearSmaHandle__FPP3SMA(&pbentley->psma1034);
    ApplyAsegCur(paseg, pbentley, grfapl, &pbentley->pasega1030, t, svt);
    ReplaceSmaHandleMask__FP2SMi3OIDiUiPP3SMA(psm, pbentley, oidState, grfapl, grfLook, &pbentley->psma1034);
    VCALL0(pbentley, 90);
}
