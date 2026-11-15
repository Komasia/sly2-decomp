/* func_001E5000: fixes the camera target of the script's actor on plo (0: releases it). Releasing puts the target
 * offset back relative to the actor (offset = last target - actor position, z 0) so it smooths back; fixing aims the
 * target at plo (GetRunAim), raised by the actor's height, with no offset. Fields: SafeHouse port (actor.h). */
#include "relay.h"
#include "cid.h"
struct ACTORCM {
    /* 0x0000 */ char pad[0x1044];
    /* 0x1044 */ int fCmTargetFixed;
    /* 0x1048 */ float sHeight;
    /* 0x104c */ char pad2[0x1060 - 0x104C];
    /* 0x1060 */ qword posCmTarget;
    /* 0x1070 */ qword vecOffset;
};
extern qword D_002A2DD0;           /* the zero vector */
int FIsBasicDerivedFrom__FP5BASIC3CID(void *, int);
qword PosOfLo__FP2LO(struct ACTORCM *);
void GetRunAim__FP3RUNP2LOP6VECTORPf(JSG *, void *, qword *, int);
void func_001E5000(JSG *pjsg, void *plo)
{
    struct ACTORCM *pactor;
    if (pjsg->ploActor && FIsBasicDerivedFrom__FP5BASIC3CID(pjsg->ploActor, CID_ACTOR))
        pactor = (struct ACTORCM *)pjsg->ploActor;
    else
        pactor = 0;
    if (pjsg->ploCmTarget) {
        if (pactor) {
            qword posTarget = pactor->posCmTarget, pos, d;
            pactor->fCmTargetFixed = 0;
            pos = PosOfLo__FP2LO(pactor);
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(posTarget), "j"(pos));
            pactor->vecOffset = d;
            ((float *)&pactor->vecOffset)[2] = 0.0f;
        }
        pjsg->ploCmTarget = 0;
    }
    if (!plo) return;
    if (pactor) {
        pactor->fCmTargetFixed = 1;
        GetRunAim__FP3RUNP2LOP6VECTORPf(pjsg, plo, &pactor->posCmTarget, 0);
        ((float *)&pactor->posCmTarget)[2] += pactor->sHeight;
        pactor->vecOffset = D_002A2DD0;
    }
    pjsg->ploCmTarget = plo;
}
