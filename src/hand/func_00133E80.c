struct X;
struct E { int f0; struct X *px; float *pg; };
struct P { char pad[0x3CCC]; int fDirty; int c; struct E *aae[3]; };
void UpdateSwPox__FP2SWP3OXAT1Uc(struct P *, struct X *, struct X *, int);
void *s1_memmove(void *, void *, unsigned int);
// name: SafeHouse port (UpdateSwAaox)
void UpdateSwAaox__FP2SW(struct P *p)
{
    int i;
    if (!p->fDirty)
        return;
    p->fDirty = 0;
    if (!p->c)
        return;
    for (i = 0; i < 3; i++) {
        struct E *pe = p->aae[i];
        struct E *ae = pe;
        float gMax = *pe->pg;
        int j;
        for (j = p->c, pe++; --j > 0; pe++) {
            float g = *pe->pg;
            if (gMax <= g) {
                gMax = g;
            } else {
                struct E *pe2;
                struct E e;
                for (pe2 = pe - 1; pe2 >= ae; pe2--) {
                    if (*pe2->pg <= g)
                        break;
                    if (pe->f0 != pe2->f0)
                        UpdateSwPox__FP2SWP3OXAT1Uc(p, pe->px, pe2->px, 0);
                }
                pe2++;
                e = *pe;
                s1_memmove(pe2 + 1, pe2, (pe - pe2) * sizeof(struct E));
                *pe2 = e;
            }
        }
    }
}
