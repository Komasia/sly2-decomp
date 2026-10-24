// laneI5v4 (Claude agent): aligned 57. laneI4v5 + pad loop via `DMA *pdma` and a `pbPad` cursor, skin offset `int ibMat = imat*0x40 + 0x6F0`, commented empty volatile asm at the start of CopyQws.
// func_00168638 (Claude agent, lane I3): fresh rewrite in the style of Lilly's matched files.
// laneI4v5 (Claude agent): aligned 120 (raw 179), frame 0x290. v4 + posCam, pos, sRadius declaration order.
// Culls a model against the view (microprogram 0x1C0), then builds the VIF packet for every visible submodel
// (optional reference, model matrix, params, bone matrices (0x1684D0), skin matrices) and queues it for rendering.
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char uchar;
typedef int qword __attribute__((mode(TI)));
struct MATRIX4
{
    float mat[4][4];
} __attribute__((aligned(16)));
struct VECTOR4
{
    float x, y, z, w;
} __attribute__((aligned(16)));
struct XF
{
    char pad[0x40];
    MATRIX4 mat;
};
struct VTENT
{
    short delta, pad;
    void (*pfn)(void *);
};
struct OBJ
{
    char pad[0xC];
    VTENT *pvt;
    char pad10[0x28];
    float sRadius;
    char pad3C[0x24];
    XF *pxf;
};
struct BONE;
struct SKIN
{
    char pad[0xC];
    char *pbOwner;
    int cmat;
    int fFirst;
    int fSecond;
    int pad1C;
    uint ib;
};
struct SUBDESC
{
    signed char kind;
    signed char cbone;
    short channel;
    float dist;
    void *pv;
    uint ib;
    uint cw;
};
struct SUB
{
    int n;
    XF *pxf;
    MATRIX4 *pmatParent;
    uint grf;
    char *pb;
    uint w;
    BONE *abone;
    SKIN *pskin;
    int pad20;
    qword *ppos;
};
struct SPH
{
    float pos[3];
    float rad;
    float sRange;
    int pad;
};
struct MODEL
{
    OBJ *powner;
    float t;
    char pad8[8];
    VECTOR4 posCenter;
    float rad;
    int cobj;
    OBJ **apobj;
    char pad2C[8];
    uint grfMode;
    int csub;
    SUBDESC *asubdesc;
    SUB *asub;
    SPH *asph;
    int pad48;
    int nStamp;
    union
    {
        ulong grf;
        float scale;
    };
};
struct SHD
{
    uint aw[9];
    MATRIX4 *pmatClip;
    uint ibRef;
    uint cqwRef;
};
struct VIEW
{
    char pad[0x1C];
    float sGain;
    char pad20[0x28];
    float sNear;
    char pad4C[0x44];
    qword posCam;
    qword aqwPlane[3];
};
struct CLOCK
{
    float t, dt;
};
struct G
{
    char pad[0x3BEC];
    int fAlt;
    char pad3BF0[0x16C];
    int nStamp;
};
struct DMA
{
    char pad[0xC];
    uchar *pb;
};
struct RPL
{
    int kind;
    float dist;
    uchar *pb;
    char *pv;
};
extern DMA D_002DEA28;
extern G D_003DD490;
extern VIEW D_002DDF40;
extern CLOCK D_002DDED0;
extern MATRIX4 D_002A2D30;
extern "C" {
void func_001681F8(MODEL *pmodel);
int func_001EDA20(OBJ *pobj);
void func_001AE5A0(void *pvDst, const void *pvSrc, uint cb);
void *func_0023320C(void *pvDst, const void *pvSrc, uint cb);
void func_0011C168(MATRIX4 *pmatDst, const MATRIX4 *pmatA, const MATRIX4 *pmatB);
void func_0011C318(MATRIX4 *pmatDst, const MATRIX4 *pmatSrc);
float func_0011CAB0(const MATRIX4 *pmat);
qword func_00167DA0(const MATRIX4 *pmat, qword qwPos, float *psRadius);
int func_0014F898(VIEW *pview, qword qwDpos, float sRange, float *pgVis);
void func_001684D0(MODEL *pmodel, SUBDESC *pdesc, SUB *psub);
RPL *func_001CD998(void);
}
static inline MATRIX4 MulMat(const MATRIX4 &matA, const MATRIX4 &matB) return mat
{
    func_0011C168(&mat, &matA, &matB);
}
static inline void CopyMat(MATRIX4 &matDst, const MATRIX4 &matSrc)
{
    func_0023320C(&matDst, &matSrc, sizeof(MATRIX4));
}
static inline qword QwSub(qword qw0, qword qw1)
{
    qword qw;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1));
    return qw;
}
static inline qword QwXfm(const MATRIX4 &mat, qword qwPos)
{
    qword qw;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(qw)
            : "j"(*(qword *)mat.mat[0]), "j"(*(qword *)mat.mat[1]), "j"(*(qword *)mat.mat[2]), "j"(*(qword *)mat.mat[3]), "j"(qwPos));
    return qw;
}
static inline qword QwXfmRef(const MATRIX4 &mat, const qword &qwPos)
{
    qword qw;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(qw)
            : "j"(*(qword *)mat.mat[0]), "j"(*(qword *)mat.mat[1]), "j"(*(qword *)mat.mat[2]), "j"(*(qword *)mat.mat[3]), "j"(qwPos));
    return qw;
}
static inline int GBitsSqLength(qword qwV)
{
    qword qwSq, qwOne;
    int g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(qwSq), "=&j"(qwOne) : "j"(qwV));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(qwSq));
    return g;
}
struct VU_FLOAT
{
    qword qw;
    // empty asm: only moves the word into the qword's register (no instruction)
    VU_FLOAT(int n) { __asm__("" : "=r"(qw) : "0"(n)); }
};
// Microprogram 0x1C0 (sphere against the view planes): its inputs and outputs live in fixed VU registers.
static inline float GCullSphere(qword posCam, qword pos, int nRange, int nRadius, qword *pdpos)
{
    qword *aqwPlane = D_002DDF40.aqwPlane;
    register qword qwPlane0 __asm__("vf10") = aqwPlane[0];
    register qword qwPlane1 __asm__("vf11") = aqwPlane[1];
    register qword qwPlane2 __asm__("vf12") = aqwPlane[2];
    register qword qwCam __asm__("vf13") = posCam;
    register qword qwGain __asm__("vf14") = VU_FLOAT(*(int *)&D_002DDF40.sGain).qw;
    register qword qwPos __asm__("vf15") = pos;
    register qword qwRadius __asm__("vf16") = VU_FLOAT(nRadius).qw;
    register qword qwRange __asm__("vf17") = VU_FLOAT(nRange).qw;
    register qword qwDpos __asm__("vf18");
    register qword qwVis __asm__("vf19");
    __asm__ __volatile__("vcallms 0x1C0\n\tcfc2.i $zero, $vi0"
                         : "=j"(qwDpos), "=j"(qwVis)
                         : "j"(qwPlane0), "j"(qwPlane1), "j"(qwPlane2), "j"(qwCam), "j"(qwGain), "j"(qwPos), "j"(qwRadius), "j"(qwRange)
                         : "vf20", "vf21", "vf22", "vf23", "vf24", "vf25");
    *pdpos = qwDpos;
    float g;
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(qwVis));
    return g;
}
static inline void CopyQws(uint *pwDst, const uint *pwSrc, int cw)
{
    // empty volatile asm: scheduling barrier (the target never moves later setup above the copy loop's entry)
    __asm__ __volatile__("");
    int c = cw - 4;
    do
    {
        uint w0 = pwSrc[0];
        uint w1 = pwSrc[1];
        uint w2 = pwSrc[2];
        uint w3 = pwSrc[3];
        pwSrc += 4;
        pwDst[0] = w0;
        pwDst[1] = w1;
        pwDst[2] = w2;
        pwDst[3] = w3;
        pwDst += 4;
        c -= 4;
    } while (c >= 0);
}
static inline void UnpackQws(uint tag, const void *pv, int cw)
{
    DMA *pdma = &D_002DEA28;
    *(uint *)pdma->pb = tag;
    pdma->pb += 4;
    CopyQws((uint *)pdma->pb, (const uint *)pv, cw);
    pdma->pb += cw * 4;
}
static inline void UnpackWords(uint tag, const void *pv, int cw)
{
    DMA *pdma = &D_002DEA28;
    *(uint *)pdma->pb = tag;
    pdma->pb += 4;
    uint *pwDst = (uint *)pdma->pb;
    const uint *pwSrc = (const uint *)pv;
    int c = cw - 1;
    do
    {
        *pwDst++ = *pwSrc++;
        c--;
    } while (c >= 0);
    pdma->pb += cw * 4;
}
static inline int KindOf(SUB *psub)
{
    return (ulong)(uchar)psub->grf >> 3;
}
extern "C" void func_00168638(MODEL *pmodel, MATRIX4 *pmatWorld, SHD *pshd, float gFirst, float gSecond)
{
    SUBDESC *pdesc;
    qword posCam = D_002DDF40.posCam;
    qword pos = QwXfmRef(pmodel->powner->pxf->mat, *(qword *)&pmodel->posCenter);
    float sRadius = pmodel->rad;
    if (pmatWorld)
    {
        pos = QwXfm(*pmatWorld, pos);
        sRadius *= func_0011CAB0(pmatWorld);
    }
    if ((pmodel->grf & 0x200000000UL) && pshd->pmatClip)
        pos = func_00167DA0(pshd->pmatClip, pos, &sRadius);
    qword dpos;
    float gVis = GCullSphere(posCam, pos, *(int *)&pmodel->powner->sRadius, *(int *)&sRadius, &dpos);
    if (gVis == 0.0f)
        return;
    pmodel->t = D_002DDED0.t;
    if (pmodel->nStamp != D_003DD490.nStamp)
        func_001681F8(pmodel);
    int i;
    for (i = 0; i < pmodel->cobj; i++)
    {
        OBJ *pobj = pmodel->apobj[i];
        if (func_001EDA20(pobj))
        {
            VTENT *pvte = &pobj->pvt[8];
            pvte->pfn((char *)pobj + pvte->delta);
        }
    }
    int fAlt = 0;
    if (pmodel->grf & 0x400000000UL)
        fAlt = D_003DD490.fAlt == 0;
    for (i = 0; i < pmodel->csub; i++)
    {
        pdesc = &pmodel->asubdesc[i];
        SUB *psub = &pmodel->asub[i];
        SPH *psph = &pmodel->asph[i];
        VECTOR4 posSph;
        MATRIX4 matModel;
        if (psub->grf & 0x800)
            continue;
        if (psub->grf & 0x1000)
        {
            func_001AE5A0(&matModel, psub->pb + 0x14, sizeof(MATRIX4));
            if (pmatWorld)
                matModel = MulMat(*pmatWorld, matModel);
        }
        else
        {
            MATRIX4 *pmatParent = psub->pmatParent;
            MATRIX4 mat;
            CopyMat(mat, psub->pxf->mat);
            if (pmatParent)
                CopyMat(mat, MulMat(mat, *pmatParent));
            if (pmatWorld)
                CopyMat(mat, MulMat(*pmatWorld, mat));
            matModel = mat;
        }
        func_001AE5A0(&posSph, psph, 12);
        qword posSub = QwXfm(matModel, *(qword *)&posSph);
        float sRadiusSub = func_0011CAB0(&matModel) * psph->rad;
        if ((psub->grf & 7) == 2 && pshd->pmatClip)
            posSub = func_00167DA0(pshd->pmatClip, posSub, &sRadiusSub);
        float gVisSub;
        qword dposSub;
        if (!psub->abone)
        {
            qword dposCull;
            gVisSub = GCullSphere(posCam, posSub, *(int *)&psph->sRange, *(int *)&sRadiusSub, &dposCull);
            if (gVisSub == 0.0f)
                continue;
            dposSub = dposCull;
        }
        else
        {
            dposSub = QwSub(posSub, posCam);
            if (!func_0014F898(&D_002DDF40, dposSub, psph->sRange, &gVisSub))
                continue;
        }
        uchar *pbStart = D_002DEA28.pb;
        if (psub->grf & 0x100)
        {
            *(ulong *)pbStart = (ulong)(int)(pshd->aw[5] | 0x40000000) | ((ulong)(int)pshd->aw[6] << 32);
            D_002DEA28.pb += 0x10;
        }
        ulong *ptag;
        switch (psub->grf & 7)
        {
        case 2:
            if (!pshd->cqwRef)
                continue;
            *(ulong *)D_002DEA28.pb = (ulong)(int)(pshd->ibRef | 0x40000000) | ((ulong)pshd->cqwRef << 32);
            D_002DEA28.pb += 0x10;
            ptag = (ulong *)D_002DEA28.pb;
            *ptag = 0x10000000;
            D_002DEA28.pb += 0x10;
            break;
        case 3:
        {
            ptag = (ulong *)D_002DEA28.pb;
            *ptag = 0x10000000;
            int g = GBitsSqLength(QwSub(posCam, posSub));
            float sNear = sRadiusSub + D_002DDF40.sNear;
            D_002DEA28.pb += 0x10;
            int fNear = *(float *)&g < sNear * sNear;
            UnpackWords(0x6001C012, &fNear, 1);
            break;
        }
        default:
            ptag = (ulong *)D_002DEA28.pb;
            *ptag = 0x10000000;
            D_002DEA28.pb += 0x10;
            break;
        }
        if (psub->abone)
        {
            MATRIX4 *pmat = pmatWorld;
            if (!pmat)
                pmat = &D_002A2D30;
            UnpackQws(0x6C04C000, pmat, 16);
        }
        else
        {
            UnpackQws(0x6C04C000, &matModel, 16);
        }
        VECTOR4 vecParams;
        if (gVis < gVisSub)
        {
            vecParams.x = gFirst * gVis;
            vecParams.y = gSecond * gVis;
        }
        else
        {
            vecParams.x = gFirst * gVisSub;
            vecParams.y = gSecond * gVisSub;
        }
        vecParams.z = pmodel->scale;
        *(uint *)&vecParams.w = (psub->grf & 0x200) ? pmodel->grfMode : 0;
        UnpackQws(0x6C01C008, &vecParams, 4);
        if (psub->abone)
            func_001684D0(pmodel, pdesc, psub);
        SKIN *pskin = psub->pskin;
        if (pskin)
        {
            MATRIX4 matInv;
            func_0011C318(&matInv, &matModel);
            uint ib = pskin->ib;
            for (int imat = 0; imat < pskin->cmat; imat++)
            {
                if (pskin->fFirst)
                {
                    MATRIX4 mat;
                    int ibMat = imat * 0x40 + 0x6F0;
                    mat = MulMat(matInv, *(MATRIX4 *)(pskin->pbOwner + ibMat));
                    UnpackQws(ib | 0x6C04C000, &mat, 16);
                    ib += 4;
                }
                if (pskin->fSecond)
                {
                    UnpackQws(ib | 0x6C04C000, pskin->pbOwner + 0x7F0 + imat * 0x40, 16);
                    ib += 4;
                }
            }
        }
        {
            DMA *pdma = &D_002DEA28;
            for (uchar *pbPad = pdma->pb; (uint)pbPad & 0xF; pbPad = pdma->pb)
            {
                *(uint *)pbPad = 0;
                pdma->pb += 4;
            }
        }
        *(uint *)ptag |= ((int)(D_002DEA28.pb - (uchar *)ptag) >> 4) - 1;
        *(ulong *)D_002DEA28.pb = 0x60000000;
        D_002DEA28.pb += 0x10;
        RPL *prpl = func_001CD998();
        switch (KindOf(psub))
        {
        case 3:
        case 4:
            if (fAlt)
                prpl->kind = (vecParams.x == 1.0f) ? 22 : 23;
            else if (vecParams.x == 1.0f)
                prpl->kind = KindOf(psub);
            else
                prpl->kind = ((psub->grf & 0xF8) == 0x18) ? 5 : 6;
            break;
        case 5:
        case 6:
            prpl->kind = fAlt ? 23 : KindOf(psub);
            break;
        case 9:
            prpl->kind = fAlt ? 24 : KindOf(psub);
            break;
        case 10:
            prpl->kind = fAlt ? 25 : KindOf(psub);
            break;
        default:
            prpl->kind = KindOf(psub);
            break;
        }
        if (psub->grf & 0x400)
            prpl->dist = pdesc->dist;
        else
            *(int *)&prpl->dist = GBitsSqLength(dposSub);
        prpl->pb = pbStart;
        prpl->pv = psub->pb;
    }
}
