/* FUN_0018bc90 (0x1AB098): waits for a memory card call: the call's immediate result must be fine (0x1AAB48: 0x1D),
 * then sceMcSync's result is mapped (0x1AAB68) and returned with the call's own result (through pnResult); an
 * ordinary result (0x22) is translated by the call's kind (FUN_0018b988). */
int func_001AAB48(void *p);
int sceMcSync(int n, int *a, int *b);
int func_001AAB68(int n);
int func_001AABC0(void *p, int n);
int FUN_0018bc90(void *pmemcard, void *nCall, void *kind, int *pnResult)
{
    int anSync[2];
    int nErr = func_001AAB48(nCall);
    if (nErr != 0x1D)
        return nErr;
    nErr = func_001AAB68(sceMcSync(0, &anSync[0], &anSync[1]));
    if (pnResult)
        *pnResult = anSync[1];
    if (nErr == 0x22)
        nErr = func_001AABC0(kind, anSync[1]);
    return nErr;
}
