struct E { int oidA; void *pA; int oidB; void *pB; int oidC; void *pC; int oidD; void *pD; int n; };
struct S { char pad[0x1010]; int c; struct E *ae; };
extern char D_003DD490[];
void *func_0015E938(void *g, int k, int oid, struct S *p);
void PostStepguardLoad__FP9STEPGUARD(struct S *p);
void func_00155450(struct S *p)
{
    int i;
    PostStepguardLoad__FP9STEPGUARD(p);
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        pe->pA = func_0015E938(D_003DD490, 4, pe->oidA, p);
        pe->pB = func_0015E938(D_003DD490, 4, pe->oidB, p);
        pe->pC = func_0015E938(D_003DD490, 4, pe->oidC, p);
        pe->pD = func_0015E938(D_003DD490, 4, pe->oidD, p);
    }
}
