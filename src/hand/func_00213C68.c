typedef int qword __attribute__((mode(TI)));
struct M { qword a, b; };
struct VE { short d; short pad; struct M *(*pf)(void *, int, int); };
struct A { struct VE *vt; };
struct S { char pad[0xC4]; struct A *pa; char pad2[0x30]; struct M *pm; };
void func_00213C68(struct S *p, struct M *src)
{
    if (!p->pm) {
        struct A *a = p->pa;
        p->pm = a->vt[1].pf((char *)a + a->vt[1].d, 0x20, 0x1F);
    }
    *p->pm = *src;
}
