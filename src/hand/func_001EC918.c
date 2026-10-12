struct O { char pad[0x14]; int n14; char pad2[0x30-0x18]; struct O *pChild; char pad3[0x40-0x34]; struct O *pNext; };
extern struct O *D_003E159C;
struct O *func_001EC918(int n)
{
    int unused[4];
    struct O *p;
    if (n == -1) return 0;
    for (p = D_003E159C; p; p = p->pNext) {
        if (p->pChild) break;
        if (p->n14 == n) return p;
    }
    return 0;
}
