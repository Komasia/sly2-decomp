extern int D_002DFB4C;
extern int D_002DFB58;
extern "C" void WaitSema(int sid) asm("WaitSema");
void SyncVBlank()
{
    D_002DFB58 = 1;
    WaitSema(D_002DFB4C);
}
