typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; void (*pfn)(); };
struct O { int a[3]; struct VTE *vt; };
void RemoveNoise__FP5NOISE(struct O *o);
void PnoiseNew__FP9NOISETMPLG9VU_VECTORiP6VECTOR(void *x, qword q, int c, struct O **ppo);
// name: SafeHouse port (SetHeldNoise)
void SetHeldNoise__FPP5NOISEG9VU_VECTORiP2LO(void *x, qword q, int c, struct O **ppo)
{
    if (*ppo) {
        struct O *o;
        struct VTE *e;
        RemoveNoise__FP5NOISE(*ppo);
        o = *ppo;
        e = &o->vt[2];
        e->pfn((char *)o + e->d);
        *ppo = 0;
    }
    if (x) {
        struct O *o;
        struct VTE *e;
        PnoiseNew__FP9NOISETMPLG9VU_VECTORiP6VECTOR(x, q, c, ppo);
        o = *ppo;
        e = &o->vt[1];
        e->pfn((char *)o + e->d);
    }
}
