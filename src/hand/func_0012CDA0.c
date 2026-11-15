/* TRKGK::Eval: the scalar track's value / rate at t: EvalHermite over the key segment around t (keys searched
 * from 1 up to c-1). Layout: SafeHouse port (aseg.h TRKGK / KEYG). */
typedef struct KEYG { float t; float g; float dgIn; float dgOut; } KEYG;
typedef struct TRKGK { int pvtbl; int ckey; KEYG *akey; } TRKGK;
void EvalHermite__FPfT0fffffff(float *pg, float *pdg, float dt, float t, float dtScale, float g0, float dg0, float g1, float dg1);
// name: SafeHouse port (TRKGK::Eval)
void Eval__5TRKGKPfT1ff(TRKGK *ptrk, float *pg, float *pdg, float t, float dtScale)
{
    int ikey;
    KEYG *pkey0, *pkey1;
    for (ikey = 1; ikey < ptrk->ckey; ikey++) {
        if (t < ptrk->akey[ikey].t)
            break;
    }
    pkey1 = (KEYG *)(ikey * 16 + (int)ptrk->akey);
    pkey0 = pkey1 - 1;
    EvalHermite__FPfT0fffffff(pg, pdg, pkey1->t - pkey0->t, t - pkey0->t, dtScale, pkey0->g, pkey0->dgOut, pkey1->g, pkey1->dgIn);
}
