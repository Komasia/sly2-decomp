struct S { int n0; int n4; int n8; };
struct L { int a; int b; int c; int d; };
void func_001EF0D8(struct L *pl);
void func_001EECD0(struct S *p)
{
    struct L l;
    if (p->n4 > 0) {
        l.a = p->n8;
        func_001EF0D8(&l);
    }
    p->n4 = 0;
}
