typedef unsigned long ulong;
typedef int qword __attribute__((mode(TI)));
struct VEC3 { float x, y, z; VEC3() {} };
struct CLR { unsigned int n; CLR() {} };
struct GIFS {
    void *max; qword *base,*count,*current; int pad,endPrim; void *vt;
    qword *tag; int registerCount,vertexCount;
};
struct O { char pad[0x3EA0]; ulong tex0; };
extern "C" {
struct SRC { float ag[3]; float aclr[3][4]; };
extern struct SRC D_003E12F4;
extern int D_002C3680[];
extern int g_pdcGif;
void ConvertUserHsvToUserRgb(const float *, VEC3 *) asm("ConvertUserHsvToUserRgb__FP6VECTORT0");
int func_00170548(void *, int);
void __4GIFS(GIFS *);
void AllocStatic(GIFS *, int, void *) asm("AllocStatic__4DMASiP2QW");
void AddDmaCnt(GIFS *) asm("AddDmaCnt__4DMAS");
void BuildImageGifs(int, int, int, int, int, int, GIFS *) asm("BuildImageGifs__FiiiiiiP4GIFS");
void AddDmaRefs(GIFS *, int, void *) asm("AddDmaRefs__4DMASiP2QW");
void AddPrimPack(GIFS *, int, int, ulong) asm("AddPrimPack__4GIFSiiUl");
void PackAD(GIFS *, int, ulong) asm("PackAD__4GIFSll");
void AddPrimEnd(GIFS *) asm("AddPrimEnd__4GIFS");
void AddDmaEnd(GIFS *) asm("AddDmaEnd__4DMAS");
void Detach(GIFS *, int *, qword **) asm("Detach__4DMASPiPP2QW");
void SendDmaSyncGsFinish(int, qword *) asm("SendDmaSyncGsFinish__FP10sceDmaChanP2QW");
void func_001EA9F0(O *p, void *pbs);
}
static inline void ClearClr(CLR *pc)
{
    pc->n = 0;
}
static inline void SetClr(CLR *pc, float g, float gA, unsigned int rgb)
{
    float h = gA * 128.0f;
    pc->n = rgb | ((unsigned int)(int)(g * h) << 24);
}
static inline void StoreColor(CLR *outColor,float *outAlpha,const float *gain,const VEC3 &v){
    unsigned int rgb=(unsigned int)(int)v.x|((unsigned int)(int)v.y<<8)|((unsigned int)(int)v.z<<16);
    float alpha=*gain*0.003921569f;
    *outAlpha=alpha;outColor->n=rgb;
}
void func_001EA9F0(O *p, void *pbs)
{
    if (!pbs && !(p->tex0 & (0x3FFFL << 37)))
        return;
    {
    float ag[3];
    CLR argb[3];
    VEC3 v;
    int i;
    {
        for (i = 0; i < 3; i++) {
            ConvertUserHsvToUserRgb(D_003E12F4.aclr[i], &v);
            StoreColor(&argb[i],&ag[i],&D_003E12F4.ag[i],v);
        }
    }
    CLR aclr[256];
    {
        CLR *pc = aclr;
        int n = 0;
        int k;
        for (k = 0; k < 0x100; k += 0x20) {
            int j;
            for (j = 0; j < 4; j++) {
                int m;
                for (m = 0; m < 8; m++) {
                    int a = (n & 0x7F) - 1;
                    float g0, g;
                    if (!(a > -1))
                        a = 0;
                    g0 = a * 0.007936508f;
                    g = (g0 > 0.0f) ? g0 : 0.0f;
                    switch (n & 0x81) {
                    case 0x81:
                        SetClr(pc++, g, ag[2], argb[2].n);
                        break;
                    case 0x80:
                        SetClr(pc++, g, ag[0], argb[0].n);
                        break;
                    case 1:
                        SetClr(pc++, g, ag[1], argb[1].n);
                        break;
                    case 0:
                        ClearClr(pc++);
                        break;
                    }
                    n++;
                }
                n += D_002C3680[j];
            }
        }
    }
    GIFS dmas;
    qword aqw[0x80];
    qword *x;
    if (pbs)
        p->tex0 = ((ulong)func_00170548(pbs, 4) << 37) | 0x2000000001B00000L;
    __4GIFS(&dmas);
    AllocStatic(&dmas, 0x80, aqw);
    AddDmaCnt(&dmas);
    BuildImageGifs((int)((p->tex0 >> 37) & 0x3FFF), 1, 0, 0x10, 0x10, 0x40, &dmas);
    AddDmaRefs(&dmas, 0x40, aclr);
    AddPrimPack(&dmas, 0, 1, 14);
    PackAD(&dmas, 0x3F, 0);
    PackAD(&dmas, 0x61, 0);
    AddPrimEnd(&dmas);
    AddDmaEnd(&dmas);
    Detach(&dmas, 0, &x);
    SendDmaSyncGsFinish(g_pdcGif, x);
    }
}
