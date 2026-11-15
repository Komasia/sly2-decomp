/* CploFindSwNearest: count the objects of an oid found from ploCtx (CFindObjects with no namespace list). */
int CFindObjects__FP2SWi3OIDP2LOPviPP2LO(void *psw, int grf, int oid, void *ploCtx, void *pnsn, int cMax, void **aplo);
// name: SafeHouse port (CploFindSwNearest)
int CploFindSwNearest__FP2LO3OIDiiii(void *psw, int grf, int oid, void *ploCtx, int cMax, void **aplo)
{
    return CFindObjects__FP2SWi3OIDP2LOPviPP2LO(psw, grf, oid, ploCtx, 0, cMax, aplo);
}
