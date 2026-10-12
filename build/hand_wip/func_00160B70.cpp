/* ~10 diffs: madd result in v1 + copy to a0 (target madd straight into a0); store order matches */
union QW;
struct sceDmaChan;
struct FR {
    int cqwGifs; QW *aqwGifs; QW *aqwGifsBuf; int cqwGifsBuf;
    int cqwVifs; QW *aqwVifs; QW *aqwVifsBuf; int cqwVifsBuf;
    int cqw20; QW *aqw24; int n28; int n2C; int n30; int adl[6]; int n4C;
};
extern FR *D_002DEB14;
extern FR D_002DEA50[2];
extern unsigned int D_002DEB0C;
extern int D_002DEB20;
extern int D_002DEB18;
extern int D_002DEB1C;
extern int D_002DEDBC;
extern sceDmaChan *D_002DE594;
extern sceDmaChan *D_002DE598;
extern "C" void func_00234A60(int sid);
extern "C" void func_00234A40(int sid);
extern "C" void func_001EE7B0(FR *pfr);
extern "C" void func_00170048();
extern "C" void func_00160F98();
extern "C" void func_002417F0(sceDmaChan *pch, int a, int b);
void RestoreGsBuffers();
void SwapGsBuffers();
void SendDmaSyncGsFinish(sceDmaChan *pch, QW *pqw);
extern "C" void func_00160B70()
{
    for (;;) {
        D_002DEB20 = 1;
        func_00234A60(D_002DEB18);
        D_002DEB20 = 0;
        FR *pfr = &D_002DEA50[D_002DEB0C++];
        D_002DEB14 = pfr;
        if (D_002DEB0C >= 2) D_002DEB0C = 0;
        func_001EE7B0(pfr);
        RestoreGsBuffers();
        func_00170048();
        SendDmaSyncGsFinish(D_002DE594, D_002DEB14->aqw24);
        SendDmaSyncGsFinish(D_002DE598, D_002DEB14->aqwGifs);
        if (D_002DEB14->n30 & 1)
            func_00160F98();
        func_002417F0(D_002DE594, 0, 0);
        func_00234A40(D_002DEB1C);
        SwapGsBuffers();
        D_002DEDBC = 1;
    }
}
