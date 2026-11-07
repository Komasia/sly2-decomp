typedef int qword __attribute__((mode(TI)));
struct F { int a[4]; qword q; };
void *func_002333B4(void *, int, int);
void RecoverActorTo__FP5ACTORPv(void *, struct F *);
// name: SafeHouse port (RecoverTo)
void RecoverTo__FP5ACTORG9VU_VECTOR(void *p, qword q) { struct F f; func_002333B4(&f, 0, sizeof f); f.q = q; RecoverActorTo__FP5ACTORPv(p, &f); }
