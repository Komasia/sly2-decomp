struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(int tagk) { InitTag(tagk); }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(float g);
};
extern "C" {
CRef RefCoerceF32(CRef *pref) asm("RefCoerceF32__4CRef");
void func_0011D8D8(void *pv, float a, float b, float c, float d);
CRef RefOpClqFit(void *pbasic, CRef *aref) asm("RefOpClqFit__FiP4CRefP6CFrame");
}
CRef RefOpClqFit(void *pbasic, CRef *aref)
{
    CRef ref(0x1C);
    {
        CRef r0 = RefCoerceF32(&aref[0]);
        float g0 = r0.u.g;
        CRef r1 = RefCoerceF32(&aref[1]);
        float g1 = r1.u.g;
        CRef r2 = RefCoerceF32(&aref[2]);
        float g2 = r2.u.g;
        CRef r3 = RefCoerceF32(&aref[3]);
        func_0011D8D8(ref.u.pv, g0, g1, g2, r3.u.g);
    }
    return ref;
}
