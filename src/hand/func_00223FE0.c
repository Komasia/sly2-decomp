/* class: CID_64, the carryables (vt slot 14 = LoadFromBrx; SafeHouse loaders.cpp): the SO's load, then its physics
 * record's +0xD4 / +0xD8 set to 2. */
struct CBinaryInputStream;
struct SOPHYS {
    /* 0x00 */ char pad0[0xd4];
    /* 0xd4 */ float gD4;
    /* 0xd8 */ float gD8;
};
struct CARRY {
    /* 0x00 */ char pad0[0xe8];
    /* 0xe8 */ struct SOPHYS *psophys;
};
void LoadSoFromBrx__FP2SOP18CBinaryInputStream(struct CARRY *pso, struct CBinaryInputStream *pbis);

void func_00223FE0(struct CARRY *pcarry, struct CBinaryInputStream *pbis)
{
    struct SOPHYS *psophys;
    LoadSoFromBrx__FP2SOP18CBinaryInputStream(pcarry, pbis);
    psophys = pcarry->psophys;
    if (psophys != 0) {
        psophys->gD4 = 2.0f;
        pcarry->psophys->gD8 = 2.0f;
    }
}
