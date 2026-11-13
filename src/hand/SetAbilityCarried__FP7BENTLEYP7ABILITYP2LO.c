/* SetAbilityCarried: an ability's thrown / carried object (+8): Bentley stops listening to the old one (0x133448) and
 * listens to the new one (0x1333C0), so its leaving the world reaches him. Source: SafeHouse port (gang.cpp). */
struct LO;
struct BENTLEY;
struct ABILITY {
    /* 0x0 */ char pad0[8];
    /* 0x8 */ struct LO *plo8;   /* field: SafeHouse port */
};
void func_00133448(struct LO *plo, struct BENTLEY *pbentley);   /* SafeHouse: RemoveLoListener */
void func_001333C0(struct LO *plo, struct BENTLEY *pbentley);   /* SafeHouse: AddLoListener */

// name: SafeHouse port (SetAbilityCarried)
void SetAbilityCarried__FP7BENTLEYP7ABILITYP2LO(struct BENTLEY *pbentley, struct ABILITY *pabil, struct LO *plo)
{
    struct LO *ploOld = pabil->plo8;
    if (ploOld != 0) {
        func_00133448(ploOld, pbentley);
        pabil->plo8 = 0;
    }
    if (plo != 0) {
        pabil->plo8 = plo;
        func_001333C0(plo, pbentley);
    }
}
