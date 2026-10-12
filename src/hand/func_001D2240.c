struct O { char pad[0x80]; int n80; };
struct S { char pad[0x4F8]; int c; struct O *ap[1]; };
int func_001D4E08(struct O *po);
struct O *func_001D2240(struct S *p) {
    int i;
    for (i = 0; i < p->c; i++) {
        struct O *po = p->ap[i];
        if (func_001D4E08(po) && po->n80 != 4) return po;
    }
    return 0;
}
