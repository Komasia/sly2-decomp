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

typedef char gs_short_2[(sizeof(short)==2)?1:-1];
typedef char gs_int_4[(sizeof(int)==4)?1:-1];
typedef char gs_long_8[(sizeof(long)==8)?1:-1];
typedef char gs_ptr_4[(sizeof(void*)==4)?1:-1];
typedef char gs_param_size_8[(sizeof(sceGsGParam)==8)?1:-1];
typedef char gs_param_align_2[(__alignof__(sceGsGParam)==2)?1:-1];
typedef char gs_param_inter_0[(((unsigned long)&((sceGsGParam*)0)->sceGsInterMode)==0)?1:-1];
typedef char gs_param_out_2[(((unsigned long)&((sceGsGParam*)0)->sceGsOutMode)==2)?1:-1];
typedef char gs_param_frame_4[(((unsigned long)&((sceGsGParam*)0)->sceGsFFMode)==4)?1:-1];
typedef char gs_param_version_6[(((unsigned long)&((sceGsGParam*)0)->sceGsVersion)==6)?1:-1];
typedef char gs_disp_size_40[(sizeof(sceGsDispEnv)==40)?1:-1];
typedef char gs_disp_align_8[(__alignof__(sceGsDispEnv)==8)?1:-1];
typedef char gs_disp_pmode_0[(((unsigned long)&((sceGsDispEnv*)0)->pmode)==0)?1:-1];
typedef char gs_disp_smode2_8[(((unsigned long)&((sceGsDispEnv*)0)->smode2)==8)?1:-1];
typedef char gs_disp_dispfb_16[(((unsigned long)&((sceGsDispEnv*)0)->dispfb)==16)?1:-1];
typedef char gs_disp_display_24[(((unsigned long)&((sceGsDispEnv*)0)->display)==24)?1:-1];
typedef char gs_disp_bgcolor_32[(((unsigned long)&((sceGsDispEnv*)0)->bgcolor)==32)?1:-1];

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
                register unsigned long yy asm("$7") = ({
                    register unsigned long bits asm("$7");
                    __asm__("dsll %0,%1,%2":"=r"(bits):"r"(yyWord),"I"(12));
                    bits;
                });
                register long xx asm("$5") = (long)ox + 0x27CL;
                register int mw asm("$4") = magh * w;
                register int md asm("$2") = dx * magh;
                register unsigned long mm asm("$10") = ({
                    register unsigned long bits asm("$10");
                    __asm__("dsll %0,%1,%2":"=r"(bits):"r"(magh-1),"I"(23));
                    bits;
                });
                register unsigned long ww asm("$3");
                --mw;
                __asm__("dsll32 %0,%1,%2":"=r"(ww):"r"(mw),"I"(0));
                xx = (xx + md) & 0xFFF;
                hh = PackInterlaceHeight(gp->sceGsFFMode,h,mm,&ww);
                {
                    register unsigned long xHeight asm("$2") = (unsigned long)xx | hh;
                    register unsigned long widthHeight asm("$3") = ww | xHeight;
                    register unsigned long displayBits asm("$2") = widthHeight | yy;
                    disp->display = displayBits;
                }
            }
        } else {
            register int magh asm("$2") = (w + 0x9FF) / w;
            {
                register unsigned long hh __asm__("$7");
                register long xx asm("$5");
                register int originY asm("$3"),yyWord asm("$3");
                register unsigned long yy asm("$3");
                register int md asm("$6"),mw asm("$4");
                register unsigned long mm asm("$2"),ww asm("$4");
                __asm__("addiu %0,%3,-1\n\tlw %1,%4\n\tdsll32 %0,%0,12\n\tlw %2,%5\n\tdaddiu %1,%1,%6"
                    :"=&r"(hh),"=&r"(xx),"=r"(originY):"r"(h),"m"(ox),"m"(oy),"I"(0x27C));
                yyWord = (dy + originY + 0x19) & 0xFFF;
                yy = (unsigned long)yyWord << 12;
                md = dx * magh;
                mw = magh * w;
                mm = (unsigned long)(magh-1) << 23;
                xx = (xx + md) & 0xFFF;
                {
                    register unsigned long xHeight asm("$5") = (unsigned long)xx | hh;
                    --mw; ww = (unsigned long)mw << 32;
                    {
                        register unsigned long widthMag asm("$2") = mm | ww;
                        register unsigned long displayBits asm("$2") = (widthMag | xHeight) | yy;
                        disp->display = displayBits;
                    }
                }
            }
        }
    } else if (gp->sceGsOutMode == 3) {
        if (gp->sceGsInterMode == 1) {
            register int magh asm("$3") = (w + 0x9FF) / w;
            {
                register unsigned long hh asm("$2");
                register int yyWord asm("$2") = (dy + oy + 0x48) & 0xFFF;
                register unsigned long yy asm("$7") = ({
                    register unsigned long bits asm("$7");
                    __asm__("dsll %0,%1,%2":"=r"(bits):"r"(yyWord),"I"(12));
                    bits;
                });
                register long xx asm("$5") = (long)ox + 0x290L;
                register int mw asm("$4") = magh * w;
                register int md asm("$2") = dx * magh;
                register unsigned long mm asm("$10") = ({
                    register unsigned long bits asm("$10");
                    __asm__("dsll %0,%1,%2":"=r"(bits):"r"(magh-1),"I"(23));
                    bits;
                });
                register unsigned long ww asm("$3");
                --mw;
                __asm__("dsll32 %0,%1,%2":"=r"(ww):"r"(mw),"I"(0));
                xx = (xx + md) & 0xFFF;
                hh = PackInterlaceHeight(gp->sceGsFFMode,h,mm,&ww);
                {
                    register unsigned long xHeight asm("$2") = (unsigned long)xx | hh;
                    register unsigned long widthHeight asm("$3") = ww | xHeight;
                    register unsigned long displayBits asm("$2") = widthHeight | yy;
                    disp->display = displayBits;
                }
            }
        } else {
            register int magh asm("$2") = (w + 0x9FF) / w;
            {
                register unsigned long hh __asm__("$7");
                register long xx asm("$5");
                register int originY asm("$3"),yyWord asm("$3");
                register unsigned long yy asm("$3");
                register int md asm("$6"),mw asm("$4");
                register unsigned long mm asm("$2"),ww asm("$4");
                __asm__("addiu %0,%3,-1\n\tlw %1,%4\n\tdsll32 %0,%0,12\n\tlw %2,%5\n\tdaddiu %1,%1,%6"
                    :"=&r"(hh),"=&r"(xx),"=r"(originY):"r"(h),"m"(ox),"m"(oy),"I"(0x290));
                yyWord = (dy + originY + 0x24) & 0xFFF;
                yy = (unsigned long)yyWord << 12;
                md = dx * magh;
                mw = magh * w;
                mm = (unsigned long)(magh-1) << 23;
                xx = (xx + md) & 0xFFF;
                {
                    register unsigned long xHeight asm("$5") = (unsigned long)xx | hh;
                    --mw; ww = (unsigned long)mw << 32;
                    {
                        register unsigned long widthMag asm("$2") = mm | ww;
                        register unsigned long displayBits asm("$2") = (widthMag | xHeight) | yy;
                        disp->display = displayBits;
                    }
                }
            }
        }
    } else if (gp->sceGsOutMode == 0x50) {
        register int center asm("$2") = (0x2D0 - w) / 2 * 2;
        register int dxWord asm("$6") = dx * 2;
        register long xOffset asm("$7") = (long)dxWord + 0xE8L;
        register long centered asm("$5") = (long)center + ox;
        register unsigned long ww asm("$6");
        register unsigned long hh asm("$3");
        register int yWord asm("$4") = dy + oy;
        register unsigned long horizontalMag asm("$2");
        __asm__("sll %0,%1,1":"=r"(ww):"r"(w));
        __asm__("addiu %0,%1,-1":"=r"(hh):"r"(h));
        centered = centered + xOffset;
        __asm__("addiu %0,%0,-1":"+r"(ww));
        __asm__("dsll32 %0,%0,12\n\tdsll32 %1,%1,0\n\tandi %2,%2,0xFFF\n\taddiu %3,%3,0x23\n\tlui %4,0x80"
            :"+&r"(hh),"+&r"(ww),"+r"(centered),"+r"(yWord),"=r"(horizontalMag));
        {
            register unsigned long packedExtent asm("$3") = hh | ww;
            register unsigned long packedX asm("$5") = (unsigned long)centered | horizontalMag;
            register unsigned long extentX asm("$3") = packedExtent | packedX;
            register unsigned long yy asm("$4");
            yWord &= 0xFFF;
            yy = (unsigned long)yWord << 12;
            {
                register unsigned long displayBits asm("$3") = extentX | yy;
                disp->display = displayBits;
            }
        }
    } else {
        printf(D_002AB330);
    }
    disp->bgcolor = 0;
}
