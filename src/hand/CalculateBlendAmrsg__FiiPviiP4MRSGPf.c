/* CalculateBlendAmrsg: the blended segment table (cmrsg segments) of an ASEGBL: each segment's length is the
 * BLs' lengths by weight and the first segment starts at the BLs' (weighted, wrapped) phase of their first segment;
 * *ptMax the blend's length (without a table: the BLs' lengths by weight). Layout: SafeHouse port (blend.h). */
struct MRSG { float t; float dt; };   /* field: SafeHouse port (blend.h) */
struct ASEG { char pad[0x74]; float tMax; };
struct BLENDBL { float weight; struct ASEG *paseg; };   /* field: SafeHouse port */
struct ASEGBL { char pad[0xC0]; int cbBl; int cbl; char *abl; };   /* field: SafeHouse port (blend.h ASEGBL) */
float GModPositive__Fff(float, float);
void CalculateBlendAmrsg__FiiPviiP4MRSGPf(struct ASEGBL *pbl, int ibAmrsg, int cmrsg, struct MRSG *amrsg, float *ptMax)
{
    float tSum = 0.0f;
    int i;
    if (cmrsg == 0) {
        if (ptMax) {
            for (i = 0; i < pbl->cbl; i++) {
                struct BLENDBL *pblT = (struct BLENDBL *)(pbl->abl + i * pbl->cbBl);
                if (pblT->weight != 0.0f)
                    tSum += pblT->paseg->tMax * pblT->weight;
            }
            *ptMax = tSum;
        }
        return;
    }
    for (i = 0; i < cmrsg; i++) {
        int j;
        amrsg[i].dt = 0.0f;
        for (j = 0; j < pbl->cbl; j++) {
            struct BLENDBL *pblT = (struct BLENDBL *)(pbl->abl + j * pbl->cbBl);
            if (pblT->weight != 0.0f)
                amrsg[i].dt += ((struct MRSG *)((char *)pblT + ibAmrsg))[i].dt * pblT->weight;
        }
        tSum += amrsg[i].dt;
    }
    {
        int fFirst = 1;
        float gAvg, gFirst;
        for (i = 0; i < pbl->cbl; i++) {
            struct BLENDBL *pblT = (struct BLENDBL *)(pbl->abl + i * pbl->cbBl);
            if (pblT->weight != 0.0f) {
                if (fFirst) {
                    fFirst = 0;
                    gAvg = *(float *)((char *)pblT + ibAmrsg) / pblT->paseg->tMax;
                    gFirst = gAvg;
                } else {
                    float d = *(float *)((char *)pblT + ibAmrsg) / pblT->paseg->tMax - gFirst;
                    if (d <= -0.5f)
                        d += 1.0f;
                    else if (0.5f < d)
                        d -= 1.0f;
                    gAvg += d * pblT->weight;
                }
            }
        }
        amrsg[0].t = GModPositive__Fff(gAvg, 1.0f) * tSum;
    }
    for (i = 1; i < cmrsg; i++) {
        float g = amrsg[i - 1].t + amrsg[i - 1].dt;
        amrsg[i].t = g;
        if (tSum <= g)
            amrsg[i].t = g - tSum;
    }
    if (ptMax)
        *ptMax = tSum;
}
