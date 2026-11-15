// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
extern int D_002C6750;              /* debug print level */
extern volatile int D_002C6774;     /* callback pending */
extern char D_002AB510[];           /* "N cmd wait\n" */
extern char D_002C7910[];           /* N-command RPC client */
int scePrintf(const char *, ...);
int DelayThread(int);
int sceSifCheckStatRpc(void *);
/* sceCdSync (libcdvd): mode 0: wait until the current N-command (and its callback) has finished;
   otherwise just return 1 while it is still running. */
int sceCdSync(int mode)
{
    if (mode == 0) {
        if (D_002C6750 > 0) scePrintf(D_002AB510);
        while (D_002C6774 || sceSifCheckStatRpc(D_002C7910)) DelayThread(4000);
        return 0;
    }
    if (D_002C6774 || sceSifCheckStatRpc(D_002C7910)) return 1;
    return 0;
}
