struct LM { float gMin; float gMax; };
struct S { char pad[0xC]; int c; struct LM alm[1]; };
// name: SafeHouse port (FInPathSpan)
struct LM *FInPathSpan__FP7PATHRECf(struct S *p, float g)
{
    int i;
    struct LM *alm = p->alm;
    for (i = 0; i < p->c; i++) {
        struct LM *plm = &alm[i];
        if (plm->gMin <= g && g <= plm->gMax) return plm;
    }
    return 0;
}
