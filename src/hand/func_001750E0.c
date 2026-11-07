struct M { int n0; int n4; int n8; };
struct T { char pad[0x5C]; int n5C; char pad2[0x1A4 - 0x60]; int n1A4; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x24]; int n38; char pad3[4]; void *p40; };
int PasegaOfKinde__FP5KINDE(void *p);
int Message__7JOBMOVEiPv(struct S *p, int msg, struct M *pm);
void SetXfMode__FP3ALOP2XFi(struct T *t, int a, int b);
// name: SafeHouse port (JOBSTAND::Message)
int Message__8JOBSTANDiPv(struct S *p, int msg, struct M *pm) {
    if (msg == 9 && p->p40 && PasegaOfKinde__FP5KINDE(p->p40) == pm->n0) {
        switch (pm->n8) {
        case 0x29: p->pt->n1A4 = 1; SetXfMode__FP3ALOP2XFi(p->pt, p->pt->n5C, 2); return 1;
        case 0x2A: p->pt->n1A4 = 0; if (!p->n38) SetXfMode__FP3ALOP2XFi(p->pt, p->pt->n5C, 1); return 1;
        }
    }
    return Message__7JOBMOVEiPv(p, msg, pm);
}
