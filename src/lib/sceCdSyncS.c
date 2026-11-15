// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
extern int D_002C6750;      /* debug print level */
extern char D_002AB520[];   /* "S cmd wait\n" */
extern char D_002C82C0[];   /* S-command RPC client */
int scePrintf(const char *, ...);
int DelayThread(int);
int sceSifCheckStatRpc(void *);
/* sceCdSyncS (libcdvd): sceCdSync for S-commands (mode 0 waits, otherwise returns 1 while busy). */
int sceCdSyncS(int mode)
{
    if (mode == 0) {
        if (D_002C6750 > 0) scePrintf(D_002AB520);
        while (sceSifCheckStatRpc(D_002C82C0)) DelayThread(4000);
        return 0;
    }
    return sceSifCheckStatRpc(D_002C82C0);
}
