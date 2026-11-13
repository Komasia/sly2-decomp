/* func_001D7748: append a 3-word entry {oid, a value, oid} to the safe house's list at +0x190 (at most 12, count at
 * +0x18C). Called by the splice method func_0010F590 (option 1338 of the safe house, cid 0x46; Sly 3's thunk map
 * has the same EOPID at 0x10F590).
 * name: was AddStepguardEffect__FP9STEPGUARD3OID3ZPK, a bad Sly 1 shape match: it sits in the safe house module
 * (after SetSafeHouseState__FP2SWi 0x1D7480, before the safe house's state stepper 0x1D77D0) and its object is the
 * safe house, not a STEPGUARD. The entries' meaning is not known (the SafeHouse port does not implement option
 * 1338), so it keeps its address name. */
typedef int OID;
struct SAFEHOUSEENTRY {
    /* 0x0 */ OID oid0;
    /* 0x4 */ int n4;       /* the splice argument of type 0x103C */
    /* 0x8 */ OID oid8;
};
struct SAFEHOUSE {
    /* 0x000 */ char pad0[0x18C];
    /* 0x18C */ unsigned int centry;
    /* 0x190 */ struct SAFEHOUSEENTRY aentry[12];
};

void func_001D7748(struct SAFEHOUSE *psh, OID oid0, int n4, OID oid8)
{
    unsigned int i = psh->centry;
    if (i < 12) {
        struct SAFEHOUSEENTRY *pentry;
        psh->centry = i + 1;
        pentry = &psh->aentry[i];
        pentry->oid0 = oid0;
        pentry->n4 = n4;
        pentry->oid8 = oid8;
    }
}
