/* RemoveLaserContacts (vt slot 54): removes every beam contact between the laser and the physics root paloOther
 * (the other side of each contact: side 1 when side 0 is the laser), frees them, and posts ApplyLaserContacts
 * (the deferred call D_002A7AC0) so the beams' visible lengths are recomputed. */
#include "h3_laser.h"

typedef struct DEFERREDCALL { short kind, index; union { short item; int value; } payload; } DEFERREDCALL;   /* g++ pointer to member */
typedef struct XPD { void *paloRoot; char unk_0x4[0x3C]; } XPD;   /* one side of a contact (0x40 bytes) */
typedef struct XP {                /* contact */
    /* 0x00 */ char unk_0x0[8];
    /* 0x08 */ XPD axpd[2];
    /* 0x88 */ char unk_0x88[0xAC - 0x88];
    /* 0xac */ struct XP *pxpNext;
} XP;
typedef struct LASER {
    /* 0x000 */ char unk_so[0x198];   /* the SO base */
    /* 0x198 */ int cpair;
    /* 0x19c */ LASERPAIR *apair;
} LASER;
extern struct G g_sw;
extern DEFERREDCALL D_002A7AC0;    /* &ApplyLaserContacts */
void SetAloOverlapNothing__FP3ALOT0(void);
void FreeSwXpList(struct G *, XP *) asm("FreeSwXpList__FP2SWP2XP");
void PostDeferredCall__FPvUi15PFNDEFERREDCALLi(struct G *, LASER *, DEFERREDCALL, int);
// name: SafeHouse port (RemoveLaserContacts)
void RemoveLaserContacts__FP3ALOT0(LASER *plaser, void *paloOther)
{
    XP *pxpFree = 0;
    int ipair;
    SetAloOverlapNothing__FP3ALOT0();
    for (ipair = 0; ipair < plaser->cpair; ipair++) {
        XP **ppxp = (XP **)&plaser->apair[ipair].pxpFirst;
        XP *pxp;
        while ((pxp = *ppxp) != 0) {
            int side = pxp->axpd[0].paloRoot == plaser;
            /* pxp->axpd[side], written as the byte offset the original computes */
            if (paloOther == ((XPD *)((char *)pxp + ((unsigned int)side << 6) + 8))->paloRoot) {
                *ppxp = pxp->pxpNext;
                pxp->pxpNext = pxpFree;
                pxpFree = pxp;
            } else {
                ppxp = &pxp->pxpNext;
            }
        }
    }
    FreeSwXpList(&g_sw, pxpFree);
    PostDeferredCall__FPvUi15PFNDEFERREDCALLi(&g_sw, plaser, D_002A7AC0, 0);
}
