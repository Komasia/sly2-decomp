struct MSG { int cb; int nKind; };
struct S { char pad[0xD4]; int c; void *pv; };
void *func_001AE1D0(struct MSG *pmsg);
static inline void *PvAllocMsg(struct MSG *pmsg, int cb, int nKind) { pmsg->cb = cb; pmsg->nKind = nKind; return func_001AE1D0(pmsg); }
void func_001D8600(struct S *p, int c) {
    struct MSG msg;
    p->c = c;
    p->pv = PvAllocMsg(&msg, c << 4, 0x10);
}
