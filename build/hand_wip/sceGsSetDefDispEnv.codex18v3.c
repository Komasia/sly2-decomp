// Build the GS display registers for the current video mode.
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
static inline unsigned long PackInterlaceHeight(int frame,int h,unsigned long mag,unsigned long *width)
{
    if (frame) {
        int height=h*2;
        *width=mag | *width;
        --height;
        return (unsigned long)height << 44;
    } else {
        int height=h-1;
        *width=mag | *width;
        return (unsigned long)height << 44;
    }
}

void sceGsSetDefDispEnv(sceGsDispEnv *disp, short psm, short w, short h, short dx, short dy)
{
    sceGsGParam *gp = sceGsGetGParam();
    int ox, oy, ow, oh;

    if (gp->sceGsOutMode != 2 && gp->sceGsOutMode != 3 && func_00240B88()) {
        func_00240C28(gp->sceGsOutMode, &ox, &oy, &ow, &oh);
    } else {
        ox = oy = ow = oh = 0;
    }
    disp->pmode = 0x66;
    if (gp->sceGsInterMode != 0) {
        if (gp->sceGsFFMode)
            disp->smode2 = 3;
        else
            disp->smode2 = 1;
    } else
        disp->smode2 = 2;
    disp->dispfb = ((unsigned long)(psm & 0xF) << 15) | ((unsigned long)(((w + 63) >> 6) & 0x3F) << 9);
    if (gp->sceGsOutMode == 2) {
        if (gp->sceGsInterMode == 1) {
            register int magh asm("$3") = (w + 0x9FF) / w;
            {
                register unsigned long hh asm("$2");
                register int yyWord asm("$2") = (dy + oy + 0x32) & 0xFFF;
                unsigned long yy = (unsigned long)yyWord << 12;
                register long xx asm("$5") = (long)ox + 0x27CL;
                register int mw asm("$4") = magh * w;
                register int md asm("$2") = dx * magh;
                register unsigned long mm asm("$10") = (unsigned long)(magh-1) << 23;
                unsigned long ww;
                --mw; ww = (unsigned long)mw << 32;
                xx = (xx + md) & 0xFFF;
                hh = PackInterlaceHeight(gp->sceGsFFMode,h,mm,&ww);
                disp->display = (ww | ((unsigned long)xx | hh)) | yy;
            }
        } else {
            register int magh asm("$2") = (w + 0x9FF) / w;
            {
                register unsigned long hh asm("$7");
                register int yyWord asm("$3") = (dy + oy + 0x19) & 0xFFF;
                register unsigned long yy asm("$3") = (unsigned long)yyWord << 12;
                register long xx asm("$5") = (long)ox + 0x27CL;
                register int mw asm("$4") = magh * w;
                register int md asm("$6") = dx * magh;
                register unsigned long mm asm("$2") = (unsigned long)(magh-1) << 23;
                register unsigned long ww asm("$4");
                --mw; ww = (unsigned long)mw << 32;
                ww |= mm;
                xx = (xx + md) & 0xFFF;
                hh = (unsigned long)(h - 1) << 44;
                disp->display = (ww | ((unsigned long)xx | hh)) | yy;
            }
        }
    } else if (gp->sceGsOutMode == 3) {
        if (gp->sceGsInterMode == 1) {
            register int magh asm("$3") = (w + 0x9FF) / w;
            {
                register unsigned long hh asm("$2");
                register int yyWord asm("$2") = (dy + oy + 0x48) & 0xFFF;
                unsigned long yy = (unsigned long)yyWord << 12;
                register long xx asm("$5") = (long)ox + 0x290L;
                register int mw asm("$4") = magh * w;
                register int md asm("$2") = dx * magh;
                register unsigned long mm asm("$10") = (unsigned long)(magh-1) << 23;
                unsigned long ww;
                --mw; ww = (unsigned long)mw << 32;
                xx = (xx + md) & 0xFFF;
                hh = PackInterlaceHeight(gp->sceGsFFMode,h,mm,&ww);
                disp->display = (ww | ((unsigned long)xx | hh)) | yy;
            }
        } else {
            register int magh asm("$2") = (w + 0x9FF) / w;
            {
                register unsigned long hh asm("$7");
                register int yyWord asm("$3") = (dy + oy + 0x24) & 0xFFF;
                register unsigned long yy asm("$3") = (unsigned long)yyWord << 12;
                register long xx asm("$5") = (long)ox + 0x290L;
                register int mw asm("$4") = magh * w;
                register int md asm("$6") = dx * magh;
                register unsigned long mm asm("$2") = (unsigned long)(magh-1) << 23;
                register unsigned long ww asm("$4");
                --mw; ww = (unsigned long)mw << 32;
                ww |= mm;
                xx = (xx + md) & 0xFFF;
                hh = (unsigned long)(h - 1) << 44;
                disp->display = (ww | ((unsigned long)xx | hh)) | yy;
            }
        }
    } else if (gp->sceGsOutMode == 0x50) {
        register int center asm("$2") = (0x2D0 - w) / 2 * 2;
        register long xOffset asm("$7") = dx * 2 + 0xE8L;
        register long centered asm("$5") = (long)center + ox;
        register unsigned long hh asm("$3") = (unsigned long)(h - 1) << 44;
        register unsigned long ww asm("$6") = (unsigned long)(w * 2 - 1) << 32;
        register unsigned long yy asm("$4") = (unsigned long)((dy + oy + 0x23) & 0xFFF) << 12;
        centered = (centered + xOffset) & 0xFFF;
        disp->display = ((hh | ww) | ((unsigned long)centered | 0x800000)) | yy;
    } else {
        printf(D_002AB330);
    }
    disp->bgcolor = 0;
}
