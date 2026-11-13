/* class: CID_49, the hack enemies (vt slot 26, a pool row taken again; SafeHouse hack.cpp ResetEnemySlot26): the hack
 * objects' reset (hit points to the maximum), then state 0. */
struct LO;
int func_0017F170(struct LO *plo, struct LO *pproxy);   /* the hack objects' slot 26 */
void SetEnemyState__FP2LOi(struct LO *plo, int state);

void func_00180638(struct LO *plo, struct LO *pproxy)
{
    func_0017F170(plo, pproxy);
    SetEnemyState__FP2LOi(plo, 0);
}
