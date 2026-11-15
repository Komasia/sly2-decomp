/* UpdateSafeHouse (SafeHouse po.cpp, the safe house's vt slot 16, class 0x46): while the safe house is shown
 * (state 1) and the camera's menu (func_0014FD50) is not taking the pad, left / right (NStepLeftRight__FP6JOYPS2) step through
 * its allowed states (StepSafeHouse__FP9SAFEHOUSEi); otherwise a pressed button of the current state's action entry (option 1338:
 * {state, buttons, target}) opens the shop (target 0x378) or starts the target script found from the safe house. */
typedef int OID;
typedef struct SAFEHOUSEACTION {     /* option 1338, added by func_001D7748 */
    /* 0x0 */ OID oidState;          /* the state machine state it applies to */
    /* 0x4 */ int grfbtn;            /* the buttons */
    /* 0x8 */ OID oidTarget;         /* 0x378: the shop; -1: none; else a script */
} SAFEHOUSEACTION;
typedef struct SAFEHOUSE {
    /* 0x000 */ char pad0[0x180];
    /* 0x180 */ int nState;          /* field: SafeHouse port (0 left, 1 shown) */
    /* 0x184 */ void *psm;
    /* 0x188 */ void *psma;          /* field: SafeHouse port */
    /* 0x18c */ int caction;
    /* 0x190 */ SAFEHOUSEACTION aaction[12];
} SAFEHOUSE;

#define OID_SHOP 0x378
#define JOYT_FIRST 2                 /* g_grfjoyt bit: use g_joy (else the other pad, D_002E0D00) */

extern struct G g_sw;
extern char D_003DA150[];            /* the shop */
extern char D_002DE2E0[];
extern int g_grfjoyt;
extern char g_joy[];
extern char D_002E0D00[];
void UpdateSo__FP2SOf(SAFEHOUSE *psh);
int func_0014FD50(void *pv);
int NStepLeftRight__FP6JOYPS2(void *pjoy);       /* -1 / 0 / 1: left / none / right */
int GrfbtnTakePressedJoy(void *pjoy, int grfbtn) asm("GrfbtnTakePressedJoy__FP6JOYPS2Ui");
OID OidSmaCur(void *psma) asm("OidSmaCur__FP3SMA");
SAFEHOUSE *PloFindSwNearest__FP2LO3OIDii(struct G *psw, int kind, int oid, SAFEHOUSE *pshFrom);
void func_001DC260(void *pshop, int ipage);   /* open the shop at a page */
void StartScptImpl__FP2LOi(SAFEHOUSE *pscpt, int n);
void StepSafeHouse__FP9SAFEHOUSEi(SAFEHOUSE *psh, int dState);

// name: SafeHouse port (UpdateSafeHouse)
void UpdateSafeHouse__FP2LO(SAFEHOUSE *psh)
{
    char *pjoy;
    int dState;
    int iaction;
    SAFEHOUSEACTION *paction;
    UpdateSo__FP2SOf(psh);
    if (psh->nState == 0)
        return;
    if (psh->nState != 1)
        return;
    if (psh->psma == 0)
        return;
    if (func_0014FD50(D_002DE2E0))
        return;
    if (g_grfjoyt & JOYT_FIRST)
        pjoy = g_joy;
    else
        pjoy = D_002E0D00;
    dState = NStepLeftRight__FP6JOYPS2(pjoy);
    if (dState == 0) {
        for (iaction = 0; ; iaction++) {
            SAFEHOUSE *pscpt;
            paction = &psh->aaction[iaction];
            if (iaction >= psh->caction)
                return;
            if (paction->oidState != OidSmaCur(psh->psma))
                continue;
            if (!GrfbtnTakePressedJoy(pjoy, paction->grfbtn))
                continue;
            if (paction->oidTarget == -1)
                continue;
            if (paction->oidTarget == OID_SHOP) {
                func_001DC260(D_003DA150, 0);
                break;
            }
            pscpt = PloFindSwNearest__FP2LO3OIDii(&g_sw, 4, paction->oidTarget, psh);
            if (pscpt) {
                StartScptImpl__FP2LOi(pscpt, 0);
                return;
            }
        }
    } else {
        StepSafeHouse__FP9SAFEHOUSEi(psh, dState);
    }
}
