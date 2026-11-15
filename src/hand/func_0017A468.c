/* OffsetUseByHands: the use's place offset for the guard's hands: pos minus the guard's +0x60 object's +0x30 vector,
 * minus the hands' point (+0xF90's +0x90) turned by the use's orientation mat. */
#include "h2_aijobs.h"

struct OBJ60 { char pad0[0x30]; qword vec; };
struct LOHANDS { char pad0[0x90]; qword pos; };
struct GUARD {
    /* 0x000 */ char pad0[0x60];
    /* 0x060 */ struct OBJ60 *p60;
    /* 0x064 */ char pad64[0xF90 - 0x64];
    /* 0xf90 */ struct LOHANDS *ploHands;   /* field: SafeHouse port (ploF90: its hands' point) */
};

// name: SafeHouse port (OffsetUseByHands)
void OffsetUseByHands__FP6JOBUSE(JOBUSE *pjob)
{
    struct GUARD *pguard = pjob->jobmove.aijob.pguard;
    qword *mat = pjob->mat;
    qword d, t;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(pjob->pos.q), "j"(pguard->p60->vec));
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(t) : "j"(pguard->ploHands->pos), "j"(mat[0]), "j"(mat[1]), "j"(mat[2]));
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(d), "j"(t));
    pjob->pos.q = d;
}
