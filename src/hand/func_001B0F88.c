typedef int qword __attribute__((mode(TI)));
struct M { int k; int pad[3]; qword a; qword b; qword c; };
struct VTE { short d; short pad; void (*pfn)(void *, struct M *); };
struct O { char pad[0xC]; struct VTE *vt; };
struct A { char pad[0x20]; qword q20; qword q30; int pad1; int n44; };
struct S { char pad[0x1C8]; struct O *p1C8; char pad1[0x220 - 0x1CC]; int n220; };
int FAbsorbSoWkr__FP2SOP3WKR(struct S *p, struct A *pa);
void SetBirdState__FP2LOi(struct S *p, int n);
// name: SafeHouse port (FAcceptBirdContact)
int FAcceptBirdContact__FP3ALOP5CTMSG(struct S *p, struct A *pa)
{
    int r = FAbsorbSoWkr__FP2SOP3WKR(p, pa);
    if (r && (pa->n44 & 8) && p->n220 != 5) {
        SetBirdState__FP2LOi(p, 5);
        if (p->p1C8) {
            struct M m;
            m.k = 6;
            m.b = pa->q20;
            m.a = pa->q30;
            p->p1C8->vt[51].pfn((char *)p->p1C8 + p->p1C8->vt[51].d, &m);
        }
    }
    return r;
}
