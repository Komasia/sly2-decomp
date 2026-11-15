#include "cid.h"
typedef int qword __attribute__((mode(TI)));
struct XFAIM { char pad[0xA0]; int pxfAimObj; };
struct ALOP { char pad[0x10]; struct ALOP *paloParent; };
struct MATRIX4V { char pad[0x30]; qword vecRow3; };
struct GUARDACTION { char pad[0x10]; struct ALOP *paloParent; int pad14; int oid; char pad2[0x7C - 0x1C]; int oidAimRef, oidAimEndRef, nAimMarker; char pad3[0x90 - 0x88]; qword dirAim;
           struct XFAIM *pxfAim; int pxfAimEnd; int pad4[1]; struct ALOP *pguard; char kinde[4]; int paseg; char pad5[0xC0 - 0xB8]; void *pkinde; };
#define OID_GUARDACTION_DEFAULT 0x2CC
void PostLoLoad__FP2LO(struct GUARDACTION *paction);
int FIsBasicDerivedFrom__FP5BASIC3CID(struct ALOP *pbasic, int cid);
void ResolveKinde__FP5KINDEP5GUARD(void *pkinde, struct ALOP *pguard);
void *func_001F4C58(struct ALOP *palo, int oid, int xfk);
float *PeventLaunch__FP5KINDEi(int paseg, int nEvent);
void CalculateAsegMatrices__FP4ASEGP3ALOP2XFT2ffP7MATRIX4T6(int paseg, struct ALOP *palo, int pxfFrom, int pxfTo, struct MATRIX4V *pmat, int pmat2, float t, float u);
/* PostLoadGuardAction (0x20AE18): GUARDACTION vt slot 15: the LO post-load; its guard is its nearest guard ancestor
 * (cid 0x38), whose kind entry it resolves (and uses, unless it is the default action oid 716); with aim records,
 * the aimed record and its end (kind 6) and the aim direction from the ASEG's matrices at its launch event. */
// name: SafeHouse port (PostLoadGuardAction)
void PostLoadGuardAction__FP2LO(struct GUARDACTION *paction)
{
    struct ALOP *palo;
    PostLoLoad__FP2LO(paction);
    for (palo = paction->paloParent; palo && !FIsBasicDerivedFrom__FP5BASIC3CID(palo, CID_STEPGUARD); palo = palo->paloParent)
        ;
    paction->pguard = palo;
    ResolveKinde__FP5KINDEP5GUARD(paction->kinde, palo);
    if (paction->oid != OID_GUARDACTION_DEFAULT)
        paction->pkinde = paction->kinde;
    if (paction->oidAimRef != -1) {
        struct MATRIX4V mat;
        int paseg;
        float *pt;
        paction->pxfAim = func_001F4C58(paction->pguard, paction->oidAimRef, 6);
        paction->pxfAimEnd = (int)func_001F4C58(paction->pguard, paction->oidAimEndRef, 6);
        paseg = paction->paseg;
        pt = PeventLaunch__FP5KINDEi(paseg, paction->nAimMarker);
        CalculateAsegMatrices__FP4ASEGP3ALOP2XFT2ffP7MATRIX4T6(paseg, paction->pguard, paction->pxfAimEnd, paction->pxfAim->pxfAimObj, &mat, 0, *pt, 1.0f);
        paction->dirAim = mat.vecRow3;
    }
}
