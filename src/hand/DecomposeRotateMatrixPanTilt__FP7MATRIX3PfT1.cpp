struct MATRIX3 { float mat[3][4]; } __attribute__((aligned(16)));
extern "C" float atan2f(float y, float x);
static inline float sqrtf_(float x) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }

void DecomposeRotateMatrixPanTilt(MATRIX3 *pmat, float *ppan, float *ptilt)
{
    *ppan = atan2f(pmat->mat[0][1], pmat->mat[0][0]);
    *ptilt = atan2f(pmat->mat[0][2], sqrtf_(pmat->mat[0][0] * pmat->mat[0][0] + pmat->mat[0][1] * pmat->mat[0][1]));
}
