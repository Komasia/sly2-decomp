int CFindObjects__FP2SWi3OIDP2LOPviPP2LO(void *a, int b, int c, int d, int e, int f, int *pn);
// name: Sly 1 find.c PloFindSwObject (CFindObjects with FSO_ReturnActualCount 0x200, one object; Sly 2 passes CFindObjects' extra pointer through); PloFindSwNearest calls it
int PloFindSwObject__FP2SWi3OIDP2LOPv(void *a, int b, int c, int d, int e)
{
    int n;
    if (!CFindObjects__FP2SWi3OIDP2LOPviPP2LO(a, b | 0x200, c, d, e, 1, &n))
        return 0;
    return n;
}
