/* func_00228958: add a pair of objects {oid, oid} to a checkpoint's list at +0x14C (at most 4, count at +0x148).
 * Called by the splice method func_0010BBE0 (method 795 of the checkpoint, cid 0x2A).
 * name: was MatchStepguardAnimationPhase__FP9STEPGUARD3OIDN31, a bad Sly 1 shape match: the SafeHouse port
 * (lo.h CHKPNT: "+0x148: objects placed at others (0x228958)"; transition.cpp: method 795 -> 0x228958) and its
 * neighbours (the checkpoint code after ApplyCheckpoint__FP2SW 0x228750) show it is the checkpoint's pair list.
 * SafeHouse gives the function no name, so it keeps its address name. */
typedef int OID;
struct OIDPAIR {
    /* 0x0 */ OID oid0;
    /* 0x4 */ OID oid1;
};
struct CHKPNT {
    /* 0x000 */ char pad0[0x148];
    /* 0x148 */ unsigned int cpair;          /* field: SafeHouse port (apair) */
    /* 0x14C */ struct OIDPAIR apair[4];     /* field: SafeHouse port */
};

void func_00228958(struct CHKPNT *pchkpnt, OID oid0, OID oid1)
{
    unsigned int i = pchkpnt->cpair;
    if (i < 4) {
        struct OIDPAIR *ppair;
        pchkpnt->cpair = i + 1;
        ppair = &pchkpnt->apair[i];
        ppair->oid0 = oid0;
        ppair->oid1 = oid1;
    }
}
