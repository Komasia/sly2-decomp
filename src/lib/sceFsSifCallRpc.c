// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
int sceSifCallRpc(void *cd, int rpc, int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int DelayThread(int);
int sceFsSifCallRpc(void *cd, int rpc, int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg, int nowait)
{
    int r;
    unsigned int delay = 1;
    int i = 0;

    do {
        r = sceSifCallRpc(cd, rpc, mode, send, ssize, recv, rsize, end, earg) < 0;
        if (!r || nowait)
            break;
        DelayThread(delay * 1000);
        if ((int)delay < 0x7F)
            delay *= 2;
        i++;
    } while (i < 101);
    return r;
}
