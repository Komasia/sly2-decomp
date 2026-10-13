typedef int qword __attribute__((mode(TI)));
struct S { int a0; int a4; int pad[2]; qword v; };
void func_001E67B8(int, float, qword *, int);
qword func_001FA970(int, qword);
static inline qword Sub(qword a,qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float LenSq(qword a) {
    qword d,one;float r;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(a));
    __asm__("mtc1 %1, %0" : "=f"(r) : "r"(d));
    return r;
}
float func_001E69A0(float g, struct S *p)
{
    qword v; float f;
    func_001E67B8(p->a0, g, &v, 0);
    if (p->a4 == 0) f=LenSq(Sub(p->v,v));
    else { qword r, k; r=func_001FA970(p->a4, Sub(v,p->v)); __asm__("qmtc2.ni %1, %0" : "=j"(k) : "r"(r)); f=LenSq(k); }
    return f;
}
