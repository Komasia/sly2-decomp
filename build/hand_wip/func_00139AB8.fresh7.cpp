// fresh7 (Claude agent laneC2_10, 2026-10-24): aligned 30 -> 27 (positional 34). The target's missing register copy for pp[0] comes from a copy-through empty asm: `char **pa = pp; __asm__("" : "+r"(pa));` with pa[0] as the arg (instruction count and loop branch offsets now match). Left: the copy gets v0 (target v1, after k1 = k+8 takes v0), pp t2 (target t4), lw x43C/lw 0x10(pp) swapped around the jal, &D_002DDED0 lui reg, and the prologue lui pair. No gain: alloc-only "r"(k1) or "r"(D+k1) on the copy asm (27), copy used for pp[4] instead (29), statement-expr in the arg (27), "=r":"0" form (27), separate D+k address exprs for gcse (30-36).
// fresh6 (Claude agent laneC2i, 2026-10-24): aligned 30 (fresh5 29), but closer in structure (193 insns like the target): VU_I ctor is `__asm__("" : "=r"(q) : "0"(i))` (exact sq v0,0x80 + por a1,zero,v0), plus an allocation-only "r"((char *)D_003DD2CC) operand (base s5 / 0x840 s6 now right); args as k = g*0x50, k1 = k+8, pp = D+k: pp[0], *(D+k1), pp[4]; dt read into an int local before k; vMin/vMax as z = y = x. Left: target keeps k80 in v1 and makes t4 = k80+base a NEW reg, with a daddu v1,t4 copy for pp[0] (ours adds in place, no copy: everything after shifts by one), and the prologue lui pair (same issue as 139DC0).
// fresh5 (Claude agent laneC2g, 2026-10-24): aligned 31 -> 29: fresh4 plus the mtc1-from-qword asm (`"r"(l)` straight into mtc1, no qmfc2 asm): the end block now matches except reload regs. The laneC2d k/k1 byte-offset arg form also gives 29 (fp = 0x50 like the target). Left: arg address computations, VU_I temp sq 0x80, prologue vMin/vMax store order.
// fresh3 (Claude agent, laneC18 2026-10-23): aligned 35 -> 33: VU_I ctor as plain `q = i` (no por asm). Target still stores the raw lw value to 0x80 (sq v0) and moves it to a1 with por (a movti); ours keeps it in a register.
// fresh2 (Claude agent, laneC4 2026-10-23): aligned 41 -> 35 with int-index form D_003DD2CC[k], [k+2], [k+4] (k = D_002C3C5C*20); target hoists sym into s5 and 0x50 into fp.
// fresh1 (Claude agent, 2026-10-23): aligned 41 (= v2). D_003DD2CC is really &D_003DD2C0[i].a[0].pv (SPRBUF[2], 0x50 each); args are a[0].pv, a[1].pv, a[2].pv. Left: target hoists sym+0xC into s5 and 0x50 into fp, forms &g_clock fully then lw 4.
typedef int qword __attribute__((mode(TI)));
struct M4 { qword a[4]; };
union VEC { qword q; struct { float x, y, z, w; } v; };
struct DL { void *head; void *tail; int ibDle; };
struct DLI { DL *m_pdl; void **m_ppv; int m_ibDle; DLI *m_pdliNext; };
struct BUF { char ab[0x2B0]; char ab2[0x560 - 0x2B0]; char ab3[0x840 - 0x560]; };
struct Q { BUF abuf[2]; int i; int c; };
struct SBE { int cb; char *pv; };
struct SPRBUF { unsigned long *aqw; char *pv; SBE a[8]; int c; int state; };
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };

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
struct VU_I { qword q; VU_I(int i) { __asm__("" : "=r"(q) : "0"(i), "r"((char *)D_003DD2CC)); } }; // VU_I: tied empty asm gives the target's sq v0,0x80 temp + por a1,v0; the "r"(D_003DD2CC) input is allocation-only (base address use, so the hoisted base gets s5 and 0x840 s6 like the target)
extern "C" {
M4 func_0015BFD8(void *p);
void func_00234CA0(int);
void func_00201620(int cb0, BUF *pb, int cb, void *p1, int cb2, void *p2, int x, int y);
void func_00201998(void);
int func_00139950(M4 *pm, VU_I dt, char *a, char *b, char *c, int n, int d, VEC *pvMin, VEC *pvMax);
void func_002017A0(BUF *pb, void *p1, void *p2, int n);
void func_00139098(Q *pq);
void func_002417F0(void *p, int a, int b);
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
    func_00201620(pq->c * 16, pb, pq->c * 16, pb->ab2, pq->c * 16, pb->ab3, 0, 0);
}
static inline qword Mid(qword a, qword b, VU_FLOAT h)
{
    qword c;
    __asm__("vmulax.xyzw $ACC, %1, %3x\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(c) : "j"(a), "j"(b), "j"(h.q));
    return c;
}
void func_00139AB8(PX *p)
{
    VEC vMin;
    VEC vMax;
    M4 m;
    vMin.q = 0;
    vMin.v.z = vMin.v.y = vMin.v.x = D_002A4AF4;
    vMax.q = 0;
    vMax.v.z = vMax.v.y = vMax.v.x = D_002A4AF8;
    m = func_0015BFD8(p->x170);
    {
    DLI dli;
    Q *pq;
    InitDli(&dli, &p->dl);
    pq = (Q *)PvNextDli(&dli);
    {
        BUF *pb = &pq->abuf[pq->i];
        func_00234CA0(0);
        func_00201620(pq->c * 16, pb, pq->c * 16, pb->ab2, pq->c * 16, pb->ab3, 0, 0);
    }
    while (pq) {
        Q *pqNext;
        int n, i;
        qword dt;
        SPRBUF *psb;
        func_00201998();
        pqNext = (Q *)PvNextDli(&dli);
        if (pqNext) Kick(pqNext);
        int dti = D_002DDED0[1]; int k = D_002C3C5C * 0x50; int k1 = k + 8;
        char **pp = (char **)((char *)D_003DD2CC + k);
        char **pa = pp;
        __asm__("" : "+r"(pa)); /* copy-through: keeps the target's daddu copy of pp */
        n = func_00139950(&m, VU_I(dti), pa[0], *(char **)((char *)D_003DD2CC + k1), pp[4], pq->c, p->x43C, &vMin, &vMax);
        i = (pq->i + 1) & 1;
        {
            BUF *pb = &pq->abuf[i];
            func_002017A0(pb, pb->ab2, pb->ab3, 0);
        }
        pq->c -= n;
        p->c444 -= n;
        if (pq->c <= 0) func_00139098(pq);
        else pq->i = i;
        pq = pqNext;
    }
    func_002417F0(D_002DE59C, 0, 0);
    if (p->c444 <= 0) {
        p->f9();
    } else {
        qword c, d, one, l;
        float g;
        c = Mid(vMin.q, vMax.q, VU_FLOAT(0.5f));
        p->vF0 = c;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(c), "j"(vMax.q));
        __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(d));
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
        __asm__("mtc1 %1, %0" : "=f"(g) : "r"(l));
        p->g100 = g + p->g120;
    }
    D_002DD2FC = dli.m_pdliNext;
    }
}
