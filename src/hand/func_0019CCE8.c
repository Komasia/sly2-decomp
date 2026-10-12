struct S { char pad[0x38]; int *p; };
void func_0019CD38(struct S *, int);
void func_0019CCE8(struct S *p) {
    if (p->p) {
        switch (*p->p) {
        case 0: case 8: case 9: case 10: return;
        }
    }
    func_0019CD38(p, 2);
}
