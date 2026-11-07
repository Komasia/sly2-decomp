struct S { char pad[0x88]; float a[32]; };
extern float g_clock;
// name: SafeHouse port (GrfPadctlPressedWithin)
int GrfPadctlPressedWithin__FP6PADCTLUif(struct S *p, unsigned int grf, float dt)
{
    int grfRet = 0;
    int i = 0;
    float *pg;
    float t = g_clock;
    if (grf) {
        pg = p->a;
        do {
            if ((grf & 1) && t - *pg <= dt) grfRet |= 1 << i;
            grf >>= 1; pg++; i++;
        } while (grf);
    }
    return grfRet;
}
