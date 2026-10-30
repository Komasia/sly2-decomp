typedef int qword __attribute__((mode(TI)));
struct S { char pad[0x1880]; int n; char p1[0xC]; qword a; qword b; qword c; char p2[0x18]; int x18d8; char p3[0xC8]; void *x19a4; };
qword func_001A62E8(void *p);
void ProjectSoTransform__FP2SOfi(struct S *p);
void func_0018A278(struct S *p)
{
    p->b = func_001A62E8(p->x19a4);
    p->n = 0;
    ProjectSoTransform__FP2SOfi(p);
    if (!p->x18d8) {
        p->a = func_001A62E8(p);
        p->c = func_001A62E8(p->x19a4);
        p->n = 3;
    } else {
        p->n = 0;
    }
}
