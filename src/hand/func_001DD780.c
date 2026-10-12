struct O { char pad[0x58]; int n58; char p1[8]; int n64; };
struct S { char pad[0x24]; struct O *po; };
int func_001DD780(struct S *p) {
    struct O *po = p->po;
    if (!po) return 0;
    if (po->n58 != 2) return 0;
    return po->n64 == 2;
}
