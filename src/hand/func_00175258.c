typedef int qword __attribute__((mode(TI)));
struct T { int a, b; void *p8; };
struct S { char pad[0x38]; void *p38; int pad2; struct T *p40; char pad3[0xC]; int n50; };
void Update__7JOBMOVE(struct S *p);
qword PosOfLo__FP2LO(void *p);
void SetK2Target__FP6K2PLAYG9VU_VECTOR(void *p, qword q);
// name: SafeHouse port (JOBSTRIKE::Update)
void Update__9JOBSTRIKE(struct S *p) { Update__7JOBMOVE(p); if (!p->p40 || !p->p40->p8) p->n50 = 0; if (p->n50) { struct T *t = p->p40; SetK2Target__FP6K2PLAYG9VU_VECTOR(t->p8, PosOfLo__FP2LO(p->p38)); } }
