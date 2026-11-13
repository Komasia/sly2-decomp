struct F { int a0; int pad; int n8; int nC; int n10; int pad2[0x13]; };
struct S { char pad[0x10]; int n10; };
void *s1_memset(void *p, int c, int n);
void PaloAcceptContact__FP5CTMSG(struct F *pf);
// name: SafeHouse port (JOBREACT::SendHit)
void SendHit__8JOBREACTii(struct S *p, int a, int b) { struct F f; s1_memset(&f, 0, sizeof(f)); f.a0 = b; f.n10 = a; f.nC = 0x40000; f.n8 = p->n10; PaloAcceptContact__FP5CTMSG(&f); }
