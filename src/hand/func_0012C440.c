/* TRKPA::Eval (keys {g, dgIn, dgOut}): the value starts as v (velocity 0); each axis with keys is evaluated by
 * EvalHermite over the key segment around g. Layout: SafeHouse port (aseg.h). */
typedef int qword __attribute__((mode(TI)));
typedef struct VECTOR { float x, y, z, w; } VECTOR;
typedef struct KEYA3 { float g; float dgIn; float dgOut; } KEYA3;
typedef struct TRKPA { int pvtbl; int ckey; float *at; KEYA3 *aakey[3]; int pad18; qword v; } TRKPA;
int IkeyFind__5TRKPAf(TRKPA *ptrk, float g);
void EvalHermite__FPfT0fffffff(float *pg, float *pdg, float dt, float u, float dtScale, float g0, float dg0, float g1, float dg1);
// name: SafeHouse port (TRKPA::Eval)
void Eval__5TRKPAP7VECTOR4T1ff(TRKPA *ptrk, VECTOR *ppos, VECTOR *pvel, float g, float dtScale)
{
    if (ppos)
        *(qword *)ppos = ptrk->v;
    if (pvel) {
        pvel->z = 0;
        pvel->y = 0;
        pvel->x = 0;
    }
    if (ptrk->ckey) {
        int ikey = IkeyFind__5TRKPAf(ptrk, g);
        unsigned int iaxis;
        for (iaxis = 0; iaxis < 3; iaxis++) {
            KEYA3 *akey = ptrk->aakey[iaxis];
            if (akey) {
                float du = g - ptrk->at[ikey - 1];
                float dt = ptrk->at[ikey] - ptrk->at[ikey - 1];
                KEYA3 *pkey0 = &akey[ikey - 1];
                KEYA3 *pkey1 = &akey[ikey];
                EvalHermite__FPfT0fffffff(ppos ? &(&ppos->x)[iaxis] : 0, pvel ? &(&pvel->x)[iaxis] : 0,
                              dt, du, dtScale,
                              pkey0->g, pkey0->dgOut, pkey1->g, pkey1->dgIn);
            }
        }
    }
}
