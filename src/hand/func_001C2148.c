typedef int qword __attribute__((mode(TI)));
struct E { qword q; int pad[4]; };
struct S { char pad[0x50]; int c; char pad2[0x1c]; struct E a[6]; };
void func_001C2148(struct S *p, qword q)
{
    if ((unsigned)p->c < 6) { struct E *pe = &p->a[p->c++]; pe->q = q; }
}
