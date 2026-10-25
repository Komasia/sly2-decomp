// lilly5 (Claude agent T1673, 2026-10-25): lilly4 (aligned 10, no barrier, no pin) with the loop written like the matched
// sibling func_00139250: `while ((pq = PvNextDli(&dli)) != 0)` (jump.c copies the exit test; identical code).
// sched1 priorities in the join block (lilly4/5): every frame store feeds the pdl->ibDle load (prio 8; pdl is the inline
// param pseudo with no base value), so hiB = ibDle+5 = 13 in every spelling, clearMax = 11, the avMax[1] BLK clobber = 12
// (and it is only ready after vMin's stores), &p->dl = 11, hi(D_002DD2FC) = 9. The target needs an ALU/none insn of
// rank > hiB at t=2 (prio 13 with reg weight 0, or 14) beside lwc1 A. None of these reach it: union/array wrappers
// (U1/U2/U1[1]; their clobbers are BLK too: aligned 10/10/16/10), VC(float) this-ctor (cse folds `this`: 13), scalar
// qword vMax (68 differ), m_pdl/m_ppv stores moved before vMax's init (breaks the frame, 21).
// lilly4 (Claude agent T1669, 2026-10-25): aligned 10, no asm barrier, no pin (lilly3 13; lilly1 9 needs a barrier).
// lilly3 with vMax as `VECTOR avMax[1] = {{...}}`: the array init emits (clobber (mem:BLK)) after vMin's stores, so in
// sched1 vMin's chain is 3 deeper than vMax's (hiA 16, clearMin 14, hiB 13). t=1 is now hiA + clearMin (zero reload
// v1-able), and &p->dl / &dli / hi(D_002DD2FC) get the target's a0/a2/v1/a1. Left: at t=2 the ALU slot still goes to
// hiB (prio 13; &p->dl is 11 at most), so lwc1 A and hi(B) are adjacent, local-alloc's fake lifetimes give hiA v1, and the
// vMax clear (after hi(D_002DD2FC)) needs its own zero reload (one extra por). The target needs an ALU insn with prio >= 13
// at t=2, which none of the natural forms gives (hiB = vMax stores + 3 always outranks the vMax clear = stores + 1).
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; struct { float x, y, z, w; } v; } VEC;
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j,j"(q) : "r,m"(f), "i,r"(0)); } };
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
static inline qword Min(qword a, qword b) { qword r; __asm__("vmini.xyz %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Max(qword a, qword b) { qword r; __asm__("vmax.xyz %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Mid(qword a, qword b, VU_FLOAT h)
{
    qword c;
    __asm__("vmulax.xyzw $ACC, %1, %3x\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(c) : "j"(a), "j"(b), "j"(h.q));
    return c;
}
struct M4 { qword r[4]; };
struct VECTOR { float x, y, z; } __attribute__((aligned(16)));
struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));

struct DL { void *head; void *tail; int ibDle; };
struct DLI { struct DL *m_pdl; void **m_ppv; int m_ibDle; struct DLI *m_pdliNext; };
struct BUF { VEC a[0x2B]; VEC b[0x2B]; VEC c[0x2B]; char pad[0x840 - 0x810]; };
struct E { qword v0; qword v10; };
struct Q { struct BUF abuf[2]; int i; int c; struct E *ae; };
struct VT { short d; short pad; void (*pfn)(void *); };
struct P {
    char pad0[0xC]; struct VT *pvt; char pad10[0xF0 - 0x10]; qword vF0; float g100; char pad104[0x120 - 0x104]; float g120;
    char pad124[0x160 - 0x124]; int x160; char pad164[0x170 - 0x164]; char x170[0x43C - 0x170]; int x43C; int pad440; int c444; struct DL dl;
};
struct CLOCK { float t; float dt; };
#define CA(p) ((VEC *)((int)(p) - 0x560))
#define CB(p) ((VEC *)((int)(p) - 0x2B0))
extern struct CLOCK D_002DDED0;
extern struct DLI *D_002DD2FC;
extern int D_002BC9C0;
extern const float D_002A4AFC, D_002A4B00;
extern "C" {
void func_00139AB8(struct P *p);
struct M4 func_0015BFD8(void *p);
void func_00117120(float, float, float, qword, qword, qword, qword, qword *, qword *, int);
float func_0011CF60(float g);
void func_00139098(struct Q *pq);
void func_00139DC0(struct P *p);
}

static __inline__ void SetV(VEC *pv, float g)
{
    pv->q = 0;
    pv->v.z = pv->v.y = pv->v.x = g;
}
static __inline__ void InitDli(struct DLI *pdli, struct DL *pdl)
{
    pdli->m_pdl = pdl;
    pdli->m_ppv = (void **)pdl;
    pdli->m_ibDle = pdl->ibDle;
    pdli->m_pdliNext = D_002DD2FC;
    D_002DD2FC = pdli;
}
static __inline__ void *PvNextDli(struct DLI *pdli)
{
    void *pv = *pdli->m_ppv;
    pdli->m_ppv = (void **)((char *)pv + pdli->m_ibDle);
    return pv;
}
static __inline__ qword MulPoint(struct M4 *pm, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]), "j"(pm->r[3]), "j"(v));
    return r;
}

void func_00139DC0(struct P *p)
{
    struct M4 m;
    if (p->x160 == 0) {
        if (D_002BC9C0 == 0) {
            func_00139AB8(p);
            return;
        }
        m = func_0015BFD8(p->x170);
    }
    {
    VECTOR vMin = {D_002A4AFC, D_002A4AFC, D_002A4AFC};
    VECTOR avMax[1] = {{D_002A4B00, D_002A4B00, D_002A4B00}};
#define vMax avMax[0]
    struct DLI dli;
    struct Q *pq;
    InitDli(&dli, &p->dl);
    while ((pq = (struct Q *)PvNextDli(&dli)) != 0) {
        int i, j, cDead, iNext;
        struct BUF *pb, *pbn;
        j = 0;
        cDead = 0;
        pb = &pq->abuf[pq->i];
        iNext = (pq->i + 1) & 1;
        pbn = &pq->abuf[iNext];
        for (i = 0; i < pq->c; i++) {
            struct CLOCK *pclock = &D_002DDED0;
            float t = D_002DDED0.t;
            float tEnd = pb->b[i].v.w;
            if (tEnd <= t) {
                cDead++;
                continue;
            }
            switch (p->x160) {
            case 0: {
                qword v = MulPoint(&m, pb->b[i].q);
                pbn->b[j].q = v;
                pbn->a[j].q = AddScaled(pb->a[i].q, v, VU_FLOAT(pclock->dt));
                break;
            }
            case 1: {
                qword v = pb->b[i].q;
                pbn->b[j].q = v;
                pbn->a[j].q = AddScaled(pb->a[i].q, v, VU_FLOAT(pclock->dt));
                break;
            }
            case 2: {
                float rem = tEnd - t;
                float dt = pclock->dt;
                func_00117120(rem, dt < rem ? dt : rem, 1.0f, pb->a[i].q, pb->b[i].q, pq->ae[i].v0, pq->ae[i].v10, &pbn->a[j].q, &pbn->b[j].q, 0);
                if (j != i)
                    pq->ae[j] = pq->ae[i];
                break;
            }
            }
            {
            VEC *pcs = &pb->c[i];
            VEC *pcd = &pbn->c[j];
            CA(pcd)[0].v.w = CA(pcs)[0].v.w;
            CB(pcd)[0].v.w = CB(pcs)[0].v.w;
            *pcd = *pcs;
            if (p->x43C == 2)
                pcd->v.w = func_0011CF60(pcs->v.w + pcs->v.z * pclock->dt);
            *(qword *)&vMin = Min(*(qword *)&vMin, CA(pcd)[0].q);
            *(qword *)&vMax = Max(*(qword *)&vMax, CA(pcd)[0].q);
            }
            j++;
        }
        pq->c -= cDead;
        p->c444 -= cDead;
        if (pq->c <= 0)
            func_00139098(pq);
        else
            pq->i = iNext;
    }
    if (p->c444 <= 0) {
        struct VT *pvt = p->pvt;
        pvt[9].pfn((char *)p + pvt[9].d);
    } else {
        qword c, d, one, l;
        float g;
        c = Mid(*(qword *)&vMin, *(qword *)&vMax, VU_FLOAT(0.5f));
        p->vF0 = c;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(c), "j"(*(qword *)&vMax));
        __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(d));
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
        __asm__("mtc1 %1, %0" : "=f"(g) : "r"(l));
        p->g100 = g + p->g120;
    }
    D_002DD2FC = dli.m_pdliNext;
    }
}
