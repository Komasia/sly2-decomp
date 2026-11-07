typedef int qword __attribute__((mode(TI)));
typedef struct VECTOR { float x, y, z, w; } VECTOR;
typedef struct KEY { float g; float dgIn; float dgOut; } KEY;
typedef struct T { int pad; int c; float *at; KEY *ak[3]; int pad2; qword v; } T;
int IkeyFind__5TRKPAf(T *t, float g);
void EvalHermite__FPfT0fffffff(float *pg, float *pdg, float dt, float u, float dtScale, float g0, float dg0, float g1, float dg1);
// name: SafeHouse port (TRKPA::Eval)
void Eval__5TRKPAP7VECTOR4T1ff(T *t, VECTOR *pv, VECTOR *pdv, float g, float dtScale)
{
    if (pv)
        *(qword *)pv = t->v;
    if (pdv) {
        pdv->z = 0;
        pdv->y = 0;
        pdv->x = 0;
    }
    if (t->c) {
        int i = IkeyFind__5TRKPAf(t, g);
        unsigned int j;
        for (j = 0; j < 3; j++) {
            KEY *ak = t->ak[j];
            if (ak) {
                float du = g - t->at[i - 1];
                float dt = t->at[i] - t->at[i - 1];
                KEY *k0 = &ak[i - 1];
                KEY *k1 = &ak[i];
                EvalHermite__FPfT0fffffff(pv ? &(&pv->x)[j] : 0, pdv ? &(&pdv->x)[j] : 0,
                              dt, du, dtScale,
                              k0->g, k0->dgOut, k1->g, k1->dgIn);
            }
        }
    }
}
