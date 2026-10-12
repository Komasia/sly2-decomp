typedef int qword __attribute__((mode(TI)));
struct S { int a; int pad[3]; qword q; };
void func_001CC1F8(int a, qword q, int z, float *pg);
float func_001CC2B8(struct S *p) { float g; func_001CC1F8(p->a, p->q, 0, &g); return g; }
