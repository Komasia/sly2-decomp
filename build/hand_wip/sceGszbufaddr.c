// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
typedef struct { short sceGsInterMode, sceGsOutMode, sceGsFFMode, sceGsVersion; } __attribute__((aligned(16))) sceGsGParam;
sceGsGParam *sceGsGetGParam(void);
short sceGszbufaddr(short psm, short w, short h)
{
    sceGsGParam *gp = sceGsGetGParam();
    int bw, bh;
    bw = (w + 63) / 64;
    if (psm & 2) bh = (h + 63) / 64;
    else bh = (h + 31) / 32;
    if (!(gp->sceGsInterMode == 1 && gp->sceGsFFMode == 0))
        return bw * bh * 2;
    return bw * bh;
}
