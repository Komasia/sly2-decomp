/* near: packed GS-register bitfield structs give ldl/sdl copies; remaining: address (base+0x18)+i*0x28 not folded in target, missing andi 0x7FF after +-1 on high-word fields, DEDB8 load scheduling */
typedef struct { unsigned int SIGNAL:1, FINISH:1, HSINT:1, VSINT:1, EDWINT:1, ZERO1:3, FLUSH:1, RESET:1, ZERO2:2, NFIELD:1, FIELD:1, FIFO:2, REV:8, ID:8; } CSR;
typedef struct { unsigned long EN1:1, EN2:1, CRTMD:3, MMOD:1, AMOD:1, SLBG:1, ALP:8, p0:48; } __attribute__((packed)) PMODE;
typedef struct { unsigned int FBP:9, FBW:6, PSM:5, p0:12, DBX:11, DBY:11, p1:10; } __attribute__((packed)) DISPFB;
typedef struct { unsigned int DX:12, DY:11, MAGH:4, MAGV:2, p0:3, DW:12, DH:11, p1:9; } __attribute__((packed)) DISPLAY;
typedef struct { PMODE pmode; unsigned long smode2; DISPFB dispfb; DISPLAY display; unsigned long bgcolor; } DISPENV;
extern DISPENV D_002DEB80[2];
extern int D_002DEDB0;
extern int D_002DEDB8;
static __inline__ int FField(void) { return ((CSR *)0x12001000)->FIELD; }
void BlendDisplayOnBufferMismatch__Fv(void)
{
    int i = D_002DEDB0 & 1;
    PMODE pmode = D_002DEB80[i].pmode;
    if (D_002DEDB8 != FField()) {
        DISPLAY display = D_002DEB80[i].display;
        DISPFB dispfb = D_002DEB80[i].dispfb;
        display.DH -= 1;
        if (D_002DEDB8)
            display.DY += 1;
        else
            dispfb.DBY += 1;
        *(DISPLAY *)0x12000080 = display;
        *(DISPFB *)0x12000070 = dispfb;
        pmode.EN1 = 1;
    }
    *(PMODE *)0x12000000 = pmode;
}
