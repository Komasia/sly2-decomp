// v10 (Claude agent, laneC19 2026-10-23): aligned 2 -> 1. The FIRST Madd's vmaddx is a non-volatile asm (MaddN; the vadda stays volatile with "memory"): sched2 then issues the w store before a's spill store like the target. Left: b reload (lqc2 vf2,0x150) vs d load (lqc2 vf3,0x10) order before the 2nd vadda (ours d first: sched1 puts the d load before the w store, so it wins the luid tie).
// v9 (Claude agent, laneC18 2026-10-23): aligned 8 -> 2. (1) pe->w loaded into a commented register pin wb in $19 (pe's dying reg, like the target), qmtc2 asm volatile. (2) b declared before a on separate lines AND `asm(vsub -> a); i = 0; b = a;` (the i = 0 between stops cse swapping the copy so the asm writes a, slot 0x140). (3) "memory" clobber on Madd's vadda. Left: in the 2nd Madd block the target orders sqc2 w, sqc2 a, lqc2 b, lqc2 d; ours sqc2 a, lqc2 d, sqc2 w, lqc2 b (sched2 rank).
// v8 (Claude agent, laneC17 2026-10-23): aligned 23 -> 8. a/b plain qword locals; NO pin; one commented empty asm using pq at the end (global-alloc priority: pq s2, pe s3). Plus d stores ordered c, d2, d1, d0. Left: zero-init slot of the sqc2, lw s3,0(s3) for pe->w, 2nd Madd VF numbers.
// v5 (Claude agent, laneC16 2026-10-23): aligned 30 -> 23: like v4 but the ONE pin is pq in $18 (copied from a renamed param; adds a daddu a3,a1 in the prologue and a3 uses in the first branch) instead of pe.
// v3 (Claude agent, laneC16 2026-10-23): aligned 57 -> 39. Also Madd ties r to a ("0"(a)) and the vadda asm has an unused "j"(s) (allocation-only). The pb == NULL branch reads p->p4 through a volatile P*: the target reloads p->p4 there, so the loop's p->p4 pseudo dies at the xC8 load (v1) like the target. Left: pq/pe s2/s3 swap, !po store order, b init via qmfc2/sq, Madd VF numbering, final store order.
// fresh1 (Claude agent, 2026-10-23): aligned 57 (old v2 58). Left: p/pe s3/s1 swap, init-store order, VF numbering in the madd block. Note: the assembler swaps vadda operands, so write "%0, $vf0".
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct VTE { short d; short pad; void *pfn; };
struct O { struct VTE *vt; };
struct SEG { float g0; float g4; };
struct CL { char pad[0x74]; float x74; };
struct E { float w; struct CL *p4; };
struct A { char pad[0x74]; float x74; char pad2[0xC0 - 0x78]; int xC0; int xC4; char *xC8; char pad3[0xD4 - 0xCC]; int xD4; };
struct B { int x0; void *x4; struct SEG *x8; };
struct P { int pad; struct A *p4; struct B *x8; struct O **xC; qword x10; };
struct Q {
    char pad[0x80];
    float x80;
    float x84;
    float *x88;
    float *x8C;
    char pad90[0x9A - 0x90];
    short x9A;
    char pad9C[0xC0 - 0x9C];
    VU xC0;
    VU xD0;
    VU xE0;
    VU xF0;
};
int func_00138370(void *, struct SEG *, float *, float, float);
void *func_002333B4(void *, int, int);
void func_00117120(float, float, float, qword, qword, qword, qword, VU *, VU *, int);

static __inline__ qword Madd(qword a, qword v, qword s)
{
    qword r;
    __asm__ __volatile__("vadda.xyzw $ACC, %0, $vf0" : : "j"(a), "j"(s) : "memory"); /* unused "j"(s): allocation-only operand (Claude agent) */
    __asm__ __volatile__("vmaddx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(s), "0"(a)); /* "0"(a): r shares a's VF reg like the target (Claude agent) */
    return r;
}


static __inline__ qword MaddN(qword a, qword v, qword s)
{
    qword r;
    __asm__ __volatile__("vadda.xyzw $ACC, %0, $vf0" : : "j"(a), "j"(s) : "memory");
    __asm__("vmaddx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(s), "0"(a));
    return r;
}

void func_00138660(struct P *p, struct Q *pq)
{
    VU c, d;
    struct Q q;
    VU w;
    float t[2];
    qword a, b;
    float u, ratio;
    int iSeg, i;
    struct A *pa = p->p4;

    if (pa->xD4 >= 0) {
        struct O *po = p->xC[pa->xD4];
        if (po) {
            struct VTE *e = &po->vt[2];
            ((void (*)(void *, struct Q *))e->pfn)((char *)po + e->d, pq);
        } else {
            qword v = p->x10;
            float *pv = pq->xD0.f;
            float *pw = pq->xF0.f;
            float *p80;
            pq->x9A = 2;
            pq->xE0.q = v;
            pq->xC0.q = v;
            pv[2] = 0;
            pv[1] = 0;
            pv[0] = 0;
            pw[2] = 0;
            pw[1] = 0;
            p80 = &pq->x80;
            pq->x8C = &pq->x84;
            pq->x84 = 1.0f;
            pq->x88 = p80;
            pq->x80 = 0.0f;
            pw[0] = 0;
        }
        return;
    }
    {
        float tCur = *pq->x88;
        if (!p->x8) {
            u = tCur / pa->x74;
        } else {
            iSeg = func_00138370(p->x8->x4, p->x8->x8, &t[0], tCur, pa->x74);
            u = t[0] / p->x8->x8[iSeg].g4;
        }
    }
    __asm__("vsub.xyzw %0, $vf0, $vf0" : "=j"(a));
    i = 0;
    b = a;
    for (; i < p->p4->xC4; i++) {
        struct E *pe = (struct E *)(p->p4->xC8 + i * p->p4->xC0);
        struct O *po;
        if (pe->w == 0.0f)
            continue;
        po = p->xC[i];
        if (!po) {
            c.q = p->x10;
            d.f[2] = 0.0f;
            d.f[1] = 0.0f;
            d.f[0] = 0.0f;
        } else {
            struct B *pb = p->x8;
            if (!pb) {
                float g = pe->p4->x74;
                ratio = g / ((struct P volatile *)p)->p4->x74; /* volatile read (Claude agent): the target reloads p->p4 here (no cse with the loop test's load) */
                t[1] = u * g;
            } else {
                struct SEG *ps = (struct SEG *)((char *)pe + pb->x0) + iSeg;
                float gMax = pe->p4->x74;
                float g4 = ps->g4;
                t[1] = ps->g0 + u * g4;
                if (gMax < t[1])
                    t[1] -= gMax;
                ratio = g4 / pb->x8[iSeg].g4;
            }
            func_002333B4(&q, 0, 0x100);
            q.x88 = &t[1];
            {
                struct VTE *e = &po->vt[2];
                ((void (*)(void *, struct Q *))e->pfn)((char *)po + e->d, &q);
            }
            func_00117120(q.x84 - q.x80, t[1] - q.x80, ratio, q.xC0.q, q.xD0.q, q.xE0.q, q.xF0.q, &c, &d, 0);
        }
        {
            qword s;
            register int wb asm("$19") = *(int *)&pe->w; /* register pin (Claude agent): target loads pe->w into pe's dying register */
            __asm__ __volatile__("qmtc2.ni %1, %0" : "=j"(s) : "r"(wb));
            a = MaddN(a, c.q, s);
            w.q = s;
            b = Madd(b, d.q, s);
        }
    }
    pq->x9A = 4;
    pq->xC0.q = a;
    pq->xD0.q = b;
    __asm__ __volatile__("" : : "r"(pq)); /* empty asm (Claude agent): one more use of pq for global-alloc priority (pq s2, pe s3 like the target) */
}
