typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; };
extern struct CLOCK D_002DDED0;
extern qword D_002A2DD0;
struct VE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VE *vt; char pad1[0x40 - 0x10]; qword v40; };
struct V3 { int x, y, z, w; };
static __inline__ void Zero(struct V3 *pv) { pv->z = 0; pv->y = 0; pv->x = 0; }
struct P { char pad[0x190]; struct V3 v190; char pad1[0x1030 - 0x1A0]; char x1030[4]; char x1034[4];
    char pad2[0x1840 - 0x1038]; int x1840; float f1844; void *x1848; void *x184C; char x1850[0x1C]; float f186C;
    char pad3[0x1890 - 0x1870]; char x1890[0x70]; struct O *x1900; void *x1904; int x1908; };
void func_0020C080(struct O *o);
void func_0020BF80(void *a, struct P *p, int n, void *b);
qword func_001A62E8(void *p);
qword *func_001A6318(void *p);
void func_001F15B8(void *p);
void func_001305B8(void *a, struct P *p, int n, void *q, float f1, float f2);
void func_001B8D30(struct P *p, int st)
{
    void *o;
    int n;
    if (st == p->x1840) return;
    if (p->x1840 == 2) {
        func_0020C080(p->x1900);
        ((void (*)())p->x1900->vt[2].pfn)((char *)p->x1900 + p->x1900->vt[2].d);
        p->x1900 = 0;
    }
    p->x1840 = st;
    p->f1844 = D_002DDED0.t;
    o = 0;
    n = 0;
    switch (st) {
    case 0:
        o = p->x1848;
        Zero(&p->v190);
        n = 1;
        break;
    case 1:
        o = p->x184C;
        n = 9;
        break;
    case 2: {
        struct O *q;
        qword r, b;
        union { qword q; float f[4]; } u, uv, u2;
        p->x1908 = 0;
        p->x1900 = (struct O *)p->x1890;
        func_0020BF80(p->x1850, p, 1, p->x1890);
        q = p->x1900;
        uv.q = func_001A62E8(p);
        __asm__("mfc1 %0, %1" : "=r"(b) : "f"(-p->f186C));
        u.q = b;
        u2.q = b;
        __asm__("vadda.xyzw $ACC, %2, $vf0\n\tvmaddx.xyzw %0, %1, %3x" : "=j"(r) : "j"(*func_001A6318(p)), "j"(uv.q), "j"(u2.q));
        q->v40 = r;
        *(qword *)&p->v190 = D_002A2DD0;
        break;
    }
    case 3:
        o = p->x1904;
        n = 1;
        break;
    case -1:
        p->x1908 = 0;
        return;
    }
    func_001F15B8(p->x1034);
    func_001305B8(o, p, n, p->x1030, 0.0f, 1.0f);
}
