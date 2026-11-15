// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* sceGszbufaddr (libgraph): frame buffer base (in pages) of the depth buffer that follows the frame buffer(s). */
typedef struct { short sceGsInterMode, sceGsOutMode, sceGsFFMode, sceGsVersion; } __attribute__((aligned(16))) sceGsGParam;
sceGsGParam *sceGsGetGParam(void);
short sceGszbufaddr(short psm, short w, short h)
{
    sceGsGParam *gp = sceGsGetGParam();
    int bw, bh;
    bw = (w + 63) / 64;
    if (psm & 2) bh = (h + 63) / 64;
    else bh = (h + 31) / 32;
    /* page count (64x32 for 32-bit formats, 64x64 for 16-bit); interlaced field mode needs one frame only */
    if (gp->sceGsInterMode == 1 && gp->sceGsFFMode == 0)
        return bw * bh;
    return bw * bh * 2;
}
