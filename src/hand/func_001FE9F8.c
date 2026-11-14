struct P { char pad[0x1BC]; float g; };
struct S;
extern struct S g_lmZeroOne;
float GLimitLm(struct S *, float) asm("GLimitLm__FP2LMf");
void snd_SetMasterVolume(int, int);
// name: SafeHouse port (SetSoundMasterVolume)
void SetSoundMasterVolume__FP8SOUNDMGRf(struct P *p, float x)
{
    float g = GLimitLm(&g_lmZeroOne, x);
    int n = (int)(g * 1024.0f);
    if ((int)(p->g * 1024.0f) != n) {
        p->g = g;
        snd_SetMasterVolume(0x10, n);
    }
}
