struct A { char pad[0x184]; int n184; };
struct B { char pad[0xC]; struct A *pa; };
struct Q { struct A *pa; void *p; };
struct S { char pad[0x26C]; char x26C[0x49C - 0x26C]; struct B *pb; };
void HandlePoMessage__FP2PO5MSGIDPv(struct S *p, int k, struct Q *q);
void func_0020D460(struct B *pb, struct A *pa);
void OfferJobMessage__FP5GUARDii(void *p, int k, struct Q *q);
void HandleStepguardMessage__FP9STEPGUARD5MSGIDPv(struct S *p, int k, struct Q *q)
{
    HandlePoMessage__FP2PO5MSGIDPv(p, k, q);
    switch (k) {
    case 4:
        if (q->p == p && q->pa->n184)
            func_0020D460(p->pb, q->pa);
        break;
    case 5:
        if (q->p == p && q->pa == p->pb->pa)
            func_0020D460(p->pb, 0);
        break;
    }
    OfferJobMessage__FP5GUARDii(p->x26C, k, q);
}
