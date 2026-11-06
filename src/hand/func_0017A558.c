typedef int qword __attribute__((mode(TI)));
extern qword D_002A2DD0;
struct G { int a; };
extern struct G g_sw;
struct S { char pad[0x10]; char *p10; };
void Exit__7JOBMOVE(struct S *p);
void SetSleepState__8JOBSLEEPi(struct S *p, int n);
void func_00156C80(struct G *g, int a, qword q, int b, void *pv);
// name: SafeHouse port (JOBSLEEP::Exit)
void Exit__8JOBSLEEP(struct S *p) { Exit__7JOBMOVE(p); SetSleepState__8JOBSLEEPi(p, -1); func_00156C80(&g_sw, -1, D_002A2DD0, 0, p->p10 + 0x35C); }
