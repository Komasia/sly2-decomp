typedef int qword __attribute__((mode(TI)));
struct S8 { float a, b; };
struct X {
    char pad[0x11C4];
    float f11C4, f11C8;
    struct S8 s11CC;
    float f11D4, f11D8;
    qword q11E0;
    char pad2[0x1280 - 0x11F0];
    qword q1280;
};
void func_00142310(struct X *p, struct S8 *ps, qword q1, qword q2, float a, float b, float c, float d)
{
    p->f11C4 = a;
    p->f11C8 = b;
    p->s11CC = *ps;
    p->f11D4 = c;
    p->f11D8 = d;
    p->q1280 = q1;
    p->q11E0 = q2;
}
