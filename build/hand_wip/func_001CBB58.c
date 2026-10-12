typedef struct VECTOR { float x, y, z, w; } __attribute__((aligned(16))) VECTOR;
struct S { char pad[0x240]; VECTOR v; };
void func_001E6F10(void *a, VECTOR *pv, int n);
void func_001CBB58(void *a, struct S *p, VECTOR *pv)
{
    VECTOR v;
    func_001E6F10(a, &v, 0);
    if (pv) {
        __asm__ ("lqc2 $vf1, %0" : : "m"(v));
        __asm__ ("lqc2 $vf2, %0" : : "m"(p->v));
        __asm__ __volatile__("vsub.xyzw $vf1, $vf1, $vf2");
        __asm__ __volatile__("sqc2 $vf1, %0" : "=m"(*pv));
    }
}
