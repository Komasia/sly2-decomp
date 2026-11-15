// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0 
// SLY2_ASM: gnu-reorder-db
/* SetTimerHandler (libkernel): thread-safe wrapper, iSetTimerHandler with interrupts disabled. */
int DIntr(void);
int iSetTimerHandler(int, int, int, int);
int EIntr(void);

int SetTimerHandler(int id, int schedule, int handler, int arg)
{
    int intr = DIntr();
    int ret = iSetTimerHandler(id, schedule, handler, arg);
    if (intr) EIntr();
    return ret;
}
