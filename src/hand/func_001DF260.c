/* ApplyLaserContacts: recomputes every beam's lengths. A beam without contacts is fully visible (sLength = sVisible
 * = endpoint distance); otherwise it is cut at its nearest contact, and the object hit there is sent a contact message
 * (CTMSG, filter 0x1000, state -10: the laser's damage) through PaloAcceptContact. */
#include "h3_laser.h"

typedef struct XP {                /* contact (fields: SafeHouse port, laser.cpp) */
    /* 0x00 */ void *psoe;         /* the laser-side shape entry */
    /* 0x04 */ char unk_0x4[0x10 - 4];
    /* 0x10 */ qword pos;          /* the contact point */
    /* 0x20 */ char unk_0x20[0x4C - 0x20];
    /* 0x4c */ void *paloOther;    /* the object hit */
    /* 0x50 */ char unk_0x50[0xA0 - 0x50];
    /* 0xa0 */ float sBeam;        /* distance from the beam's first endpoint (AddLaserContacts) */
    /* 0xa4 */ char unk_0xa4[0xAC - 0xA4];
    /* 0xac */ struct XP *pxpNext;
} XP;
typedef struct LASER {
    /* 0x000 */ char unk_so[0x198];   /* the SO base */
    /* 0x198 */ int cpair;
    /* 0x19c */ LASERPAIR *apair;
} LASER;
typedef struct CTMSG {             /* contact message (fields: SafeHouse port) */
    /* 0x00 */ LASER *ploSender;
    /* 0x04 */ void *pvOther;
    /* 0x08 */ void *ploReceiver;
    /* 0x0c */ int grfFilter;
    /* 0x10 */ int nState;
    /* 0x14 */ int unk_0x14[3];
    /* 0x20 */ qword pos;
    /* 0x30 */ char unk_0x30[0x30];
} CTMSG;
typedef struct { qword apos[2]; } ENDPOS;
#define GRFCTMSG_Laser 0x1000
#define NSTATE_LaserHit -10
void func_001DEF98(LASER *plaser, LASERPAIR *ppair, ENDPOS *pendpos, float *psLength);   /* endpoint positions */
void *s1_memset(void *, int, int) asm("memset");
void PaloAcceptContact__FP5CTMSG(CTMSG *pctmsg);
// name: SafeHouse port (ApplyLaserContacts)
void ApplyLaserContacts__FP3ALO(LASER *plaser)
{
    int ipair;
    for (ipair = 0; ipair < plaser->cpair; ipair++) {
        ENDPOS endpos;
        CTMSG ctmsg;
        float sLength;
        LASERPAIR *ppair = &plaser->apair[ipair];
        func_001DEF98(plaser, ppair, &endpos, &sLength);
        if (ppair->pxpFirst == 0) {
            ppair->sLength = ppair->sVisible = sLength;
        } else {
            float sNearest = sLength;
            XP *pxpNearest = 0;
            XP *pxp;
            for (pxp = (XP *)ppair->pxpFirst; pxp; pxp = pxp->pxpNext) {
                if (pxp->sBeam < sNearest) {
                    sNearest = pxp->sBeam;
                    pxpNearest = pxp;
                }
            }
            s1_memset(&ctmsg, 0, sizeof(ctmsg));
            ctmsg.ploSender = plaser;
            ctmsg.pvOther = pxpNearest->psoe;
            ctmsg.ploReceiver = pxpNearest->paloOther;
            ctmsg.grfFilter = GRFCTMSG_Laser;
            ctmsg.nState = NSTATE_LaserHit;
            ctmsg.pos = pxpNearest->pos;
            PaloAcceptContact__FP5CTMSG(&ctmsg);
            ppair->sVisible = sNearest;
        }
    }
}
