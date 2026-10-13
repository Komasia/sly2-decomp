typedef int qword __attribute__((mode(TI)));
struct P;
struct S { struct P *a; int pad[3]; qword q; };
void func_001CC1F8(struct P *a, qword q, float *projection, float *distance, float t);
float func_001CC2B8(struct S *p, float t) { float g; func_001CC1F8(p->a, p->q, 0, &g, t); return g; }
