/* class: SM (called by LoadSmFromBrx and 0x1D77D0): IsmsFindSmOptional with the arguments unchanged. */
typedef struct SM SM;
int IsmsFindSmOptional__FP2SM3OID(SM *psm, int oid);

// name: Sly 1 sm.c IsmsFindSmRequired (wraps IsmsFindSmOptional; same callers LoadSmFromBrx / the SMA code; Sly 2 drops the clamp)
int IsmsFindSmRequired__FP2SM3OID(SM *psm, int oid)
{
    return IsmsFindSmOptional__FP2SM3OID(psm, oid);
}
