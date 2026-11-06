typedef int qword __attribute__((mode(TI)));
struct G { int a; };
extern struct G g_sw;
struct T { char pad[0xF64]; void *pF64; };
struct S { char pad[0x10]; struct T *pt; };
void Enter__7JOBMOVE(struct S *p);
void SetSleepState__8JOBSLEEPi(struct S *p, int n);
void func_00153FF8(void *p);
qword func_001A62E8(void *p);
void func_00156C80(struct G *g, int a, qword q, void *b, void *pv);
// name: SafeHouse port (JOBSLEEP::Enter)
void Enter__8JOBSLEEP(struct S *p) { Enter__7JOBMOVE(p); SetSleepState__8JOBSLEEPi(p, 0); func_00153FF8(p->pt->pF64); func_00156C80(&g_sw, 1, func_001A62E8(p->pt), p->pt, (char *)p->pt + 0x35C); }
