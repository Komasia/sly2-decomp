extern int D_002DFB54;
extern int D_002DFB50;
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
