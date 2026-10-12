struct E { char pad[8]; short h; char pad2[14]; };
struct S { short a; unsigned short c; char pad[4]; struct E *ae; };
int func_00217EF8(struct S *p)
{
    int i;
    int c = p->c;
    for (i = 0; i < c; i++) {
        if (p->ae[i].h < 0)
            return i;
    }
    return 0;
}
