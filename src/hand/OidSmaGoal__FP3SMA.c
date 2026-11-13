/* OidSmaGoal: the oid of a state machine player's goal state (OidFromSmIsms of its machine). Layout: SafeHouse port
 * (smrun.h SMA). */
struct SM;
struct SMA {
    /* 0x00 */ char pad0[0x24];
    /* 0x24 */ struct SM *psm;     /* field: SafeHouse port */
    /* 0x28 */ char pad28[0x3c - 0x28];
    /* 0x3c */ int ismsGoal;           /* field: SafeHouse port */
};
int OidFromSmIsms__FP2SMi(struct SM *psm, int isms);

// name: SafeHouse port (OidSmaGoal, smrun.cpp)
int OidSmaGoal__FP3SMA(struct SMA *psma)
{
    return OidFromSmIsms__FP2SMi(psma->psm, psma->ismsGoal);
}
