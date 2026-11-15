// ResetGs (Sly 1 gs.c): the GS FINISH interrupt handler: when SendDmaSyncGsFinish waits and GS CSR FINISH is set,
// wake it.
extern int D_002DFB54;   /* a FINISH is awaited */
extern int D_002DFB50;   /* its semaphore */
extern "C" void iSignalSema(int sid);
int ResetGs()
{
    if (D_002DFB54 && (*(volatile long *)0x12001000 & 2)) {
        D_002DFB54 = 0;
        iSignalSema(D_002DFB50);
    }
    asm volatile("sync\n\tei");
    return -1;
}
