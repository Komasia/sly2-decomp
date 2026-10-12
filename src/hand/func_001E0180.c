struct T { char pad[0x10]; int n; };
struct O { char pad[0x28]; struct T *pt; char pad2[0xE4-0x2C]; struct O *pNext; };
struct S { char pad[0x5C]; struct O *pFirst; };
struct O *func_001E0180(struct S *s, int n, struct O *pSkip)
{
    int unused[4];
    struct O *p;
    for (p = s->pFirst; p; p = p->pNext) {
        if (p != pSkip && p->pt->n == n) return p;
    }
    return 0;
}
