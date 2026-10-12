typedef int qword __attribute__((mode(TI)));
struct Q2 { qword a, b; };
struct S { char pad[0x40]; struct Q2 q; char pad2[0x40]; float gA0; };
void func_0017DA28(struct S *p);
void func_0017DD38(struct S *p, struct Q2 *pq) { p->q = *pq; p->gA0 = -3.40282346638528859812e+38f; func_0017DA28(p); }
