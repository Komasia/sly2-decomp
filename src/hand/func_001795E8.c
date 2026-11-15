/* JOBHIT::Update: the move goes on, the guard's held noise follows it; at tJolt the camera jolts, at tEntryHit the
 * guard's body entries strike back (entry mode 2). */
#include "clock.h"
#include "h2_aijobs.h"

struct CM;
extern struct CM g_cm;
struct NOISE { char pad0[0x20]; qword pos; };
struct GUARD {
    /* 0x000 */ char pad0[0x35C];
    /* 0x35c */ struct NOISE *pnoise;   /* field: SafeHouse port - the guard's held noise */
};
void Update__7JOBMOVE(JOBHIT *pjob);
qword PosOfLo__FP2LO(struct GUARD *pguard);
void JoltCm__FP2CMi(struct CM *pcm, int n);
void SetAloEntryMode__FP3ALOi(struct GUARD *pguard, int mode);

// name: SafeHouse port (JOBHIT::Update)
void Update__6JOBHIT(JOBHIT *pjob)
{
    float t;
    Update__7JOBMOVE(pjob);
    { struct GUARD *pguard = pjob->jobmove.aijob.pguard; struct NOISE *pnoise = pguard->pnoise; pnoise->pos = PosOfLo__FP2LO(pguard); }
    t = g_clock.t + 0.0001f;
    if (pjob->tJolt < t) { pjob->tJolt = 3.40282346638528859812e+38f; JoltCm__FP2CMi(&g_cm, 0); }
    if (pjob->tEntryHit < t) { pjob->tEntryHit = 3.40282346638528859812e+38f; SetAloEntryMode__FP3ALOi(pjob->jobmove.aijob.pguard, 2); }
}
