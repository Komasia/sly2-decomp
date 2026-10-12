typedef int qword __attribute__((mode(TI)));
struct S { char pad[0x98]; int c; qword *a; };
void func_001733C8(struct S *p, qword x) { int i = p->c; if (i < 16) { qword *a = p->a; p->c = i + 1; a[i] = x; } }
