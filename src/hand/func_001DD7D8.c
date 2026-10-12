extern char D_002D8368[];
struct S { int a, b, c; void *vt; char pad[0x10]; int n20; };
struct S *func_001DA728(struct S *p);
void func_001DA7D0(struct S *p);
struct S *func_001DD7D8(struct S *p) {
    func_001DA728(p);
    p->vt = D_002D8368;
    p->n20 = 0x5D2;
    func_001DA7D0(p);
    return p;
}
