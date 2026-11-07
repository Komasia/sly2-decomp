typedef int qword __attribute__((mode(TI)));
struct E;
struct D { char pad[0x10]; struct E *pe; };
struct C { char pad[0xDC]; struct D *pd; };
struct B { char pad[0xE8]; int k; char pad2[0xF4 - 0xEC]; qword *pq; };
struct A { char pad[0xE8]; struct C *pc; char pad2[0x294 - 0xEC]; struct B *pb; };
struct P { char pad[0x10]; struct A *pa; char pad1[4]; void *p18; char pad2[0x30 - 0x1C]; int f30; char pad3[0x40 - 0x34]; qword v; };
qword func_001A62E8(struct A *pa);
void FNavPathCrv__FP9NAVREGIONiiP3CRV(struct E *pe, qword r, qword v, struct B *pb);
void RecalcCrv__FP3CRV(struct B *pb);
void Follow__9JOBFOLLOWP3CRVi(void *p, struct B *pb, int n);
// name: SafeHouse port (JOBACTORWALK::SetGoal)
void SetGoal__12JOBACTORWALKG9VU_VECTOR(struct P *p, qword v)
{
    p->v = v;
    if (p->p18) {
        struct A *pa = p->pa;
        struct B *pb = pa->pb;
        struct D *pd = pa->pc ? pa->pc->pd : 0;
        struct E *pe = pd ? pd->pe : 0;
        qword r = func_001A62E8(pa);
        if (!pe || p->f30) {
            pb->k = 2;
            pb->pq[0] = r;
            pb->pq[1] = p->v;
            RecalcCrv__FP3CRV(pb);
        } else {
            FNavPathCrv__FP9NAVREGIONiiP3CRV(pe, r, p->v, pb);
        }
        Follow__9JOBFOLLOWP3CRVi(p->p18, pb, 0);
    }
}
