typedef struct { short d; short pad; void *pfn; } VTE;
struct T { char pad[0x14]; int n14; };
struct A { char pad[0x200]; struct T *pt; };
struct Q { struct A *pa; int pad[2]; int nC; };
struct S { char pad[0xC]; VTE *vt; char pad2[4]; int n14; char pad3[0x26C - 0x18]; char x26C[4]; };
int FIsBasicDerivedFrom__FP5BASIC3CID(struct A *pa, int n);
int FAbsorbSoWkr__FP2SOP3WKR(struct S *p, struct Q *q);
void OfferJobMessage__FP5GUARDii(void *p, int k, struct Q *q);
// name: SafeHouse port (FAcceptContactGuard)
int FAcceptContactGuard__FP3ALOP5CTMSG(struct S *p, struct Q *q)
{
    if (!((int (*)(void *))p->vt[86].pfn)((char *)p + p->vt[86].d)) {
        if (((int (*)(void *, int))p->vt[76].pfn)((char *)p + p->vt[76].d, q->nC))
            return 1;
        if (q->pa && FIsBasicDerivedFrom__FP5BASIC3CID(q->pa, 0x4F) && q->pa->pt->n14 == p->n14)
            return 1;
        if (!FAbsorbSoWkr__FP2SOP3WKR(p, q))
            return 0;
    }
    OfferJobMessage__FP5GUARDii(p->x26C, 0xC, q);
    return 1;
}
