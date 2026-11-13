struct VTE { short d; short pad; float *(*pfn)(void *); };
struct S { char pad[0xC]; struct VTE *vt; char pad1[0x1D8 - 0x10]; float rad; };
float atan2f(float y, float x);
float RadNormalize__Ff(float r);
// name: SafeHouse port (FBirdFacing)
int FBirdFacing__FP2LO(struct S *p)
{
    float *a = p->vt[31].pfn((char *)p + p->vt[31].d);
    float *b = p->vt[31].pfn((char *)p + p->vt[31].d);
    float r = RadNormalize__Ff(p->rad - atan2f(a[1], b[0]));
    if (__builtin_fabsf(r) < 0.017453294f)
        return 1;
    return 0;
}
