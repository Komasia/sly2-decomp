struct ALLOCREQ { int cb; int nAlign; };
/* a 0x28-byte world record (+0x3F0C): two -1 ids and a DL of 0x14-byte links */
struct SWREC28 { int idA; int unk_0x04; int idB; int unk_0x0c; int unk_0x10; int unk_0x14; char dl[0x10]; };
/* the world fields used here: the pending request's flags (+0x3BF4), three 0x4800-byte buffers, a flag, the record,
 * a 0x8000-byte buffer, the two render targets */
struct SW {
    char pad0[0x3BF4]; int grfReq;
    char pad1[0x3CD4 - 0x3BF8]; void *apvBuf3CD4[3];
    char pad2[0x3E38 - 0x3CE0]; int f3E38;
    char pad3[0x3F0C - 0x3E3C]; struct SWREC28 *prec3F0C; char pad4[0x3F20 - 0x3F10]; void *pvBuf3F20;
    char pad5[0x45E8 - 0x3F24]; char artgt[2][0x28];
};
struct ZPR { char ab[0x630]; };
extern char g_game[];
void *PvAllocSwImpl__Fi(struct ALLOCREQ *preq);
void *PvAllocSwClearImpl__Fi(struct ALLOCREQ *preq);
void func_0011A050(void *pdl, int cb);   /* InitDl */
void InitZpr(struct ZPR *pzpr, int zpk, int plo) asm("InitZpr__FP3ZPR3ZPKP2LO");
void func_001BE398(void *prtgt, struct ZPR *pzpr);   /* a render target */
void BroadcastTaskEvent__FP2SWiP2LO(void *psw, int nEvent, int plo);

/* func_0020E180 (0x20E180): the world's memory at its load: three 0x4800-byte buffers, a cleared 0x8000-byte one and
 * a 0x28-byte record, the two render targets (0x1BE398 with a ZPR of 0x1400 / 0x1800: SafeHouse rtgt.h); +0x3E38 set for a request
 * with flag 0x20; then task event 2. */
void func_0020E180(struct SW *psw)
{
    struct ALLOCREQ req;
    struct ZPR zpr;
    int i;
    unsigned int j;
    for (i = 0; i < 3; i++) {
        req.cb = 0x4800;
        req.nAlign = 0x10;
        psw->apvBuf3CD4[i] = PvAllocSwImpl__Fi(&req);
    }
    req.cb = 0x8000;
    req.nAlign = 0x10;
    psw->pvBuf3F20 = PvAllocSwClearImpl__Fi(&req);
    req.cb = 0x28;
    req.nAlign = 0x10;
    psw->prec3F0C = PvAllocSwClearImpl__Fi(&req);
    psw->prec3F0C->idA = -1;
    psw->prec3F0C->idB = -1;
    func_0011A050(psw->prec3F0C->dl, 0x14);
    InitZpr(&zpr, 0x1400, 0x1800);
    for (j = 0; j < 2; j++)
        func_001BE398(psw->artgt[j], &zpr);
    if (psw->grfReq & 0x20)
        psw->f3E38 = 1;
    BroadcastTaskEvent__FP2SWiP2LO(g_game, 2, 0);
}
