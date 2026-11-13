typedef struct { int cb; int cbAlign; } AREQ;
struct O { char pad[0x40]; void *x40; };
struct S {
    char pad[0x50]; int x50; int x54; int x58; char pad5c[0x14]; int x70; int x74; int x78; int x7C;
    char pad80[0x10]; float x90; int x94; int x98; char pad9c[0x20]; int xBC; struct O *xC0; void *xC4;
};
extern char D_003E1C70[], D_003E1C80[], D_003E106C[];
void LoadLoFromBrx__FP2LOP18CBinaryInputStream(struct S *p, void *pbis);
int S8Read(void *pbis) asm("S8Read__18CBinaryInputStream");
float F32Read(void *pbis) asm("F32Read__18CBinaryInputStream");
int U32Read(void *pbis) asm("U32Read__18CBinaryInputStream");
struct O *PvAllocSwClearImpl__Fi(AREQ *preq);
void ReadRecord64(void *pbis, struct O *po) asm("ReadRecord64__18CBinaryInputStreamPv");
void func_0011A070(void *, struct O *po);
void LoadElemsFromBrx__FPvP18CBinaryInputStreamT0PiT3(struct S *p, void *pbis, struct S *p2, int *pa, int *pb);
void LoadGroupsFromBrx__FP5OWNERP18CBinaryInputStreamP4ROOT(struct S *p, void *pbis, struct S *p2);
// name: SafeHouse port (LoadScreenObjFromBrx)
void LoadScreenObjFromBrx__FP9SCREENOBJP18CBinaryInputStream(struct S *p, void *pbis)
{
    int f;
    p->x70 = 0x310;
    p->x74 = 0x30F;
    p->x78 = 0x311;
    LoadLoFromBrx__FP2LOP18CBinaryInputStream(p, pbis);
    f = S8Read(pbis);
    p->x90 = F32Read(pbis);
    p->x94 = U32Read(pbis);
    p->x98 = U32Read(pbis);
    p->xBC = U32Read(pbis);
    if (f) {
        AREQ req;
        p->x58 = 0;
        req.cb = 0x50;
        req.cbAlign = 0x10;
        p->xC4 = D_003E1C70;
        p->xC0 = PvAllocSwClearImpl__Fi(&req);
        p->xC0->x40 = p;
        ReadRecord64(pbis, p->xC0);
        func_0011A070(D_003E106C, p->xC0);
    } else {
        p->x58 = 1;
        p->xC4 = D_003E1C80;
        LoadElemsFromBrx__FPvP18CBinaryInputStreamT0PiT3(p, pbis, p, &p->x50, &p->x54);
        LoadGroupsFromBrx__FP5OWNERP18CBinaryInputStreamP4ROOT(p, pbis, p);
    }
    p->x7C = -1;
}
