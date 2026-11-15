// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
extern char D_002C82C0[];   /* S-command RPC client */
extern int D_002C7940[];    /* S-command receive buffer (read uncached) */
extern int D_002C676C;      /* S-command semaphore */
int _sceCd_scmd_prechk(int);
int sceSifCallRpc(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int SignalSema(int);
/* sceCdGetError (libcdvd): error code of the last command (SCECdErNO = 0), or -1. */
int sceCdGetError(void)
{
    int r;
    if (_sceCd_scmd_prechk(3) == 0)
        return -1;
    if (sceSifCallRpc(D_002C82C0, 4, 0, 0, 0, D_002C7940, 4, 0, 0) >= 0) {
        r = *(int *)((unsigned int)D_002C7940 | 0x20000000)  /* uncached */;
        SignalSema(D_002C676C);
        return r;
    }
    SignalSema(D_002C676C);
    return -1;
}
