union QW;
struct FR {
    int cqwGifs; QW *aqwGifs; QW *aqwGifsBuf; int cqwGifsBuf;
    int cqwVifs; QW *aqwVifs; QW *aqwVifsBuf; int cqwVifsBuf;
    int cqw20; QW *aqw24; int n28; int n2C; int n30; int adl[6]; int n4C;
};
extern FR *D_002DEB14;
extern FR D_002DEA50[2];
extern volatile int D_002DEB20;
extern int D_002DEB1C;
extern int D_002DEDBC;
extern "C" int WaitSema(int sid) asm("WaitSema");
extern "C" int SignalSema(int sid) asm("SignalSema");
extern "C" void RenderFrame__FP3FRMi(FR *pfr, int f);
extern "C" void BlendPrevFrame__Fv();
extern "C" void ClearPendingFrame__FP3FRM(FR *pfr);
extern "C" void func_001C2BA8(int phase);
void SwapGsBuffers();
// name: Sly 1 frm.c FlushFrames(fFreeze) (suggested by h2)
extern "C" void FlushFrames__Fi(int fReset)
{
    unsigned int i;
    for (i = 0; i < 2; i++)
        WaitSema(D_002DEB1C);
    for (i = 0; i < 2; i++)
        SignalSema(D_002DEB1C);
    while (!D_002DEB20)
        ;
    if (fReset && D_002DEB14) {
        for (int j = 0; j < 3; j++) {
            RenderFrame__FP3FRMi(D_002DEB14, 1);
            if (D_002DEB14->n30 & 1)
                BlendPrevFrame__Fv();
            SwapGsBuffers();
        }
        D_002DEDBC = 3;
    }
    if (fReset) {
        FR *pfr = D_002DEA50;
        do {
            ClearPendingFrame__FP3FRM(pfr);
            pfr++;
        } while (pfr < D_002DEA50 + 2);
    }
    func_001C2BA8(3);
    D_002DEB14 = 0;
}
