typedef struct CRef { int an[4]; } __attribute__((aligned(16))) CRef;
typedef struct VEC16 { int an[4]; } __attribute__((aligned(16))) VEC16;

CRef func_00201360(int c, CRef *aref, int *aotype, ...);
void func_00129EC8(CRef *pref);
void func_0012A0B0(CRef *pref, int n);
void func_001D4B48(void *pv, int n, VEC16 *pvec, float g);
void func_001291A8(CRef *prefDst, CRef *prefSrc);

CRef *func_001104F0(CRef *prefRet, void *pv, int carg, CRef *aref)
{
    VEC16 vec;
    CRef ref;
    int n;
    float g;

    {
        VEC16 *pvec = &vec;
        float *pg = &g;
        int *pn = &n;
        int aotype[3] = { 0x12, 0x11, 0x10 };
        ref = func_00201360(3, aref, aotype, pn, pg, pvec);
    }
    func_00129EC8(&ref);
    func_0012A0B0(&ref, 0x24);
    func_001D4B48(pv, n, &vec, g);
    func_001291A8(prefRet, &ref);
    func_00129EC8(&ref);
    return prefRet;
}
