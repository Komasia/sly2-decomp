// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
/* sceSifFreeIopHeap (libkernel iopheap): free IOP memory from sceSifAllocIopHeap. */
extern int D_002C4A94;      /* <0 until sceSifInitIopHeap */
extern char D_0044BE80[];   /* heap RPC client data */
extern int D_0044BF00[];    /* send buffer */
extern int D_0044BEC0[];    /* receive buffer */
int sceSifCallRpc(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int sceSifFreeIopHeap(void *addr)
{
    if (D_002C4A94 < 0)
        return 0;
    D_0044BF00[0] = (int)addr;
    if (sceSifCallRpc(D_0044BE80, 2 /* free */, 0, D_0044BF00, 4, D_0044BEC0, 4, 0, 0) < 0)
        return -1;
    return D_0044BEC0[0];
}
