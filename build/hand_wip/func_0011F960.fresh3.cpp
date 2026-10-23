// fresh3 (Claude agent, lane A10, 2026-10-23): aligned 16 -> 14. Case 0x1A/0x16 uses its own MulVectorR(qword*, const float&) with ONE commented pin (s copy in vf1): fixes that path's VF numbers. Left: target loads the float bits into s1 (pr's reg), pointer regs v0 (ours a0/v1), 0x16/0x1A mfc1 order, &mat addiu, 0x1D beq/beql slot.
// wip (Claude agent): `*` builtin. 20 diffs: 0x16/0x1A pv load scheduled before mfc1; 0x1A/0x16 path (target lw s1 + swapped VF regs, ref.u.pv in v0 not a0); &mat addiu scheduling in 0x1B/0x16; 0x1D beq/beql delay-slot fill.
typedef int qword __attribute__((mode(TI)));
struct VECTOR { float x, y, z, w; };
struct MATRIX4 { float af[16]; } __attribute__((aligned(16)));
struct V8 { float x, y; };
struct VU_FLOAT {
    qword q;
    VU_FLOAT(const float &f) { __asm__("" : "=r"(q) : "0"(*(const int *)&f)); }
    float F() const { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
};
struct VU_FLOAT_M {
    qword q;
    VU_FLOAT_M(float f) { __asm__("mfc1 %0, %1" : "=r"(q) : "f"(f)); }
    float F() const { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
};
struct VU_FLOAT_V {
    qword q;
    VU_FLOAT_V(const float &f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(*(const int *)&f)); }
};
struct VU_FLOAT_X { qword q; VU_FLOAT_X(float f); };
struct VU_VECTOR { qword q; VU_VECTOR(const VECTOR &v); };
qword operator*(VU_FLOAT_X f, VU_VECTOR v);
extern "C" qword *func_00256D18(VECTOR *p, qword v);
MATRIX4 func_0011C168(const MATRIX4 &a, const MATRIX4 &b);
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(int n);
    CRef &operator=(float g);
    CRef &operator=(qword v);
    CRef &operator=(const MATRIX4 &m);
};
struct NODE { int x0, x4; CRef ref; NODE *pnext; };
CRef func_00129BC8(CRef *pref, void *a, void *b);
extern "C" CRef func_0011F960(void *pv, CRef *aref);

static inline qword MulVF(const qword *pv, float g)
{
    VU_FLOAT_V s(g);
    qword r;
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(s.q), "j"(*pv));
    return r;
}
static inline void MulVectorR(qword *pq, const float &g)
{
    VU_FLOAT_V s(g);
    register qword sv __asm__("vf1") = s.q; /* pin */
    qword r;
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(sv), "j"(*pq));
    *pq = r;
}
static inline void MulVector(qword *pq, float g)
{
    VU_FLOAT_V s(g);
    qword a = *pq, r;
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(s.q), "j"(a));
    *pq = r;
}
static inline void MulMatrixM(MATRIX4 *pm, float d)
{
    MATRIX4 mat;
    float g = VU_FLOAT_M(d).F();
    for (int i = 0; i < 16; i++)
        mat.af[i] = g * pm->af[i];
    *pm = mat;
}
static inline void MulMatrix(MATRIX4 *pm, const float &d)
{
    MATRIX4 mat;
    float g = VU_FLOAT(d).F();
    for (int i = 0; i < 16; i++)
        mat.af[i] = g * pm->af[i];
    *pm = mat;
}
static inline qword MulMatVec(const MATRIX4 *pm, const qword *pv)
{
    const qword *aq = (const qword *)pm;
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(aq[0]), "j"(aq[1]), "j"(aq[2]), "j"(aq[3]), "j"(*pv));
    return r;
}

CRef func_0011F960(void *pv, CRef *aref)
{
    CRef ref;
    int fInt = 0;
    switch (aref[0].m_tagk) {
    case 0x15:
        ref = (float)aref[0].u.n;
        fInt = 1;
        break;
    case 0x16:
    case 0x1A:
    case 0x1B:
    case 0x1C:
    case 0x1D:
        ref = func_00129BC8(&aref[0], 0, 0);
        break;
    }
    NODE *pn = 0;
    if (aref[1].m_tagk)
        pn = (NODE *)aref[1].u.pv;
    for (; pn; pn = pn->pnext) {
        CRef *pr = &pn->ref;
        switch (ref.m_tagk) {
        case 0x16:
            switch (pr->m_tagk) {
            case 0x16: {
                float d;
                d = pr->u.g;
                fInt = 0;
                goto LMul;
            case 0x15:
                d = (float)pr->u.n;
            LMul:
                ref.u.g *= d;
                break;
            }
            case 0x1A:
                ref = MulVF((qword *)pr->u.pv, ref.u.g);
                break;
            case 0x1B: {
                MATRIX4 *pm = (MATRIX4 *)pr->u.pv;
                VU_FLOAT_M s(ref.u.g);
                float g = s.F();
                MATRIX4 mat;
                for (int i = 0; i < 16; i++)
                    mat.af[i] = g * pm->af[i];
                ref = mat;
                break;
            }
            case 0x1C: {
                float g = ref.u.g;
                ref.Decref();
                ref.InitTag(0x1C);
                register VECTOR *pvec __asm__("$18") = (VECTOR *)ref.u.pv;
                register VECTOR *pvSrc __asm__("$17") = (VECTOR *)pr->u.pv;
                func_00256D18(pvec, VU_FLOAT_X(g) * VU_VECTOR(*pvSrc));
                break;
            }
            case 0x1D: {
                float g = ref.u.g;
                ref.Decref();
                ref.InitTag(0x1D);
                V8 *ps = (V8 *)pr->u.pv;
                V8 *pd = (V8 *)ref.u.pv;
                pd->x = ps->x * g;
                pd->y = ps->y * g;
                break;
            }
            }
            break;
        case 0x1A:
            switch (pr->m_tagk) {
            case 0x15: MulVector((qword *)ref.u.pv, (float)pr->u.n); break;
            case 0x16: MulVectorR((qword *)ref.u.pv, pr->u.g); break;
            }
            break;
        case 0x1B:
            switch (pr->m_tagk) {
            case 0x15: MulMatrixM((MATRIX4 *)ref.u.pv, (float)pr->u.n); break;
            case 0x16: MulMatrix((MATRIX4 *)ref.u.pv, pr->u.g); break;
            case 0x1A: ref = MulMatVec((MATRIX4 *)ref.u.pv, (qword *)pr->u.pv); break;
            case 0x1B: {
                MATRIX4 *pm = (MATRIX4 *)ref.u.pv;
                *pm = func_0011C168(*pm, *(MATRIX4 *)pr->u.pv);
                break;
            }
            }
            break;
        case 0x1C:
            switch (pr->m_tagk) {
            case 0x15: {
                VECTOR *pvec = (VECTOR *)ref.u.pv;
                func_00256D18(pvec, VU_FLOAT_X((float)pr->u.n) * VU_VECTOR(*pvec));
                break;
            }
            case 0x16: {
                VECTOR *pvec = (VECTOR *)ref.u.pv;
                func_00256D18(pvec, VU_FLOAT_X(pr->u.g) * VU_VECTOR(*pvec));
                break;
            }
            }
            break;
        case 0x1D: {
            float d;
            switch (pr->m_tagk) {
            case 0x15: d = (float)pr->u.n; break;
            case 0x16: d = pr->u.g; break;
            default: continue;
            }
            V8 *p = (V8 *)ref.u.pv;
            p->x *= d;
            p->y *= d;
            break;
        }
        }
    }
    if (fInt && ref.m_tagk == 0x16)
        ref = (int)ref.u.g;
    return ref;
}
