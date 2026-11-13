typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct O { char pad[0x40]; M3 mat; };
extern "C" M3 InverseMatrix3(const M3 *pm) asm("InverseMatrix3__FP7MATRIX3");
extern "C" void *s1_memcpy(void *d, const void *s, int n) asm("s1_memcpy");
static inline M3 Mul(const M3 &a, const M3 &b) return r
{
    qword a0 = a.r[0], a1 = a.r[1], a2 = a.r[2];
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
        : "=j"(r.r[0]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[0]));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
        : "=j"(r.r[1]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[1]));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z"
        : "=j"(r.r[2]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[2]));
}
// name: SafeHouse port (MatConvertXfs)
extern "C" M3 *MatConvertXfs__FP2XFT0P7MATRIX3Pv(M3 *pr, O *pa, O *pb, const M3 *pm)
{
    if (pa) {
        if (pb) {
            M3 m = Mul(Mul(InverseMatrix3(&pb->mat), pa->mat), *pm);
            s1_memcpy(pr, &m, 0x30);
        } else {
            M3 m = Mul(pa->mat, *pm);
            s1_memcpy(pr, &m, 0x30);
        }
    } else if (pb) {
        M3 m = Mul(InverseMatrix3(&pb->mat), *pm);
        s1_memcpy(pr, &m, 0x30);
    } else {
        s1_memcpy(pr, pm, 0x30);
    }
    return pr;
}
