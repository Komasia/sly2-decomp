/* the world: the job to restart at its end */
struct SW { char pad[0x3B18]; int pjobRestart; };
extern char g_game[], D_003D9E70[], g_cm[], D_003DD040[], D_002E0CCC[];
extern int D_002E1E40, D_002F7900, D_002DD5BC, D_002DD648, D_003D4A54, D_002DE570, D_002DFB80, g_grfusr;   /* the world's players and special objects (D_002DD648: SafeHouse g_pguard3F) */
extern int D_003E1C40, D_003E1C44, D_003E1C48, D_003E1C4C, D_003E1C50, D_003DD48C;   /* the world records; the guards' shared object */
void BroadcastTaskEvent__FP2SWiP2LO(void *psw, int nEvent, int plo);
void RestartJob__FP3JOB(int pjob);
void ResetHudWidgets__FP2DL(void *phud);
void func_001FF830(struct SW *psw);
void func_00161458(void *pgame);
void ResetCm__FP2CM(void *pcm);
void ResetSoundMgr__FP8SOUNDMGR(void *psoundmgr);
void func_001EC7E8(void);
void SetRumbleRums(void *prumble, int rums) asm("SetRumbleRums__FP6RUMBLE4RUMS");
void FreeSw(void) asm("FreeSw__Fv");

/* UnloadWorld (0x20E068): the old world's end: task event 1, a job that ended restarted, the HUD widgets, sound and
 * camera reset, the rumble stopped (RUMS 3), the world's player / special-object pointers and the world records
 * cleared, and its objects freed (FreeSw). */
// name: SafeHouse port (UnloadWorld)
void UnloadWorld__FPv(struct SW *psw)
{
    void *pgame = g_game;
    BroadcastTaskEvent__FP2SWiP2LO(pgame, 1, 0);
    if (psw->pjobRestart) {
        RestartJob__FP3JOB(psw->pjobRestart);
        psw->pjobRestart = 0;
    }
    ResetHudWidgets__FP2DL(D_003D9E70);
    func_001FF830(psw);
    func_00161458(pgame);
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
