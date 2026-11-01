extern char g_cm[];
typedef struct S { char pad[0x130]; float g; } S;
typedef struct T { int pad[4]; S *ps; } T;
void func_0014FCC8(T *t, void *b, S *s);
void SetCmFov__FP2CMf(void *a, float g);
void func_0012E798(T *t, void *b, S *s)
{
    func_0014FCC8(t, b, s);
    t->ps = s;
    if (s->g != 0.0f)
        SetCmFov__FP2CMf(g_cm, s->g);
}
