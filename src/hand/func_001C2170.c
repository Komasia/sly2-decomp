typedef int qword __attribute__((mode(TI)));
struct E { qword q; int pad[4]; };
struct S { char pad[0x50]; int c; char pad2[0xC]; struct E a[6]; char pad3[4]; int n124; int n128; int pad4; qword q130; qword q140; };
void PostLoLoad__FP2LO(struct S *p);
qword func_001C1F28(struct E *pe);
int PregionAt__FG9VU_VECTORi(qword q, int n);
void func_001C2170(struct S *p)
{
    PostLoLoad__FP2LO(p);
    p->q130 = func_001C1F28(&p->a[0]);
    p->n124 = PregionAt__FG9VU_VECTORi(p->q130, 0);
    p->q140 = func_001C1F28(/*B*/&p->a[p->c] - 1/*E*/);
    p->n128 = PregionAt__FG9VU_VECTORi(p->q140, 0);
}
