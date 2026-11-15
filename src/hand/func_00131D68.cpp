// CTRLASEG::Query: a position channel's controller predicts its record's value / velocity dt seconds on: the
// ASEGA's time moved by dt at its speed and wrapped, then the track's Eval (TRKP vt slot 3); without a track, the
// base CTRL::Query. Layout: SafeHouse port (xf.h CTRLASEG, asega.h ASEGA, aseg.h TRKP).
class TRKP {
public:
    virtual void Load();
    virtual void Setup();
    virtual void Eval(int ppos, int pvel, float g, float dtScale);
};
struct ASEGA { char pad[0x1c]; float t; char pad2[0x40 - 0x20]; float svt; };   // field: SafeHouse port
struct CTRLASEG { int pad[7]; TRKP *ptrkp; int ptrkg; ASEGA *pasega; };   // field: SafeHouse port
extern "C" void FWrapAsegaTime(ASEGA *, float *, float *) asm("FWrapAsegaTime__FP5ASEGAPfT1");
extern "C" void Query(CTRLASEG *, int, int) asm("Query__4CTRLP7VECTOR4T1f");
// name: SafeHouse port (CTRLASEG::Query)
extern "C" void Query__8CTRLASEGP7VECTOR4T1f(CTRLASEG *pctrl, int ppos, int pvel, float dt)
{
    if (pctrl->ptrkp) {
        ASEGA *pasega = pctrl->pasega;
        float t, svt;
        svt = pasega->svt;
        t = pasega->t + dt * svt;
        FWrapAsegaTime(pasega, &t, &svt);
        pctrl->ptrkp->Eval(ppos, pvel, t, svt);
    } else {
        Query(pctrl, ppos, pvel);
    }
}
