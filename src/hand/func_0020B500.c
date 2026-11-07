struct G;
extern struct G g_sw;
typedef struct ALLOCREQ { int cb; int nKind; } ALLOCREQ;
struct S { char pad[0x50]; int c; void **apv; };
void PostLoLoad__FP2LO(struct S *p);
int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(struct G *pg, int a, int b, int c, int cMax, void **apv);
void *PvAllocSwImpl__Fi(ALLOCREQ *preq);
// name: SafeHouse port (PostLoadGuardManager)
void PostLoadGuardManager__FP2LO(struct S *p)
{
    ALLOCREQ req;
    PostLoLoad__FP2LO(p);
    p->c = CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(&g_sw, 0x605, 0x38, 0, 0, 0);
    req.cb = p->c * 4;
    req.nKind = 0x10;
    p->apv = PvAllocSwImpl__Fi(&req);
    CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(&g_sw, 0x405, 0x38, 0, p->c, p->apv);
}
