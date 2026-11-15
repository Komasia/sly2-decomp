// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
extern int D_002C8350;    /* command in progress (sceMcFunc*), 0 = none */
extern int D_002C8354;    /* libmc command semaphore */
extern int D_002C8358;    /* libmc completion semaphore */
extern int D_00451E40;    /* libmc receive buffer (command result) */
int PollSema(int);
int WaitSema(int);
int SignalSema(int);
/* sceMcSync (libmc): mode 0 waits for the pending command, otherwise polls. Returns 1 when it has finished
   (with its sceMcFunc number in *cmd and its result in *result), 0 while still busy, -1 if none is pending. */
int sceMcSync(int mode, int *cmd, int *result)
{
    int r;
    if (!D_002C8350) return -1;
    if (PollSema(D_002C8358) < 0) r = 1; else r = 0;
    if (mode == 0 && r) {
        WaitSema(D_002C8358);
        r = 0;
    }
    r = !r;
    if (cmd) *cmd = D_002C8350;
    if (r) {
        D_002C8350 = 0;
        if (result) *result = D_00451E40;
        SignalSema(D_002C8354);
    }
    return r;
}
