typedef int qword __attribute__((mode(TI)));
struct S { int pad[8]; qword q20; qword q30; };
qword func_001507F8(struct S *p);
int func_0011D4D0(float a, float b, float eps);
static __inline__ float GetX(qword q)
{
    float x;
    __asm__("mtc1 %1, %0" : "=f"(x) : "r"(q));
    return x;
}
static __inline__ float GetY(qword q)
{
    float y;
    __asm__("prot3w %0, %1" : "=r"(y) : "r"(q));
    return y;
}
static __inline__ float GetZ(qword q)
{
    float z;
    __asm__("pextuw %0, $0, %1" : "=r"(z) : "r"(q));
    return z;
}
int func_00151018(struct S *p)
{
    int f = 0;
    qword a = p->q30;
    qword b = func_001507F8(p);
    if (func_0011D4D0(GetX(a), GetX(b), 0.0001f))
        if (func_0011D4D0(GetY(a), GetY(b), 0.0001f))
            if (func_0011D4D0(GetZ(a), GetZ(b), 0.0001f))
                f = 1;
    return f;
}
