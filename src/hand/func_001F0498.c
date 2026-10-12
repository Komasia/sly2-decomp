struct Q { int a; char *ab; };
struct A { char pad[0x50]; int c; };
struct Q *func_001F0458(struct A *p, int n);
int func_001F0498(struct A *p, int n, int y, int x)
{
    struct Q *pq = func_001F0458(p, n);
    int r = 0;
    if (pq)
        r = pq->ab[y * p->c + x];
    return r;
}
