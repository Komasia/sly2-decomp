struct S { char pad[0x18C8]; int n; };
int func_001409B8(struct S *p);
int func_00189488(struct S *p)
{
    int r = func_001409B8(p);
    if (r != -1) return r;
    switch (p->n) {
    case 1: case 5: case 6: case 9:
        return 1;
    }
    return -1;
}
