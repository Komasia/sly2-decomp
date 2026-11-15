// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* sceGsResetGraph (libgraph): mode 0 resets the GS and sets the video mode (interlace, NTSC/PAL/480p, field/frame),
   dropping any V-blank handler; mode 1 only flushes the GS; mode 5 sets the video mode without a reset. */
typedef struct {
    short sceGsInterMode;
    short sceGsOutMode;
    short sceGsFFMode;
    short sceGsVersion;
    int vsync_id;
    int handler_id;
} sceGsGParam;
sceGsGParam *sceGsGetGParam(void);
int GsPutIMR(unsigned long);        /* syscall */
int DisableIntc(int);
int RemoveIntcHandler(int, int);
void SetGsCrt(short, short, short);
void sceGsResetGraph(short mode, short inter, short omode, short ffmode)
{
    sceGsGParam *gp;
    switch (mode) {
    case 0:
        gp = sceGsGetGParam();
        *(volatile unsigned long *)0x12001000 = 0x200;     /* GS CSR.RESET */
        gp->sceGsInterMode = inter;
        gp->sceGsOutMode = omode;
        gp->sceGsVersion = (*(volatile unsigned long *)0x12001000 >> 16) & 0xFF;   /* CSR.REV */
        GsPutIMR(0xFF00);                                   /* mask every GS interrupt */
        gp->sceGsFFMode = (ffmode != 0);
        if (gp->vsync_id) {
            DisableIntc(2);             /* INTC_VBLANK_S */
            RemoveIntcHandler(2, gp->handler_id);
            gp->vsync_id = 0;
            gp->handler_id = 0;
        }
        SetGsCrt(inter & 1, omode & 0xFF, ffmode & 1);
        break;
    case 1:
        *(volatile unsigned long *)0x12001000 = 0x100;     /* GS CSR.FLUSH */
        break;
    case 5:
        gp = sceGsGetGParam();
        gp->sceGsInterMode = inter;
        gp->sceGsOutMode = omode;
        gp->sceGsFFMode = (ffmode != 0);
        gp->sceGsVersion = (*(volatile unsigned long *)0x12001000 >> 16) & 0xFF;
        SetGsCrt(inter & 1, omode & 0xFF, ffmode & 1);
        break;
    }
}
