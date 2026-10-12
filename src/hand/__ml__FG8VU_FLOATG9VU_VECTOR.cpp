typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword q; };
struct VU_VECTOR { qword q; };
qword operator*(VU_FLOAT f, VU_VECTOR v)
{
    qword r;
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(f.q), "j"(v.q));
    return r;
}
