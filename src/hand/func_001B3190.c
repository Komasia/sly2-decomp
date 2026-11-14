struct S { int a; char pad[0x9C]; int xa0; int xa4; };
void snd_CloseMovieSound(void);
void snd_SetMasterVolume(int n, int v);
void snd_ContinueAllSoundsInGroup(unsigned int m);
void func_001B3190(struct S *p)
{
    p->a = 0;
    snd_CloseMovieSound();
    snd_SetMasterVolume(2, p->xa0);
    snd_SetMasterVolume(0x10, p->xa4);
    snd_ContinueAllSoundsInGroup(0xFFFFFFFF);
}
