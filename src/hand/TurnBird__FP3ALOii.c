/* TurnBird: a bird's turn is its rotation braked (BrakeAloRotation with its matrix +0x1E0 and angles +0x210). */
struct ALO;
struct MATRIX3;
void BrakeAloRotation(struct ALO *palo, struct MATRIX3 *pmat, float *prad) asm("BrakeAloRotation__FP3ALOP7MATRIX3Pf");

// name: SafeHouse port (TurnBird)
void TurnBird__FP3ALOii(struct ALO *palo, int a, int b)
{
    BrakeAloRotation(palo, (struct MATRIX3 *)((char *)palo + 0x1E0), (float *)((char *)palo + 0x210));
}
