typedef int qword __attribute__((mode(TI)));
struct P;
struct S { struct P *a; int pad[3]; qword q; };
void GReachDist__FP5REACHG9VU_VECTORP6VECTORPff(struct P *a, qword q, float *projection, float *distance, float t);
float func_001CC288(struct S *p, float t) { float g; GReachDist__FP5REACHG9VU_VECTORP6VECTORPff(p->a, p->q, 0, &g, t); return g; }
