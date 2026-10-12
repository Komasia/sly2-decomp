struct E { int a; int b; };
struct S { char pad[0x110]; unsigned int c; struct E ae[16]; };
void func_00211E70(struct S *p, int v)
{
    unsigned int c = p->c;
    if (c < 16) {
        p->ae[c].a = v;
        p->c = c + 1;
    }
}
