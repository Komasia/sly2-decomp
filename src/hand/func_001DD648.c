extern char D_002D83E8[];
struct S { int a, b, c; void *vt; char pad[0x10]; int n20; };
struct S *func_001DA728(struct S *p);
void func_001DA7D0(struct S *p);
struct S *func_001DD648(struct S *p) {
    func_001DA728(p);
    p->vt = D_002D83E8;
    p->n20 = 0x52D;
    func_001DA7D0(p);
    return p;
}
