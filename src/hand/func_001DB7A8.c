extern char D_002D84E8[];
struct S { int a, b, c; void *vt; char pad[0x10]; int n20; };
struct S *func_001DA728(struct S *p);
void func_001DB820(struct S *p);
struct S *func_001DB7A8(struct S *p) {
    func_001DA728(p);
    p->vt = D_002D84E8;
    p->n20 = 0x378;
    func_001DB820(p);
    return p;
}
