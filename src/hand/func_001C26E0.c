struct LO { char pad[0x28]; unsigned long x28; char p1[0x120 - 0x30]; int x120; int x124; int x128; };
struct G { char pad[0xE94]; int c; int a[84]; int xFE8; };
int func_001C26E0(void *p, struct LO *plo, struct G *g)
{
    int m, i, f1, f2, c;
    if (!((plo->x28 >> 60) & 1)) return 0;
    m = (plo->x120 == 1) ? 3 : 2;
    if ((m & g->xFE8) != m) return 0;
    c = g->c;
    if (c > 0) {
        int *ids = g->a;
        f1 = 0; f2 = 0;
        for (i = 0; i < c; i++) {
            int id = ids[i];
            if (plo->x124 == id) f1 = 1;
            if (plo->x128 == id) f2 = 1;
            if (f1 && f2) break;
        }
        if (!f1 || !f2) return 0;
    }
    return 1;
}
