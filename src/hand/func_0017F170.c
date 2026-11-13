/* class: HACKSO, the hack objects (cid 0x47; vt slot 26, a pool row taken again; SafeHouse hack.cpp
 * ResetHackSoSlot26): after the base 0x1CB518, the hit points back to their maximum. */
struct LO;
struct HACKSO {
    /* 0x000 */ char pad0[0x180];
    /* 0x180 */ int cHpMax;   /* field: SafeHouse port */
    /* 0x184 */ int cHp;      /* field: SafeHouse port */
};
void func_001CB518(struct HACKSO *plo, struct LO *pproxy);   /* the base slot 26 */

int func_0017F170(struct HACKSO *phackso, struct LO *pproxy)
{
    func_001CB518(phackso, pproxy);
    return phackso->cHp = phackso->cHpMax;
}
