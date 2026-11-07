// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
typedef struct { char pad[0x50]; int x50; char pad2[0xC]; float m[12]; char x90[0xC]; float x9C; } S;
qword PosConvertXfs__FP2XFT0G9VU_VECTOR(int, int, qword); void func_00256D18(void *, qword); void TouchLox__FP3LOX(S *);
// name: SafeHouse port (SetLoxPos)
void SetLoxPos(S *p, qword v)
{
    float *m = p->m;
    qword r = PosConvertXfs__FP2XFT0G9VU_VECTOR(0, p->x50, v);
    func_00256D18((char *)p + 0x90, r);
    m[15] = 1.0f;
    TouchLox__FP3LOX(p);
}
