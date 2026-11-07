struct CMD { int kind; int b; char pad[0x48]; };
struct Q { char pad[0x50]; int c; struct CMD *a; int cMax; };
extern struct CMD D_003DA740;
void func_002333B4(void *p, int b, int cb);
// name: SafeHouse port (PcmdNew)
struct CMD *PcmdNew__FP4SCPTii(struct Q *pq, int kind, int b)
{
    struct CMD *p;
    int cMax = pq->cMax;
    if (cMax <= -1) cMax = 0x200;
    if (pq->c >= cMax) return &D_003DA740;
    p = &pq->a[pq->c++];
    func_002333B4(p, 0, sizeof(struct CMD));
    p->kind = kind;
    p->b = b;
    return p;
}
