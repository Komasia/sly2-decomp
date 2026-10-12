typedef int qword __attribute__((mode(TI)));
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q)); return z; }
struct E { float x, y, z, w; };
struct O { char pad[0xE8]; int c; int a, b; struct E *ae; };
struct S { char pad[0x5AC]; struct O *po; int n5B0; };
qword func_001A62E8(struct S *p);
void func_001D2420(struct S *p) {
    qword q;
    int i;
    p->n5B0 = 0;
    q = func_001A62E8(p);
    for (i = 0; i < p->po->c; i++) {
        p->po->ae[i].z = GetZ(q);
    }
}
