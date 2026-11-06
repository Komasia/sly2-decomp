typedef int qword __attribute__((mode(TI)));
struct S { char pad[0x10]; void *p10; char pad2[0x1C]; void *p30; };
qword func_001A62E8(void *p);
void GetCmdAim__FP5GUARDG9VU_VECTORP2LOP6VECTORPf(void *p, qword q, int a, int b, int c);
void func_00171AF8(struct S *p, int a, int b, int c) { GetCmdAim__FP5GUARDG9VU_VECTORP2LOP6VECTORPf(p->p30, func_001A62E8(p->p10), a, b, c); }
