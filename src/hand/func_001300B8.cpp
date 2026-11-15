/* CalculateAsegMatrices: the transform of pxfFrom relative to pxfTo (up pxfFrom's parent chain) at time t of the
 * animation, and its derivative: each record on the chain takes its channel's value (its matrix by MatXfWithValue,
 * the derivative by its kind), else its own matrix; mat = product, dmat by the product rule. Layout: SafeHouse port
 * (aseg.h ASEGCHN, lo.h XF). */
// (Claude agent, laneB10) memsets through an inline ClearM4 helper keep &dmat/&dmatXf out of gcse; pchn at function scope.
typedef int qword __attribute__((mode(TI)));
struct AREQ { int cb; int cbAlign; AREQ(int c, int a) { cb = c; cbAlign = a; } };
class FRAME { public: FRAME(); ~FRAME(); int a[4]; };
struct M4 { qword a[4]; };
struct XF { M4 m; char pad[0x94 - 0x40]; int kind; int pad98[2]; XF *pxfRef; };
struct TRKP { virtual void f1(); virtual void f2(); virtual void Eval(float t, float svt, qword *ppos, qword *pvel); };   // vt slot 3
struct ASEGCHN { unsigned oid : 20; unsigned isub : 10; unsigned fDisabled : 1; unsigned fScalar : 1; TRKP *ptrk; };
struct ASEG { char pad[0x5C]; int cchn; ASEGCHN *achn; };
extern "C" {
void *PvAllocStackImpl(const AREQ &req) asm("PvAllocStackImpl__Fi");
void *s1_memset(void *pv, int b, int cb) asm("memset");
void GetAsegChannelTarget(ASEG *paseg, void *palo, ASEGCHN *pchn, int *ppalo, XF **ppxf) asm("GetAsegChannelTarget__FP4ASEGP3ALOP7ASEGCHNPP3ALOPP2XF");
M4 MulMatrix4(M4 *pa, M4 *pb) asm("MulMatrix4__FP7MATRIX4T0Pv");
M4 MatXfWithValue(XF *pxf, qword q) asm("MatXfWithValue__FP2XFP7VECTOR4G9VU_VECTOR");
M4 func_0022CB90(XF *pxf, M4 *pm, qword q1, qword q2);
M4 DmatOfValue(XF *pxf, qword q) asm("DmatOfValue__FP2XFP7VECTOR4G9VU_VECTOR");
void CalculateAsegMatrices(ASEG *paseg, void *palo, XF *pxfFrom, XF *pxfTo, float t, float svt, M4 *pmat, M4 *pdmat) asm("CalculateAsegMatrices__FP4ASEGP3ALOP2XFT2ffP7MATRIX4T6");
}
static inline void ClearM4(M4 *pm) { s1_memset(pm, 0, sizeof(M4)); }
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
void CalculateAsegMatrices(ASEG *paseg, void *palo, XF *pxfFrom, XF *pxfTo, float t, float svt, M4 *pmat, M4 *pdmat)
{
    M4 matXf;
    M4 dmatXf;
    M4 mat;
    M4 dmat;
    FRAME frame;
    qword aq[2];
    XF **apxf;
    int i;
    XF *pxf;
    ASEGCHN *pchn;
    ClearM4(&dmat);
    {
        float *pg = (float *)&mat;
        s1_memset(pg, 0, sizeof(M4));
        pg[15] = 1.0f; pg[10] = 1.0f; pg[5] = 1.0f; pg[0] = 1.0f;
    }
    apxf = (XF **)PvAllocStackImpl(AREQ(paseg->cchn * 4, 0x10));
    for (i = 0; i < paseg->cchn; i++) {
        pchn = &paseg->achn[i];
        if (pchn->fDisabled) {
            apxf[i] = 0;
        } else {
            int n;
            GetAsegChannelTarget(paseg, palo, pchn, &n, &apxf[i]);
        }
    }
    for (pxf = pxfFrom; pxf != pxfTo; pxf = pxf->pxfRef) {
        for (i = 0; i < paseg->cchn; i++) {
            pchn = &paseg->achn[i];
            if (pxf == apxf[i] && !pchn->fScalar) {
                pchn->ptrk->Eval(t, svt, &aq[0], &aq[1]);
                matXf = MatXfWithValue(pxf, aq[0]);
                switch (pxf->kind) {
                case 6: case 7:
                    dmatXf = func_0022CB90(pxf, &matXf, aq[0], aq[1]);
                    break;
                default:
                    dmatXf = DmatOfValue(pxf, aq[1]);
                    break;
                }
                goto found;
            }
        }
        matXf = pxf->m;
        ClearM4(&dmatXf);
    found:
        {
            dmat = AddM4(MulMatrix4(&matXf, &dmat), MulMatrix4(&dmatXf, &mat));
            mat = MulMatrix4(&matXf, &mat);
        }
    }
    if (pmat) *pmat = mat;
    if (pdmat) *pdmat = dmat;
}
