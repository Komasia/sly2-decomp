// func_001D5808 (w5lane4 fresh rewrite): draws a scene tree. Updates the scene's animations, refreshes its packets
// (func_001681F8) when stale, then walks the block tree (a STACK of BLOCKs, four RENDER records each), culls every record
// against the view with VU0 microprogram 0x1C0 and queues the visible ones: child blocks are pushed, deferred objects are
// collected (their virtual 19 runs at the end), packets/meshes get a render-list entry and a VIF packet.
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char uchar;
union U
{
    qword q;
    float f[4];
    uint w[4];
};
struct M4
{
    U r[4];
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
};
struct BLOCK;
enum KIND
{
    KIND_NONE = -1,
    KIND_MESH = 0,
    KIND_BLOCK = 1,
    KIND_PACKET = 3,
    KIND_DEFERRED = 4
};
struct RENDER
{
    U sphere;
    uint word;
    KIND kind : 4;
    long channels : 8;
    long sort : 6;
    ulong hidden : 1;
    ulong index : 13;
    void *pv;
    BLOCK *pblockNext;
};
struct BLOCK
{
    RENDER ar[4];
};
struct STACK
{
    uint c;
    BLOCK *a[256];
};
struct XF
{
    char pad[0x40];
    M4 mat;
};
struct SKIN
{
    char pad[0xC];
    uchar *pbOwner;
    int cmat;
    int fFirst;
    int fSecond;
    int pad1C;
    uint ib;
};
struct MESH
{
    int unknown;
    XF *pxf;
    M4 *pmatParent;
    uint grf;
    void *pv;
    int pad14[2];
    SKIN *pskin;
    int pad20[2];
};
struct DESC
{
    int unknown;
    float dist;
    void *chain;
    int padC[2];
};
struct SCENE
{
    char pad[0x24];
    int cobj;
    OBJ **apobj;
    char pad2C[0x10];
    DESC *adesc;
    MESH *amesh;
    void *pv44;
    BLOCK *pblockRoot;
    int nStamp;
    float scale;
};
struct VIEW
{
    char pad[0x14];
    int grfChannels;
    int pad18;
    float sGain;
    char pad20[0x28];
    float sNear;
    char pad4C[0x44];
    qword posCam;
    qword aqwPlane[3];
};
struct G
{
    char pad[0x3D5C];
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
    void *pv;
};
extern DMA D_002DEA28;
extern G D_003DD490;
extern VIEW D_002DDF40;
extern RPL D_003B3980[0x2000];
extern RPL *D_003D4A50;
extern "C" {
int func_001EDA20(OBJ *pobj);
void func_001681F8(SCENE *pscene);
void func_001D57B8(STACK *pstack, BLOCK *pblock);
BLOCK *func_001D57E0(STACK *pstack);
M4 func_0011C168(const M4 &matA, const M4 &matB);
M4 func_0011C318(const M4 &matSrc);
}
struct VU_FLOAT
{
    qword q;
    // empty asm: only moves the word into the qword's register (no instruction)
    VU_FLOAT(int n) { __asm__("" : "=r"(q) : "0"(n)); }
};
struct VU_VECTOR
{
    qword q;
    VU_VECTOR(const qword &v) { q = v; }
};
static inline qword Dot(VU_VECTOR a, VU_VECTOR b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3
	vaddw.x %1, $vf0, $vf0w
	vadday.x $ACC, %0, %0y
	vmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a.q), "j"(b.q));
    return d;
}
static inline float Scalar(VU_VECTOR v)
{
    float f;
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(v.q));
    return f;
}
static inline float SqLength(VU_VECTOR v)
{
    return Scalar(Dot(v, v));
}
// Microprogram 0x1C0 (sphere against the view): inputs in vf10..vf17, results (offset, visibility) in vf18/vf19.
static inline void StartCull(VIEW *pview, VU_VECTOR posSphere, VU_FLOAT radius, VU_FLOAT word)
{
    register qword qwGain __asm__("vf14") = VU_FLOAT(*(int *)&pview->sGain).q;
    register qword qwRadius __asm__("vf16") = radius.q;
    register qword qwPos __asm__("vf15") = posSphere.q;
    register qword qwWord __asm__("vf17") = word.q;
    qword *aqwPlane = D_002DDF40.aqwPlane;
    register qword qwCam __asm__("vf13") = D_002DDF40.posCam;
    register qword qwPlane0 __asm__("vf10") = aqwPlane[0];
    register qword qwPlane1 __asm__("vf11") = aqwPlane[1];
    register qword qwPlane2 __asm__("vf12") = aqwPlane[2];
    __asm__ __volatile__("vcallms 0x1C0"
                         :
                         : "j"(qwPlane0), "j"(qwPlane1), "j"(qwPlane2), "j"(qwCam), "j"(qwGain), "j"(qwPos), "j"(qwRadius), "j"(qwWord)
                         : "vf18", "vf19", "vf20", "vf21", "vf22", "vf23", "vf24", "vf25");
}
static inline float GVisCull(qword *pdpos)
{
    register qword qwDpos __asm__("vf18");
    register qword qwVis __asm__("vf19");
    // wait for the microprogram; its results are in vf18/vf19
    __asm__("cfc2.i $zero, $vi0" : "=j"(qwDpos), "=j"(qwVis));
    *pdpos = qwDpos;
    return Scalar(qwVis);
}
static inline void CopyQws(uint *pwDst, const uint *pwSrc, int cw)
{
    for (int k = 0; k < cw; k += 4)
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
    }
}
template <uint TAG> static inline void UnpackQws(const void *pv, int cw)
{
    DMA *pdma = &D_002DEA28;
    *(uint *)pdma->pb = TAG;
    pdma->pb += 4;
    CopyQws((uint *)pdma->pb, (const uint *)pv, cw);
    pdma->pb += cw * 4;
}
static inline void UnpackQws(uint tag, const void *pv, int cw)
{
    DMA *pdma = &D_002DEA28;
    *(uint *)pdma->pb = tag;
    pdma->pb += 4;
    CopyQws((uint *)pdma->pb, (const uint *)pv, cw);
    pdma->pb += cw * 4;
}
template <uint TAG> static inline void UnpackWords(const void *pv, int cw)
{
    DMA *pdma = &D_002DEA28;
    *(uint *)pdma->pb = TAG;
    pdma->pb += 4;
    uint *pwDst = (uint *)pdma->pb;
    const uint *pwSrc = (const uint *)pv;
    for (int k = 0; k < cw; k++)
        pwDst[k] = pwSrc[k];
    pdma->pb += cw * 4;
}
static inline void PadQw()
{
    DMA *pdma = &D_002DEA28;
    for (uchar *pbPad = pdma->pb; (uint)pbPad & 0xF; pbPad = pdma->pb)
    {
        *(uint *)pbPad = 0;
        pdma->pb += 4;
    }
}
static inline RPL *PrplAlloc()
{
    RPL *prpl = D_003D4A50;
    if ((uint)(prpl - D_003B3980) >= 0x2000)
        return 0;
    D_003D4A50 = prpl + 1;
    return prpl;
}
extern "C" void func_001D5808(STACK *pstack, SCENE *pscene)
{
    OBJ *apobjDeferred[512];
    int i;
    for (i = 0; i < pscene->cobj; i++)
    {
        OBJ *pobj = pscene->apobj[i];
        if (func_001EDA20(pobj))
        {
            VTENT *pvte = &pobj->pvt[8];
            pvte->pfn((char *)pobj + pvte->delta);
        }
    }
    G *pg = &D_003DD490;
    if (pscene->nStamp != pg->nStamp)
        func_001681F8(pscene);
    int cDeferred = 0;
    func_001D57B8(pstack, pscene->pblockRoot);
    VIEW *pview = &D_002DDF40;
    int grfChannels = pview->grfChannels;
    BLOCK *pblock;
    while ((pblock = func_001D57E0(pstack)) != 0)
    {
        for (uint ir = 0; ir < 4; ir++)
        {
            RENDER *prender = &pblock->ar[ir];
            if (prender->kind == -1)
                continue;
            StartCull(pview, prender->sphere.q, prender->sphere.w[3], prender->word);
            if (!(prender->channels & grfChannels))
                continue;
            qword qwDpos;
            float gVis = GVisCull(&qwDpos);
            if (gVis == 0.0f)
                continue;
            VU_VECTOR dpos = qwDpos;
            switch (prender->kind)
            {
            case 1:
                func_001D57B8(pstack, (BLOCK *)prender->pv);
                break;
            case 4:
                if ((uint)cDeferred < 512)
                    apobjDeferred[cDeferred++] = (OBJ *)prender->pv;
                break;
            case 3:
            {
                if (prender->hidden)
                    break;
                RPL *prpl = D_003D4A50;
                if ((uint)(prpl - D_003B3980) >= 0x2000)
                    break;
                D_003D4A50 = prpl + 1;
                int sort = prender->sort;
                prpl->kind = sort;
                prpl->dist = SqLength(dpos);
                if (gVis < 1.0f)
                {
                    if (sort == 3)
                        prpl->kind = 5;
                    else if (sort == 4)
                        prpl->kind = 6;
                }
                if (1.0f <= gVis)
                {
                    prpl->pb = (uchar *)prender->pv;
                    prpl->pv = 0;
                }
                else
                {
                    DMA *pdma = &D_002DEA28;
                    prpl->pb = pdma->pb;
                    prpl->pv = (uchar *)prender->pv + 0x70;
                    *(ulong *)pdma->pb = ((ulong)(uint)((uchar *)prender->pv + 0x10) << 32) | 0x40000006;
                    pdma->pb += 0x10;
                    U params;
                    params.f[0] = gVis;
                    params.f[1] = 1.0f;
                    params.f[2] = pscene->scale;
                    params.w[3] = 0;
                    *(ulong *)pdma->pb = 0x10000002;
                    pdma->pb += 0x10;
                    UnpackQws<0x6C01C008>(&params, 4);
                    PadQw();
                    *(ulong *)D_002DEA28.pb = 0x60000000;
                    D_002DEA28.pb += 0x10;
                }
                break;
            }
            case 0:
            {
                uint index = prender->index;
                MESH *pmesh = &pscene->amesh[index];
                DESC *pdesc = &pscene->adesc[index];
                if (prender->hidden)
                    break;
                RPL *prpl = D_003D4A50;
                if ((uint)(prpl - D_003B3980) >= 0x2000)
                    break;
                D_003D4A50 = prpl + 1;
                prpl->kind = prender->sort;
                if (gVis < 1.0f)
                {
                    switch (prender->sort)
                    {
                    case 3:
                        prpl->kind = 5;
                        break;
                    case 4:
                        prpl->kind = 6;
                        break;
                    }
                }
                if (pmesh->grf & 0x400)
                    prpl->dist = pdesc->dist;
                else
                    prpl->dist = SqLength(dpos);
                DMA *pdma = &D_002DEA28;
                ulong *ptag = (ulong *)pdma->pb;
                *ptag = 0x10000000;
                pdma->pb += 0x10;
                if (pmesh->pmatParent)
                {
                    M4 mat;
                    mat = func_0011C168(*pmesh->pmatParent, pmesh->pxf->mat);
                    UnpackQws<0x6C04C000>(&mat, 16);
                }
                else
                {
                    UnpackQws<0x6C04C000>(&pmesh->pxf->mat, 16);
                }
                SKIN *pskin = pmesh->pskin;
                if (pskin)
                {
                    M4 matInv;
                    if (pmesh->pmatParent)
                        matInv = func_0011C318(func_0011C168(*pmesh->pmatParent, pmesh->pxf->mat));
                    else
                        matInv = func_0011C318(pmesh->pxf->mat);
                    uint ib = pskin->ib;
                    for (int imat = 0; imat < pskin->cmat; imat++)
                    {
                        if (pskin->fFirst)
                        {
                            M4 mat;
                            mat = func_0011C168(matInv, *(M4 *)(pskin->pbOwner + imat * 0x40 + 0x6F0));
                            UnpackQws(ib | 0x6C04C000, &mat, 16);
                            ib += 4;
                        }
                        if (pskin->fSecond)
                        {
                            UnpackQws(ib | 0x6C04C000, pskin->pbOwner + imat * 0x40 + 0x7F0, 16);
                            ib += 4;
                        }
                    }
                }
                U params;
                params.f[0] = gVis;
                params.f[1] = 1.0f;
                params.f[2] = pscene->scale;
                params.w[3] = 0;
                UnpackQws<0x6C01C008>(&params, 4);
                int sort = prender->sort;
                if (sort == 7 || sort == 8)
                {
                    float sNear = prender->sphere.f[3] + pview->sNear;
                    int fNear = SqLength(dpos) < sNear * sNear;
                    UnpackWords<0x6001C012>(&fNear, 1);
                }
                PadQw();
                *(uint *)ptag |= ((int)(D_002DEA28.pb - (uchar *)ptag) >> 4) - 1;
                *(ulong *)D_002DEA28.pb = 0x60000000;
                D_002DEA28.pb += 0x10;
                prpl->pb = (uchar *)ptag;
                prpl->pv = pmesh->pv;
                break;
            }
            }
        }
        if (pblock->ar[3].pblockNext)
            func_001D57B8(pstack, pblock->ar[3].pblockNext);
    }
    for (i = 0; i < cDeferred; i++)
    {
        OBJ *pobj = apobjDeferred[i];
        VTENT *pvte = &pobj->pvt[19];
        pvte->pfn((char *)pobj + pvte->delta);
    }
}
