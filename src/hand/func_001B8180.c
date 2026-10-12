struct S { char pad[0x13D0]; int n; };
int func_001B8180(struct S *p)
{
    switch (p->n) {
    case 0: case 1: case 9: case 10:
        return 1;
    }
    return 0;
}
