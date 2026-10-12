struct B { int n0; int n4; struct B *next; };
struct S { int n0; int n4; int n8; struct B *ap[8]; int c; struct B ab[1]; };
int func_00170448(int n);
void func_001704B8(struct S *p) {
    struct B *pb;
    int n, i;
    if (!(p->n4 & 0x7F)) return;
    pb = &p->ab[p->c++];
    pb->n0 = p->n4;
    n = (p->n4 + 0x7F) & ~0x7F;
    p->n4 = n;
    pb->n4 = n;
    i = func_00170448(n - pb->n0);
    pb->next = p->ap[i];
    p->ap[i] = pb;
}
