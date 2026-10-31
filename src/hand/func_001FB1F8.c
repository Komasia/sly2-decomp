struct P { char pad[0x10]; float g; };
struct S;
extern struct S g_lmZeroOne;
float func_0011D948(struct S *, float);
void func_001FB658(struct P *, int, int);
void func_001FB1F8(struct P *p, float x)
{
    float g = func_0011D948(&g_lmZeroOne, x);
    if ((int)(g * 1024.0f) != (int)(p->g * 1024.0f)) {
        p->g = g;
        func_001FB658(p, 0x10, 0x10);
    }
}
