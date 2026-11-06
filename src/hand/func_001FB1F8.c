struct P { char pad[0x10]; float g; };
struct S;
extern struct S g_lmZeroOne;
float func_0011D948(struct S *, float);
void SetDirty__4CSndUiUi(struct P *, int, int);
// name: SafeHouse port (CSnd::SetVolume)
void SetVolume__4CSndf(struct P *p, float x)
{
    float g = func_0011D948(&g_lmZeroOne, x);
    if ((int)(g * 1024.0f) != (int)(p->g * 1024.0f)) {
        p->g = g;
        SetDirty__4CSndUiUi(p, 0x10, 0x10);
    }
}
