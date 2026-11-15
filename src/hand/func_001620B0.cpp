struct TASKOBJE { int oid; int oidOwner; int grfState; int iwrec; };   /* include/h2_task.h */
class LO {
public:
    int a, b, c;
    virtual void V1();
    virtual void V2();
    virtual void V3();
    virtual void V4();
    virtual void V5();
    virtual void V6();
    virtual void V7();
    virtual void V8();
    virtual void V9();
};
struct G;
extern G g_sw;
extern "C" int func_00161FC8(int nState);
extern "C" int func_00161FF0(int cnState, int *anState);
extern "C" int func_00210A88();   /* the world's index */
extern "C" void *PloFindSwNearest(G *psw, int grf, int oid, void *ploCtx) asm("PloFindSwNearest__FP2LO3OIDii");
/* ApplyTaskObjects: show the objects of a list for a state: each object in this state's group (4 / 5 the start /
 * end group, else states 0..3) and this world is added (vtable entry 8) when its states include the state, else
 * removed (entry 9). */
// name: SafeHouse port (ApplyTaskObjects)
extern "C" void ApplyTaskObjects__FPviiT0(void *pv, int nState, int cobje, TASKOBJE *aobje)
{
    int i;
    int grfState = func_00161FC8(nState);
    int grfAll;
    if (nState == 4 || nState == 5) {
        int anState[2] = { 4, 5 };
        grfAll = func_00161FF0(2, anState);
    } else {
        int anState[4] = { 0, 1, 2, 3 };
        grfAll = func_00161FF0(4, anState);
    }
    for (i = 0; i < cobje; i++) {
        TASKOBJE *pobje = &aobje[i];
        if (!(pobje->grfState & grfAll))
            continue;
        if (pobje->iwrec != -1 && pobje->iwrec != func_00210A88())
            continue;
        void *ploOwner = PloFindSwNearest(&g_sw, 5, pobje->oidOwner, 0);
        LO *plo = (LO *)PloFindSwNearest(&g_sw, ploOwner ? 4 : 5, pobje->oid, ploOwner);
        if (!plo)
            continue;
        if (pobje->grfState & grfState)
            plo->V8();   /* AddLo */
        else
            plo->V9();   /* RemoveLo */
    }
}
