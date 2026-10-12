typedef int qword __attribute__((mode(TI)));
struct S { char pad[0x10]; void *p10; char pad2[0x1C]; void *p30; };
qword func_001A62E8(void *p);
void func_001710F8(void *p, qword q, int a, int b, int c);
void func_00171AF8(struct S *p, int a, int b, int c) { func_001710F8(p->p30, func_001A62E8(p->p10), a, b, c); }
