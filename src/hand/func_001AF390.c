struct F { int pad[5]; void (*pfn)(struct F *); int pad2[2]; };
struct E { int n; struct F *af; int x8; int xC; int x10; int x14; int x18; };
struct S { int pad[3]; struct E a[1]; };
struct S1 { char pad[0x1EC]; int x1EC; };
void SetMenuState__FP4MENUi(struct S *s, int n);
void *s1_memset(void *p, int c, unsigned int n);
// name: SafeHouse port (ReplacePage)
void ReplacePage__FP4MENUiPv(struct S *s, int n, struct F *af)
{
    int x18, x8;
    int k;
    struct E *e;
    int i;
    SetMenuState__FP4MENUi(s, 3);
    k = s->a[0].x18;
    if (k > 0) {
        e = &s->a[k];
        x8 = e->x8;
        x18 = e->x18;
    }
    ((struct S1 *)s)->x1EC = k + 1;
    e = &s->a[k + 1];
    s1_memset(e, 0, sizeof(*e));
    e->af = af;
    e->x8 = x8;
    e->xC = 1;
    e->x18 = x18;
    e->n = n;
    for (i = 0; i < e->n; i++) {
        struct F *f = &e->af[i];
        if (f->pfn)
            f->pfn(f);
    }
}
