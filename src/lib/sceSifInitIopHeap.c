// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* sceSifInitIopHeap (libkernel iopheap): bind the IOP heap RPC server, retrying until it is registered. */
#define SIF_RPC_ID_IOPHEAP 0x80000003
typedef struct { char p[0x24]; int server; } RpcCD;
extern int D_002C4A94;
extern RpcCD D_0044BE80;
int sceSifBindRpc(RpcCD *, unsigned int, int);
int sceSifInitIopHeap(void)
{
    int delay;
    for (;;) {
        if (sceSifBindRpc(&D_0044BE80, SIF_RPC_ID_IOPHEAP, 0) < 0)
            return -1;
        if (D_0044BE80.server != 0)
            break;
        delay = 0x100000;
        while (delay--)
            ;
    }
    D_002C4A94 = 0;
    __asm__ __volatile__(""); /* emulates Sony scheduler: keep the store before the return-value set */
    return 0;
}
