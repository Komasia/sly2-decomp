struct AREQ { int cb; int cbAlign; };
struct E { int x0; int x4; };
struct P { char pad[0x4640]; int c; struct E *ae; };
extern int D_002E1E54;
extern char g_heapSw[];
extern char D_003E1C20[];
int U8Read(void *pbs) asm("U8Read__18CBinaryInputStream");
int S16Read(void *pbs) asm("S16Read__18CBinaryInputStream");
void *PvAllocSwImpl__Fi(struct AREQ *preq);
void func_00118380(void *pbs, int *pn, void *pv, int n);
void ReadDebugString__FP18CBinaryInputStream(void *pbs);
void func_00210BE0(void *pv);
// name: SafeHouse port (LoadTextFromBrx)
void LoadTextFromBrx__FP2SWP18CBinaryInputStream(struct P *p, void *pbs)
{
    struct AREQ req;
    int i;
    int iMatch = 0;
    int c = U8Read(pbs);
    {
        int j;
        for (j = 0; j < c; j++) {
            if (U8Read(pbs) == D_002E1E54)
                iMatch = j;
        }
    }
    i = 0;
    p->c = S16Read(pbs);
    req.cbAlign = 0x10;
    req.cb = p->c * sizeof(struct E);
    p->ae = (struct E *)PvAllocSwImpl__Fi(&req);
    for (; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        int j;
        pe->x0 = S16Read(pbs);
        for (j = 0; j < c; j++) {
            if (j == iMatch)
                func_00118380(pbs, &pe->x4, g_heapSw, 0x2E);
            else
                ReadDebugString__FP18CBinaryInputStream(pbs);
        }
    }
    func_00210BE0(D_003E1C20);
}
