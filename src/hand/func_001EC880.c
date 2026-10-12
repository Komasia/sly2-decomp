struct O { int oid; char pad[0x14]; struct O *pNext; };
extern struct O *D_003E1590;
struct O *func_001EC880(int oid)
{
    int unused[4];
    struct O *p;
    if (oid == -1) return 0;
    for (p = D_003E1590; p; p = p->pNext) {
        if (p->oid == oid) return p;
    }
    return 0;
}
