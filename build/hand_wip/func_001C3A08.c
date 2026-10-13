typedef int qword __attribute__((mode(TI)));
typedef struct VECTOR { float x, y, z, w; } __attribute__((aligned(16))) VECTOR;
extern float D_002C0D04;
void func_001C3500(void *p, int n, qword *pv);
void func_001E6F10(void *p, float g, VECTOR *pv, VECTOR *tangent);

void func_001C3A08(void *p, int unused, qword *pvec, float g)
{
    qword a[3];
    VECTOR b;
    union { qword q; float f; } s;
    qword r;
    func_001C3500(p, 1, a);
    func_001E6F10(p, g, &b, 0);
    if (pvec) {
        __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(*(int *)&D_002C0D04));
        __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(*(qword *)&b), "j"(a[0]), "j"(s.q));
        *pvec = r;
    }
}
