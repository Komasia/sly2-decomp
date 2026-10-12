extern char D_002D85E8[];
struct S { int a, b, c; void *vt; char pad[0x10]; int n20; };
void func_001DA7D0(struct S *p);
struct S *func_001DA728(struct S *p) {
    p->a = 0;
    p->b = 0;
    p->vt = D_002D85E8;
    p->n20 = -1;
    func_001DA7D0(p);
    return p;
}
