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
    CRef &operator=(int n);
};
extern "C" {
CRef RefCoerceF32(CRef *pref) asm("RefCoerceF32__4CRef");
int NRandInRange(int a, int b) asm("NRandInRange__Fii");
float GRandInRange(float a, float b) asm("GRandInRange__Fff");
CRef RefOpRandom(void *pbasic, CRef *aref) asm("RefOpRandom__FiP4CRefP6CFrame");
}
CRef RefOpRandom(void *pbasic, CRef *aref)
{
    CRef ref;
    if (aref[0].m_tagk == 0x15 && aref[1].m_tagk == aref[0].m_tagk) {
        ref = NRandInRange(aref[0].u.n, aref[1].u.n);
    } else {
        float g0 = RefCoerceF32(&aref[0]).u.g;
        float g1 = RefCoerceF32(&aref[1]).u.g;
        ref = GRandInRange(g0, g1);
    }
    return ref;
}
