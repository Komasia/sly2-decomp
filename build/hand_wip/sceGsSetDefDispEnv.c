// WIP (Claude agent, ee-gcc2.9): ~170/229 differ; structure right (offsets/prologue), smode2 if-chain gives movn and display OR/add order differ.
// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct {
    short sceGsInterMode;
    short sceGsOutMode;
    short sceGsFFMode;
    short sceGsVersion;
} sceGsGParam;
typedef struct {
    unsigned long pmode;
    unsigned long smode2;
    unsigned long dispfb;
    unsigned long display;
    unsigned long bgcolor;
} sceGsDispEnv;
extern char D_002AB330[];
sceGsGParam *sceGsGetGParam(void);
int func_00240B88(void);
void func_00240C28(int, int *, int *, int *, int *);
int printf(const char *, ...);
void sceGsSetDefDispEnv(sceGsDispEnv *disp, short psm, short w, short h, short dx, short dy)
{
    sceGsGParam *gp = sceGsGetGParam();
    int ox, oy, ow, oh;
    int magh;

    if (gp->sceGsOutMode != 2 && gp->sceGsOutMode != 3 && func_00240B88()) {
        func_00240C28(gp->sceGsOutMode, &ox, &oy, &ow, &oh);
    } else {
        ox = oy = ow = oh = 0;
    }
    disp->pmode = 0x66;
    if (gp->sceGsInterMode == 0)
        disp->smode2 = 2;
    else if (gp->sceGsFFMode)
        disp->smode2 = 3;
    else
        disp->smode2 = 1;
    disp->dispfb = ((unsigned long)(psm & 0xF) << 15) | ((unsigned long)(((w + 63) >> 6) & 0x3F) << 9);
    if (gp->sceGsOutMode == 2) {
        if (gp->sceGsInterMode == 1) {
            magh = (w + 0x9FF) / w;
            disp->display = ((dx * magh + (ox + 0x27CL)) & 0xFFF)
                | ((unsigned long)((dy + oy + 0x32) & 0xFFF) << 12)
                | ((unsigned long)(magh - 1) << 23)
                | ((unsigned long)(magh * w - 1) << 32)
                | ((unsigned long)(gp->sceGsFFMode ? h * 2 - 1 : h - 1) << 44);
        } else {
            magh = (w + 0x9FF) / w;
            disp->display = ((dx * magh + (ox + 0x27CL)) & 0xFFF)
                | ((unsigned long)((dy + oy + 0x19) & 0xFFF) << 12)
                | ((unsigned long)(magh - 1) << 23)
                | ((unsigned long)(magh * w - 1) << 32)
                | ((unsigned long)(h - 1) << 44);
        }
    } else if (gp->sceGsOutMode == 3) {
        if (gp->sceGsInterMode == 1) {
            magh = (w + 0x9FF) / w;
            disp->display = ((dx * magh + (ox + 0x290L)) & 0xFFF)
                | ((unsigned long)((dy + oy + 0x48) & 0xFFF) << 12)
                | ((unsigned long)(magh - 1) << 23)
                | ((unsigned long)(magh * w - 1) << 32)
                | ((unsigned long)(gp->sceGsFFMode ? h * 2 - 1 : h - 1) << 44);
        } else {
            magh = (w + 0x9FF) / w;
            disp->display = ((dx * magh + (ox + 0x290L)) & 0xFFF)
                | ((unsigned long)((dy + oy + 0x24) & 0xFFF) << 12)
                | ((unsigned long)(magh - 1) << 23)
                | ((unsigned long)(magh * w - 1) << 32)
                | ((unsigned long)(h - 1) << 44);
        }
    } else if (gp->sceGsOutMode == 0x50) {
        disp->display = (((0x2D0 - w) / 2 * 2 + ox + (dx * 2 + 0xE8L)) & 0xFFF)
            | ((unsigned long)((dy + oy + 0x23) & 0xFFF) << 12)
            | ((unsigned long)1 << 23)
            | ((unsigned long)(w * 2 - 1) << 32)
            | ((unsigned long)(h - 1) << 44);
    } else {
        printf(D_002AB330);
    }
    disp->bgcolor = 0;
}
