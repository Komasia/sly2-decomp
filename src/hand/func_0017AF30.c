/* JOBB1::Message: after the move's own handling: message 9 (an animation event): the entry's event 0x3D resets the
 * launch count; message 12 (a contact): another launching hit (0x200000, accepted with bit 8) while not rising: the
 * entry restarts if it was done, seeks the latest launch event for the count (0x38.., at most 4), the launch starts over
 * (rising), a sound object for the count is told (its vt slot 0x33, message 5) at the guard, the guard's hit points
 * lowered (at least 5) and a noise made (SW +0x4028's template). SafeHouse port (aihit.cpp JOBB1::Message). */
#include "vtbl.h"
#include "h2_aijobs.h"

struct NOISETMPL;
struct SW { char pad0[0x4028]; struct NOISETMPL *ptmpl4028; };   /* field: SafeHouse port (template 708) */
extern struct SW g_sw;
extern void *D_002BE6D0[];              /* the launch events by count */
extern int D_002BE6E8[];                /* the sound objects' oids by count */
struct LOVT { char pad0[0xC]; VTENT *vt; };
struct ASEG;
struct ASEGA;
struct KINDE { int k; struct ASEG *paseg; struct ASEGA *pasega; int grf; };   /* field: SafeHouse port (guard.h KINDE) */
struct GUARD {
    /* 0x000 */ char pad0[0x33C];
    /* 0x33c */ int nHp;                /* field: SafeHouse port (n33C) - its hit points */
};
/* messages 9 (ASEGMSG9: n0 the ASEGA, n8 the event) and 12 (CTMSG: the rest) */
struct AIMSGV { int n0; int pad4; int nEvent; unsigned int grfFilter; int nAmount; char pad14[0x30]; unsigned int grfAccepted; };
/* the sound object's message */
struct SNDMSG { int k; int pad[7]; qword pos; qword pad2; };
int Message__7JOBMOVEiPv(JOBB1 *pjob, int msg, struct AIMSGV *pmsg);
int PasegaOfKinde__FP5KINDE(struct KINDE *pkinde);
int FKindeDone__FP5KINDE(struct KINDE *pkinde);
void StopKinde__FP5KINDE(struct KINDE *pkinde);
void PlayKinde__FP5KINDEP5GUARDif(struct KINDE *pkinde, struct GUARD *pguard, int grf, float t);
float *PeventLaunch__FP5KINDEi(struct ASEG *paseg, void *pvEvent);
void SetAsegaTime__FP5ASEGAiff(struct ASEGA *pasega, float t, float svt, int n);
void SetState__5JOBB1i(JOBB1 *pjob, int st);
struct LOVT *PloFindSwNearest__FP2LO3OIDii(struct SW *psw, int a, int oid, int c);
void *s1_memset(void *pv, int c, int cb) asm("memset");
qword PosOfLo__FP2LO(struct GUARD *pguard);
void func_00156698(struct NOISETMPL *ptmpl, qword pos, struct GUARD *pguard);   /* SafeHouse port: PnoiseNew */

// name: SafeHouse port (JOBB1::Message)
int Message__5JOBB1iPv(JOBB1 *pjob, int msg, struct AIMSGV *pmsg)
{
    if (Message__7JOBMOVEiPv(pjob, msg, pmsg)) return 1;
    switch (msg) {
    case 9:
        if (pjob->jobmove.pkinde == 0) return 0;
        if (PasegaOfKinde__FP5KINDE(pjob->jobmove.pkinde) != pmsg->n0) return 0;
        if (pmsg->nEvent == 0x3D) pjob->nLaunch = 0;
        return 0;
    case 0xC:
        {
            int i;
            float t;
            struct LOVT *plo;
            struct GUARD *pguard;
            if (pmsg->grfFilter != HITK_Launch) return 0;
            if (!(pmsg->grfAccepted & 8)) return 0;
            if (!pjob->stLaunch) return 0;
            if (FKindeDone__FP5KINDE(pjob->jobmove.pkinde)) {
                StopKinde__FP5KINDE(pjob->jobmove.pkinde);
                PlayKinde__FP5KINDEP5GUARDif(pjob->jobmove.pkinde, pjob->jobmove.aijob.pguard, pjob->jobmove.pkinde->grf | 1, 0.0f);
            }
            pjob->nLaunch++;
            t = 0.0f;
            i = 4; if (pjob->nLaunch <= 3) i = pjob->nLaunch;
            while (i > 0) {
                float *pt = PeventLaunch__FP5KINDEi(pjob->jobmove.pkinde->paseg, D_002BE6D0[i]);
                if (pt) { t = *pt; break; }
                i--;
            }
            SetAsegaTime__FP5ASEGAiff(pjob->jobmove.pkinde->pasega, t, 1.0f, 0);
            SetState__5JOBB1i(pjob, LAUNCHS_Rise);
            plo = PloFindSwNearest__FP2LO3OIDii(&g_sw, 5, D_002BE6E8[i], 0);
            if (plo) {
                struct SNDMSG sndmsg;
                VTENT *pvte;
                s1_memset(&sndmsg, 0, sizeof sndmsg);
                sndmsg.k = 5;
                sndmsg.pos = PosOfLo__FP2LO(pjob->jobmove.aijob.pguard);
                pvte = &plo->vt[0x33];
                ((void (*)(void *, struct SNDMSG *))pvte->pfn)(VT_THIS(plo, pvte), &sndmsg);
            }
            pguard = pjob->jobmove.aijob.pguard;
            {
                int nHpNew = pguard->nHp + pmsg->nAmount;
                pguard->nHp = nHpNew < 5 ? 5 : nHpNew;
            }
            func_00156698(g_sw.ptmpl4028, PosOfLo__FP2LO(pjob->jobmove.aijob.pguard), pjob->jobmove.aijob.pguard);
            return 1;
        }
    }
    return 0;
}
