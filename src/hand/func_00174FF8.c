typedef int qword __attribute__((mode(TI)));
extern qword D_002A2DD0;
struct T { char pad[0x58]; int n58; int n5C; char pad2[0xF64 - 0x60]; void *pF64; char pad3[0xFCC - 0xF68]; int nFCC; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x24]; int n38; };
void func_00174950(struct S *p);
int func_00209A68(struct T *t, int n);
void func_0020AB68(struct T *t, int a, int b, qword q);
void func_00153FF8(void *p);
void func_002303A0(struct T *t, int a, int b);
void func_00174FF8(struct S *p) {
    func_00174950(p);
    if (func_00209A68(p->pt, 1)) {
        func_0020AB68(p->pt, 0, 0, D_002A2DD0);
        func_00153FF8(p->pt->pF64);
        if (p->pt->nFCC) p->n38 = p->pt->nFCC;
    }
    func_002303A0(p->pt, p->pt->n58, 1);
    if (!p->n38) func_002303A0(p->pt, p->pt->n5C, 1);
}
