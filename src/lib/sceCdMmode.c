// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
extern char D_002C82C0[];   /* S-command RPC client */
extern int D_002C7940[];    /* S-command receive buffer (read uncached) */
extern int D_002C7D80[];    /* S-command send buffer */
extern volatile int D_002C676C;   /* S-command semaphore */
extern int D_002C82E8, D_002C82EC, D_002C82F0;   /* Mmode RPC function number, send and receive size */
int _sceCd_scmd_prechk(int);
void sceSifWriteBackDCache(void *, int);
int sceSifCallRpc(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int SignalSema(int);
/* sceCdMmode (libcdvd): tell the drive which media to expect (SCECdCD / SCECdDVD). Returns 1 on success. */
int sceCdMmode(int media)
{
    int r;
    int *p = D_002C7D80;
    if (_sceCd_scmd_prechk(0x22) == 0)
        return 0;
    D_002C7D80[0] = media;
    sceSifWriteBackDCache(p, 4);
    if (sceSifCallRpc(D_002C82C0, D_002C82E8, 0, p, D_002C82EC, D_002C7940, D_002C82F0, 0, 0) < 0) {
        SignalSema(D_002C676C);
        return 0;
    }
    r = *(int *)((unsigned int)D_002C7940 | 0x20000000);
    SignalSema(D_002C676C);
    return r;
}
