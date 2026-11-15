/* CProc::CloneTo: a copy of the closure over pframe (or its own frame when null), sharing formals and body. */
struct X;
struct Y;
struct SPX { X *p; ~SPX(); SPX &operator=(X *px); };
struct SPY { Y *p; ~SPY(); SPY &operator=(Y *py); };
struct O {
    int cref;
    int x4;
    SPX spx;
    int crefReq;
    int fVarArg;
    SPY sppairFormals;
    SPY sppairBody;
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
    sp->sppairFormals = poSrc->sppairFormals.p;
    sp->crefReq = poSrc->crefReq;
    sp->fVarArg = poSrc->fVarArg;
    sp->sppairBody = poSrc->sppairBody.p;
    return SPO(sp.p);
}
