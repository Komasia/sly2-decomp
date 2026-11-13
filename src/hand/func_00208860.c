typedef struct QW { int a[4]; } QW;
struct O { char pad[0xFC]; int c; QW a[1]; };
struct S { char pad[0x3A4]; int n; char p2[0xF64 - 0x3A8]; struct O *o; };
QW *PdetentryFind__FP8DETECTORi(struct O *o);
void CopyAb(void *dst, void *src, int cb) asm("CopyAb__FPvT0Ui");
void func_00208860(struct S *p)
{
    QW *pq = PdetentryFind__FP8DETECTORi(p->o);
    struct O *o = p->o;
    int c = o->c;
    QW *pqEnd = &o->a[c - p->n];
    if (pq && pq < pqEnd) {
        int i;
        o->c = c - 1;
        i = pq - o->a;
        CopyAb(pq, pq + 1, (p->o->c - i) * 16);
    }
}
