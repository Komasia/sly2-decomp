// BeginScptLoad: loads a relay (relay.h RELAY, SafeHouse scpt.cpp). The commands are appended one at a time while
// the object's options run, so a scratch array of 0x200 commands is taken from the stack heap first, with the opening
// BlockBegin command (no label: -1) and the closing BlockEnd still to append; after the LO load the commands are
// copied into a world allocation sized for the larger of the count and the script's limit, plus one (the BlockEnd).
struct MSG { int cb; int nKind; };   // allocation request: size, alignment
struct FRAME {                       // stack-heap frame (released on return)
    int a[4];
    FRAME();
    ~FRAME();
};
struct RELAYCMD { char a[0x50]; };
struct RELAY {                       // relay.h RELAY
    char lo[0x50];                   // the LO base
    int crelaycmd;
    RELAYCMD *arelaycmd;
    int crelaycmdMax;
    char unk_0x5c[0x7C - 0x5C];
    int fAppendEnd;
};
void *PvAllocStackImpl(MSG *) asm("PvAllocStackImpl__Fi");
void *PvAllocSwImpl(MSG *) asm("PvAllocSwImpl__Fi");
void CopyAb(void *, void *, int) asm("CopyAb__FPvT0Ui");
extern "C" void func_001E0290(RELAY *prelay, int oidLabel);   // append a BlockBegin command
void LoadLoFromBrx(RELAY *, void *) asm("LoadLoFromBrx__FP2LOP18CBinaryInputStream");
static inline int Max(int a, int b) { return a < b ? b : a; }
// name: SafeHouse port (BeginScptLoad)
extern "C" void BeginScptLoad__FP2LOPv(RELAY *prelay, void *pbis)
{
    FRAME frame;
    MSG msg;
    MSG *pmsg = &msg;
    pmsg->cb = 0x200 * sizeof(RELAYCMD);
    pmsg->nKind = 0x10;
    prelay->arelaycmd = (RELAYCMD *)PvAllocStackImpl(pmsg);
    func_001E0290(prelay, -1);
    prelay->fAppendEnd = 1;
    LoadLoFromBrx(prelay, pbis);
    {
        RELAYCMD *arelaycmdScratch = prelay->arelaycmd;
        prelay->crelaycmdMax = Max(prelay->crelaycmd, prelay->crelaycmdMax) + 1;
        pmsg->cb = prelay->crelaycmdMax * sizeof(RELAYCMD);
        pmsg->nKind = 0x10;
        prelay->arelaycmd = (RELAYCMD *)PvAllocSwImpl(pmsg);
        CopyAb(prelay->arelaycmd, arelaycmdScratch, prelay->crelaycmd * sizeof(RELAYCMD));
    }
}
