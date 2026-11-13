extern char D_0025AFA0[], D_0025B870[], D_002DF800[];
extern char D_004421A0[], D_004424B0[], D_004424D0[], D_004424F0[], D_00442520[], D_004425A0[], D_00442560[], D_00442240[];
extern char D_000000C0[], D_00000100[];
void EnsureVu1Code__FP4VIFSPvT1(void *, void *, void *);
void AddDmaCnt(void *) asm("AddDmaCnt__4DMAS");
void AddVifFlush(void *) asm("AddVifFlush__4VIFS");
void AddDmaCall(void *, void *) asm("AddDmaCall__4DMASP2QW");
void AddVifBaseOffset(void *, int, int) asm("AddVifBaseOffset__4VIFSii");
void AddVifUnpack(void *, int, int, void *, int) asm("AddVifUnpack__4VIFS3UPKiPvi");
void AddVifMscal(void *, void *) asm("AddVifMscal__4VIFSPv");
void AddVifFlusha(void *) asm("AddVifFlusha__4VIFS");
void AddVifDirect(void *, int, void *, int) asm("AddVifDirect__4VIFSiP2QWi");
void EndDmaCnt(void *) asm("EndDmaCnt__4DMAS");
void func_00211A80(void *p)
{
    EnsureVu1Code__FP4VIFSPvT1(p, D_0025AFA0, D_0025B870);
    AddDmaCnt(p);
    AddVifFlush(p);
    AddDmaCall(p, D_002DF800);
    AddVifBaseOffset(p, 0, 0);
    AddVifUnpack(p, 0xC, 7, D_004421A0, 0xD);
    AddVifUnpack(p, 0xC, 2, D_004424B0, 0x15);
    AddVifUnpack(p, 0xC, 2, D_004424D0, 0x17);
    AddVifUnpack(p, 0xC, 3, D_004424F0, 0x19);
    AddVifUnpack(p, 0xC, 4, D_00442520, 0x1C);
    AddVifUnpack(p, 0xC, 3, D_004425A0, 0x20);
    AddVifUnpack(p, 0xC, 4, D_00442560, 0x23);
    AddVifBaseOffset(p, 0x32, 0x1E7);
    AddVifMscal(p, D_000000C0);
    AddVifFlusha(p);
    AddVifDirect(p, 0x27, D_00442240, 0);
    AddVifFlusha(p);
    AddVifMscal(p, D_00000100);
    AddVifFlusha(p);
    EndDmaCnt(p);
}
