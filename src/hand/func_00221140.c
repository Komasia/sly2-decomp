/* class: ZONE (cid 0x0F, vt slot 41 = Clone; SafeHouse brx.cpp): the transform's clone, then its +0x10C object cloned
 * under its parent. */
struct LO;
struct ZONE {
    /* 0x000 */ char pad0[0x10];
    /* 0x010 */ struct LO *psoParent;
    /* 0x014 */ char pad14[0x10c - 0x14];
    /* 0x10c */ struct LO *plo10C;
};
void func_002311B0(struct ZONE *pzone, struct LO *ploBase);   /* the LOX clone */
struct LO *PloCloneLo__FP2LOi(struct LO *plo, struct LO *ploParent);

void func_00221140(struct ZONE *pzone, struct LO *ploBase)
{
    func_002311B0(pzone, ploBase);
    pzone->plo10C = PloCloneLo__FP2LOi(pzone->plo10C, pzone->psoParent);
}
