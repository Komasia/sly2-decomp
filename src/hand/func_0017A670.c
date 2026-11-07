typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
struct V { char pad[0x20]; qword q20; };
struct T { char pad[0x35C]; struct V *p35C; };
struct S { char pad[0x10]; struct T *pt; char pad2[0x3C]; int n50; int pad3; float g58; };
void Update__7JOBMOVE(struct S *p);
void SetSleepState__8JOBSLEEPi(struct S *p, int n);
qword PosOfLo__FP2LO(void *p);
// name: SafeHouse port (JOBSLEEP::Update)
void Update__8JOBSLEEP(struct S *p) {
    int s;
    Update__7JOBMOVE(p);
    do {
        s = p->n50;
        if (s == 0 && g_clock.t > p->g58) SetSleepState__8JOBSLEEPi(p, 1);
    } while (p->n50 != s);
    { struct T *t = p->pt; struct V *v = t->p35C; v->q20 = PosOfLo__FP2LO(t); }
}
