// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
extern unsigned int *gCommBusy; extern int gAwaitingInts; extern int D_002C46B8; extern char D_00443800[]; extern char D_002AA140[];
void FlushCache(int); int sceSifCheckStatRpc(void *); void printf(void *);
int snd_GotReturns__Fv(void)
{
    FlushCache(0);
    if (gCommBusy == 0) return 1;
    if (sceSifCheckStatRpc(D_00443800)) return 0;
    if (gCommBusy[0] == 0xFFFFFFFF && gCommBusy[gAwaitingInts + 1] == gCommBusy[0]) {
        gCommBusy = 0;
        return 1;
    }
    if (D_002C46B8 == 0) printf(D_002AA140);
    return 0;
}
