/* TRKPA::Eval for kind-4 tracks (keys {g, dg}): v (velocity 0), then each keyed axis by EvalHermite over the
 * key segment around g. Layout: SafeHouse port (aseg.h). */
typedef int qword __attribute__((mode(TI)));
typedef struct VECTOR { float x, y, z, w; } VECTOR;
typedef struct KEYA2 { float g; float dg; } KEYA2;
typedef struct TRKPA { int pvtbl; int ckey; float *at; KEYA2 *aakey[3]; int pad18; qword v; } TRKPA;
int func_0012C708(TRKPA *ptrk, float g);
void EvalHermite__FPfT0fffffff(float *pg, float *pdg, float dt, float u, float dtScale, float g0, float dg0, float g1, float dg1);
void func_0012CA68(TRKPA *ptrk, VECTOR *ppos, VECTOR *pvel, float g, float dtScale)
{
    if (ppos)
        *(qword *)ppos = ptrk->v;
    if (pvel) {
        pvel->z = 0;
        pvel->y = 0;
        pvel->x = 0;
    }
    if (ptrk->ckey) {
        int ikey = func_0012C708(ptrk, g);
        unsigned int iaxis;
        for (iaxis = 0; iaxis < 3; iaxis++) {
            KEYA2 *akey = ptrk->aakey[iaxis];
            if (akey) {
                float du = g - ptrk->at[ikey - 1];
                float dt = ptrk->at[ikey] - ptrk->at[ikey - 1];
                KEYA2 *pkey0 = &akey[ikey - 1];
                KEYA2 *pkey1 = &akey[ikey];
                EvalHermite__FPfT0fffffff(ppos ? &(&ppos->x)[iaxis] : 0, pvel ? &(&pvel->x)[iaxis] : 0,
                              dt, du, dtScale,
                              pkey0->g, pkey0->dg, pkey1->g, pkey1->dg);
            }
        }
    }
}
