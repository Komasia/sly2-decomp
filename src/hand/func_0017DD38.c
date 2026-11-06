typedef int qword __attribute__((mode(TI)));
struct Q2 { qword a, b; };
struct S { char pad[0x40]; struct Q2 q; char pad2[0x40]; float gA0; };
void Search__7JOBGOTO(struct S *p);
// name: SafeHouse port (JOBGOTO::SetGoal)
void SetGoal__7JOBGOTOP4GOAL(struct S *p, struct Q2 *pq) { p->q = *pq; p->gA0 = -3.40282346638528859812e+38f; Search__7JOBGOTO(p); }
