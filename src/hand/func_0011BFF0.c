typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
typedef struct { float m[3][4]; } MATRIX3;
static __inline__ qword Make(float x, float y, float z)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
float GLimitAbs(float g, float gLimit) asm("GLimitAbs__Fff");
float asinf(float g);
float atan2f(float y, float x);
// name: SafeHouse port (DecomposeEulerMatrix)
qword DecomposeEulerMatrix__FP7MATRIX3(MATRIX3 *pmat)
{
    U r;
    qword q;
    float tilt = asinf(GLimitAbs(-pmat->m[0][2], 1.0f));
    if (tilt < 1.5706963539123535f) {
        if (-1.5706963539123535f < tilt) {
            float x = atan2f(pmat->m[1][2], pmat->m[2][2]);
            r.q = Make(x, tilt, atan2f(pmat->m[0][1], pmat->m[0][0]));
            q = r.q;
        } else {
            r.q = Make(0.0f, tilt, atan2f(-pmat->m[1][0], -pmat->m[2][0]));
            q = r.q;
        }
    } else {
        r.q = Make(0.0f, tilt, atan2f(-pmat->m[1][0], pmat->m[2][0]));
        q = r.q;
    }
    return q;
}
