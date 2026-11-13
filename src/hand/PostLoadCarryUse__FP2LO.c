/* PostLoadCarryUse: after the world load (0x183F50, the base post-load) a carry use object's three authored
 * references are resolved: each oid (+0x184 / +0x18C / +0x194) to the nearest object with it (the next word).
 * Layout: SafeHouse port (murraycarry.cpp). */
struct SW;
struct LO;
struct OIDREF {
    /* 0x0 */ int oid;
    /* 0x4 */ struct LO *plo;
};
struct CARRYUSE {
    /* 0x000 */ char pad0[0x184];
    /* 0x184 */ struct OIDREF aref[3];
};
extern struct SW g_sw;
void func_00183F50(struct CARRYUSE *puse);
struct LO *PloFindSwNearest(struct SW *psw, int grf, int oid, struct CARRYUSE *puse) asm("PloFindSwNearest__FP2LO3OIDii");

// name: SafeHouse port (PostLoadCarryUse)
void PostLoadCarryUse__FP2LO(struct CARRYUSE *puse)
{
    func_00183F50(puse);
    puse->aref[0].plo = PloFindSwNearest(&g_sw, 4, puse->aref[0].oid, puse);
    puse->aref[1].plo = PloFindSwNearest(&g_sw, 4, puse->aref[1].oid, puse);
    puse->aref[2].plo = PloFindSwNearest(&g_sw, 4, puse->aref[2].oid, puse);
}
