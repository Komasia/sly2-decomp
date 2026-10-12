struct VTE { short d; short pad; void (*pf)(); };
struct LO { char pad[0xC]; struct VTE *vt; char p1[0x3C - 0x10]; struct N *x3C; };
struct N { int id; struct N *next; int p8[2]; struct LO *x10; };
struct R { int n; char pad[0x6C - 4]; };
struct G { char pad[0x3F08]; struct R *ar; void *x3F0C; };
struct H { int a; };
extern struct G D_003DD490;
struct N *func_001C99D8(void *p, int c, int *a);
int func_001C9950(int id);
void func_001AE478(struct H *p);
void func_001AE4A0(struct H *p, int n);
void func_001CA118(struct LO *p, int id, int f)
{
    int a[16];
    struct H h;
    struct LO **ap;
    struct N *pn;
    struct N *r;
    int c = 16;
    pn = p->x3C;
    for (; pn && pn->id != -1; pn = pn->next)
        a[--c] = pn->id;
    c--;
    a[c] = id;
    r = func_001C99D8(D_003DD490.x3F0C, 16 - c, &a[c]);
    for (pn = p->x3C; pn->id != -1 && pn->x10 == p; pn = pn->next)
        pn->x10 = 0;
    for (pn = r; pn->id != -1 && D_003DD490.ar[func_001C9950(pn->id)].n == 1 && !pn->x10; pn = pn->next)
        pn->x10 = p;
    p->x3C = r;
    if (f) {
        int n, i;
        func_001AE478(&h);
        n = ((int (*)(void *, struct LO ***))p->vt[28].pf)((char *)p + p->vt[28].d, &ap);
        for (i = 0; i < n; i++) {
            struct LO *q = ap[i];
            ((void (*)(void *, int, int))q->vt[25].pf)((char *)q + q->vt[25].d, id, 1);
        }
        func_001AE4A0(&h, 2);
    }
}
