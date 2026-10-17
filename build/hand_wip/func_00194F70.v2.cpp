// (Claude agent) v2 aligned 51 (was 55): last loop as `if (!r) break; a->x10 = r;` gives the target's bnel layout. Left: pq spilled to 0x20(sp) in target (ours spills i-1 instead; fp role swap), copy of r into a2.
typedef int qword __attribute__((mode(TI)));
struct O;
typedef struct { short d; short pad; int (*pfn)(void *, float *); } VTA1;
typedef struct { short d; short pad; void (*pfn)(void *, void *, qword *, int, float); } VTA3;
typedef union { VTA1 v1; VTA3 v3; } VTA;
typedef struct { short d; short pad; void (*pfn)(void *, qword); } VTL;
struct A { char pad[0x14]; int x14; char pad2[0x20 - 0x18]; VTA *vt; };
struct L { char pad[0xC]; VTL *vt; };
typedef struct { int x0; struct A *x4; float x8; int xc; struct L *x10; int x14; float x18; float x1c; int pad[4]; } __attribute__((aligned(16))) E;
struct P { char pad[0x4678]; int c; int pad2; E ae[4]; };
struct Q { char pad[0x9C4]; void *x9C4; };
struct CLOCK { float t; float dt; };
extern "C" { extern struct CLOCK D_002DDED0;
extern int D_002E1E50;
extern float D_002BF710, D_002BF714;
extern char D_002BF718[];
extern char D_002DEB30[]; }
extern "C" {
int func_00194F48(const void *, const void *);
void func_002338C0(void *base, int n, int cb, int (*cmp)(const void *, const void *));
void *func_002332B8(void *dst, void *src, int cb);
float func_0011D018(float, float, float, void *, float *);
void func_001F7BF8(void *p, float f);
void func_001619A0(void *p, int n, int m);
struct L *func_001956D0(struct P *p, void *x, E *pe);
void func_00194F70(struct P *p, struct Q *pq, int n, E *ae);
}
void func_00194F70(struct P *p, struct Q *pq, int n, E *ae)
{
    int i, k;
    E *e, *a, *pe;
    if (n > 0) {
        func_002338C0(ae, n, 0x30, func_00194F48);
        if (ae->x4->x14 != -1) ae->xc = 1;
    }
    for (i = p->c - 1; i >= 0; i--) {
        e = &p->ae[i];
        int j = n;
        goto test;
        do {
        a = &ae[j];
        if (e->x0 == a->x0) {
            e->x8 = a->x8;
            if (!e->x10) {
                e->x18 = a->x18;
                e->x1c = 0.0f;
            } else {
                float ag[2];
                qword q;
                float w;
                int fWrap = a->x4->vt[1].v1.pfn((char *)a->x4 + a->x4->vt[1].v1.d, ag);
                if (fWrap) {
                    float d;
                    w = ag[1] - ag[0];
                    d = a->x18 - e->x18;
                    if (w * 0.5f < d) {
                        d -= w;
                        a->x18 = e->x18 + d;
                    } else if (d < w * -0.5f) {
                        d += w;
                        a->x18 = e->x18 + d;
                    } else {
                        fWrap = 0;
                    }
                }
                if (D_002E1E50) {
                    float dt = D_002DDED0.dt;
                    float v = e->x1c;
                    float vNew = v + dt * ((a->x18 - e->x18) * D_002BF710 + (a->x1c - v) * D_002BF714);
                    float vAvg;
                    e->x1c = vNew;
                    vAvg = (v + vNew) * 0.5f;
                    e->x18 = e->x18 + dt * vAvg;
                } else {
                    e->x18 = func_0011D018(e->x18, a->x18, D_002DDED0.dt, D_002BF718, &e->x1c);
                }
                if (fWrap) {
                    if (ag[1] < e->x18) e->x18 = e->x18 - w;
                    else if (e->x18 < ag[0]) e->x18 = e->x18 + w;
                }
                e->x4->vt[3].v3.pfn((char *)e->x4 + e->x4->vt[3].v3.d, pq, &q, 0, e->x18);
                e->x10->vt[29].pfn((char *)e->x10 + e->x10->vt[29].d, q);
            }
            func_002332B8(a, a + 1, (n - j) * 0x30 - 0x30);
            n--;
            goto next;
        }
    test:;
        } while (--j >= 0);
        if (e->x10) func_001F7BF8(e->x10, 0.5f);
        func_002332B8(e, e + 1, (3 - i) * 0x30);
        p->c--;
    next:;
    }
    for (k = 0; k < n; k++) {
        a = &ae[k];
        if (pq->x9C4 && a->xc == 1) {
            struct L *r = func_001956D0(p, pq->x9C4, a);
            if (!r) break;
            a->x10 = r;
        }
        p->ae[p->c++] = *a;
        func_001619A0(D_002DEB30, 0x3D, a->x0);
    }
    func_002338C0(p->ae, p->c, 0x30, func_00194F48);
}
