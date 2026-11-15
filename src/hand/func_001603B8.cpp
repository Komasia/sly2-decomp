struct ALLOCREQ { int cb; int nKind; };
class CBinaryInputStream {
public:
    int S8Read();
    int S16Read();
};
struct ALOLINK;
struct LOX { char pad[0xA8]; ALOLINK *palolink; };   /* the linked object's record */
/* field: SafeHouse port (lo.h ALOLINK): plo follows ploTarget in world space */
struct ALOLINK { LOX *ploTarget; LOX *plo; int fPosition; int fRotation; };
extern LOX D_002C44F0;   /* the default target (no object found) */
class LOBase {
public:
    int a, b, c;
#define V(n) virtual void V##n();
    V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10)
    V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20)
    V(21) V(22) V(23) V(24) V(25) V(26) V(27) V(28) V(29) V(30)
    V(31) V(32) V(33) V(34) V(35) V(36) V(37) V(38) V(39) V(40)
    V(41) V(42) V(43) V(44) V(45) V(46) V(47) V(48) V(49) V(50)
#undef V
    virtual LOX *PloFind(int oid);
};
extern "C" void *PvAllocSwClearImpl(ALLOCREQ *preq) asm("PvAllocSwClearImpl__Fi");
extern "C" void SetXfMode(LOBase *palo, LOX *plo, int xfm) asm("SetXfMode__FP3ALOP2XFi");
// name: SafeHouse port (LoadAloLinksFromBrx)
/* LoadAloLinksFromBrx: load an object's links: per link the target and the linked object (found by oid from the
 * object), whether the position / rotation follow; the linked object's transform mode becomes 15 (UpdateXfLink). */
extern "C" void LoadAloLinksFromBrx__FP3ALOP18CBinaryInputStream(LOBase *palo, CBinaryInputStream *pbis)
{
    int clink = pbis->S8Read();
    for (int i = 0; i < clink; i++) {
        ALLOCREQ req;
        req.cb = 0x10;
        req.nKind = 0x10;
        ALOLINK *palolink = (ALOLINK *)PvAllocSwClearImpl(&req);
        palolink->ploTarget = palo->PloFind(pbis->S16Read());
        if (!palolink->ploTarget)
            palolink->ploTarget = &D_002C44F0;
        palolink->plo = palo->PloFind(pbis->S16Read());
        palolink->fPosition = pbis->S8Read();
        palolink->fRotation = pbis->S8Read();
        palolink->plo->palolink = palolink;
        SetXfMode(palo, palolink->plo, 0xF);   /* XFM_Link */
    }
}
