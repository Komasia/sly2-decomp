struct P { char pad[0x70]; float a[6]; char pad2[0x3BC - 0x88]; int fl; };
struct S;
extern struct S g_lmZeroOne;
float GLimitLm(struct S *, float) asm("GLimitLm__FP2LMf");
void SetDirty__4CSndUiUi(struct P *, int, int);
// name: SafeHouse port (CSndVoice::SetVoiceVolume)
void SetVoiceVolume__9CSndVoiceif(struct P *p, unsigned int k, float g)
{
    if (k < 6) {
        float f = GLimitLm(&g_lmZeroOne, g);
        if ((int)(f * 1024.0f) != (int)(p->a[k] * 1024.0f)) {
            p->fl |= 1 << k;
            p->a[k] = f;
            SetDirty__4CSndUiUi(p, 0x80, 0x80);
        }
    }
}
