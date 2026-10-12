struct E { int id; int a[7]; };
struct S { char pad[0x4C]; int c; struct E *ae; };
struct E *func_001DAE20(struct S *p, int id) {
    int i;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        if (pe->id == id) return pe;
    }
    return 0;
}
