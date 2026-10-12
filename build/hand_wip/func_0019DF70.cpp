typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
#include "mat.h"
typedef struct MATRIX3 M3;
typedef struct { short d; short pad; qword (*pfn)(void *); } VT;
struct S14 { char pad[0x74]; float x74; };
struct S1030 { char pad[0x14]; struct S14 *x14; int pad2; float x1c; };
struct O { char pad[0xC]; VT *vt; char pad2[0x1030-0x10]; struct S1030 *x1030; };
struct P { struct O *x0; int x4; int x8; int xc; float x10; int x14; int x18; };
struct CLOCK { float t; float dt; };
extern "C" struct CLOCK D_002DDED0;
extern "C" qword D_002A2DD0;
extern "C" void func_001C3500(int a, int b, M3 *pm, float g);
extern "C" M3 *func_001A6318(struct O *o);
extern "C" void func_00117308(M3 *a, float g, float dt, float one, qword v, M3 *pm, qword z, M3 *pm2, int n);
extern "C" M3 func_0011BC00(M3 *a, M3 *b);
extern "C" void func_0011BCF8(M3 *pm, float *pg, U *pv);
extern "C" void func_0019DF70(struct P *p)
{
    M3 m, m2, m4;
    U vec;
    float f;
    M3 *pm;
    func_001C3500(p->xc, p->x18 == 0, &m, p->x10);
    if (p->x4 == 0 || p->x4 == 4) {
        struct O *o = p->x0;
        float dt = D_002DDED0.dt;
        float g = o->x1030->x14->x74 - o->x1030->x1c;
        M3 *pa;
        g = g > dt ? g : dt;
        pa = func_001A6318(o);
        func_00117308(pa, g, dt, 1.0f, p->x0->vt[34].pfn((char *)p->x0 + p->x0->vt[34].d), &m, D_002A2DD0, &m2, 0);
        pm = &m2;
    } else {
        m2 = m;
        pm = &m2;
    }
    m4 = func_0011BC00(func_001A6318(p->x0), pm);
    func_0011BCF8(&m4, &f, &vec);
    {
        qword s;
        qword r;
        __asm__("qmtc2.ni %1, %0" : "=j"(s) : "r"(f / D_002DDED0.dt));
        __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(vec.q), "j"(s));
        ((void (*)(void *, qword))p->x0->vt[36].pfn)((char *)p->x0 + p->x0->vt[36].d, r);
    }
}
