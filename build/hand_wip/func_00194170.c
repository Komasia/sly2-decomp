typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
typedef struct { short d; short pad; qword (*pfn)(void *); } VT;
struct E8 { char pad[0x80]; qword x80; };
struct O { char pad[0xC]; VT *vt; char pad2[0xE8-0x10]; struct E8 *xe8; };
struct S { char pad[0x1BC]; int x1bc; float x1c0; float x1c4; };
struct P { struct O *x0; int x4; int x8; int pad[2]; struct S *x14; int x18; float x1c; };
struct CLOCK { float t; float dt; };
extern struct CLOCK D_002DDED0;
extern char D_002BF700[];
void func_001E67B8(struct S *s, int n, U *pv, float g);
void func_0011D018(float a, float b, float dt, void *p, float *pg);
void func_001FAC30(struct O *o, qword q);
static __inline__ float Dot(qword a, qword b)
{
    qword r, t;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(r), "=&j"(t) : "j"(a), "0"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(r));
    return g;
}
static __inline__ float Dot2(qword a, qword b)
{
    qword r, t;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(r), "=&j"(t) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(r));
    return g;
}
static __inline__ float GClamp(float g, float lo, float hi)
{
    if (g < lo)
        return lo;
    if (g > hi)
        return hi;
    return g;
}
void func_00194170(struct P *p)
{
    U v, w, r, k;
    float a, b;
    struct S *s;
    float d1, d2, x;
    if (p->x8 != 3)
        return;
    s = p->x14;
    if (!s->x1bc)
        return;
    v.q = p->x0->vt[33].pfn((char *)p->x0 + p->x0->vt[33].d);
    func_001E67B8(s, 0, &w, p->x1c);
    d1 = Dot(w.q, v.q);
    d2 = Dot2(w.q, p->x0->xe8->x80);
    func_0011D018(d1, s->x1c0, D_002DDED0.dt, D_002BF700, &a);
    func_0011D018(d1, -s->x1c0, D_002DDED0.dt, D_002BF700, &b);
    x = GClamp(s->x1c4 * d2, b, a) - d2;
    __asm__("qmtc2.ni %1, %0" : "=j"(k.q) : "r"(x));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r.q) : "j"(w.q), "j"(k.q));
    func_001FAC30(p->x0, r.q);
}
