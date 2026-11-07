struct T { char pad[0x28]; int n28; };
struct G { char pad[0x45CC]; struct T *p45CC; };
extern struct G g_sw;
struct S { char pad[0x30]; int n30; int pad2; int n38; char pad3[0x64]; float gA0; int nA4; };
void Init__5AIJOB(struct S *p);
// name: SafeHouse port (JOBGOTO::Init)
void Init__7JOBGOTO(struct S *p) { Init__5AIJOB(p); p->n30 = -1; p->n38 = -1; p->gA0 = -3.40282346638528859812e+38f; p->nA4 = g_sw.p45CC->n28; }
