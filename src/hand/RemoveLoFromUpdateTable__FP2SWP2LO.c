/* RemoveLoFromUpdateTable: take an object out of the world's update table. LO +0x40 is either the object's
 * update flags (bit 0 set: not in the table) or its table entry; the entry's flags go back to the object, the entry
 * is cleared and counted dead (SW +0x3F18). SafeHouse port: task.cpp ("+0x40 ... its update entry's flags"),
 * sw.h (cupdDead). */
struct LO;
struct UPDENT {
    /* 0x0 */ unsigned int grf;   /* the object's update flags */
    /* 0x4 */ struct LO *plo;
};
struct LO {
    /* 0x00 */ char pad0[0x40];
    /* 0x40 */ struct UPDENT *pupd;   /* (or the flags themselves when bit 0 is set) */
};
struct SW {
    /* 0x0000 */ char pad0[0x3f18];
    /* 0x3f18 */ int cupdDead;   /* field: SafeHouse port */
};

// name: SafeHouse port (RemoveLoFromUpdateTable)
void RemoveLoFromUpdateTable__FP2SWP2LO(struct SW *psw, struct LO *plo)
{
    struct UPDENT *pupd = plo->pupd;
    if (((int)pupd ^ 1) & 1) {
        plo->pupd = (struct UPDENT *)pupd->grf;
        pupd->grf = 0;
        pupd->plo = 0;
        psw->cupdDead++;
    }
}
