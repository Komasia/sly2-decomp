struct S { char pad[0x13d0]; int st; };
int func_00135FF0(struct S *p) {
    switch (p->st) {
    case 0: case 1: case 5: case 7: return 1;
    }
    return 0;
}
