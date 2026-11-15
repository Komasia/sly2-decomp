/* PloFindSwNearest: the object of an oid found from ploCtx (PloFindSwObject__FP2SWi3OIDP2LOPv with no namespace list). */
void *PloFindSwObject__FP2SWi3OIDP2LOPv(void *psw, int grf, int oid, void *ploCtx, void *pnsn);
// name: SafeHouse port (PloFindSwNearest)
void *PloFindSwNearest__FP2LO3OIDii(void *psw, int grf, int oid, void *ploCtx)
{
    return PloFindSwObject__FP2SWi3OIDP2LOPv(psw, grf, oid, ploCtx, 0);
}
