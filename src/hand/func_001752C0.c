struct T { char pad[0xF3C]; int nF3C; };
struct S { char pad[0x10]; struct T *pt; };
void Exit__7JOBMOVE(struct S *p);
// name: SafeHouse port (JOBSTRIKE::Exit)
void Exit__9JOBSTRIKE(struct S *p) { Exit__7JOBMOVE(p); p->pt->nF3C = 0; }
