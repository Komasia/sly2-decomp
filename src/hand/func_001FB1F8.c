struct P { char pad[0x10]; float g; };
struct S;
extern struct S g_lmZeroOne;
float GLimitLm(struct S *, float) asm("GLimitLm__FP2LMf");
void SetDirty__4CSndUiUi(struct P *, int, int);
// name: SafeHouse port (CSnd::SetVolume)
void SetVolume__4CSndf(struct P *p, float x)
{
    float g = GLimitLm(&g_lmZeroOne, x);
    if ((int)(g * 1024.0f) != (int)(p->g * 1024.0f)) {
        p->g = g;
        SetDirty__4CSndUiUi(p, 0x10, 0x10);
    }
}
