typedef int qword __attribute__((mode(TI)));
struct A { char pad[0x124]; int k124; };
struct S { char pad[0xF80]; int kF80; struct A *pF84; int xF88; int nF8C; void *pF90; };
int FIsBasicDerivedFrom__FP5BASIC3CID(struct A *pa, int n);
qword PosOfLo__FP2LO(void *p);
void NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(struct A *pa, qword q, int a, int b, int c, int d, int *pn);
void PairActorWith__FP5ACTORP2LOi(struct S *p, struct A *pa, int n);

// name: SafeHouse port (AttachGuardMove)
void AttachGuardMove__FP5GUARDP2LOi(struct S *p, struct A *pa, int n)
{
    p->pF84 = pa;
    p->nF8C = n;
    if (FIsBasicDerivedFrom__FP5BASIC3CID(pa, 0xB)) {
        p->kF80 = 1;
        NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(p->pF84, PosOfLo__FP2LO(p->pF90), 0, 0, 0, 0, &p->xF88);
        PairActorWith__FP5ACTORP2LOi(p, p->pF84, 1);
    } else if (FIsBasicDerivedFrom__FP5BASIC3CID(p->pF84, 0xD)) {
        p->kF80 = 0;
        NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2(p->pF84, PosOfLo__FP2LO(p), 0, 0, 0, 0, &p->xF88);
        PairActorWith__FP5ACTORP2LOi(p, p->pF84, 1);
    } else if (FIsBasicDerivedFrom__FP5BASIC3CID(p->pF84, 0x13) && p->pF84->k124 == 3) {
        p->kF80 = 2;
        PairActorWith__FP5ACTORP2LOi(p, p->pF84, 1);
    } else if (FIsBasicDerivedFrom__FP5BASIC3CID(p->pF84, 0x27)) {
        p->kF80 = 3;
        PairActorWith__FP5ACTORP2LOi(p, p->pF84, 1);
    } else {
        p->pF84 = 0;
    }
}
