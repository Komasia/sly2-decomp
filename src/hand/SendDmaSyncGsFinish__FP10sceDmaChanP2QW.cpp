struct CRITSECT;
struct sceDmaChan;
union QW;
extern CRITSECT D_002DFB40;
extern int D_002DFB54;
extern int D_002DFB50;
void EnterCritSect(CRITSECT *pcs);
void LeaveCritSect(CRITSECT *pcs);
extern "C" int func_00240B68();
extern "C" void func_00240AA0(int n);
extern "C" void FlushCache(int n) asm("FlushCache");
extern "C" void sceDmaSend(sceDmaChan *pch, QW *pqw) asm("sceDmaSend");
extern "C" void WaitSema(int sid) asm("WaitSema");
void SendDmaSyncGsFinish(sceDmaChan *pch, QW *pqw)
{
    EnterCritSect(&D_002DFB40);
    D_002DFB54 = 1;
    *(volatile long *)0x12001000 |= 2;
    func_00240AA0(func_00240B68() & ~0x200);
    FlushCache(0);
    sceDmaSend(pch, pqw);
    WaitSema(D_002DFB50);
    LeaveCritSect(&D_002DFB40);
}
