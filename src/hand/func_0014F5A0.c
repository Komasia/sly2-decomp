struct CM { char pad[0x20]; float a, b; int c; };
void RecalcCmFrustrum__FP2CM(struct CM *p);
void func_0014F5A0(struct CM *p, float f)
{
    int fChanged = __builtin_fabsf(f - p->a) > 0.0001f;
    p->a = f;
    p->b = f;
    p->c = 0;
    if (fChanged) RecalcCmFrustrum__FP2CM(p);
}
