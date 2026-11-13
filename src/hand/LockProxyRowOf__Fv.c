/* LockProxyRowOf: the instance row of a streaming proxy's object kept (not reused while the object is out of its
 * stand, e.g. carried booty); UnlockProxyRowOf (0x1CB4B8) gives it back. Layout: SafeHouse port (sw.h, the row
 * node's +0x08 afRowLocked). */
struct SW;
struct LO;
struct PROXYROW {
    /* 0x00 */ char pad0[8];
    /* 0x08 */ int fLocked;   /* field: SafeHouse port */
};
struct PROXYROW *IrowOfObject__FP2SWi(struct SW *psw, struct LO *pproxy, struct LO *plo);

// name: SafeHouse port (LockProxyRowOf)
void LockProxyRowOf__Fv(struct SW *psw, struct LO *pproxy, struct LO *plo)
{
    struct PROXYROW *prow = IrowOfObject__FP2SWi(psw, pproxy, plo);
    if (prow != 0)
        prow->fLocked = 1;
}
