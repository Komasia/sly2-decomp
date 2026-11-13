typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct O19C0 { char pad[0xA0]; int xA0; };
struct O19CC { char pad[0x70]; qword x70; };
struct P {
    char pad[0x18C4]; void *x18C4;
    char pad1[0x1960 - 0x18C8]; qword x1960;
    char pad2[0x19C0 - 0x1970]; O19C0 *x19C0;
    char pad3[0x19CC - 0x19C4]; O19CC *x19CC;
    char pad4[0x1A00 - 0x19D0]; void *x1A00;
};
extern "C" {
qword PosOfLo(void *p) asm("PosOfLo__FP2LO");
qword VecConvertXfs(int a, int b, qword v) asm("VecConvertXfs__FP2XFT0G9VU_VECTOR");
void SetCtrlPos(void *p, qword q) asm("SetCtrlPos__FP7CTRLPOSG9VU_VECTOR");
qword PosSmooth(qword a, qword b, float g, float *p, int n) asm("PosSmooth");
void UpdateSlyHangPlace(P *p) asm("UpdateSlyHangPlace__FP3SLY");
}
M3 BuildRotateVectorsMatrix(qword a, qword b) asm("BuildRotateVectorsMatrix__FP7MATRIX3G9VU_VECTORT1");
M3 BuildRotateMatrixAxis(qword a, float g) asm("BuildRotateMatrixAxis__FP7MATRIX3fG9VU_VECTOR");
qword DecomposeEulerMatrix(M3 *pm) asm("DecomposeEulerMatrix__FP7MATRIX3");
extern qword D_002A2DA0;
extern qword D_002A2DD0;
extern float D_002BF594;
extern float D_002BF598[];
extern float D_002DDED4;
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline M3 Mul(const M3 &a, const M3 &b) return r
{
    __asm__("vmulax.xyz ACC, %1, %4x\n\tvmadday.xyz ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
        : "=j"(r.r[0]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[0]));
    __asm__("vmulax.xyz ACC, %1, %4x\n\tvmadday.xyz ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
        : "=j"(r.r[1]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[1]));
    __asm__("vmulax.xyz ACC, %1, %4x\n\tvmadday.xyz ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
        : "=j"(r.r[2]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[2]));
}
// name: SafeHouse port (UpdateSlyHangPlace)
void UpdateSlyHangPlace(P *p)
{
    M3 m;
    qword d = Sub(PosOfLo(p->x18C4), p->x19CC->x70);
    qword q = VecConvertXfs(0, p->x19C0->xA0, d);
    m = Mul(BuildRotateVectorsMatrix(D_002A2DA0, q), BuildRotateMatrixAxis(D_002A2DA0, D_002BF594));
    SetCtrlPos(p->x1A00, DecomposeEulerMatrix(&m));
    p->x1960 = PosSmooth(p->x1960, D_002A2DD0, D_002DDED4, D_002BF598, 0);
}
