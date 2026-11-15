int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(void *a, int b, int c, int d, int f, int *pn);
// name: Sly 1 find.c PloFindSwObjectByClass (CFindObjectsByClass with FSO_ReturnActualCount 0x200, one object)
int PloFindSwObjectByClass__FP2SWi3CIDP2LO(void *a, int b, int c, int d)
{
    int n;
    if (!CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(a, b | 0x200, c, d, 1, &n))
        return 0;
    return n;
}
