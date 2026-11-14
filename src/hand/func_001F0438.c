/* class: SM (called by LoadSmFromBrx and 0x1D77D0): IsmsFindSmOptional with the arguments unchanged. */
typedef struct SM SM;
int IsmsFindSmOptional__FP2SM3OID(SM *psm, int oid);

int func_001F0438(SM *psm, int oid)
{
    return IsmsFindSmOptional__FP2SM3OID(psm, oid);
}
