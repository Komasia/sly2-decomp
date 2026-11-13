struct P { char pad[0x24]; void *p24; char pad2[0x30 - 0x28]; int n30; int n34; int n38; char pad3[0x48 - 0x3C]; int n48; };
int FSmaRetracted(struct P *) asm("FSmaRetracted__FP3SMA");
int IsmsFindSmOptional(void *, int) asm("IsmsFindSmOptional__FP2SM3OID");
int PsmtPath__FP2SMUiii(void *, int, int, int, int);
void SetSmaGoal__FP3SMA3OID(struct P *, int);
// name: SafeHouse port (SeekSma)
void SeekSma__FP3SMA3OID(struct P *p, int n)
{
    if (!FSmaRetracted(p) && n != -1) {
        int r = IsmsFindSmOptional(p->p24, n);
        if (r != -1 && PsmtPath__FP2SMUiii(p->p24, p->n48, !p->n30 ? p->n34 : p->n38, r, 0))
            SetSmaGoal__FP3SMA3OID(p, n);
    }
}
