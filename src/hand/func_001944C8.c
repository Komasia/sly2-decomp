struct S { int a, b, k, c; char pad[0x54-0x10]; int x54, x58, x5c, x60, x64; };
int func_001944C8(struct S *p, int *pf) {
    int f = 0;
    int v;
    switch (p->k) {
    case 0:
        if (p->c == 5) v = p->x60;
        else v = p->x54;
        break;
    case 1:
        v = p->x58;
        break;
    case 8:
        switch (p->c) {
        case 9: case 10: v = p->x64; f = 1; break;
        default: v = 0; break;
        }
        break;
    default:
        v = 0;
        break;
    }
    *pf = f;
    return v;
}
