#include "so.h"
struct G { char pad[0x3EFC]; struct LO *plo3EFC; struct LO *plo3F00; };
struct CRef { int m_tagk; int m_tag; int pad[2]; };
struct LO *func_001C4A48(struct G *p);
int FIsBasicDerivedFrom__FP5BASIC3CID(struct LO *plo, int n);
struct CRef *SetProgressPoCurrent__FP4CRefPci(struct CRef *pret, struct CRef *pref, const char *s, int n);
void Decref(struct CRef *p) asm("Decref__4CRef");
void TrackJt__FP5ACTORP5JTENTiP10JTGRABCAND(struct G *p, int a, int b, int c);
void func_001C48C0(struct G *p);
#define VCALL(o, n, a) ((void (*)(void *, int))(o)->pvt[n].pfn)(VT_THIS((o), &(o)->pvt[n]), a)
// name: SafeHouse port (po.h SetPoCurrent, orig 0x1C4940; sets the progress oidPoCurrent)
void SetPoCurrent__FP2SWP2LO(struct G *p, struct LO *plo)
{
    struct LO *cur = func_001C4A48(p);
    struct LO *nw = p->plo3F00;
    if (!nw) nw = plo;
    if (cur != nw && cur) VCALL(cur, 78, 0);
    p->plo3EFC = plo;
    if (cur != nw && nw) VCALL(nw, 78, 1);
    if (plo && FIsBasicDerivedFrom__FP5BASIC3CID(plo, 0x34)) {
        struct CRef ret, ref;
        ref.m_tagk = 0x15;
        ref.m_tag = plo->oid;
        SetProgressPoCurrent__FP4CRefPci(&ret, &ref, "oidPoCurrent", 0);
        Decref(&ret);
        Decref(&ref);
    }
    TrackJt__FP5ACTORP5JTENTiP10JTGRABCAND(p, 0, 0, 0);
    func_001C48C0(p);
}
