// SyncVBlank (Sly 1 gs.c): wait for the next VBlank (VBlankS_Interrupt signals the semaphore).
extern int D_002DFB4C;   /* the VBlank semaphore */
extern int D_002DFB58;   /* a waiter is pending */
extern "C" void WaitSema(int sid) asm("WaitSema");
void SyncVBlank()
{
    D_002DFB58 = 1;
    WaitSema(D_002DFB4C);
}
