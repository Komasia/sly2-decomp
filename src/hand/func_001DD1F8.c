typedef struct { char pad[0x58]; int x58; } W;
typedef struct { void *p; int a; int b; } ENT;
typedef struct {
    char pad[0x24];
    W *pw;
    char pad28[0x40 - 0x28];
    int kind;
    char pad44[4];
    int c;
    ENT ae[17];
    int sel;
} OBJ;
void SelectScreenObjPartHandle__FP2LOiPi(W *, int, int *);
int func_00163400(void *);
int FTaskDone__FP4TASK(void *);
// name: SafeHouse port (UpdateJobHelpLook)
void UpdateJobHelpLook__FPv(OBJ *p)
{
    int i;
    if (p->pw->x58 != 2)
        return;
    for (i = 0; i < p->c; i++) {
        int f;
        ENT *pe = &p->ae[i];
        SelectScreenObjPartHandle__FP2LOiPi(p->pw, i == p->sel ? i + 0x4FD : i + 0x4E9, &pe->a);
        f = 0;
        switch (p->kind) {
        case 0:
            f = func_00163400(pe->p);
            break;
        case 1:
            f = FTaskDone__FP4TASK(pe->p);
            break;
        }
        SelectScreenObjPartHandle__FP2LOiPi(p->pw, f ? i + 0x507 : -1, &pe->b);
    }
}
