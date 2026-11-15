/* FUN_0018c9c0 (0x1ABFC0): one card file's directory entry: the listing (FUN_0018c888) of exactly that path must
 * give one entry, else error 0xE. */
int func_001ABE78(int pmc, int szPath, int centMax, int adirent, int *pcent);
int FUN_0018c9c0(int pmc, int szPath, int pdirent)
{
    int cent;
    int nErr = func_001ABE78(pmc, szPath, 1, pdirent, &cent);
    if (nErr) return nErr;
    return cent == 1 ? 0 : 0xE;
}
