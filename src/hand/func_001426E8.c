typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
struct SO { char pad[0x40]; M3 mat; };
struct X60 { char pad[0x40]; M3 mat; };
struct P { char pad[0x60]; struct X60 *p60; char pad2[0x10F4 - 0x64]; void *p10F4; char pad3[0x1150 - 0x10F8]; M3 mat; };
struct SO *func_001F4C58(struct P *p, int x, int n);
M3 func_0011B340(M3 *pm);
qword DecomposeEulerMatrix__FP7MATRIX3(M3 *pm);
void *PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(struct P *p, struct SO *pso, int a, int b, int c, qword q);
void EnsureCtrlRemoved__FP4CTRL(void *pv);
static __inline__ qword MulV(M3 *pm, qword v)
{
    qword o;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(o) : "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]), "j"(v));
    return o;
}
static __inline__ M3 MulM3(M3 *pa, M3 *pb)
{
    M3 m;
    m.r[0] = MulV(pa, pb->r[0]);
    m.r[1] = MulV(pa, pb->r[1]);
    m.r[2] = MulV(pa, pb->r[2]);
    return m;
}
// name: SafeHouse port (AttachActorLook)
void AttachActorLook__FP5ACTORi(struct P *p, int x)
{
    struct SO *pso = func_001F4C58(p, x, 6);
    M3 m, a;
    if (pso) {
        a = func_0011B340(&p->p60->mat);
        {
            M3 t;
            M3 *pb = &pso->mat;
            t.r[0] = m.r[0] = MulV(&a, pb->r[0]);
            t.r[1] = m.r[1] = MulV(&a, pb->r[1]);
            m.r[2] = t.r[2] = MulV(&a, pb->r[2]);
            p->mat = t;
        }
        p->p10F4 = PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(p, pso, 3, 7, 2, DecomposeEulerMatrix__FP7MATRIX3(&p->mat));
        EnsureCtrlRemoved__FP4CTRL(p->p10F4);
    }
}
