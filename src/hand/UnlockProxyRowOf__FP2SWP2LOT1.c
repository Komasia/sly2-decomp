/* UnlockProxyRowOf: the instance row of a streaming proxy's object given back (LockProxyRowOf keeps it).
 * Layout: SafeHouse port (sw.h, the row node's +0x08 afRowLocked). */
struct SW;
struct LO;
struct PROXYROW {
    /* 0x00 */ char pad0[8];
    /* 0x08 */ int fLocked;   /* field: SafeHouse port */
};
struct PROXYROW *IrowOfObject__FP2SWi(struct SW *psw, struct LO *pproxy, struct LO *plo);

// name: SafeHouse port (UnlockProxyRowOf, activate.cpp)
void UnlockProxyRowOf__FP2SWP2LOT1(struct SW *psw, struct LO *pproxy, struct LO *plo)
{
    struct PROXYROW *prow = IrowOfObject__FP2SWi(psw, pproxy, plo);
    if (prow != 0)
        prow->fLocked = 0;
}
