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
extern "C" void func_00234CA0(int n);
extern "C" void func_00241728(sceDmaChan *pch, QW *pqw);
extern "C" void func_00234A60(int sid);
void SendDmaSyncGsFinish(sceDmaChan *pch, QW *pqw)
{
    EnterCritSect(&D_002DFB40);
    D_002DFB54 = 1;
    *(volatile long *)0x12001000 |= 2;
    func_00240AA0(func_00240B68() & ~0x200);
    func_00234CA0(0);
    func_00241728(pch, pqw);
    func_00234A60(D_002DFB50);
    LeaveCritSect(&D_002DFB40);
}
