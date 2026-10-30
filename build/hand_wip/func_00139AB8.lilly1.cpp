// lilly1 (Claude agent, T1659, 2026-10-25): aligned 19 -> 17, NO pin. Built on laneK4v1 (header kept below).
// Changes: func_002417F0 is sceDmaSync and returns int (the void prototype put the p->c444 reload in v0; target v1),
// callees use the team names (LoadSprBuf/SaveSprBuf are variadic C++, FlushCache, sceDmaSync C).
// Left: (1) prologue: sched1 issues hi($LC0) and hi($LC1) together (tie at prio 28), so they get v0/v1; the target's vMin
// chain must outrank vMax's so the vMin zero-clear issues beside hi1 (zero reload -> v1, both his v0). (2) arg block: the
// pa copy-through asm hides pa's base, so sched1 orders sq 0x80 before the a2 load with prio 29 > c/x43C loads (target
// loads x43C and c before the sq); k1 ties to k's v1 (target k1 v0 / pa v1 = k not dying at k1 or pp). See notes/130000.md.
// laneK4v1 (Claude agent, lane K4, 2026-10-24): aligned 24 -> 19, NO pin. fresh10 in the 14C748 style (struct VU_FLOAT with a qmtc2 ctor, const-ref QwMid/QwSub/QwLength/GFromQw), k1 = k + 8 unpinned (stays addiu), plus a clobber of the dead a0 on the dt VuFloatFromWord asm: the &m arg setup now waits, so the g_clock address reload takes a0 like the target and the end-block qmfc2 reload lands in a0. Left: prologue lui pair (sched1 tie hi1/hi2 both prio 28), pa/k1 v0/v1 swap, c/x43C/sq 0x80 order.
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
extern int D_002DDED0[];
extern int D_002C3C5C;
extern SPRBUF D_003DD2C0[2];
extern char *D_003DD2CC[];
extern void *D_002DE59C;
}
static inline VU_FLOAT VuFloatFromWord(int n)
{
    VU_FLOAT v;
    __asm__("" : "=r"(v.qw) : "0"(n), "r"((char *)D_003DD2CC) : "$4"); /* empty asm (Claude agent), clobber of the dead a0 delays the &m setup: the int's bits as a VU_FLOAT, like the target's sq v0 + por */
    return v;
} // VU_I: tied empty asm gives the target's sq v0,0x80 temp + por a1,v0; the "r"(D_003DD2CC) input is allocation-only (base address use, so the hoisted base gets s5 and 0x840 s6 like the target)
void LoadSprBuf(int cb, ...);
void SaveSprBuf(void *pv, ...);
extern "C" {
M4 func_0015BFD8(void *p);
void FlushCache(int);

void func_00201998(void);
int func_00139950(M4 *pm, VU_FLOAT dt, char *a, char *b, char *c, int n, int d, VEC *pvMin, VEC *pvMax);

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
    VF vMax = {-3.40282347e+38f, -3.40282347e+38f, -3.40282347e+38f};
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
        int c = pq->c; int x43C = p->x43C;
        int dti = D_002DDED0[1]; int k = D_002C3C5C * 0x50; int k1 = k + 8;
        char **pp = (char **)((char *)D_003DD2CC + k);
        char **pa = pp;
        __asm__("" : "+r"(pa)); /* copy-through: keeps the target's daddu copy of pp */
        n = func_00139950(&m, VuFloatFromWord(dti), pa[0], *(char **)((char *)D_003DD2CC + k1), pp[4], c, x43C, (VEC *)&vMin, (VEC *)&vMax);
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
