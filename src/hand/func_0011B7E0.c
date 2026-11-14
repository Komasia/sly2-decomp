typedef int VU_VECTOR __attribute__((mode(TI)));
typedef struct MATRIX3 { float mat[3][4]; } __attribute__((aligned(16))) MATRIX3;

extern VU_VECTOR g_normalZ;
MATRIX3 BuildLookAtMatrix__FP6VECTORG9VU_VECTORT1(VU_VECTOR vecX, VU_VECTOR vecY);
void *s1_memcpy(void *pvDst, const void *pvSrc, unsigned int cb) asm("memcpy");

MATRIX3 *func_0011B7E0(MATRIX3 *pmat, VU_VECTOR vec)
{
    MATRIX3 mat = BuildLookAtMatrix__FP6VECTORG9VU_VECTORT1(vec, g_normalZ);
    s1_memcpy(pmat, &mat, sizeof(MATRIX3));
    return pmat;
}
