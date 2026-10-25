// lilly3 = PROBE (Claude agent, T1663): lilly2 with vMax as a 1-element array, aligned 9. Shows the sched1 dependency the target needs
// (BLK clobber between the vMin stores and the vMax clear); not a candidate source. See lilly2 header and notes/130000.md.
// lilly2 (Claude agent, T1663, 2026-10-25): aligned 17 -> 7 (11/193 differ), NO register pin, no allocation-only asm inputs.
// Built on lilly1 (T1659). Arg block of func_00139950 now matches exactly:
//  - the three SPRBUF entry pointers come from an inline accessor PvSprBuf(i) = D_003DD2C0[D_002C3C5C].a[i].pv. RTL inlining
//    with a constant i gives the target's s5 = &...a[0].pv base, the daddu copy for a[0], (k+8)+s5 for a[1] and 0x10(t4) for
//    a[2] by itself (no copy-through asm, no k1 variable).
//  - dt is a VU_FLOAT temp from `lw %0, %1` on "m"(D_002DDED0[1]) (float array: the address stays lui/addiu + 4 like the target;
//    a struct member or a const float & parameter folds %lo into the lw). Gives the sq v0,0x80 temp + por a1 in target order.
//  - pq->c and p->x43C passed directly (locals read early).
// Left: only the prologue (vMin/vMax init). Target = hi1 v0, zero v1, hi2 v0, then all f0 swc1s, then all f1 swc1s.
// sched1 here issues hi($LC0)/hi($LC1) together (both prio 28), so they get v0/v1. The target needs an edge from vMin's swc1s to
// vMax's clear: probe .y1 (vMax as `VF avMax[1] = {{...}}`: the complete array constructor emits a (clobber (mem:BLK)), which
// alias.c treats as conflicting with every frame slot) gets that sched1 order and the f0/f1 store order, but local-alloc's
// fake-lifetime extension then gives hi1 v1 (hi2 is born right after hi1 dies) and the zero is reloaded twice (aligned 9).
typedef int qword __attribute__((mode(TI)));
struct M4 { qword a[4]; };
struct VF { float x, y, z, w; } __attribute__((aligned(16)));
#define Q_(v) (*(qword *)&(v))
union VEC { qword q; struct { float x, y, z, w; } v; };
struct DL { void *head; void *tail; int ibDle; };
struct DLI { DL *m_pdl; void **m_ppv; int m_ibDle; DLI *m_pdliNext; };
struct BUF { char ab[0x2B0]; char ab2[0x560 - 0x2B0]; char ab3[0x840 - 0x560]; };
struct Q { BUF abuf[2]; int i; int c; };
struct SBE { int cb; char *pv; };
struct SPRBUF { unsigned long *aqw; char *pv; SBE a[8]; int c; int state; };
struct VU_FLOAT { qword qw; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(qw) : "r"(f)); } VU_FLOAT() {} };
struct VU_FLOATM { qword qw; };

struct P {
    int pad0[3];
    virtual void f1(); virtual void f2(); virtual void f3(); virtual void f4(); virtual void f5();
    virtual void f6(); virtual void f7(); virtual void f8(); virtual void f9();
};
struct PX : P {
    char pad[0xF0 - 0x10]; qword vF0; float g100; char pad104[0x120 - 0x104]; float g120;
    char pad124[0x170 - 0x124]; char x170[0x43C - 0x170]; int x43C; int pad440; int c444; DL dl;
};
extern "C" {
extern DLI *D_002DD2FC;
extern const float D_002A4AF4;
extern const float D_002A4AF8;
extern float D_002DDED0[];
extern int D_002C3C5C;
extern SPRBUF D_003DD2C0[2];
extern void *D_002DE59C;
}
void LoadSprBuf(int cb, ...);
void SaveSprBuf(void *pv, ...);
extern "C" {
M4 func_0015BFD8(void *p);
void FlushCache(int);

void func_00201998(void);
int func_00139950(M4 *pm, VU_FLOATM dt, char *a, char *b, char *c, int n, int d, VEC *pvMin, VEC *pvMax);

void func_00139098(Q *pq);
int sceDmaSync(void *pch, int mode, int timeout);
void func_00139AB8(PX *p);
}
static inline void InitDli(DLI *pdli, DL *pdl)
{
    pdli->m_pdl = pdl;
    pdli->m_ppv = (void **)pdl;
    pdli->m_ibDle = pdl->ibDle;
    pdli->m_pdliNext = D_002DD2FC;
    D_002DD2FC = pdli;
}
static inline void *PvNextDli(DLI *pdli)
{
    void *pv = *pdli->m_ppv;
    pdli->m_ppv = (void **)((char *)pv + pdli->m_ibDle);
    return pv;
}
static inline VU_FLOATM VuFloatDt()
{
    VU_FLOATM v;
    __asm__("lw %0, %1" : "=r"(v.qw) : "m"(D_002DDED0[1]));
    return v;
}
static inline char *PvSprBuf(int i)
{
    return D_003DD2C0[D_002C3C5C].a[i].pv;
}
static inline void Kick(Q *pq)
{
    BUF *pb = &pq->abuf[pq->i];
    LoadSprBuf(pq->c * 16, pb, pq->c * 16, pb->ab2, pq->c * 16, pb->ab3, 0, 0);
}
static inline qword QwMid(const qword &a, const qword &b, const VU_FLOAT &g)
{
    qword qw;
    __asm__("vmulax.xyzw $ACC, %1, %3x\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(qw) : "j"(a), "j"(b), "j"(g.qw));
    return qw;
}
static inline qword QwSub(const qword &qw0, const qword &qw1)
{
    qword qw;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1));
    return qw;
}
static inline qword QwLength(const qword &v)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
    return qw;
}
static inline float GFromQw(const qword &qw)
{
    float g;
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(qw)); /* mtc1 from a qword: gcc emits the qmfc2 */
    return g;
}
void func_00139AB8(PX *p)
{
    VF vMin = {3.40282347e+38f, 3.40282347e+38f, 3.40282347e+38f};
    VF avMax[1] = {{-3.40282347e+38f, -3.40282347e+38f, -3.40282347e+38f}};
#define vMax avMax[0]
    M4 m;
    m = func_0015BFD8(p->x170);
    {
    DLI dli;
    Q *pq;
    InitDli(&dli, &p->dl);
    pq = (Q *)PvNextDli(&dli);
    {
        BUF *pb = &pq->abuf[pq->i];
        FlushCache(0);
        LoadSprBuf(pq->c * 16, pb, pq->c * 16, pb->ab2, pq->c * 16, pb->ab3, 0, 0);
    }
    while (pq) {
        Q *pqNext;
        int n, i;
        qword dt;
        SPRBUF *psb;
        func_00201998();
        pqNext = (Q *)PvNextDli(&dli);
        if (pqNext) Kick(pqNext);
        n = func_00139950(&m, VuFloatDt(), PvSprBuf(0), PvSprBuf(1), PvSprBuf(2), pq->c, p->x43C, (VEC *)&vMin, (VEC *)&vMax);
        i = (pq->i + 1) & 1;
        {
            BUF *pb = &pq->abuf[i];
            SaveSprBuf(pb, pb->ab2, pb->ab3, 0);
        }
        pq->c -= n;
        p->c444 -= n;
        if (pq->c <= 0) func_00139098(pq);
        else pq->i = i;
        pq = pqNext;
    }
    sceDmaSync(D_002DE59C, 0, 0);
    if (p->c444 <= 0) {
        p->f9();
    } else {
        qword c = QwMid(Q_(vMin), Q_(vMax), VU_FLOAT(0.5f));
        p->vF0 = c;
        float g = GFromQw(QwLength(QwSub(c, Q_(vMax))));
        p->g100 = g + p->g120;
    }
    D_002DD2FC = dli.m_pdliNext;
    }
}
