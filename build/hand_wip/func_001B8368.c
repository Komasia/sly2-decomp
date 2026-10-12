struct S { char pad[0x204]; int f204; char pad2[0x13D0 - 0x208]; int n; int pad3; int m; };
int func_00143C78(struct S *p);
int func_001B8368(struct S *p)
{
    int f;
    if (p->f204) return 0;
    if (p->m != 1 && p->n == 0x14) f = 0;
    else f = func_00143C78(p);
    return f;
}
