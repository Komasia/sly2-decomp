/* FInvertMatrix3: invert a 3x3 matrix (rows of 4 floats) with the general inverter. */
struct MATRIX3;
int FInvertMatrix(int cColumn, int c, struct MATRIX3 *pmatSrc, struct MATRIX3 *pmatDst) asm("FInvertMatrix__FiPfT1");

// name: SafeHouse port (FInvertMatrix3)
void FInvertMatrix3__FP7MATRIX3T0(struct MATRIX3 *pmatSrc, struct MATRIX3 *pmatDst)
{
    FInvertMatrix(4, 3, pmatSrc, pmatDst);
}
