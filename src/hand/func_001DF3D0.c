/* func_001DF3D0: the laser's own part of UpdateLaser: advances every moving (path) endpoint along its motion profile
 * by dt times the laser's speed multiplier (wrapping into the next segment when the current one runs out), marks the
 * laser's bound-box attachment dirty (once: flag 2, appended to the dirty list D_003E11C4), and refreshes the
 * lengths of each moved beam that has no contacts. */
#include "clock.h"
#include "h3_laser.h"

typedef struct OXA { char unk_0x0[0x70]; unsigned long grf; } OXA;   /* bound-box attachment (SafeHouse port) */
#define GRFOXA_Dirty 0x2
typedef struct LASER {
    /* 0x000 */ char unk_so[0xEC];    /* the SO base */
    /* 0x0ec */ OXA *poxa;
    /* 0x0f0 */ char unk_so_f0[0x198 - 0xF0];
    /* 0x198 */ int cpair;
    /* 0x19c */ LASERPAIR *apair;
    /* 0x1a0 */ char unk_0x1a0[0x1C0 - 0x1A0];
    /* 0x1c0 */ float rSpeed;         /* moving-endpoint speed multiplier */
} LASER;
typedef struct { int an[8]; } ENDPOS;
extern char D_003E11C4[];          /* the dirty attachment list (DL) */
float fmodf(float, float);
void AppendDlEntry__FP2DLPv(void *pdl, OXA *poxa);
void func_001DEF98(LASER *plaser, LASERPAIR *ppair, ENDPOS *pendpos, float *psLength);   /* endpoint positions */
void func_001DF3D0(LASER *plaser)
{
    int ipair;
    for (ipair = 0; ipair < plaser->cpair; ipair++) {
        LASERPAIR *ppair = &plaser->apair[ipair];
        int fMoved = 0;
        unsigned int iend;
        for (iend = 0; iend < 2; iend++) {
            LASEREND *pend = &ppair->aend[iend];
            LASERSEG *pseg;
            float t;
            if (pend->kind != LASERENDK_Path)
                continue;
            pseg = &pend->track.motion.aseg[pend->track.motion.iseg];
            pseg->elapsed = t = pseg->elapsed + plaser->rSpeed * g_clock.dt;
            if (pseg->duration < t) {
                float tOver = fmodf(t, pseg->duration);
                pend->track.motion.iseg = (pend->track.motion.iseg + 1) % pend->track.motion.cseg;
                pseg = &pend->track.motion.aseg[pend->track.motion.iseg];
                pseg->elapsed = tOver;
            }
            pend->track.s = pseg->start + pseg->speed * pseg->elapsed + pseg->accel * pseg->elapsed * pseg->elapsed * 0.5f;
            if (!(plaser->poxa->grf & GRFOXA_Dirty)) {
                plaser->poxa->grf |= GRFOXA_Dirty;
                AppendDlEntry__FP2DLPv(D_003E11C4, plaser->poxa);
            }
            fMoved = 1;
        }
        if (fMoved && ppair->pxpFirst == 0) {
            ENDPOS endpos;
            float sLength;
            func_001DEF98(plaser, ppair, &endpos, &sLength);
            ppair->sLength = ppair->sVisible = sLength;
        }
    }
}
