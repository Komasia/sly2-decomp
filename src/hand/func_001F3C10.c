struct G { char pad[0x3D60]; int n; };
extern struct G D_003DD490;
struct Q { char pad[0xC]; int n; };
struct A { char pad[0x134]; struct Q *pq; };
void func_001A4478(struct G *pg, int n, struct Q *pq);
void func_001F3C10(struct A *p)
{
    struct Q *pq = p->pq;
    if (pq && pq->n != D_003DD490.n) {
        func_001A4478(&D_003DD490, 0, pq);
        p->pq->n = D_003DD490.n;
    }
}
