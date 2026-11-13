/* ResetShip (the hack ship's vt slot 83, the reset): the hack object's base reset, then state 1 when the ship has the
 * pad (0x1C40F8), else 0, and its HUD updated. Source: SafeHouse port (hack.cpp). */
struct LO;
void ResetHackSoBase__FP2LO(struct LO *plo);
int func_001C40F8(struct LO *plo);   /* SafeHouse: NPoEnabled */
void SetShipState__FP2LOi(struct LO *plo, int st);
void UpdateHackHud__FP2LO(struct LO *plo);

// name: SafeHouse port (ResetShip)
void ResetShip__FP2LO(struct LO *plo)
{
    ResetHackSoBase__FP2LO(plo);
    if (func_001C40F8(plo))
        SetShipState__FP2LOi(plo, 1);
    else
        SetShipState__FP2LOi(plo, 0);
    UpdateHackHud__FP2LO(plo);
}
