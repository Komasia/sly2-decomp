extern char D_002D8468[];
struct S { int a, b, c; void *vt; char pad[0x10]; int n20; };
struct S *func_001DA728(struct S *p);
void func_001DCD08(struct S *p);
struct S *func_001DCC58(struct S *p) {
    func_001DA728(p);
    p->vt = D_002D8468;
    p->n20 = 0x4E0;
    func_001DCD08(p);
    return p;
}
