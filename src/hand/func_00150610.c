struct A { void *p0; int pad[3]; float g10; float g14; int pad2[7]; void *p34; void *p38; int pad3[4]; float g4C; float g50; };
extern char g_cm[];
void Stop__4CSndf(void *p, float g);
void func_00258040(void **pp, int n);
int FIsBasicDerivedFrom__FP5BASIC3CID(void *p, int n);
void SetCmCut__FP2CMff(void *p, float a, float b);
void Deactivate__5CPLCYP2LOPv(struct A *a, int n, void *b);
static inline void Release(void **pp, float g)
{
    if (pp && *pp) {
        Stop__4CSndf(*pp, g);
        func_00258040(pp, 0);
    }
}
// name: SafeHouse port (CPRECON::Deactivate)
void Deactivate__7CPRECONP2LOPv(struct A *a, int n, void *b)
{
    Release(&a->p34, 0.0f);
    Release(&a->p38, 0.5f);
    if (FIsBasicDerivedFrom__FP5BASIC3CID(a->p0, 0x34))
        SetCmCut__FP2CMff(g_cm, a->g10 + 3.1415927f, -a->g14);
    else
        SetCmCut__FP2CMff(g_cm, a->g4C + 3.1415927f, -a->g50);
    Deactivate__5CPLCYP2LOPv(a, n, b);
}
