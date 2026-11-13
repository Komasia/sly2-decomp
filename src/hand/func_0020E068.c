struct S { char pad[0x3B18]; int h3B18; };
extern char g_game[], D_003D9E70[], g_cm[], D_003DD040[], D_002E0CCC[];
extern int D_002E1E40, D_002F7900, D_002DD5BC, D_002DD648, D_003D4A54, D_002DE570, D_002DFB80, g_grfusr;
extern int D_003E1C40, D_003E1C44, D_003E1C48, D_003E1C4C, D_003E1C50, D_003DD48C;
void BroadcastTaskEvent__FP2SWiP2LO(void *p, int a, int b);
void RestartJob__FP3JOB(int h);
void func_001D9408(void *p);
void func_001FF830(struct S *p);
void func_00161458(void *p);
void ResetCm__FP2CM(void *p);
void ResetSoundMgr__FP8SOUNDMGR(void *p);
void func_001EC7E8(void);
void SetRumbleRums(void *p, int n) asm("SetRumbleRums__FP6RUMBLE4RUMS");
void FreeSw(void) asm("FreeSw__Fv");

// name: SafeHouse port (UnloadWorld)
void UnloadWorld__FPv(struct S *p)
{
    void *pv = g_game;
    BroadcastTaskEvent__FP2SWiP2LO(pv, 1, 0);
    if (p->h3B18) {
        RestartJob__FP3JOB(p->h3B18);
        p->h3B18 = 0;
    }
    func_001D9408(D_003D9E70);
    func_001FF830(p);
    func_00161458(pv);
    ResetCm__FP2CM(g_cm);
    ResetSoundMgr__FP8SOUNDMGR(D_003DD040);
    func_001EC7E8();
    SetRumbleRums(D_002E0CCC, 3);
    D_002E1E40 = 0;
    D_002F7900 = 0;
    D_002DD5BC = 0;
    D_002DD648 = 0;
    D_003D4A54 = 0;
    D_002DE570 = 0;
    D_002DFB80 = 0;
    g_grfusr = 0;
    D_003E1C40 = 0;
    D_003E1C44 = 0;
    D_003E1C48 = 0;
    D_003E1C4C = 0;
    D_003E1C50 = 0;
    D_003DD48C = 0;
    FreeSw();
}
