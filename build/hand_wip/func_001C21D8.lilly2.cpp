// func_001C21D8 near-miss (lilly2, from w5lane10 v3): 19/321 positional, aligned 7, frame 0x140, every home at the target offset.
// PROBE, not promotable as is: the target has an unreferenced 1-byte object at sp+0x30 (all SImode homes are +4 from w5lane10's
// draft). A named empty-class local with inline ctor/dtor declared after dlClosed reproduces it (empty classes are QImode, 1-byte
// slot at their declaration, never written). What the real object is remains unknown (team policy rejects slot-only objects).
// Remaining aligned 7 = the two sched ties in notes/190000-1F0000_lanes.md (w5lane10): init block (asm "=r,m" MEM output gives
// the pnavStart->index load an extra sched1 anti dependent) and goal block (posGoal reload has 3 dependents vs pnavDest's 2).
typedef int qword __attribute__((mode(TI)));
struct MSG { int cb; int nKind; };
struct DL { void *pvFirst; void *pvLast; int ibDle; };
struct NAV { char pad[0x124]; int index; };
struct EDGE { char pad[0x128]; NAV *pnavDest; int pad12C; qword posBegin; qword posEnd; };
struct ADJ { int cedge; int *aiedge; };
struct GRAPH { char pad[0x10]; int cnav; char pad14[8]; ADJ *aadj; int cedge; EDGE **apedge; };
struct NODE { NAV *pnav; EDGE *pedge; NODE *pnodeParent; float gCost; union { float gEstimate; int nEstimate; }; int state; NODE *pnodeNext; NODE *pnodePrev; };

extern "C" {
void *func_001AE478(void *pframe);
void func_001AE4A0(void *pframe, int n);
void *func_001AE378(MSG *pmsg);
void *func_001AE318(MSG *pmsg);
void *func_002333B4(void *pv, int b, unsigned int cb);
qword func_001A62E8(void *pv);
NAV *func_001C0D70(qword pos, int f);
void func_0011A200(DL *pdl);
void func_0011A1F8(DL *pdl, int ibDle);
void func_0011A220(DL *pdl, void *pv);
void func_0011A2E8(DL *pdl, void *pv);
void func_0011A280(DL *pdl, void *pvNext, void *pv);
int func_0011A3B0(DL *pdl);
int func_001C26E0(GRAPH *pgraph, EDGE *pedge, void *pvActor);
int func_001C0920(NAV *pnav, qword pos, int f);
}

static inline void *PvAllocClear(int cb) { MSG msg; msg.cb = cb; msg.nKind = 0x10; return func_001AE378(&msg); }
static inline void *PvAlloc(int cb) { MSG msg; msg.cb = cb; msg.nKind = 0x10; return func_001AE318(&msg); }
// The current stack-allocation scope (out of line: 0x1AE478 / 0x1AE4A0)
struct STACKSCOPE { STACKSCOPE(); ~STACKSCOPE(); };
static inline qword QwSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword QwLength(qword v)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(qw), "=j"(vfOne) : "j"(v), "j"(v));

    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
    return qw;
}
// Unknown empty object at sp+0x30 (see the header comment)
struct EMPTY { EMPTY() {} ~EMPTY() {} };
static inline NAV *PnavFind(const qword &pos) { return func_001C0D70(pos, 0); }
static inline void AppendNode(DL *pdl, NODE *pnode) { func_0011A220(pdl, pnode); }
static inline void RemoveNode(DL *pdl, NODE *pnode) { func_0011A2E8(pdl, pnode); }
static inline void InsertNode(DL *pdl, NODE *pnodeNext, NODE *pnode) { func_0011A280(pdl, pnodeNext, pnode); }
static inline float GFromQw(qword qw) { float g; __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(qw)); return g; }
static inline int NFromQw(qword qw) { int n; __asm__("qmfc2.ni %0, %1" : "=r"(n) : "j"(qw)); return n; }
static inline float GDist(const qword &a, const qword &b) { return GFromQw(QwLength(QwSub(a, b))); }
static inline float GFromQwM(qword qw) { float g; __asm__("qmfc2.ni %0, %1" : "=r,m"(g) : "j,!r"(qw)); return g; }
static inline int NDist(const qword &a, const qword &b) { return NFromQw(QwLength(QwSub(a, b))); }

extern "C" int func_001C21D8(GRAPH *pgraph, void *pvActor, qword posGoal, int fExact, int cpedgeMax, EDGE **apedge)
{
    STACKSCOPE scope;
    NODE *anode;
    int *afAllowed;
    anode = (NODE *)PvAllocClear(pgraph->cnav * sizeof(NODE));
    afAllowed = (int *)PvAlloc(pgraph->cedge * sizeof(int));
    func_002333B4(afAllowed, 0xFF, pgraph->cedge * sizeof(int));
    qword posStart = func_001A62E8(pvActor);
    NAV *pnavStart = PnavFind(posStart);
    NAV *pnavGoal = PnavFind(posGoal);

    if (!pnavStart || !pnavGoal) {
        return 0;
    }
    DL dlOpen;
    DL dlClosed;
    func_0011A200(&dlOpen);
    func_0011A1F8(&dlOpen, 0x18);
    func_0011A200(&dlClosed);
    func_0011A1F8(&dlClosed, 0x18);
    EMPTY e;
    NODE *pnode = &anode[pnavStart->index];
    pnode->pnav = pnavStart;
    pnode->gEstimate = GFromQwM(QwLength(QwSub(posStart, posGoal)));


    pnode->state = 2;
    AppendNode(&dlOpen, pnode);
    while (!func_0011A3B0(&dlOpen)) {
        pnode = (NODE *)dlOpen.pvFirst;
        if (fExact) {
            if (pnode->pnav == pnavGoal)
                break;
        } else if (func_001C0920(pnode->pnav, posGoal, 1)) {
            break;
        }
        RemoveNode(&dlOpen, pnode);
        pnode->state = 1;
        AppendNode(&dlClosed, pnode);
        qword posFrom;
        if (pnode->pedge)
            posFrom = pnode->pedge->posEnd;
        else
            posFrom = posStart;
        ADJ *padj = &pgraph->aadj[pnode->pnav->index];
        for (int i = 0; i < padj->cedge; i++) {
            int iedge = padj->aiedge[i];
            EDGE *pedge = pgraph->apedge[iedge];
            if (afAllowed[iedge] == -1)
                afAllowed[iedge] = func_001C26E0(pgraph, pedge, pvActor);
            if (!afAllowed[iedge])
                continue;

            float gDist = GDist(posFrom, pedge->posBegin) + GDist(pedge->posBegin, pedge->posEnd);
            NAV *pnavDest = pedge->pnavDest;
            float gCost = pnode->gCost + gDist;
            NODE *pnodeDest = &anode[pnavDest->index];
            float gEstimate = gCost + GDist(pedge->posEnd, posGoal);
            if (pnodeDest->state && pnodeDest->gEstimate <= gEstimate)
                continue;
            switch (pnodeDest->state) {
            case 0:
                break;
            case 1:
                RemoveNode(&dlClosed, pnodeDest);
                break;
            case 2:
                RemoveNode(&dlOpen, pnodeDest);
                break;
            }
            pnodeDest->pnav = pnavDest;
            pnodeDest->pedge = pedge;
            pnodeDest->gCost = gCost;
            pnodeDest->pnodeParent = pnode;
            pnodeDest->gEstimate = gEstimate;
            pnodeDest->state = 2;
            NODE *pnodeNext;
            for (pnodeNext = (NODE *)dlOpen.pvFirst; pnodeNext; pnodeNext = pnodeNext->pnodeNext) {
                if (pnodeNext->gEstimate > pnodeDest->gEstimate)
                    break;
            }
            InsertNode(&dlOpen, pnodeNext, pnodeDest);
        }
    }
    int c = 0;
    if (!func_0011A3B0(&dlOpen)) {
        if (!fExact && !pnode->pnodeParent) {
            apedge[0] = 0;
            c = 1;
        } else {
            int cpedge = 0;
            NODE *pnodeT;
            for (NODE *pnodeCount = pnode; pnodeCount->pnodeParent; pnodeCount = pnodeCount->pnodeParent)
                cpedge++;
            if (cpedge < cpedgeMax)
                c = cpedge;
            else
                c = cpedgeMax;
            for (pnodeT = pnode; pnodeT->pnodeParent; pnodeT = pnodeT->pnodeParent) {
                if (cpedge <= cpedgeMax)
                    apedge[cpedge - 1] = pnodeT->pedge;
                cpedge--;
            }
        }
    }
    return c;
}
