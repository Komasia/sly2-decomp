// (Claude agent, laneB10) memsets through an inline ClearM4 helper keep &m2/&mB out of gcse; pe at function scope.
typedef int qword __attribute__((mode(TI)));
struct AREQ { int cb; int cbAlign; AREQ(int c, int a) { cb = c; cbAlign = a; } };
class FRAME { public: FRAME(); ~FRAME(); int a[4]; };
struct M4 { qword a[4]; };
struct Y { M4 m; char pad[0x94 - 0x40]; int x94; int pad98[2]; Y *pyNext; };
struct OBJ { virtual void f1(); virtual void f2(); virtual void Eval(float f, float g, qword *pq1, qword *pq2); };
struct ENT { unsigned n : 20; unsigned k : 10; unsigned f30 : 1; unsigned f31 : 1; OBJ *pobj; };
struct X { char pad[0x5C]; int c; ENT *aent; };
extern "C" {
void *PvAllocStackImpl(const AREQ &req) asm("PvAllocStackImpl__Fi");
void *func_002333B4(void *pv, int b, int cb);
void GetAsegChannelTarget(X *px, void *p, ENT *pent, int *pa, Y **ppy) asm("GetAsegChannelTarget__FP4ASEGP3ALOP7ASEGCHNPP3ALOPP2XF");
M4 func_0011C168(M4 *pa, M4 *pb);
M4 MatXfWithValue(Y *py, qword q) asm("MatXfWithValue__FP2XFP7VECTOR4G9VU_VECTOR");
M4 func_0022CB90(Y *py, M4 *pm, qword q1, qword q2);
M4 DmatOfValue(Y *py, qword q) asm("DmatOfValue__FP2XFP7VECTOR4G9VU_VECTOR");
void CalculateAsegMatrices(X *px, void *p, Y *pyFirst, Y *pyLast, float f, float g, M4 *pm1, M4 *pm2) asm("CalculateAsegMatrices__FP4ASEGP3ALOP2XFT2ffP7MATRIX4T6");
}
static inline void ClearM4(M4 *pm) { func_002333B4(pm, 0, sizeof(M4)); }
static inline M4 AddM4(const M4 &a, const M4 &b) return m
{
    int i;
    for (i = 0; i < 4; i++) {
        qword q;
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(q) : "j"(a.a[i]), "j"(b.a[i]));
        m.a[i] = q;
    }
}
// name: SafeHouse port (CalculateAsegMatrices)
void CalculateAsegMatrices(X *px, void *p, Y *pyFirst, Y *pyLast, float f, float g, M4 *pm1, M4 *pm2)
{
    M4 mA;
    M4 mB;
    M4 m1;
    M4 m2;
    FRAME frame;
    qword aq[2];
    Y **apy;
    int i;
    Y *py;
    ENT *pe;
    ClearM4(&m2);
    {
        float *pg = (float *)&m1;
        func_002333B4(pg, 0, sizeof(M4));
        pg[15] = 1.0f; pg[10] = 1.0f; pg[5] = 1.0f; pg[0] = 1.0f;
    }
    apy = (Y **)PvAllocStackImpl(AREQ(px->c * 4, 0x10));
    for (i = 0; i < px->c; i++) {
        pe = &px->aent[i];
        if (pe->f30) {
            apy[i] = 0;
        } else {
            int n;
            GetAsegChannelTarget(px, p, pe, &n, &apy[i]);
        }
    }
    for (py = pyFirst; py != pyLast; py = py->pyNext) {
        for (i = 0; i < px->c; i++) {
            pe = &px->aent[i];
            if (py == apy[i] && !pe->f31) {
                pe->pobj->Eval(f, g, &aq[0], &aq[1]);
                mA = MatXfWithValue(py, aq[0]);
                switch (py->x94) {
                case 6: case 7:
                    mB = func_0022CB90(py, &mA, aq[0], aq[1]);
                    break;
                default:
                    mB = DmatOfValue(py, aq[1]);
                    break;
                }
                goto found;
            }
        }
        mA = py->m;
        ClearM4(&mB);
    found:
        {
            m2 = AddM4(func_0011C168(&mA, &m2), func_0011C168(&mB, &m1));
            m1 = func_0011C168(&mA, &m1);
        }
    }
    if (pm1) *pm1 = m1;
    if (pm2) *pm2 = m2;
}
