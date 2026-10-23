// fresh1 (Claude agent, 2026-10-23): aligned 89 (old 94). m = func_0015BFD8 only inside if (x160 == 0); extern const float min/max; CLOCK *pclock for dt (gives the target's hoisted t3 = &g_clock). Left: target's loop givs are based on &pb->c[i] / &pbn->c[j] (negative offsets), ours on a[i]; frame 0x10 smaller.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; struct { float x, y, z, w; } v; } VEC;
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(*(int *)&f)); } };
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
    VEC vMin;
    VEC vMax;
    vMin.q = 0;
    vMin.v.z = vMin.v.x = vMin.v.y = D_002A4AFC;
    vMax.q = 0;
    vMax.v.z = vMax.v.x = vMax.v.y = D_002A4B00;
    struct DLI dli;
    struct Q *pq;
    InitDli(&dli, &p->dl);
    pq = (struct Q *)PvNextDli(&dli);
    while (pq) {
        int i, j, cDead, iNext;
        struct BUF *pb, *pbn;
        struct CLOCK *pclock = &D_002DDED0;
        j = 0;
        cDead = 0;
        pb = &pq->abuf[pq->i];
        iNext = (pq->i + 1) & 1;
        pbn = &pq->abuf[iNext];
        for (i = 0; i < pq->c; i++) {
            float tEnd = pb->b[i].v.w;
            if (tEnd <= D_002DDED0.t) {
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
                float rem = tEnd - D_002DDED0.t;
                float dt = pclock->dt;
                func_00117120(rem, rem < dt ? rem : dt, 1.0f, pb->a[i].q, pb->b[i].q, pq->ae[i].v0, pq->ae[i].v10, &pbn->a[j].q, &pbn->b[j].q, 0);
                if (j != i)
                    pq->ae[j] = pq->ae[i];
                break;
            }
            }
            pbn->a[j].v.w = pb->a[i].v.w;
            pbn->b[j].v.w = pb->b[i].v.w;
            pbn->c[j] = pb->c[i];
            if (p->x43C == 2)
                pbn->c[j].v.w = func_0011CF60(pb->c[i].v.w + pb->c[i].v.z * pclock->dt);
            vMin.q = Min(vMin.q, pbn->a[j].q);
            vMax.q = Max(vMax.q, pbn->a[j].q);
            j++;
        }
        pq->c -= cDead;
        p->c444 -= cDead;
        if (pq->c <= 0)
            func_00139098(pq);
        else
            pq->i = iNext;
        pq = (struct Q *)PvNextDli(&dli);
    }
    if (p->c444 <= 0) {
        struct VT *pvt = p->pvt;
        pvt[9].pfn((char *)p + pvt[9].d);
    } else {
        qword c, d, one, l;
        float g;
        c = Mid(vMin.q, vMax.q, VU_FLOAT(0.5f));
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(c), "j"(vMax.q));
        p->vF0 = c;
        __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(d));
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
        __asm__("mtc1 %1, %0" : "=f"(g) : "r"(l));
        p->g100 = g + p->g120;
    }
    D_002DD2FC = dli.m_pdliNext;
    }
}
