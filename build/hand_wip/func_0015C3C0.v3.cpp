// (Claude agent) 3/129: NRV `operator*(...) return r` plus chained `t.r[k] = r.r[k] = Mul3(..)` (dead second copy) gives the per-row 0xE0/0x110 stores. Left: load order of px->mat rows for xf.pos (target m0,m2,m1; ours m2,m1,m0).
typedef int qword __attribute__((mode(TI)));
struct MATRIX4 { qword r[4]; };
struct MATRIX3 { qword r[3]; };
struct VEC { int x, y, z, w; } __attribute__((aligned(16)));
struct XF { qword pos; MATRIX3 mat; VEC v; VEC w; };
struct P { int fl; void *pv; int a8, aC; qword q10, q20; int x30; XF *pxf; int x38, x3C; };
struct VTE { short d; short pad; void (*pfn)(void *, P *); };
struct O { int pad[3]; VTE *vt; char pad1[0x60 - 0x10]; MATRIX4 mat; };
struct S { char pad[0x60]; MATRIX4 mat; char pad1[0xE0 - 0xA0]; int c; O **apo; };
MATRIX4 func_0011C318(MATRIX4 *pm);
MATRIX4 operator*(const MATRIX4 &a, const MATRIX4 &b);
static inline qword MulRow(const MATRIX3 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz ACC, %1, %4x\n\tvmadday.xyz ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z" : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(v));
    return r;
}
static inline qword Add(qword a, qword b) { qword d; __asm__("vadd.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static inline qword Mul3(qword m0, qword m1, qword m2, qword v)
{
    qword r;
    __asm__("vmulax.xyz ACC, %1, %4x\n\tvmadday.xyz ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z" : "=j"(r) : "j"(m0), "j"(m1), "j"(m2), "j"(v));
    return r;
}
static inline MATRIX3 operator*(const MATRIX3 &a, const MATRIX3 &b) return r
{
    qword b0 = b.r[0], b1 = b.r[1], b2 = b.r[2];
    MATRIX3 t;
    t.r[0] = r.r[0] = Mul3(b0, b1, b2, a.r[0]);
    t.r[1] = r.r[1] = Mul3(b0, b1, b2, a.r[1]);
    t.r[2] = r.r[2] = Mul3(b0, b1, b2, a.r[2]);
}
extern "C" void func_0015C3C0(S *p, P *pp);
void func_0015C3C0(S *p, P *pp)
{
    P loc = *pp;
    XF xf;
    loc.pxf = &xf;
    loc.fl |= 0x40;
    if (loc.fl & 1) {
    } else {
        loc.pv = p;
        loc.fl |= 1;
    }
    for (int i = 0; i < p->c; i++) {
        O *po = p->apo[i];
        MATRIX4 mRel;
        mRel = func_0011C318(&p->mat) * po->mat;
        MATRIX3 &m3 = *(MATRIX3 *)&mRel;
        if (pp->fl & 0x40) {
            XF *px = pp->pxf;
            xf.mat = m3 * px->mat;
            xf.pos = Add(px->pos, MulRow(px->mat, mRel.r[3]));
            xf.v = px->v;
            xf.w = px->w;
        } else {
            xf.mat = m3;
            xf.pos = mRel.r[3];
            xf.v.x = xf.v.y = xf.v.z = 0;
            xf.w.x = xf.w.y = xf.w.z = 0;
        }
        po->vt[51].pfn((char *)po + po->vt[51].d, &loc);
    }
}
