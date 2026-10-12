struct S { char pad[0x18C8]; int n; };
int func_001894F8(struct S *p)
{
    switch (p->n) {
    case 0: case 1: case 5: case 10: case 12: case 24:
        return 1;
    }
    return 0;
}
