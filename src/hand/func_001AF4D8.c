struct F { int pad[5]; void (*pfn)(struct F *); int pad2[2]; };
struct E { int n; struct F *af; int x8; int xC; int x10; int x14; int x18; };
struct S { int pad[9]; int x24; struct E a[16]; int x1E8; int x1EC; };
void SetMenuState__FP4MENUi(struct S *s, int n);
void *s1_memset(void *p, int c, unsigned int n);
int func_001B0108(struct S *s);
// name: SafeHouse port (PushPage)
void PushPage__FP4MENUiPviUi(struct S *s, int n, struct F *af, int x8, int x18)
{
    struct E *e;
    int i;
    if (!x8) {
        if (s->x24 > 0)
            x8 = s->a[s->x24 - 1].x8;
    }
    e = &s->a[s->x24++];
    s1_memset(e, 0, sizeof(*e));
    e->af = af;
    e->n = n;
    e->x8 = x8;
    e->x18 = x18;
    e->xC = 0;
    SetMenuState__FP4MENUi(s, 1);
    for (i = 0; i < e->n; i++) {
        struct F *f = &e->af[i];
        if (f->pfn)
            f->pfn(f);
    }
    if (func_001B0108(s)) {
        s->x1EC = s->x24;
        s->x24--;
    }
}
