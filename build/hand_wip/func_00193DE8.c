typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct LO;
typedef struct { short d; short pad; void (*pfn)(void *, int, void *, qword, qword, qword); } VT82;
typedef struct { short d; short pad; qword (*pfn)(void *); } VT33;
typedef union { VT82 v82; VT33 v33; } VTE;
struct LO { char pad[0xC]; VTE *vt; char pad2[0x190 - 0x10]; qword x190; char pad3[0x218 - 0x1A0]; qword *x218; };
struct T { char pad[0xE4]; int xe4; char pad2[0x1BC - 0xE8]; int x1bc; };
struct S { struct LO *x0; int x4; int x8; int xc; int x10; struct T *x14; int x18; float x1c; float x20; };
extern qword D_002A2DB0;
qword func_001A62E8(void *p);
qword *func_001A6318(struct LO *p);
void func_001E6ED8(struct T *t, qword a, int n, qword *p0, qword *p1, float *pf0, float *pf1, float g);
float func_001E6620(struct T *t);
float func_001E6648(struct T *t);
void func_001E6F10(struct T *t, qword *pv, int n, float g);
static __inline__ float Dot(qword a, qword b)
{
    qword d, t;
    float r;
    __asm__("vmul.xyz %0, %2, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(t) : "j"(a), "0"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(r) : "j"(d));
    return r;
}
static __inline__ float Dot2(qword a, qword b)
{
    qword d, t;
    float r;
    __asm__("vmul.xyz %0, %0, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(t) : "j"(b), "0"(a));
    __asm__("qmfc2.ni %0, %1" : "=r"(r) : "j"(d));
    return r;
}
void func_00193DE8(struct S *p)
{
    switch (p->x8) {
    case 4: {
        U pos;
        pos.q = func_001A62E8(p->x14);
        p->x0->vt[82].v82.pfn((char *)p->x0 + p->x0->vt[82].v82.d, 0x23, p->x14, pos.q, D_002A2DB0, *p->x0->x218);
        break;
    }
    case 3: {
        U v0, v1;
        struct T *t = p->x14;
        int k;
        func_001E6ED8(t, *p->x0->x218, 0, &v0.q, &v1.q, &p->x1c, &p->x20, p->x1c);
        k = 0x22;
        if (!t->x1bc && !t->xe4) {
            U vel;
            qword *m;
            qword w;
            float d0, d1;
            vel.q = p->x0->vt[33].v33.pfn((char *)p->x0 + p->x0->vt[33].v33.d);
            d0 = Dot(vel.q, v1.q);
            m = func_001A6318(p->x0);
            __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
                    : "=j"(w) : "j"(p->x0->x190), "j"(m[0]), "j"(m[1]), "j"(m[2]));
            d1 = -Dot2(w, v1.q);
            if ((d0 < -2.0f || d1 < 2.0f) && p->x20 < func_001E6620(t) + 50.0f) {
                k = 0x2A;
                func_001E6F10(t, &v0.q, 0, func_001E6620(t) + 50.0f);
            } else if ((2.0f < d0 || -2.0f < d1) && func_001E6648(t) - 50.0f < p->x20) {
                U s;
                k = 0x2A;
                func_001E6F10(t, &v0.q, 0, func_001E6648(t) - 50.0f);
                __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(-1.0f));
                __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(v1.q) : "j"(v1.q), "j"(s.q));
            }
        }
        p->x0->vt[82].v82.pfn((char *)p->x0 + p->x0->vt[82].v82.d, k, t, v0.q, v1.q, *p->x0->x218);
        break;
    }
    }
}
