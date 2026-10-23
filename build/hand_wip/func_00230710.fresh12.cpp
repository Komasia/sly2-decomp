// (Claude agent) fresh1 rewrite
typedef int qword __attribute__((mode(TI)));
typedef union { qword r[4]; float m[4][4]; } M4;
struct M3 { qword r[3]; };
struct VT { short d; short pad; void (*pfn)(); };
struct OB { char pad[0x18]; VT *vt; };
struct O {
    M4 local; char pad40[0x90 - 0x40]; OB *pob; int k94; short k98; short k9A; char pad9C[0xB0 - 0x9C]; qword qB0;
};
extern "C" {
int func_00230310(int);
M4 *func_0022C8C0(M4 *pm, O *po, qword v);
M4 *func_0022CB90(M4 *pr, O *pa, const M4 *basis, qword c, qword d);
M4 *func_0022CC00(M4 *pm, O *po, qword v);
M4 *func_0022CCD0(M4 *pm, O *pa, const M4 *basis, qword v);
M3 *func_0011B570(M3 *, qword);
qword func_0022CA18(O *pa, const M4 *matrix);
qword *func_00256D18(qword *, qword);
void *func_002333B4(void *, int, int);
void func_00230710(O *po, M4 *pm, M4 *pm2, float g);
}
struct VUF { qword q; VUF(float g) { int i; __asm__("mfc1 %0, %1" : "=r"(i) : "f"(g)); __asm__ __volatile__("qmtc2.ni %1, %0" : "=j"(q) : "r"(i)); } };
static inline M3 BuildRotation(qword v) return m { func_0011B570(&m, v); }
static inline M3 MulM3(const M3 &a, const M3 &b) return m
{
    M3 t;
    qword r0, r1, r2;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r0) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[0]));
    t.r[0] = r0; m.r[0] = r0;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r1) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[1]));
    t.r[1] = r1; m.r[1] = r1;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r2) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[2]));
    t.r[2] = r2; m.r[2] = r2;
}
static inline void SetM4(M4 *pm, const M3 &mat, qword pos)
{
    func_00256D18(&pm->r[3], pos);
    *(M3 *)pm = mat;
    pm->m[3][3] = 1.0f;
    pm->m[2][3] = 0.0f;
    pm->m[1][3] = 0.0f;
    pm->m[0][3] = 0.0f;
}
static inline M4 C8c0(O *po, const qword &v) return r { func_0022C8C0(&r, po, v); }
static inline M4 Cc00(O *po, const qword &v) return r { func_0022CC00(&r, po, v); }
static inline M4 Ccd0(O *po, const M4 *pm, qword v) return r { func_0022CCD0(&r, po, pm, v); }
static inline qword Scale(qword v, const VUF &f)
{
    qword r;
    __asm__ __volatile__("vmulx.xyzw %0, %2, %1x" : "=&j"(r) : "j"(f.q), "j"(v));
    return r;
}
static inline qword AddScale(qword a, qword v, const VUF &f)
{
    qword r;
    __asm__ __volatile__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(v), "j"(f.q));
    return r;
}
void func_00230710(O *po, M4 *pm, M4 *pm2, float g)
{
    if (po->pob) {
        qword q[2];
        M4 t;
        OB *pob = po->pob;
        ((void (*)(void *, qword *, qword *))pob->vt[5].pfn)((char *)pob + pob->vt[5].d, &q[0], &q[1]);
        func_0022C8C0(&t, po, q[0]);
        *pm = t;
        switch (po->k94) {
        case 6: case 7:
            func_0022CB90(&t, po, pm, q[0], q[1]);
            *pm2 = t;
            break;
        default:
            func_0022CC00(&t, po, q[1]);
            *pm2 = t;
            break;
        }
    } else if (func_00230310(po->k98)) {
        switch (po->k94) {
        case 6: case 7: {
            M3 mat;
            mat = MulM3(BuildRotation(Scale(po->qB0, VUF(g))), *(M3 *)&po->local);
            SetM4(pm, mat, po->local.r[3]);
            *pm2 = Ccd0(po, pm, po->qB0);
            break;
        }
        default: {
            qword v[1];
            v[0] = AddScale(func_0022CA18(po, &po->local), po->qB0, VUF(g));
            *pm = C8c0(po, v[0]);
            *pm2 = Cc00(po, po->qB0);
            break;
        }
        }
    } else {
        *pm = po->local;
        func_002333B4(pm2, 0, 0x40);
    }
}
