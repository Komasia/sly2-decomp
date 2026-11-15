/* func_0020A5F8 (0x20A5F8): a pursuit target record (SafeHouse aipursuit.h TARGETREC; 0xAC bytes) made for an
 * object: gains 1 / 2, no timer and no heading mode, then added to the records' list D_003E145C. */
#include "so.h"
struct LO;
struct TARGETREC {
    /* 0x00 */ float t0;          /* when the first guard came */
    /* 0x04 */ float tTimer;      /* the timer's time */
    /* 0x08 */ int nTimer;        /* the timer's value (1 seen, 2 lost but near, 3 an action, 4 a shot, 5 hit) */
    /* 0x0c */ struct LO *plo;
    /* 0x10 */ int nMode;         /* 0 the camera's heading, 1 the object's facing */
    /* 0x14 */ float g14;
    /* 0x18 */ float radAct;      /* the angle the guards may act within */
};
extern DL D_003E145C;   /* the pursuit target records */
void AppendDlEntry__FP2DLPv(DL *pdl, void *pv);

struct TARGETREC *func_0020A5F8(struct TARGETREC *ptargetrec, struct LO *plo)
{
    ptargetrec->plo = plo;
    ptargetrec->g14 = 1.0f;
    ptargetrec->radAct = 2.0f;
    ptargetrec->nMode = -1;
    ptargetrec->nTimer = -1;
    AppendDlEntry__FP2DLPv(&D_003E145C, ptargetrec);
    return ptargetrec;
}
