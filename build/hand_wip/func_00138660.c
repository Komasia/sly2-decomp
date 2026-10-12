typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct V3 { float x, y, z; };
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
void func_00117120(qword, qword, qword, qword, float, float, float, VU *, VU *, int);

static __inline__ qword Madd(qword a, qword v, qword s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, $vf0, %1\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(v), "j"(s));
    return r;
}

void func_00138660(struct P *p, struct Q *pq)
{
    float u;
    float tCur;
    float ratio;
    int iSeg;
    int i;
    VU c, d;
    struct Q q;
    VU w;
    float t[2];
    VU a, b;

    if (p->p4->xD4 >= 0) {
        struct O *po = p->xC[p->p4->xD4];
        if (po) {
            struct VTE *e = &po->vt[2];
            ((void (*)(void *, struct Q *))e->pfn)((char *)po + e->d, pq);
            return;
        }
        {
            qword v = p->x10;
            struct V3 *pv = (struct V3 *)&pq->xD0;
            struct V3 *pw = (struct V3 *)&pq->xF0;
//@@BEGIN
            pq->x9A = 2;
            pq->xC0.q = v;
            pq->xE0.q = v;
            pv->y = 0;
            pv->z = 0;
            pv->x = 0;
            pw->y = 0;
            pw->z = 0;
            pw->x = 0;
            pq->x8C = &pq->x84;
            pq->x84 = 1.0f;
            pq->x88 = &pq->x80;
            pq->x80 = 0.0f;
//@@END
        }
        return;
    }
    tCur = *pq->x88;
    if (p->x8 == 0) {
        u = tCur / p->p4->x74;
    } else {
        iSeg = func_00138370(p->x8->x4, p->x8->x8, &t[0], tCur, p->p4->x74);
        u = t[0] / p->x8->x8[iSeg].g4;
    }
    {
        qword z;
        __asm__("vsub.xyzw %0, $vf0, $vf0" : "=j"(z));
        b.q = a.q = z;
    }
    for (i = 0; i < p->p4->xC4; i++) {
        struct E *pe = (struct E *)(p->p4->xC8 + i * p->p4->xC0);
        struct O *po;
        if (pe->w == 0.0f)
            continue;
        po = p->xC[i];
        if (!po) {
            c.q = p->x10;
            d.f[1] = 0.0f;
            d.f[0] = 0.0f;
            d.f[2] = 0.0f;
        } else {
            struct B *pb = p->x8;
            if (!pb) {
                float g = pe->p4->x74;
                t[1] = u * g;
                ratio = g / p->p4->x74;
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
            func_00117120(q.xC0.q, q.xD0.q, q.xE0.q, q.xF0.q, q.x84 - q.x80, t[1] - q.x80, ratio, &c, &d, 0);
        }
        {
            qword s;
            __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(*(int *)&pe->w));
            w.q = s;
            a.q = Madd(a.q, c.q, s);
            b.q = Madd(b.q, d.q, s);
        }
    }
    pq->x9A = 4;
    pq->xC0.q = a.q;
    pq->xD0.q = b.q;
}
