/* 2 diffs: target schedules j=0 before &p->fC8 and &p->fD0 in blez delay; ours puts j=0 in the delay slot */
typedef struct CRef { int m_tagk; int m_tag; } CRef;
struct BF { unsigned long pad:52; long k:4; unsigned long pad2:8; };
struct S {
    char pad[0x28]; struct BF bf;
    char pad0[0x40 - 0x30]; int fl;
    char pad1[0x64 - 0x44]; int f64; int f68;
    char pad2[0x78 - 0x6C]; float f78; struct S *f7c; int f80;
    char pad3[0x90 - 0x84]; int *a90; int c94; void **a98; int *a9C; int cA0; void **aA4; int fa8, fac, fb0, fb4;
    char pad4[0xC8 - 0xB8]; int fc8; int pad5; int fd0;
};
extern char D_003D4A60[];
extern char D_003DD490[];
void func_001A5C48(struct S *p);
void func_0011A070(void *psl, struct S *p);
void *func_0015E938(void *pg, int kind, int oid, void *owner);
int func_00164018(struct S *p);
int func_001637E8(struct S *p);
void func_001620B0(struct S *p, int n, int c, int a);
void func_001623D0(struct S *p, int n, int c, int a, int b);
void *func_002581C0(CRef *pref, void *a, void *b);
void func_00129EC8(CRef *pref);
void func_001A6CA8(struct S *p, int n);
void func_001638F8(struct S *p)
{
    CRef ref;
    int i, j;
    int *pnC8;
    int *pnD0;
    func_001A5C48(p);
    if (p->f7c)
        func_0011A070((char *)p->f7c + 0x80, p);
    i = 0;
    j = 0;
    pnD0 = &p->fd0;
    pnC8 = &p->fc8;
    for (; i < p->c94; i++) {
        void *pv = func_0015E938(D_003DD490, 0x105, p->a90[i], 0);
        if (pv)
            p->a98[j++] = pv;
    }
    p->c94 = j;
    j = 0;
    for (i = 0; i < p->cA0; i++) {
        void *pv = func_0015E938(D_003DD490, 0x105, p->a9C[i], 0);
        if (pv)
            p->aA4[j++] = pv;
    }
    p->cA0 = j;
    if (!func_00164018(p) && func_001637E8(p)) {
        func_001620B0(p, 5, p->fa8, p->fac);
        func_001623D0(p, 5, p->fb0, p->fb4, 1);
    }
    if (p->fc8) {
        int n;
        func_002581C0(&ref, pnC8, D_003D4A60);
        n = ref.m_tag;
        func_00129EC8(&ref);
        p->f64 = n;
    }
    if (p->fd0) {
        int n;
        func_002581C0(&ref, pnD0, D_003D4A60);
        n = ref.m_tag;
        func_00129EC8(&ref);
        p->f68 = n;
    }
    if (p->f78 != 0.0f || p->f80) {
        int v;
        if (p->bf.k == 2)
            func_001A6CA8(p, 0);
        v = p->fl;
        if ((v ^ 1) & 1)
            *(int *)v |= 2;
        else
            p->fl = v | 2;
    }
}
