struct MSG { int cb; int nKind; };
struct S { char pad[0xE8]; int c; char pad2[0x1EC - 0xEC]; void *p; };
void LoadPathFromBrx__FP2LOP18CBinaryInputStream(struct S *p);
void *PvAllocSwClearImpl__Fi(struct MSG *pmsg);
static __inline__ void *PvAllocMsg(struct MSG *pmsg, int cb, int nKind) { pmsg->cb = cb; pmsg->nKind = nKind; return PvAllocSwClearImpl__Fi(pmsg); }
void func_001BC088(struct S *p)
{
    struct MSG msg;
    LoadPathFromBrx__FP2LOP18CBinaryInputStream(p);
    p->p = PvAllocMsg(&msg, (p->c << 4) - 0x10, 0x10);
}
