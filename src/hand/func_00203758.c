struct S { char pad[0xEC]; void *p; int n; };
int FTaskDone__FP4TASK(void *p);
int func_00203758(struct S *p) { if (p->p) return FTaskDone__FP4TASK(p->p); return p->n; }
