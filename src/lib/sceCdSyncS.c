// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
extern int D_002C6750;
extern char D_002AB520[];
extern char D_002C82C0[];
int func_00236960(const char *, ...);
int DelayThread(int);
int sceSifCheckStatRpc(void *);
int sceCdSyncS(int mode)
{
    if (mode == 0) {
        if (D_002C6750 > 0) func_00236960(D_002AB520);
        while (sceSifCheckStatRpc(D_002C82C0)) DelayThread(0xFA0);
        return 0;
    }
    return sceSifCheckStatRpc(D_002C82C0);
}
