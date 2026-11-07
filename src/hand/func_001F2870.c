typedef int qword __attribute__((mode(TI)));
struct M { qword a[4]; };
struct O { char pad[0x40]; struct M m; char pad2[0xA4 - 0x80]; int nA4; };
struct E { struct O *po; int pad[7]; struct M m; char pad3[0xA8 - 0x60]; int nA8; int nAC; };
struct VTE { short d; short p; int (*pfn)(void *); };
struct VT { struct VTE a[63]; };
struct Q { char pad[0x34]; char dl[1]; };
struct P { char pad[0xC]; struct VT *pvt; char pad2[0xEC - 0x10]; struct Q *pq; };
void PoxaEnsure__FP3ALO(struct P *);
int FFindDlEntry__FP2DLPv(void *, void *);
void AppendDlEntry__FP2DLPv(void *, void *);
void MarkAloDirty__FP3ALO(struct P *);
void UpdateSoeWorld__FP3SOE(struct E *);
void WakeAlo__FP3ALO(struct P *);
// name: SafeHouse port (AddSoeToOxa)
void AddSoeToOxa__FP3ALOP3SOE(struct P *p, struct E *pe)
{
    struct O *po;
    PoxaEnsure__FP3ALO(p);
    if (FFindDlEntry__FP2DLPv(p->pq->dl, pe)) return;
    AppendDlEntry__FP2DLPv(p->pq->dl, pe);
    po = pe->po;
    pe->nA8 = -1;
    pe->m = po->m;
    pe->nAC = po->nA4;
    MarkAloDirty__FP3ALO(p);
    UpdateSoeWorld__FP3SOE(pe);
    if (!p->pvt->a[62].pfn((char *)p + p->pvt->a[62].d)) WakeAlo__FP3ALO(p);
}
