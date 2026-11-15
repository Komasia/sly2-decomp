// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* libcdvd N-command completion (interrupt context): record the finished command, release the N-command semaphore
   and wake the callback thread when a user callback is set. */
extern volatile int D_002C67A0;     /* N-command in progress */
extern volatile int D_002C67A4;     /* last N-command */
extern volatile int D_002C6774;     /* callback pending */
extern volatile int D_002C6768;     /* N-command semaphore */
extern volatile int D_002C6754;     /* callback thread */
extern volatile int D_002C6760;     /* callback semaphore */
extern volatile int D_004502C0;     /* user callback (sceCdCallback) */
int iSignalSema(int);
void func_002418D0(int *data)
{
    D_002C67A0 = *data;
    D_002C67A4 = D_002C67A0;
    if (D_002C67A0 == 11) {     /* no semaphore to release */
        D_002C67A0 = 0;
        D_002C6774 = 0;
        return;
    }
    iSignalSema(D_002C6768);
    if (D_002C6754 != 0 && D_004502C0 != 0)
        iSignalSema(D_002C6760);
    else
        D_002C6774 = 0;
    D_002C67A0 = 0;
}
