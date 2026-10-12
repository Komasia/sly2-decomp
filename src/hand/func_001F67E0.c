struct B { char pad[0x18]; int n; };
struct N { char pad[0x1C]; struct N *next; int pad2; struct B *pb; int n; };
extern struct N *D_003E126C;
struct N *func_001F67E0(int n, int m)
{
    struct N *p;
    int unused[4];
    for (p = D_003E126C; p; p = p->next) {
        if (p->n == n) {
            if (m == -1 || p->pb->n == m)
                return p;
        }
    }
    return 0;
}
