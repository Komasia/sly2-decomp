struct S { char pad[0x18D8]; int n; };
int func_0018ED98(struct S *p);
int func_0018F050(struct S *p)
{
    int r;
    switch (p->n) {
    case 0x16: r = 0x17; break;
    case 0x17: r = 0x16; break;
    default:
        r = func_0018ED98(p) ? 0x17 : 0x16;
        break;
    }
    return r;
}
