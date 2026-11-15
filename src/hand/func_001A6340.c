/* func_001A6340 (0x1A6340): the LO's rotation as Euler angles in degrees (its world matrix decomposed, times
 * 180 / pi). */
typedef int qword __attribute__((mode(TI)));
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static __inline__ qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
#define RAD_TO_DEG 57.2957763671875f
extern void *MatJtLo__FP2LO(void);
extern qword DecomposeEulerMatrix__FP7MATRIX3(void *p);
qword func_001A6340(void)
{
    union { qword q; float f; } deg;
    qword rad = DecomposeEulerMatrix__FP7MATRIX3(MatJtLo__FP2LO());
    deg.q = Make(GetX(rad) * RAD_TO_DEG, GetY(rad) * RAD_TO_DEG, GetZ(rad) * RAD_TO_DEG);
    return deg.q;
}
