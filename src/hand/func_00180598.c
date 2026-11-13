/* class: CID_49, the hack enemies (vt slot 12 = OnRemove; SafeHouse hack.cpp): the hack objects' removal, then state -1. */
struct LO;
void OnRemoveHackSo__FP2LO(struct LO *plo);
void SetEnemyState__FP2LOi(struct LO *plo, int state);

void func_00180598(struct LO *plo)
{
    OnRemoveHackSo__FP2LO(plo);
    SetEnemyState__FP2LOi(plo, -1);
}
