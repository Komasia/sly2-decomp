struct E { int oidA; void *pA; int oidB; void *pB; int oidC; void *pC; int oidD; void *pD; int n; };
struct S { char pad[0x1010]; int c; struct E *ae; };
extern char g_sw[];
void *PloFindSwNearest__FP2LO3OIDii(void *g, int k, int oid, struct S *p);
void PostStepguardLoad__FP9STEPGUARD(struct S *p);
void func_00155450(struct S *p)
{
    int i;
    PostStepguardLoad__FP9STEPGUARD(p);
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        pe->pA = PloFindSwNearest__FP2LO3OIDii(g_sw, 4, pe->oidA, p);
        pe->pB = PloFindSwNearest__FP2LO3OIDii(g_sw, 4, pe->oidB, p);
        pe->pC = PloFindSwNearest__FP2LO3OIDii(g_sw, 4, pe->oidC, p);
        pe->pD = PloFindSwNearest__FP2LO3OIDii(g_sw, 4, pe->oidD, p);
    }
}
