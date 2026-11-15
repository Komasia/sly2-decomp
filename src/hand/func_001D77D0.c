typedef struct { char pad[0x50]; int c; } LIST;
typedef struct {
    char pad[0x184];
    LIST *plist;
    void *x188;
    char pad18c[0x220 - 0x18C];
    int c;
    void *a[8];
} OBJ;
void *OidSmaCur(void *) asm("OidSmaCur__FP3SMA");
int IsmsFindSmRequired__FP2SM3OID(LIST *, void *);
void *OidFromSmIsms__FP2SMi(LIST *, int);
void SetSmaGoal__FP3SMA3OID(void *, void *);
void ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(int, OBJ *, int, int, void **);
// name: SafeHouse port (po.cpp StepSafeHouse, orig 0x1D77D0: the safe house's state machine; suggested by h3)
void StepSafeHouse__FP9SAFEHOUSEi(OBJ *p, int d)
{
    int i0;
    int i;
    if (p->x188 == 0)
        return;
    i = IsmsFindSmRequired__FP2SM3OID(p->plist, OidSmaCur(p->x188));
    i0 = i;
    for (;;) {
        void *pv;
        int j;
        i += d;
        if (i < 0)
            i = p->plist->c - 1;
        else if (i >= p->plist->c)
            i = 0;
        pv = OidFromSmIsms__FP2SMi(p->plist, i);
        for (j = 0; j < p->c; j++) {
            if (p->a[j] == pv) {
                SetSmaGoal__FP3SMA3OID(p->x188, pv);
                return;
            }
        }
        if (d == 0)
            d = 1;
        else if (i == i0)
            break;
    }
    ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(0, p, -1, 0, &p->x188);
}
