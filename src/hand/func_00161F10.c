/* func_00161F10: append a checkpoint task entry {oid, state} to a list of at most cMax (0 when full). */
struct CHKTASK { int oid; int nState; };
int func_00161F10(int unused, struct CHKTASK *achktask, int cMax, int *pc, int oid, int nState)
{
    struct CHKTASK *pchktask;
    if (*pc < cMax) {
        pchktask = &achktask[(*pc)++];
        pchktask->oid = oid;
        pchktask->nState = nState;
        return 1;
    }
    return 0;
}
