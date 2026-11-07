typedef int qword __attribute__((mode(TI)));
struct LO { char pad0[0x70]; qword pos; };
struct FILTER;
struct NODE { NODE *pnodeLeft, *pnodeRight; qword *pplane; };
struct CONTACT;
struct WORLD;
// one collision shape of an object
struct SHAPE {
    LO *plo;                        // 0x00
    FILTER *pfilter;                // 0x04
    float sRadius;                  // 0x08
    int unk0C;
    unsigned long grf;              // 0x10
    int grfFilter;                  // 0x18
    int iFirst;                     // 0x1C
    char pad20[0x40];
    SHAPE *pshapeNext;              // 0x60
    char pad64[8];
    int cnodeMax;                   // 0x6C
    char pad70[4];
    NODE *pnodeRoot;                // 0x74
    int c;                          // 0x78
    char pad7C[0x2C];
    int genOld, gen;                // 0xA8, 0xAC
};
struct SO {
    char pad0[0x20];
    qword pos;                      // 0x20
    float sRadius;                  // 0x30
    SHAPE *pshapeFirst;             // 0x34
    char pad38[0x34];
    CONTACT *pcontactFirst;         // 0x6C
    unsigned long grf;              // 0x70
};
struct STACKSCOPE { STACKSCOPE(); ~STACKSCOPE(); };
// ach[2] is never touched; it only places the scope at sp+2 (target `addiu v0,sp,2`), the same shape as the
// accepted src/hand/ForgetGuardsInteract.cpp (struct { char c; FRAME frame; int i, j; }). Judgment call: see notes/1A0000.md (T1866).
struct SCOPE2 { char ach[2]; STACKSCOPE scope; };
struct CNODE { int c; };
struct ALLOCREQ { int cb, cbAlign; ALLOCREQ(int c, int a) { cb = c; cbAlign = a; } };
extern NODE D_002BBB20;
extern "C" {
void *PvAllocStackImpl(const ALLOCREQ &req) asm("PvAllocStackImpl__Fi");
int func_00118A88(NODE *pnode, int cnodeMax, qword pos, float sRadius, int *pcnode, NODE **ppnode);
int PaloXpFilter(FILTER *pfilter, int grf) asm("PaloXpFilter__FP3ALOUi");
void MarkSweptVertices(WORLD *pworld, SHAPE *pshape, SHAPE *pshapeOther, CONTACT **ppcontact) asm("MarkSweptVertices__FP3SOET0PP2XPPv");
void MarkSphereSphere(WORLD *pworld, SHAPE *pshape, SHAPE *pshapeOther, CONTACT **ppcontact) asm("MarkSphereSphere__FP3SOET0PP2XPPP7CONTACT");
void MarkSphereBsp(WORLD *pworld, SHAPE *pshape, SHAPE *pshapeOther, int cnode, NODE *pnode, CONTACT **ppcontact) asm("MarkSphereBsp__FP3SOET0PviPP2XPPP7CONTACT");
void MarkBspBsp(WORLD *pworld, SHAPE *pshape, SHAPE *pshapeOther, int cnode, NODE *pnode, NODE *pnodeLast, CONTACT **ppcontact) asm("MarkBspBsp__FP3SOET0P5SHAPEiP6BSPSELPP2XPPP7CONTACT");
void PrependXpList(WORLD *pworld, CONTACT *pcontact, CONTACT **ppcontact) asm("PrependXpList__FP2XPPP2XPPv");
CONTACT *PxpCloneList(WORLD *pworld, CONTACT *pcontact) asm("PxpCloneList__FP2XPPv");
void MarkOwnContacts(WORLD *pworld, SO *pso, SO *psoOther, SHAPE *pshape, int cnodeMax, NODE *pnode, NODE *pnodeRoot, CONTACT **ppcontact) asm("MarkOwnContacts__FP3OXAT0P3SOEPP2XPiPvN25");
}
static inline float LengthSq(qword v)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("qmfc2.ni %0,%1" : "=r"(g) : "j"(d));
    return g;
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline int NMin(int a, int b) { return (a < b) ? a : b; }
#define SHAPE_FILTERED (1UL << 48)
#define SHAPE_SPHERE (1UL << 49)

// name: SafeHouse port (PxpMarkOxaContacts)
extern "C" CONTACT *PxpMarkOxaContacts__FP3OXAT0P2SO(WORLD *pworld, SO *psoSmall, SO *psoLarge)
{
    CONTACT *pcontactFirst = 0;
    SO *psoT = psoSmall;
    if (psoSmall->sRadius > psoLarge->sRadius) {
        psoSmall = psoLarge;
        psoLarge = psoT;
    }
    int cnodeMax = 0;
    SHAPE *pshape;
    SHAPE *pshapeOther;
    for (pshape = psoLarge->pshapeFirst; pshape; pshape = pshape->pshapeNext)
        if (cnodeMax < pshape->cnodeMax)
            cnodeMax = pshape->cnodeMax;
    SCOPE2 stackscope;
    cnodeMax = NMin(cnodeMax, 0x1555);
    NODE *anode = (NODE *)PvAllocStackImpl(ALLOCREQ(cnodeMax * sizeof(NODE), 0x10));
    for (pshape = psoLarge->pshapeFirst; pshape; pshape = pshape->pshapeNext) {
        int fFilter = pshape->grfFilter != 0;
        if ((pshape->grf & SHAPE_FILTERED) && !fFilter)
            continue;
        NODE *pnodeFirst;
        int cnode;
        NODE *pnodeLast;
        int status = 2;
        if ((pshape->grf & SHAPE_SPHERE) || (psoSmall->grf & 0x20)) {
            pnodeLast = 0;
            pnodeFirst = 0;
            cnode = 0;
        } else {
            CNODE query;
            query.c = cnodeMax;
            pnodeLast = anode;
            pnodeFirst = anode;
            status = func_00118A88(pshape->pnodeRoot, 0x7FFFFFFF, psoSmall->pos, psoSmall->sRadius, &query.c, &pnodeLast);
            if (status == 1)
                continue;
            if (status == 0) {
                cnode = 0;
                pnodeLast = &D_002BBB20;
                pnodeFirst = &D_002BBB20;
            } else {
                cnode = pnodeLast - pnodeFirst;
                pnodeLast--;
            }
        }
        for (pshapeOther = psoSmall->pshapeFirst; pshapeOther; pshapeOther = pshapeOther->pshapeNext) {
            int fFilterOther = pshapeOther->grfFilter != 0;
            if ((pshapeOther->grf & SHAPE_FILTERED) && !fFilterOther)
                continue;
            if ((pshape->grf & SHAPE_FILTERED) && (pshapeOther->grf & SHAPE_FILTERED))
                continue;
            CONTACT *pcontactTemp = 0;
            CONTACT **ppcontact = &pcontactFirst;
            if (fFilter) {
                int fMatch = PaloXpFilter(pshapeOther->pfilter, pshape->grfFilter) != 0;
                if (pshape->grf & SHAPE_FILTERED) {
                    if (!fMatch)
                        continue;
                    ppcontact = &pcontactTemp;
                } else if (fMatch) {
                    if (!(pshapeOther->grf & SHAPE_FILTERED))
                        ppcontact = &pcontactTemp;
                }
            }
            if (fFilterOther) {
                int fMatch = PaloXpFilter(pshape->pfilter, pshapeOther->grfFilter) != 0;
                if (pshapeOther->grf & SHAPE_FILTERED) {
                    if (!fMatch)
                        continue;
                    ppcontact = &pcontactTemp;
                } else if (fMatch && !(pshape->grf & SHAPE_FILTERED)) {
                    ppcontact = &pcontactTemp;
                }
            }
            CONTACT *pcontactPrev = *ppcontact;
            if (pshapeOther->gen != pshapeOther->genOld || pshape->gen != pshape->genOld) {
                if (pshapeOther->iFirst < pshapeOther->c)
                    MarkSweptVertices(pworld, pshapeOther, pshape, ppcontact);
                if (pshape->iFirst < pshape->c)
                    MarkSweptVertices(pworld, pshape, pshapeOther, ppcontact);
            }
            if (*ppcontact == pcontactPrev) {
                if (pshape->grf & SHAPE_SPHERE) {
                    if (pshapeOther->grf & SHAPE_SPHERE)
                        MarkSphereSphere(pworld, pshapeOther, pshape, ppcontact);
                    else
                        MarkSphereBsp(pworld, pshape, pshapeOther, 0, 0, ppcontact);
                } else if (pshapeOther->grf & SHAPE_SPHERE) {
                    int fFar = 0;
                    if (!status || 1.0f < LengthSq(Sub(pshape->plo->pos, psoSmall->pos)) ||
                        1.0f < __builtin_fabsf(pshape->sRadius - psoSmall->sRadius))
                        fFar = 1;
                    MarkSphereBsp(pworld, pshapeOther, pshape, fFar ? 0 : cnode, fFar ? 0 : pnodeFirst, ppcontact);
                } else {
                    MarkBspBsp(pworld, pshapeOther, pshape, cnode, pnodeFirst, pnodeLast, ppcontact);
                }
            }
            if (pcontactTemp) {
                int fCopied = 0;
                if (fFilter) {
                    if (pshape->grf & SHAPE_FILTERED)
                        PrependXpList(pworld, pcontactTemp, &psoLarge->pcontactFirst);
                    else if (!(pshapeOther->grf & SHAPE_FILTERED)) {
                        fCopied = 1;
                        PrependXpList(pworld, PxpCloneList(pworld, pcontactTemp), &psoLarge->pcontactFirst);
                    }
                }
                if (fFilterOther) {
                    if (pshapeOther->grf & SHAPE_FILTERED)
                        PrependXpList(pworld, pcontactTemp, &psoSmall->pcontactFirst);
                    else if (!(pshape->grf & SHAPE_FILTERED)) {
                        fCopied = 1;
                        PrependXpList(pworld, PxpCloneList(pworld, pcontactTemp), &psoSmall->pcontactFirst);
                    }
                }
                if (fCopied)
                    PrependXpList(pworld, pcontactTemp, &pcontactFirst);
            }
        }
        if (!(pshape->grf & SHAPE_FILTERED))
            MarkOwnContacts(pworld, psoSmall, psoLarge, pshape, pshape->cnodeMax, pshape->pnodeRoot, pshape->pnodeRoot, &pcontactFirst);
    }
    for (pshapeOther = psoSmall->pshapeFirst; pshapeOther; pshapeOther = pshapeOther->pshapeNext)
        if (!(pshapeOther->grf & SHAPE_FILTERED))
            MarkOwnContacts(pworld, psoLarge, psoSmall, pshapeOther, pshapeOther->cnodeMax, pshapeOther->pnodeRoot, pshapeOther->pnodeRoot, &pcontactFirst);
    return pcontactFirst;
}
