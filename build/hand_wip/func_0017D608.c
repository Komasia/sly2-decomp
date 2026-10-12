typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
qword D_002A2DC0;
extern float D_002BE750, D_002BE754;
struct X { int a[4]; };
struct Y { int pad[4]; qword v; char pad2[0x40]; };
struct X *func_001AE478(struct X *x);
void func_001AE4A0(struct X *x, int n);
void func_001B44D8(int *pa, int *pb);
int func_0014CC58(int n, qword a, qword b, int c, int d, struct Y *y);
static __inline__ qword MAdd(qword p, qword up, int s0) {
    U u;
    register int s __asm__("$3") = s0;
    qword r;
    __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(s));
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(p), "j"(up), "j"(u.q));
    return r;
}
int func_0017D608(qword *pv) {
    struct X x;
    int na, nb;
    qword va, vb;
    func_001AE478(&x);
    func_001B44D8(&na, &nb);
    va = MAdd(*pv, D_002A2DC0, *(int *)&D_002BE750);
    vb = MAdd(*pv, D_002A2DC0, *(int *)&D_002BE754);
    {
    struct Y y;
    if (func_0014CC58(0, va, vb, na, nb, &y)) {
        *pv = y.v;
        func_001AE4A0(&x, 2);
        return 1;
    }
    }
    func_001AE4A0(&x, 2);
    return 0;
}
