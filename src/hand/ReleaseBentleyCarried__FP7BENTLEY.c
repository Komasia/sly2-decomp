/* ReleaseBentleyCarried: the object Bentley carries let go: a carry object (0x224610: kind 7 / 11) notes him as its
 * carrier and the ability is told; the proxy row of the object is given back (UnlockProxyRowOf). Layout: SafeHouse
 * port (gang.h BENTLEY, carry.h CARRY). */
struct LO;
struct ABILITY {
    /* 0x0 */ char pad0[4];
    /* 0x4 */ struct LO *plo4;          /* field: SafeHouse port - the proxy */
};
struct CARRY {
    /* 0x000 */ char pad0[0x16c];
    /* 0x16c */ struct BENTLEY *plo16C;  /* field: SafeHouse port - the carrier */
};
struct BENTLEY {
    /* 0x0000 */ char pad0[0x16b4];
    /* 0x16b4 */ struct ABILITY *pabil16B4;   /* field: SafeHouse port */
    /* 0x16b8 */ char pad16B8[0x186c - 0x16b8];
    /* 0x186c */ struct CARRY *ploCarried;    /* field: SafeHouse port */
};
int func_00224610(struct CARRY *pcarry);   /* SafeHouse: a carry object */
void SetAbilityCarried__FP7BENTLEYP7ABILITYP2LO(struct BENTLEY *pbentley, struct ABILITY *pabil, struct CARRY *plo);
void func_001CB4B8(struct LO *pproxy, struct CARRY *plo);   /* SafeHouse: UnlockProxyRowOf */

// name: SafeHouse port (ReleaseBentleyCarried)
void ReleaseBentleyCarried__FP7BENTLEY(struct BENTLEY *pbentley)
{
    if (func_00224610(pbentley->ploCarried)) {
        pbentley->ploCarried->plo16C = pbentley;
        SetAbilityCarried__FP7BENTLEYP7ABILITYP2LO(pbentley, pbentley->pabil16B4, pbentley->ploCarried);
    }
    func_001CB4B8(pbentley->pabil16B4->plo4, pbentley->ploCarried);
    pbentley->ploCarried = 0;
    pbentley->pabil16B4 = 0;
}
