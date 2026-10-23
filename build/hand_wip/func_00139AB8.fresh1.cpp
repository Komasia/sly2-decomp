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
struct VU_I { qword q; VU_I(int i) { __asm__("por %0, $0, %1" : "=r"(q) : "r"(i)); } };
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
extern void *D_002DE59C;
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
    vMin.v.z = vMin.v.x = vMin.v.y = D_002A4AF4;
    vMax.q = 0;
    vMax.v.z = vMax.v.x = vMax.v.y = D_002A4AF8;
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
        psb = &D_003DD2C0[D_002C3C5C];
        n = func_00139950(&m, VU_I(D_002DDED0[1]), psb->a[0].pv, psb->a[1].pv, psb->a[2].pv, pq->c, p->x43C, &vMin, &vMax);
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
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(c), "j"(vMax.q));
        p->vF0 = c;
        __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(d));
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
        {
            int li;
            __asm__("qmfc2.ni %0, %1" : "=r"(li) : "j"(l));
            __asm__("mtc1 %1, %0" : "=f"(g) : "r"(li));
        }
        p->g100 = g + p->g120;
    }
    D_002DD2FC = dli.m_pdliNext;
    }
}
