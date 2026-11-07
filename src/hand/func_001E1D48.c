struct O { int n0; char pad[0xC]; int n10; };
struct S { char pad[0x40]; struct O *po; };
int FCmdDone__FP3RUNP7SCPTCMD(struct S *p, struct O *po);
void SetRunPending__FP3RUNiP2LO(struct S *p, int a, int b);
// name: SafeHouse port (FinishRunPending)
void FinishRunPending__FP3RUN(struct S *p)
{
    if (p->po && FCmdDone__FP3RUNP7SCPTCMD(p, p->po)) {
        int f = 1;
        if (p->po->n0 == 0x1D) f = (p->po->n10 == -1);
        if (f) SetRunPending__FP3RUNiP2LO(p, 0, 0);
    }
}
