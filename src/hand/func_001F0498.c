struct Q { int a; char *ab; };
struct A { char pad[0x50]; int c; };
struct Q *PsmgFind__FP2SMUi(struct A *p, int n);
// name: SafeHouse port (CsmtDistance)
int CsmtDistance__FP2SMUiii(struct A *p, int n, int y, int x)
{
    struct Q *pq = PsmgFind__FP2SMUi(p, n);
    int r = 0;
    if (pq)
        r = pq->ab[y * p->c + x];
    return r;
}
