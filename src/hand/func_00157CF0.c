typedef struct MATRIX4 { float mat[4][4]; } __attribute__((aligned(16))) MATRIX4;
typedef struct K { int a, b, c; } K;
typedef struct KG { K k; float g; } KG;
typedef struct GS { char pad[0x3E38]; int x3E38; } GS;
typedef struct CM { char pad[0x4C]; float rNear; float rFar; char pad2[0xC]; MATRIX4 m60; char pad3[0xA0]; MATRIX4 m140; } CM;
typedef struct P { char pad[0x20]; int x20; } P;
extern GS g_sw;
extern void *g_pfrmOpen;
extern char D_002DEA50[];
extern char D_002DF940[], D_002DFA80[], D_002DF800[], D_002DF010[];
extern CM g_cm;
extern K D_002C1F00, D_002C1F10;
extern char D_003E12B8[];
extern void AddDmaCall(P *, void *) asm("AddDmaCall__4DMASP2QW");
extern void AddDmaCnt(P *) asm("AddDmaCnt__4DMAS");
extern void AddVifFlush(P *) asm("AddVifFlush__4VIFS");
extern void AddVifDirect(P *, int, void *, int) asm("AddVifDirect__4VIFSiP2QWi");
extern void AddVifBaseOffset(P *, int, int) asm("AddVifBaseOffset__4VIFSii");
extern void AddVifUnpack(P *, int, int, void *, int) asm("AddVifUnpack__4VIFS3UPKiPvi");
extern void MatCmStereoEye__FP2CMiP7MATRIX4iPv(CM *, int, int, MATRIX4 *, MATRIX4 *);
extern void EndDmaCnt(P *) asm("EndDmaCnt__4DMAS");
extern void func_0016E1A8(P *, void *, void *);
void func_00157CF0(P *p, void *a1, void *a2)
{
    KG akg[2];
    MATRIX4 m1, m2;
    if (g_sw.x3E38) {
        if (g_pfrmOpen == D_002DEA50)
            AddDmaCall(p, D_002DF940);
        else
            AddDmaCall(p, D_002DFA80);
    } else {
        AddDmaCall(p, D_002DF800);
    }
    p->x20 = 1;
    AddDmaCnt(p);
    AddVifFlush(p);
    AddVifDirect(p, 0x25, D_002DF010, 0);
    AddVifBaseOffset(p, 0, 0);
    {
        CM *pcm = &g_cm;
        float rNear = pcm->rNear;
        float rFar = pcm->rFar;
        float r = (rNear + rFar) / (rNear - rFar);
        float s = rNear * (1.0f - r);
        akg[0].k = D_002C1F00;
        akg[0].g = 1.0f / s;
        akg[1].k = D_002C1F10;
        akg[1].g = -r / s;
        AddVifUnpack(p, 0xC, 2, akg, 0);
        if (g_sw.x3E38) {
            if (g_pfrmOpen == D_002DEA50)
                MatCmStereoEye__FP2CMiP7MATRIX4iPv(pcm, 1, 0, &m1, &m2);
            else
                MatCmStereoEye__FP2CMiP7MATRIX4iPv(pcm, 2, 0, &m1, &m2);
        } else {
            MATRIX4 *pm1 = &pcm->m140;
            MATRIX4 *pm2 = &pcm->m60;
            m1 = *pm1;
            m2 = *pm2;
        }
    }
    AddVifUnpack(p, 0xC, 4, &m1, 2);
    AddVifUnpack(p, 0xC, 4, &m2, 6);
    AddVifUnpack(p, 0xC, 1, D_003E12B8, 10);
    AddVifBaseOffset(p, 0x32, 0x1E7);
    EndDmaCnt(p);
    func_0016E1A8(p, a1, a2);
}
