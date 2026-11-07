typedef struct MATRIX4 { float mat[4][4]; } __attribute__((aligned(16))) MATRIX4;

MATRIX4 InverseAffineMatrix4__FP7MATRIX4(void *pv);
MATRIX4 MulMatrix4__FP7MATRIX4T0Pv(MATRIX4 *pmatA, MATRIX4 *pmatB);

void func_0011C3D0(void *pv, MATRIX4 *pmat, MATRIX4 *pmatOut)
{
    MATRIX4 matRes;
    MATRIX4 matT;
    matT = InverseAffineMatrix4__FP7MATRIX4(pv);
    matRes = MulMatrix4__FP7MATRIX4T0Pv(pmat, &matT);
    *pmatOut = matRes;
}
