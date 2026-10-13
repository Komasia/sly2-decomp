typedef int qword __attribute__((mode(TI)));
typedef struct VECTOR { float x, y, z, w; } __attribute__((aligned(16))) VECTOR;
struct S { char pad[0x240]; VECTOR v; };
void func_001E6F10(void *a, float g, VECTOR *pv, int n);
void func_001CBB58(void *a, float g, struct S *p, VECTOR *pv)
{
    VECTOR v;
    qword diff;
    func_001E6F10(a, g, &v, 0);
    if (pv) {
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(diff) : "j"(*(qword *)&v), "j"(*(qword *)&p->v));
        *(qword *)pv = diff;
    }
}
