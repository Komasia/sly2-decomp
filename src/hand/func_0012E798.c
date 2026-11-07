extern char g_cm[];
typedef struct S { char pad[0x130]; float g; } S;
typedef struct T { int pad[4]; S *ps; } T;
void Activate__5CPLCYP2LOPv(T *t, void *b, S *s);
void SetCmFov__FP2CMf(void *a, float g);
// name: SafeHouse port (CPLOOKAT::Activate)
void Activate__8CPLOOKATP2LOPv(T *t, void *b, S *s)
{
    Activate__5CPLCYP2LOPv(t, b, s);
    t->ps = s;
    if (s->g != 0.0f)
        SetCmFov__FP2CMf(g_cm, s->g);
}
