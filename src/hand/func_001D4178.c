typedef int qword __attribute__((mode(TI)));
struct E { int a[8]; float g20; int b[11]; qword q50; };
struct S { char pad[0x190]; int c; int pad2[3]; struct E ae[8]; };
void UpdateSoBounds__FP2SO(struct S *p);
qword func_001A6F00(struct S *p, int n, qword q);
void func_001F5480(struct S *p, qword q, float g);
void func_001D4178(struct S *p) {
    int i;
    UpdateSoBounds__FP2SO(p);
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        func_001F5480(p, func_001A6F00(p, 0, pe->q50), pe->g20);
    }
}
