/* RecalcBlend: after the BLs' weights changed: the dominant BL (the last with weight > 0.9999, else -1), the blended
 * segment tables and the blend's length (the playing ASEGAs keep their phase: their time over the length is kept), and
 * the timed events' times scaled from the events' BL (+0xD8). Layout: SafeHouse port (blend.h ASEGBL). */
// (Claude agent) matched: count-down search as do { if (--ibl < 0) break; if (...) break; } while (1); separate counter k in the last loop.
struct ASEGA { char pad[0x1C]; float t; char pad2[0x2C - 0x20]; struct ASEGA *pnext; };   /* field: SafeHouse port */
struct AMRSGT { int ibAmrsg; int cmrsg; int amrsg; };   /* a segment table */
struct ASEGEV { float t; int kind; int n8; int nC; };
struct ASEGBL { char pad[0x50]; struct ASEGA *pasegaFirst; char pad1[0x74 - 0x54]; float tMax; char pad2[0xA0 - 0x78]; int cevTimed; struct ASEGEV *aevTimed;
    char pad3[0xC0 - 0xA8]; int cbBl; int cbl; char *abl; int ctable; struct AMRSGT *aamrsg; int iblDominant; struct ASEGBL *pasegSkel; };   /* field: SafeHouse port (blend.h ASEGBL) */
void SetBlendDominant__FP6ASEGBLi(struct ASEGBL *pbl, int i);
void CalculateBlendAmrsg(struct ASEGBL *pbl, int ibAmrsg, int cmrsg, int amrsg, float *ptMax) asm("CalculateBlendAmrsg__FiiPviiP4MRSGPf");
// name: SafeHouse port (RecalcBlend)
void RecalcBlend__FP6ASEGBL(struct ASEGBL *pbl)
{
    int unused[4];
    int i;
    struct ASEGA *pasega;
    {
        int ibl;
        ibl = pbl->cbl;
        do {
            if (--ibl < 0)
                break;
            if (0.9999f < *(float *)(pbl->abl + ibl * pbl->cbBl))
                break;
        } while (1);
        SetBlendDominant__FP6ASEGBLi(pbl, ibl);
    }
    for (pasega = pbl->pasegaFirst; pasega; pasega = pasega->pnext)
        pasega->t = pasega->t / pbl->tMax;
    for (i = 0; i < pbl->ctable; i++) {
        struct AMRSGT *pamrsgt = &pbl->aamrsg[i];
        CalculateBlendAmrsg(pbl, pamrsgt->ibAmrsg, pamrsgt->cmrsg, pamrsgt->amrsg, &pbl->tMax);
    }
    if (pbl->ctable == 0)
        CalculateBlendAmrsg(pbl, 0, 0, 0, &pbl->tMax);
    for (pasega = pbl->pasegaFirst; pasega; pasega = pasega->pnext)
        pasega->t = pasega->t * pbl->tMax;
    if (pbl->pasegSkel) {
        float uScale = pbl->tMax / pbl->pasegSkel->tMax;
        int k;
        for (k = 0; k < pbl->cevTimed; k++)
            pbl->aevTimed[k].t = uScale * pbl->pasegSkel->aevTimed[k].t;
    }
}
