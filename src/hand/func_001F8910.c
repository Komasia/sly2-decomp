struct E { int k; int pad[2]; int nC; struct E *next; };
struct Q { char pad[0x90]; struct E *pe; };
struct P { char pad[0x20]; void *p20; struct Q *pq; };
void RemoveXfCtrl__FP3ALOP2XFP4CTRL(void *, struct Q *, struct E *);
void func_0012E210(struct E *);
void SortXfCtrls__FP3ALOP2XF(void *, struct Q *);
void SetXfMode__FP3ALOP2XFi(void *, struct Q *, int);
void HoldXfMode(void *, struct Q *);
// name: SafeHouse port (PctrlFindXfh)
struct E *PctrlFindXfh__FP7XFBASICiii(struct P *p, int k, int n, int m)
{
    struct E *pe;
    for (pe = p->pq->pe; pe; pe = pe->next) {
        if (pe->k != k) continue;
        if (n == -1) {
            RemoveXfCtrl__FP3ALOP2XFP4CTRL(p->p20, p->pq, pe);
            func_0012E210(pe);
            return 0;
        }
        if (m != pe->nC) {
            pe->nC = m;
            SortXfCtrls__FP3ALOP2XF(p->p20, p->pq);
        }
        if (pe == p->pq->pe) {
            SetXfMode__FP3ALOP2XFi(p->p20, p->pq, n);
            HoldXfMode(p->p20, p->pq);
        }
        return pe;
    }
    return 0;
}
