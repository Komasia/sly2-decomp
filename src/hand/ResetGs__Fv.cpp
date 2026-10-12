extern int D_002DFB54;
extern int D_002DFB50;
extern "C" void func_00234A50(int sid);
int ResetGs()
{
    if (D_002DFB54 && (*(volatile long *)0x12001000 & 2)) {
        D_002DFB54 = 0;
        func_00234A50(D_002DFB50);
    }
    asm volatile("sync\n\tei");
    return -1;
}
