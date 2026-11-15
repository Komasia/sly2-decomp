// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
/* sceSifAllocIopHeap (libkernel iopheap): allocate `size` bytes of IOP memory through the IOP heap RPC server.
   Returns the IOP address, or 0. */
extern int D_002C4A94;      /* <0 until sceSifInitIopHeap */
extern char D_0044BE80[];   /* heap RPC client data */
extern int D_0044BF00[];    /* send buffer */
extern int D_0044BEC0[];    /* receive buffer */
int sceSifCallRpc(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
void *sceSifAllocIopHeap(int size)
{
    if (D_002C4A94 < 0)
        return 0;
    D_0044BF00[0] = size;
    if (sceSifCallRpc(D_0044BE80, 1 /* alloc */, 0, D_0044BF00, 4, D_0044BEC0, 4, 0, 0) < 0)
        return 0;
    return (void *)D_0044BEC0[0];
}
