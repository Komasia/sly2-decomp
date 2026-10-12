typedef int qword __attribute__((mode(TI)));
struct S { int a0; int a4; int pad[2]; qword v; };
void func_001E67B8(int, qword *, int);
qword func_001FA970(int, qword);
float func_001E69A0(struct S *p)
{
    qword v, d, one, a, b;
    float f;
    func_001E67B8(p->a0, &v, 0);
    if (p->a4 == 0) {
        __asm__("lqc2 %0, %1" : "=j"(a) : "m"(p->v));
        __asm__("lqc2 %0, %1" : "=j"(b) : "m"(v));
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
        __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "0"(d));
        __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
    } else {
        qword r;
        __asm__("lqc2 %0, %1" : "=j"(b) : "m"(p->v));
        __asm__("lqc2 %0, %1" : "=j"(a) : "m"(v));
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
        r = func_001FA970(p->a4, d);
        __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(r));
        __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(d));
    }
    return f;
}
