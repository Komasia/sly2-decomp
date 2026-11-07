struct A { char pad[0x15c]; void *f15c; };
struct G { char pad[0x4638]; void *f4638; };
extern struct G g_sw;
struct S { char pad[0x194]; struct A *pa; };
int IdStandSaved__FP2LO(struct S *);
struct A *func_001CB250(void *, int);
void SelectBootyRecord__FP2LOi(struct A *, int);
void SetBootyState__FP2LOi(struct A *, int);
// name: SafeHouse port (AttachStandBooty)
void AttachStandBooty__FP2LO(struct S *p) {
    struct G *pg;
    int i;
    struct A *pa;
    if (p->pa) return;
    pg = &g_sw;
    if (!pg->f4638) return;
    i = IdStandSaved__FP2LO(p);
    if (i == -1) return;
    pa = func_001CB250(pg->f4638, 0);
    p->pa = pa;
    if (pa) {
        SelectBootyRecord__FP2LOi(pa, i);
        p->pa->f15c = p;
        SetBootyState__FP2LOi(p->pa, 1);
    }
}
