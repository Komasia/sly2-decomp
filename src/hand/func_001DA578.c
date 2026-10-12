struct S { char pad[0x18]; int n18; int n1C; int n20; };
void func_001DA578(struct S *p, int n) {
    if (n == -1) {
        p->n20 = -1;
        p->n1C = 0;
    } else if (n == p->n18) {
        p->n1C = 0;
    } else if (n == p->n20) {
        p->n20 = -1;
    }
}
