struct T { char pad[0x58]; int n58; int n5C; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x24]; int n38; };
void Exit__7JOBMOVE(struct S *p);
void SetXfMode__FP3ALOP2XFi(struct T *t, int a, int b);
// name: SafeHouse port (JOBSTAND::Exit)
void Exit__8JOBSTAND(struct S *p) { Exit__7JOBMOVE(p); SetXfMode__FP3ALOP2XFi(p->pt, p->pt->n58, 2); if (!p->n38) SetXfMode__FP3ALOP2XFi(p->pt, p->pt->n5C, 2); }
