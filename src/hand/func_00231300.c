// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0 -ffast-math -mvu0-use-vf0-vf31
typedef struct { float x, y, z, w; } V4;
typedef struct { V4 r[3]; } M3 __attribute__((aligned(16)));
typedef struct { char pad[0x50]; int x50; char pad2[0xC]; M3 m; } S;
M3 MatConvertXfs__FP2XFT0P7MATRIX3Pv(int, int, int); void TouchLox__FP3LOX(S *);
static inline void SetM(M3 *pm, M3 m)
{
    *pm = m;
    pm->r[0].w = 0;
    pm->r[1].w = 0;
    pm->r[2].w = 0;
}
// name: SafeHouse port (SetLoxRotation)
void SetLoxRotation(S *p, int x)
{
    SetM(&p->m, MatConvertXfs__FP2XFT0P7MATRIX3Pv(0, p->x50, x));
    TouchLox__FP3LOX(p);
}
