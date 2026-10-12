struct S { char pad[0x204]; int x204; char p1[0x16C0]; int n; };
int func_00143C78(struct S *p);
int func_0018DEE0(struct S *p)
{
    if (p->x204) return 0;
    switch (p->n) {
    case 3: case 8: case 21: case 22:
        return 0;
    case 13: case 14:
        return 1;
    case 24:
        return 0xF;
    }
    return func_00143C78(p);
}
