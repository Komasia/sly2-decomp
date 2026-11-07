struct LM { int pad[8]; float g20; float g24; };
struct S { int pad[5]; struct LM *plm; };
float GSuck__FPv(struct S *p, int n);
// name: SafeHouse port (NScaleDamage)
int NScaleDamage__FPvi(struct S *p, int n)
{
    float g = GSuck__FPv(p, n);
    return (int)(((1.0f - g) * p->plm->g20 + g * p->plm->g24) * (float)n);
}
