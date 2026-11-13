/* OidSmaCur: the oid of a state machine player's current state (OidFromSmIsms of its machine). Layout: SafeHouse port
 * (smrun.h SMA). */
struct SM;
struct SMA {
    /* 0x00 */ char pad0[0x24];
    /* 0x24 */ struct SM *psm;     /* field: SafeHouse port */
    /* 0x28 */ char pad28[0x34 - 0x28];
    /* 0x34 */ int ismsCur;           /* field: SafeHouse port */
};
int OidFromSmIsms__FP2SMi(struct SM *psm, int isms);

// name: SafeHouse port (OidSmaCur, smrun.cpp)
int OidSmaCur__FP3SMA(struct SMA *psma)
{
    return OidFromSmIsms__FP2SMi(psma->psm, psma->ismsCur);
}
