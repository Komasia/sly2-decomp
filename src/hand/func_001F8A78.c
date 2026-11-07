typedef int qword __attribute__((mode(TI)));
struct B { char pad[0xA0]; int n; };
struct A { char pad[0x24]; struct B *pb; };
qword PosConvertXfs__FP2XFT0G9VU_VECTOR(int a, int n, qword q);
void SetXfhPos__FP7XFBASICiiG9VU_VECTOR(struct A *p, int a, int b, qword q);
void func_001F8A78(struct A *p, int a, int b, qword q)
{
    SetXfhPos__FP7XFBASICiiG9VU_VECTOR(p, a, b, PosConvertXfs__FP2XFT0G9VU_VECTOR(0, p->pb->n, q));
}
