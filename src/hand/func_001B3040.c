struct G { char pad[0x110]; int x110; };
extern struct G D_002F66B0;
extern char D_003DD040[], D_004435F0[];
struct S { int x0; int x4; char x8[0x28]; char x30[0x20]; char x50[0x50]; int xA0; int xA4; };
void snd_PauseAllSoundsInGroup(unsigned int m);
void StopDialog__FP8SOUNDMGR(void *p);
void func_00227788(void *p);
void func_00232408(void);
int snd_FlushSoundCommands(void);
void snd_StreamSafeCheckCDIdle(int n);
void snd_StreamSafeCdSync(int n);
int snd_GetMasterVolume(int n);
void snd_SetMasterVolume(int n, int m);
void Init__10CByteQueueiPv(void *pbq, int cb, void *pv);
void func_001B3040(struct S *p)
{
    snd_PauseAllSoundsInGroup(0xFFFFFFFF);
    StopDialog__FP8SOUNDMGR(D_003DD040);
    func_00227788(D_004435F0);
    func_00232408();
    while (snd_FlushSoundCommands()) ;
    snd_StreamSafeCheckCDIdle(1);
    snd_StreamSafeCdSync(0);
    p->xA0 = snd_GetMasterVolume(2);
    p->xA4 = snd_GetMasterVolume(0x10);
    snd_SetMasterVolume(2, 0x400);
    snd_SetMasterVolume(0x10, 0x400);
    p->x0 = 1;
    p->x4 = -1;
    Init__10CByteQueueiPv(p->x30, 0x28, p->x8);
    Init__10CByteQueueiPv(p->x50, 0x18000, (void *)(D_002F66B0.x110 + 0x80000));
}
