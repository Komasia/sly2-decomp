typedef int qword __attribute__((mode(TI)));
struct S { int a[5]; int n14; };
void *func_001BF1F8(struct S *p, int n, qword q);
qword func_001BFDB0(void *p, qword q);
int func_001C0320(struct S *p, qword q, qword *pq)
{
    void *pv = func_001BF1F8(p, p->n14, q);
    if (!pv) return 0;
    *pq = func_001BFDB0(pv, q);
    return 1;
}
