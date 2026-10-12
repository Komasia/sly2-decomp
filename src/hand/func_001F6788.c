struct B { char pad[0x18]; int n; };
struct N { char pad[0x14]; struct B *pb; int n; char pad2[8]; struct N *next; };
extern struct N *D_003E1218;
struct N *func_001F6788(int n, int m)
{
    struct N *p;
    int unused[4];
    for (p = D_003E1218; p; p = p->next) {
        if (p->n == n) {
            if (m == -1 || p->pb->n == m)
                return p;
        }
    }
    return 0;
}
