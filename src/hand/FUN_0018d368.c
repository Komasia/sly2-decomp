/* FUN_0018d368 (0x1AC900): writes a whole file to the card: opened for writing (mode 0x202: create, write), written,
 * closed; 7 when fewer bytes than asked were written. */
#define SCE_WRONLY_CREAT 0x202
int func_001AC7A0(void *pmc, void *szFile, int mode, int *pfd);
int func_001AC8A8(void *pmc, int fd, void *pv, int cb, int *pcb);
void func_001AC808(void *pmc, int fd);
int FUN_0018d368(void *pmc, void *szFile, void *pv, int cb)
{
    int fd = -1;
    int cbDone;
    int nErr = func_001AC7A0(pmc, szFile, SCE_WRONLY_CREAT, &fd);
    if (nErr)
        return nErr;
    nErr = func_001AC8A8(pmc, fd, pv, cb, &cbDone);
    if (!nErr && cbDone != cb)
        nErr = 7;
    func_001AC808(pmc, fd);
    return nErr;
}
