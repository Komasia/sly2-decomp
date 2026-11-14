typedef int qword __attribute__((mode(TI)));
struct F { int a[4]; qword q; };
void *s1_memset(void *, int, int) asm("memset");
void RecoverActorTo__FP5ACTORPv(void *, struct F *);
// name: SafeHouse port (RecoverTo)
void RecoverTo__FP5ACTORG9VU_VECTOR(void *p, qword q) { struct F f; s1_memset(&f, 0, sizeof f); f.q = q; RecoverActorTo__FP5ACTORPv(p, &f); }
