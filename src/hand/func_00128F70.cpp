struct X;
struct Y;
struct SPX { X *p; ~SPX(); SPX &operator=(X *px); };
struct SPY { Y *p; ~SPY(); SPY &operator=(Y *py); };
struct O {
    int cref;
    int x4;
    SPX spx;
    int xC;
    int x10;
    SPY spy14;
    SPY spy18;
    ~O();
};
struct SPO {
    O *p;
    void Set(O *po);
    SPO() {}
    SPO(O *po) { Set(po); }
    SPO(const SPO &);
    ~SPO() { O *po = p; if (po && --po->cref == 0) delete po; }
    O *operator->() { return p; }
};
extern "C" {
O *PprocNew() asm("PprocNew__Fv");
SPO CloneTo(O *poSrc, X *px) asm("CloneTo__5CProcP5CProc");
}
// name: SafeHouse port (CProc::CloneTo)
SPO CloneTo(O *poSrc, X *px)
{
    SPO sp;
    sp.Set(PprocNew());
    if (px)
        sp->spx = px;
    else
        sp->spx = poSrc->spx.p;
    sp->spy14 = poSrc->spy14.p;
    sp->xC = poSrc->xC;
    sp->x10 = poSrc->x10;
    sp->spy18 = poSrc->spy18.p;
    return SPO(sp.p);
}
