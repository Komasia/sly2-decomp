extern char g_cm[];
void OnLoAdd__FP2LO(void *p);
void SetCmPolicy__FP2CM3CPPP5CPLCYii(void *a, int b, void *c, int d, void *e);
typedef struct T { char pad[0x124]; int f; } T;
// name: SafeHouse port (EnableCmObject)
void EnableCmObject__FP2LO(T *t)
{
    OnLoAdd__FP2LO(t);
    if (t->f)
        SetCmPolicy__FP2CM3CPPP5CPLCYii(g_cm, 10, g_cm + 0x4A8, 0, t);
}
