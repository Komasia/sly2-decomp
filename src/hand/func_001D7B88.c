struct MSG { int cb; int nKind; };
typedef struct BIS BIS;
typedef struct { int c; void *pv; char ht[1]; } OBJ;
extern char g_heapSw[];
extern struct G D_003D4A60;
int U16Read(BIS *) asm("U16Read__18CBinaryInputStream");
void Read__18CBinaryInputStreamiPv(BIS *, int, void *);
void func_00118380(BIS *, char **, void *, int);
void func_001D8600(void *, int);
void func_001D8690(void *, char *, int);
void *PvAllocSwImpl__Fi(struct MSG *);
void ValidateGameSave__FPvT0(OBJ *, struct G *);
// name: SafeHouse port (LoadProgressFromBrx)
void LoadProgressFromBrx__FP2SWP18CBinaryInputStream(OBJ *p, BIS *pbis)
{
    struct MSG msg;
    char *pchz;
    int i;
    int n;
    int c;
    n = U16Read(pbis);
    func_001D8600(p->ht, n);
    for (i = 0; i < n; i++) {
        int v = U16Read(pbis);
        func_00118380(pbis, &pchz, g_heapSw, 0x2D);
        func_001D8690(p->ht, pchz, v);
    }
    c = U16Read(pbis);
    p->c = c;
    msg.cb = c * 10;
    msg.nKind = 0x10;
    p->pv = PvAllocSwImpl__Fi(&msg);
    Read__18CBinaryInputStreamiPv(pbis, c * 10, p->pv);
    ValidateGameSave__FPvT0(p, &D_003D4A60);
}
