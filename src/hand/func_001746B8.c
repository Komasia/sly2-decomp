struct E { int n; int a[11]; };
struct S { char pad[0x5C]; int c; struct E *ae; };
void func_001A5848(struct S *p);
void func_00173928(struct S *p, struct E *pe, int a, int b);
void func_001746B8(struct S *p) {
    int i;
    func_001A5848(p);
    if (!p->ae) return;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i]; if (pe->n) func_00173928(p, pe, 0, 0);
    }
}
