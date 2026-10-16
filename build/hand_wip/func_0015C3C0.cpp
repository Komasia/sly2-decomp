// NEAR MISS (round 9, see notes/150000.md)
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
static inline MATRIX3 operator*(const MATRIX3 &a, const MATRIX3 &b)
{
    MATRIX3 r;
    r.r[0] = MulRow(b, a.r[0]);
    r.r[1] = MulRow(b, a.r[1]);
    r.r[2] = MulRow(b, a.r[2]);
    return r;
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
        if (pp->fl & 0x40) {
            XF *px = pp->pxf;
            xf.mat = *(MATRIX3 *)&mRel * px->mat;
            xf.pos = Add(px->pos, MulRow(px->mat, mRel.r[3]));
            xf.v = px->v;
            xf.w = px->w;
        } else {
            xf.mat = *(MATRIX3 *)&mRel;
            xf.pos = mRel.r[3];
            xf.v.x = xf.v.y = xf.v.z = 0;
            xf.w.x = xf.w.y = xf.w.z = 0;
        }
        po->vt[51].pfn((char *)po + po->vt[51].d, &loc);
    }
}
