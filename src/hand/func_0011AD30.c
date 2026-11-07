typedef struct MSG { int cb; int nKind; } MSG;
typedef struct DL { void *pvFirst; void *pvLast; int ibDle; } DL;
typedef struct DLE { void *pvNext; void *pvPrev; } DLE;
typedef struct FRAME { int an[4]; } FRAME;

typedef struct DZ {
    int nKind;
    int n4;
    float g8;
    float gC;
    float g10;
    int n14;
    float *ag;
    int n1C;
    DLE dle;
} DZ;

typedef struct DZG {
    int cdzsMax;
    int cdzs;
    DZ *adzs;
    DL dlA;
    DL dlB;
    DL dlC;
    DL dlD;
    int n3C;
    void *pv40;
    void *pv44;
    void *pv48;
    void *pv4C;
} DZG;

void __10STACKSCOPE(FRAME *pframe);
void _$_10STACKSCOPE(FRAME *pframe, int n);
void *PvAllocStackImpl__Fi(MSG *pmsg);
void func_001AE5A0(void *pvDst, void *pvSrc, unsigned int cb);
DZG *InitDzgRows__FP3DZGi(DZG *pdzg, int cdzsMax);
void AppendDlEntry__FP2DLPv(DL *pdl, void *pv);
void EnforceDzgConstraints__FP3DZG(DZG *pdzg);

static inline void *PvAllocMsg(MSG *pmsg, int cb, int nKind) { pmsg->cb = cb; pmsg->nKind = nKind; return PvAllocStackImpl__Fi(pmsg); }
// name: SafeHouse port (SolveDzgConstraints)
void SolveDzgConstraints__FiPfN21f(int c, float *agA, float *agB, float *agX, float g)
{
    FRAME frame;
    DZG dzg;
    MSG msg;
    int i;

    __10STACKSCOPE(&frame);
    InitDzgRows__FP3DZGi(&dzg, c);
    for (i = 0; i < c; i++) {
        DZ *pdz = &dzg.adzs[i];
        pdz->g8 = g;
        pdz->ag = (float *)PvAllocMsg(&msg, c * sizeof(float), 0x10);
        func_001AE5A0(pdz->ag, agA + i * c, c * sizeof(float));
        pdz->g10 = agB[i];
        AppendDlEntry__FP2DLPv(&dzg.dlD, pdz);
    }
    dzg.cdzs = c;
    EnforceDzgConstraints__FP3DZG(&dzg);
    for (i = 0; i < c; i++) {
        agX[i] = dzg.adzs[i].gC;
    }
    _$_10STACKSCOPE(&frame, 2);
}
