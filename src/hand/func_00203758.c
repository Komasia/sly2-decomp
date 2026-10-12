struct S { char pad[0xEC]; void *p; int n; };
int func_00164030(void *p);
int func_00203758(struct S *p) { if (p->p) return func_00164030(p->p); return p->n; }
