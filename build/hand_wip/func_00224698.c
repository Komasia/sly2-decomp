// WIP: structure right; '+j' asm on a forces the qmtc2/sqc2 spill like target. Remaining: n (D_002A2DA0 path) should be
// lq into a1 + qmtc2 in branch delay, and D_002A2DC0 reloaded as lq a2 (not CSE'd), vf numbering.
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
struct O;
struct S { char pad[0x150]; int k; char pad1[8]; int x15C; struct O *p160; };
extern qword D_002A2DC0, D_002A2DA0, D_002A2DD0;
extern char D_002C4300[], D_002C4310[];
void func_001F9B20(struct S *p);
qword func_001A62E8(void *p);
M3 *func_0011B830(M3 *pm, qword v, qword up);
void *func_001A6318(struct S *p);
void func_0011B938(void *pv, int a, M3 *pm);
void func_001F5C30(struct S *p, M3 *pm, void *a, qword b, void *c);
void func_00224698(struct S *p)
{
    M3 m;
    if (p->k == 0 || p->k == 4) return;
    func_001F9B20(p);
    if (p->x15C != 0x1A && p->x15C != 0x29) return;
    if (p->p160) {
        qword a = func_001A62E8(p->p160);
        qword b, d, t, one, l, n;
        float g;
        __asm__("" : "+j"(a));
        b = func_001A62E8(p);
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
        __asm__("vmul.xyz %1, %2, %3\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddz.x %1, %0, %1z" : "=&j"(one), "=&j"(t) : "j"(d), "j"(D_002A2DC0));
        __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(t) : "j"(D_002A2DC0), "j"(t));
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(d), "j"(t));
        __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(l), "=&j"(one) : "j"(d));
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(l));
        __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
        if (g < 1.0e-4f) {
            n = D_002A2DA0;
        } else {
            __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(n) : "j"(l), "j"(d));
        }
        {
            M3 m2;
            func_0011B830(&m2, n, D_002A2DC0);
            m = m2;
        }
    } else {
        func_0011B938(func_001A6318(p), 0, &m);
    }
    func_001F5C30(p, &m, D_002C4300, D_002A2DD0, D_002C4310);
}
