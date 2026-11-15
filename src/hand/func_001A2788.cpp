/* FWaterSurfaceUnder (0x1A2788): the water's surface at the actor: collects the water's entries (CsoeCollect with the
 * filter 0x229D60) on the stack and clips the vertical segment from the actor's position + sWaterTop (+0x109C) down to
 * + sWaterBottom (+0x1098) against them; the first hit point is the surface (*ppos). SafeHouse damage.cpp. */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct FRAME { int a[4]; FRAME(); ~FRAME(); };
struct STACKREQ { int cb; int nKind; };  /* a stack allocation request */
struct LSG { qword pos; char pad[0x5F0]; };  /* the clipped segments (16 entries) */
struct O { char pad[0x1098]; float x1098; float x109C; };  /* ACTOR: +0x1098 / +0x109C the segment's ends below / above */
struct ALO { char pad[0xE0]; int csoe; };  /* the water: +0xE0 its entry count */
extern "C" {
extern qword g_vecZero asm("D_002A2DD0");
qword PosOfLo(void *p) asm("PosOfLo__FP2LO");
void *PvAllocStackImpl(STACKREQ *preq) asm("PvAllocStackImpl__Fi");
int CsoeCollect(ALO *palo, void *pfnFilter, int n, void *apsoe) asm("CsoeCollect__FP3ALOPvN21");
int CClipSegmentEntries(qword posA, qword posB, int csoe, void *apsoe, int clsgMax, LSG *alsg) asm("CClipSegmentEntries__FG9VU_VECTORT0iP3LSGiT3");
void func_00229D60(void);
int FWaterSurfaceUnder(O *pactor, ALO *pwater, qword *ppos) asm("FWaterSurfaceUnder__FP5ACTORP3ALOP6VECTOR");
}
// name: SafeHouse port (FWaterSurfaceUnder)
int FWaterSurfaceUnder(O *pactor, ALO *pwater, qword *ppos)
{
    U off, posBottom, posTop;
    LSG alsg;
    off.q = g_vecZero;
    {
        qword p = PosOfLo(pactor);
        qword d;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(p), "j"(off.q));
        posTop.q = d;
        posBottom.q = d;
    }
    posTop.f[2] += pactor->x109C;
    posBottom.f[2] += pactor->x1098;
    FRAME frame;
    STACKREQ req;
    STACKREQ *preq = &req;
    preq->cb = pwater->csoe * 4;
    preq->nKind = 0x10;
    void *apsoe = PvAllocStackImpl(preq);
    int csoe = CsoeCollect(pwater, (void *)func_00229D60, 0, apsoe);
    if (!CClipSegmentEntries(posTop.q, posBottom.q, csoe, apsoe, 0x10, &alsg))
        return 0;
    qword r;
    __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(alsg.pos), "j"(off.q));
    *ppos = r;
    return 1;
}
