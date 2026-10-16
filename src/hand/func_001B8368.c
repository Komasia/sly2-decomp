struct S { char pad[0x204]; int f204; char pad2[0x13D0-0x208]; int n; int reserved; int m; };
int func_00143C78(struct S *p);
int func_001B8368(struct S *p)
{
    if (p->f204) return 0;
    if (p->m == 1 || p->n == 20) return 0;
    return func_00143C78(p);
}
