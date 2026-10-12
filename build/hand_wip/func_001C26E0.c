struct LO { char pad[0x28]; unsigned long x28; char p1[0x120 - 0x30]; int x120; int x124; int x128; };
struct G { char pad[0xE94]; int c; int a[(0xFE8 - 0xE98) / 4]; int xFE8; };
int func_001C26E0(void *p, struct LO *plo, struct G *g)
{
    int m, i, f1, f2, c, x1, x2;
    if (!((int)(plo->x28 >> 60) & 1)) return 0;
    m = (plo->x120 == 1) ? 3 : 2;
    if ((g->xFE8 & m) != m) return 0;
    c = g->c;
    if (c > 0) {
        f1 = 0;
        f2 = 0;
        x1 = plo->x124;
        x2 = plo->x128;
        for (i = 0; i < c; i++) {
            if (x1 == g->a[i]) f1 = 1;
            if (x2 == g->a[i]) f2 = 1;
            if (f1 && f2) break;
        }
        if (!f1 || !f2) return 0;
    }
    return 1;
}
