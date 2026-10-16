// wip (Claude agent): script matrix-slerp builtin. Code shape right; stack layout differs (target: m 0x50, matRot 0x80, inline m 0xB0, rad 0xE0; frame 0x140) and target keeps ret in s3 / &ref in s2.
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
typedef union { qword q; float g; } UF;
struct MATRIX4 { float m[4][4]; };
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(int tagk) { InitTag(tagk); }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
};
extern "C" {
M3 func_0011BC00(M3 *pa, M3 *pb);
void func_0011BCF8(M3 *pmat, float *prad, qword *pvec);
M3 func_0011B500(float rad, qword axis);
void *func_002333B4(void *pv, int n, int cb);
}
static inline M3 MulM3(M3 *pa, M3 *pb)
{
    M3 m;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(m.r[0]) : "j"(pa->r[0]), "j"(pa->r[1]), "j"(pa->r[2]), "j"(pb->r[0]));
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(m.r[1]) : "j"(pa->r[0]), "j"(pa->r[1]), "j"(pa->r[2]), "j"(pb->r[1]));
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(m.r[2]) : "j"(pa->r[0]), "j"(pa->r[1]), "j"(pa->r[2]), "j"(pb->r[2]));
    return m;
}
extern "C" CRef func_00122F00(void *pv, CRef *aref);
CRef func_00122F00(void *pv, CRef *aref)
{
    M3 mat = func_0011BC00((M3 *)aref[0].u.pv, (M3 *)aref[1].u.pv);
    UF normal;
    float rad;
    func_0011BCF8(&mat, &rad, &normal.q);
    CRef ref(0x1B);
    MATRIX4 *pm = (MATRIX4 *)ref.u.pv;
    func_002333B4(pm, 0, 0x40);
    pm->m[0][0] = pm->m[1][1] = pm->m[2][2] = pm->m[3][3] = 1.0f;
    M3 matRot = func_0011B500(rad * aref[2].u.g, normal.q);
    M3 m = MulM3(&matRot, (M3 *)aref[0].u.pv);
    *(M3 *)ref.u.pv = m;
    return ref;
}
