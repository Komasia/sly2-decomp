/* an entry of the guard's kind table (0x20 bytes): a KINDE, then its state mask */
struct KINDEM { char pad[0x10]; long grfKind; char pad2[8]; };
struct GUARD { char pad[0x4C0]; int ckindem; char pad2[0xC]; struct KINDEM akindem[1]; };
long func_00207A20(int st);
int func_00209A28(long grfKind, long grfState);
/* PkindeBest (0x209AD0): the kind table entry that best fits the state mask: all of its states set, its states
 * including the lowest state of grfState, and the most states. */
// name: SafeHouse port (PkindeBest)
struct KINDEM *PkindeBest__FP5GUARDUl(struct GUARD *pguard, long grfState)
{
    int i;
    int st = 0;
    long grfLowest = 0;
    int cstBest = 0;
    struct KINDEM *pkindemBest = 0;
    struct KINDEM *pkindem;
    for (; st < 0x30; st++) {
        grfLowest = func_00207A20(st);
        if (grfState & grfLowest)
            break;
    }
    for (i = 0; i < pguard->ckindem; i++) {
        int cst;
        pkindem = &pguard->akindem[i];
        cst = func_00209A28(pkindem->grfKind, grfState);
        if (cst && (pkindem->grfKind & grfLowest) && cstBest < cst) {
            cstBest = cst;
            pkindemBest = pkindem;
        }
    }
    return pkindemBest;
}
