struct DISPENV { int a[10]; };
extern int D_002DFB58;
extern int D_002DFB4C;
extern int D_002DEDBC;
extern int D_002DFB5C;
extern int D_002DFB60;
extern int D_002DEDB0;
extern int D_002BE590;
extern int D_002BE594;
extern DISPENV D_002DEB80[2];
extern "C" void func_00234A50(int sid);
extern "C" void func_00240600(DISPENV *pdisp);
void BlendDisplayOnBufferMismatch();
int VBlankS_Interrupt(int ch)
{
    if (D_002DFB58) {
        D_002DFB58 = 0;
        func_00234A50(D_002DFB4C);
    }
    switch (D_002DEDBC) {
    case 1:
        if (!D_002DFB5C) {
            D_002BE594 = D_002BE590;
            BlendDisplayOnBufferMismatch();
        }
        break;
    case 2:
        if (!D_002DFB5C)
            BlendDisplayOnBufferMismatch();
        break;
    case 3:
        D_002DEDB0++;
        D_002DFB60 = 1;
        func_00240600(&D_002DEB80[D_002DEDB0 & 1]);
        break;
    }
    asm volatile("sync\n\tei");
    return 0;
}
