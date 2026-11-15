// PtrkgNew: a new scalar track (TRKG) of the given kind, zeroed from the slot heap; null for an unknown kind.
struct AREQ { int cb; int cbAlign; };
extern "C" void *PvAllocSwClearImpl(AREQ *preq) asm("PvAllocSwClearImpl__Fi");
struct CBase {
    void *operator new(unsigned int cb) { AREQ req; req.cb = cb; req.cbAlign = 0x10; return PvAllocSwClearImpl(&req); }
    virtual void F();
};
// The three scalar-track classes (SafeHouse aseg.h). The class names are kept short on purpose: they name the local
// vtables (_vt$2C0..) that the link check compares, so they stay as they are.
struct C0 : CBase { int a; virtual void F(); };             // kind 0: TRKGC, a constant {g}
struct C1 : CBase { int a, b; virtual void F(); };          // kind 1: TRKGK, keys {ckey, akey}
struct C2 : CBase { int a, b, c, d; virtual void F(); };    // kind 2: TRKGN (nothing loaded)
extern "C" CBase *PtrkgNew(int kind) asm("PtrkgNew__Fi");
// name: SafeHouse port (PtrkgNew)
CBase *PtrkgNew(int kind)
{
    switch (kind) {
    case 0: return new C0;
    case 1: return new C1;
    case 2: return new C2;
    }
    return 0;
}
