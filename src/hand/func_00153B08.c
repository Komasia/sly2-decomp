typedef struct MSG { int cb; int nKind; } MSG;
void *PvAllocSwClearImpl__Fi(MSG *pmsg);
static inline void *PvAllocMsg(MSG *pmsg, int cb, int nKind) { pmsg->cb = cb; pmsg->nKind = nKind; return PvAllocSwClearImpl__Fi(pmsg); }
struct E { char *pchz; int n4; int n8; int nC; char ab[0x40]; };
struct S { char pad[0x50]; int c; struct E *ae; };
extern char g_heapSw[];
void LoadLoFromBrx__FP2LOP18CBinaryInputStream(struct S *p, void *pbis);
int U8Read(void *pbis) asm("U8Read__18CBinaryInputStream");
int S8Read(void *pbis) asm("S8Read__18CBinaryInputStream");
int S32Read(void *pbis) asm("S32Read__18CBinaryInputStream");
void func_00118380(void *pbis, char **ppchz, void *palloc, int nKind);
void func_00118458(void *pbis, void *pv);
void func_00153B08(struct S *p, void *pbis)
{
    MSG msg;
    int i;
    LoadLoFromBrx__FP2LOP18CBinaryInputStream(p, pbis);
    p->c = U8Read(pbis);
    p->ae = PvAllocMsg(&msg, p->c * sizeof(struct E), 0x10);
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        func_00118380(pbis, &pe->pchz, g_heapSw, 7);
        pe->n4 = S8Read(pbis);
        pe->n8 = S32Read(pbis);
        pe->nC = S32Read(pbis);
        func_00118458(pbis, pe->ab);
    }
}
