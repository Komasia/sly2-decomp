/* func_001A63B0 (0x1A63B0): sets the LO's rotation from Euler angles in degrees (times pi / 180, built into a
 * matrix, then the vtable entry 30, the rotation setter). */
#include "so.h"
typedef struct { qword r[3]; } M3;
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
static __inline__ qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2
	mfc1 %1,%3
	pextlw %0,%1,%0
	mfc1 %1,%4
	pcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
struct LO;
void BuildEulerMatrix__FP6VECTORG9VU_VECTOR(M3 *pm, qword v);
#define DEG_TO_RAD 0.017453294f
void func_001A63B0(struct LO *plo, qword deg)
{
    M3 matCopy;
    union { qword q; float f; } rad;
    M3 mat;
    rad.q = Make(GetX(deg) * DEG_TO_RAD, GetY(deg) * DEG_TO_RAD, GetZ(deg) * DEG_TO_RAD);
    BuildEulerMatrix__FP6VECTORG9VU_VECTOR(&mat, rad.q);
    matCopy = mat;
    ((void (*)(struct LO *, M3 *))plo->pvt[30].pfn)((struct LO *)VT_THIS(plo, &plo->pvt[30]), &matCopy);
}
