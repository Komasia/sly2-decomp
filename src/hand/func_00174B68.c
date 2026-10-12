struct S { char pad[0x30]; int n30; char pad2[0xC]; void *p40; };
void func_001EEF98(struct S *p);
int func_00209430(void *p);
void func_001749C0(struct S *p, int n);
void func_00174B68(struct S *p) {
    int s;
    func_001EEF98(p);
    do {
        s = p->n30;
        if (s == 0 && func_00209430(p->p40)) func_001749C0(p, 1);
    } while (s != p->n30);
}
