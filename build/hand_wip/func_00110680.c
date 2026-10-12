typedef struct CRef { int an[4]; } __attribute__((aligned(16))) CRef;
typedef struct OTYPES { int aotype[2]; } OTYPES;
typedef struct VEC16 { int an[4]; } __attribute__((aligned(16))) VEC16;

extern OTYPES D_002A40D8;
CRef func_00201360(int c, CRef *aref, int *paotype, ...);
void func_00129EC8(CRef *pref);
void func_0012A0B0(CRef *pref, int n);
void func_001D4C48(void *pv, int n, VEC16 *pvec);
void func_001291A8(CRef *prefDst, CRef *prefSrc);

CRef *func_00110680(CRef *prefRet, void *pv, int carg, CRef *aref)
{
    int aotype[2] = { 0x12, 0x11 };
    VEC16 vec;
    CRef ref;
    int n;

    ref = func_00201360(2, aref, aotype, &n, &vec);
    func_00129EC8(&ref);
    func_0012A0B0(&ref, 0x24);
    func_001D4C48(pv, n, &vec);
    func_001291A8(prefRet, &ref);
    func_00129EC8(&ref);
    return prefRet;
}
