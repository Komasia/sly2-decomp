struct S { int a[4]; float g10, g14, g18, g1c, g20, g24, g28, g2c; int n30; };
void ForgetPadctlPresses__FP6PADCTLUi(struct S *p, int grf);
// name: SafeHouse port (ClearPadctl)
void ClearPadctl__FP6PADCTL(struct S *p)
{
    p->n30 = 0;
    p->g20 = p->g24 = p->g28 = p->g2c = p->g10 = p->g14 = p->g18 = p->g1c = 0.0f;
    ForgetPadctlPresses__FP6PADCTLUi(p, 0xFFFF);
}
