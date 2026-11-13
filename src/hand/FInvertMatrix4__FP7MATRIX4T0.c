/* FInvertMatrix4: invert a 4x4 matrix with the general inverter. */
struct MATRIX4;
int FInvertMatrix(int cColumn, int c, struct MATRIX4 *pmatSrc, struct MATRIX4 *pmatDst) asm("FInvertMatrix__FiPfT1");

// name: SafeHouse port (FInvertMatrix4)
void FInvertMatrix4__FP7MATRIX4T0(struct MATRIX4 *pmatSrc, struct MATRIX4 *pmatDst)
{
    FInvertMatrix(4, 4, pmatSrc, pmatDst);
}
