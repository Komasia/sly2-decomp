/* class: CID_48, the hack ship (vt slot 12 = OnRemove; SafeHouse hack.cpp): the hack objects' removal, then state -1. */
struct LO;
void OnRemoveHackSo__FP2LO(struct LO *plo);
void SetShipState__FP2LOi(struct LO *plo, int state);

void func_0017F740(struct LO *plo)
{
    OnRemoveHackSo__FP2LO(plo);
    SetShipState__FP2LOi(plo, -1);
}
