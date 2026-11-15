/* JOBB0::Update: let go / thrown end (no state) once the guard touches the floor; carried (or extracted) the guard makes
 * a noise (from SW +0x4020's template, its +0x54 set to 3) every D_002BE6C0 s. */
#include "clock.h"
#include "h2_aijobs.h"

extern float D_002BE6C0;                /* the carried noise's period */
struct NOISETMPL;
struct SW { char pad0[0x4020]; struct NOISETMPL *ptmpl4020; };   /* the world's noise templates (+0x4020..) */
extern struct SW g_sw;
struct NOISE { char pad0[0x54]; int n54; };
struct GUARD {
    /* 0x000 */ char pad0[0x208];
    /* 0x208 */ void *pxpFloor;         /* field: SafeHouse port (STEP +0x208: the floor contact) */
};
void Update__5AIJOB(JOBB0 *pjob);
void SetState__5JOBB0i(JOBB0 *pjob, int st);
qword PosOfLo__FP2LO(struct GUARD *pguard);
struct NOISE *func_00156698(struct NOISETMPL *ptmpl, qword pos, struct GUARD *pguard);   /* SafeHouse port: PnoiseNew */

// name: SafeHouse port (JOBB0::Update)
void Update__5JOBB0(JOBB0 *pjob)
{
    int st;
    Update__5AIJOB(pjob);
    do {
        st = pjob->stHeld;
        if (st < HELDS_Extracted) { if (st >= HELDS_LetGo && pjob->aijob.pguard->pxpFloor) SetState__5JOBB0i(pjob, HELDS_None); }
    } while (st != pjob->stHeld);
    if (st == HELDS_Carried || st == HELDS_Extracted) {
        if (g_clock.t - pjob->tNoise > D_002BE6C0) {
            struct SW *psw = &g_sw;
            pjob->tNoise = g_clock.t;
            func_00156698(psw->ptmpl4020, PosOfLo__FP2LO(pjob->aijob.pguard), pjob->aijob.pguard)->n54 = 3;
        }
    }
}
