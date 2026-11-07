typedef int qword __attribute__((mode(TI)));
struct M3 { qword a[3]; };
struct O { char pad[0xA0]; int nA0; };
struct P { char pad[0x24]; struct O *po; };
void MatConvertXfs__FP2XFT0P7MATRIX3Pv(struct M3 *, int, int);
qword DecomposeEulerMatrix__FP7MATRIX3(struct M3 *);
void SetXfhPos__FP7XFBASICiiG9VU_VECTOR(struct P *, int, int, qword);
void func_001F8AD8(struct P *p, int a, int b)
{
    struct M3 c, t;
    MatConvertXfs__FP2XFT0P7MATRIX3Pv(&t, 0, p->po->nA0);
    c = t;
    SetXfhPos__FP7XFBASICiiG9VU_VECTOR(p, a, b, DecomposeEulerMatrix__FP7MATRIX3(&c));
}
