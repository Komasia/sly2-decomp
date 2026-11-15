// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* _DelayThreadHandler (libkernel): DelayThread's alarm handler; wakes the sleeping thread by signalling its
   semaphore. Returning 0 makes the alarm one-shot. */
void iSignalSema(int sema);

int _DelayThreadHandler(int id, unsigned short scheduled, int actual, int sema)
{
    iSignalSema(sema);
    __asm__ volatile("sync");
    __asm__ volatile("ei");
    return 0;
}
