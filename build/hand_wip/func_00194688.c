typedef int qword __attribute__((mode(TI)));
struct A;
typedef struct { short d; short pad; void (*pfn)(void *, ...); } VTE;
typedef struct { short d; short pad; void (*pfn)(void *, void *, qword *, int, float); } VTE3;
typedef union { VTE v; VTE3 v3; } VTU;
struct A { char pad[0x10]; int x10; char pad1[4]; int x18; int x1c; VTU *vt; };
struct LO { char pad[0x10]; int x10; char pad2[0x38 - 0x14]; float x38; };
typedef struct { struct LO *x0; struct A *x4; float x8; int xc; int x10; float x14; float x18; float x1c; qword x20; } E;
struct Y { char pad[0x18]; int x18; };
struct P {
    char pad[0x2CC]; struct LO *x2cc; char pad1[0x37C - 0x2D0]; struct LO *x37c; char pad2[0x4D4 - 0x380];
    struct LO *x4d4; struct Y *x4d8; char pad3[0xF5C - 0x4DC]; struct LO *xf5c; char pad4[0x1000 - 0xF60];
    int x1000; char pad5[0x18C4 - 0x1004]; struct LO *x18c4; char pad6[0x1F18 - 0x18C8]; struct LO *x1f18;
};
struct CLOCK { float t; float dt; };
extern struct CLOCK D_002DDED0;
extern struct P *D_002E1E40;
extern int D_002E1E4C;
extern float D_002BF664;
qword func_001A62E8(void *p);
void func_001AE5A0(void *dst, void *src, int cb);
void *func_002333B4(void *p, int c, int cb);
void *func_002332B8(void *dst, void *src, int cb);
void func_00194688(void *unused, struct P *p, qword pos, struct LO *lo, struct A *a, int n, E *ae)
{
    E e;
    int i;
    if (lo->x10) {
        qword q = func_001A62E8(lo);
        qword d, t;
        float r, dd;
        int f;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(q), "j"(pos));
        __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(d), "=&j"(t));
        __asm__("qmfc2.ni %0, %1" : "=r"(dd) : "j"(d));
        r = lo->x38;
        f = r * r < dd;
        if (f) return;
    }
    if (lo == p->x4d4) return;
    if (lo == p->x2cc) return;
    if (a->x18 && p->x4d8 && a->x18 == p->x4d8->x18) return;
    if (lo == p->x37c) return;
    if (lo == p->xf5c) return;
    if (p == D_002E1E40) {
        if (lo == p->x18c4) return;
        if (lo == p->x1f18) return;
    }
    if (!(p->x1000 & a->x1c)) return;
    if (D_002E1E4C) {
        if (p->x4d4) return;
        if (p->xf5c) return;
        if (p == D_002E1E40) {
            if (p->x18c4) return;
            if (p->x1f18) return;
        }
    }
    a->vt[2].v.pfn((char *)a + a->vt[2].v.d, p, &e.x18);
    a->vt[3].v3.pfn((char *)a + a->vt[3].v3.d, p, &e.x20, 0, e.x18);
    {
        qword d, t;
        float dist;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(pos), "j"(e.x20));
        __asm__("vmul.xyz %0, %0, %0\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z\n\tvsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d), "=&j"(t));
        __asm__("qmfc2.ni %0, %1" : "=r"(dist) : "j"(d));
        e.x8 = dist;
    }
    e.xc = a->x10;
    a->vt[4].v.pfn((char *)a + a->vt[4].v.d, &e.x8);
    if (D_002BF664 < e.x8) return;
    if (a->x18) {
        for (i = 0; i < n; i++) {
            E *pe = &ae[i];
            if (!pe->x4) break;
            if (pe->x4->x18 == a->x18) {
                if (e.x8 < ae[i].x8) {
                    func_001AE5A0(&ae[i], &ae[i + 1], (n - 1 - i) * 0x30);
                    func_002333B4(&ae[n - 1], 0, 0x30);
                    ae[n - 1].x8 = D_002BF664;
                    break;
                }
                return;
            }
        }
    }
    i = n;
    do {
        E *pe = &ae[i - 1];
        if (e.xc < pe->xc || (pe->xc == e.xc && pe->x8 < e.x8))
            break;
    } while (--i != 0);
    if (i == n) return;
    func_002332B8(&ae[i + 1], &ae[i], (n - i) * 0x30 - 0x30);
    e.x0 = lo;
    e.x4 = a;
    e.x14 = D_002DDED0.t;
    e.x10 = 0;
    e.x1c = 0.0f;
    ae[i] = e;
}
