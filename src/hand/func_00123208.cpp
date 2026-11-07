typedef int qword __attribute__((mode(TI)));
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(int tagk) { InitTag(tagk); }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
};
struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));
struct MATRIX3 { VECTOR mat[3]; };
struct W { char pad[0xC]; qword *pv; };
extern qword g_normalZ;
extern "C" {
MATRIX3 BuildLookAtMatrix(qword a, qword b) asm("BuildLookAtMatrix__FP6VECTORG9VU_VECTORT1");
CRef RefOpMatrixLookAt(void *pbasic, CRef *aref) asm("RefOpMatrixLookAt__FiP4CRefP6CFrame");
}
static inline qword VecSub(qword *pb, qword *pa)
{
    register qword a __asm__("vf2") = *pa;
    register qword b __asm__("vf1") = *pb;
    __asm__ ("vsub.xyzw %0, %0, %1" : "+j"(b) : "j"(a));
    return b;
}
CRef RefOpMatrixLookAt(void *pbasic, CRef *aref)
{
    qword *pup;
    if (aref[2].m_tagk == 0)
        pup = &g_normalZ;
    else
        pup = ((W *)aref[2].u.pv)->pv;
    union { qword q; } v;
    v.q = VecSub((qword *)aref[1].u.pv, (qword *)aref[0].u.pv);
    CRef ref(0x1B);
    MATRIX3 *pmat = (MATRIX3 *)ref.u.pv;
    *pmat = BuildLookAtMatrix(v.q, *pup);
    pmat->mat[2].w = 0.0f;
    pmat->mat[1].w = 0.0f;
    pmat->mat[0].w = 0.0f;
    return ref;
}
