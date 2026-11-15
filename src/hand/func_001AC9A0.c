/* func_001AC9A0 (0x1AC9A0): reads a whole file from the card: opened for reading (mode 1), read, closed; 8 when fewer
 * bytes than asked were read. */
#define SCE_RDONLY 1
int func_001AC7A0(void *pmc, void *szFile, int mode, int *pfd);
int func_001AC850(void *pmc, int fd, void *pv, int cb, int *pcb);
void func_001AC808(void *pmc, int fd);
int func_001AC9A0(void *pmc, void *szFile, void *pv, int cb)
{
    int fd = -1;
    int cbDone;
    int nErr = func_001AC7A0(pmc, szFile, SCE_RDONLY, &fd);
    if (nErr)
        return nErr;
    nErr = func_001AC850(pmc, fd, pv, cb, &cbDone);
    if (!nErr && cbDone != cb)
        nErr = 8;
    func_001AC808(pmc, fd);
    return nErr;
}
