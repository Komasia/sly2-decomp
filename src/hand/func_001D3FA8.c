struct O { char pad[0x14]; int id; };
struct S { char pad[0x4F8]; int c; struct O *ap[1]; };
struct O *func_001D3FA8(struct S *p, int id) {
    int i;
    for (i = 0; i < p->c; i++) {
        struct O *po = p->ap[i];
        if (po->id == id) return po;
    }
    return 0;
}
