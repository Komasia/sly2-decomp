typedef int qword __attribute__((mode(TI)));
struct S { char pad[0x98]; int c; qword *a; };
void func_001733C8(struct S *p, qword x) { register int n __asm__("$3"); register int i __asm__("$6"); i = p->c; if (i < 16) { register qword *a __asm__("$4"); register int off __asm__("$2"); a = p->a; off = i * 16; n = i + 1; p->c = n; *(qword *)(off + (int)a) = x; } }
