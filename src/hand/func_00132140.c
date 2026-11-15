/* OverlapKindBarrier (vt slot 61): how the barrier overlaps palo: palo is listed when it is one of the barrier's
 * objects (by oid or alias) or derives from one of its classes; mode 0: 2 (collides) when listed, else 1 (passes);
 * mode 1 (+0x178): 3 (passes) when listed, else the ALO's own overlap kind. Layout: SafeHouse port (barrier.cpp). */
struct BARRIER {
    char pad[0x150];
    int coid; int aoid[4];      /* +0x150; field: SafeHouse port (EOPID 456) */
    int ccid; int acid[4];      /* +0x164; field: SafeHouse port (EOPID 457) */
    int fMode;                  /* +0x178; field: SafeHouse port (EOPID 458) */
};
int func_001A6290(void *plo, int oid);   /* the object's oid or alias is oid */
int FIsBasicDerivedFrom__FP5BASIC3CID(void *pbasic, int cid);
int OverlapKindAlo__FP3ALOT0(struct BARRIER *pbarrier, void *palo);
// name: SafeHouse port (OverlapKindBarrier)
int OverlapKindBarrier__FP3ALOT0(struct BARRIER *pbarrier, void *palo)
{
    int ioid, icid;
    int fListed;
    ioid = 0;
    fListed = 0;
    for (; ioid < pbarrier->coid; ioid++) {
        if (func_001A6290(palo, pbarrier->aoid[ioid]))
            fListed = 1;
    }
    for (icid = 0; icid < pbarrier->ccid; icid++) {
        if (FIsBasicDerivedFrom__FP5BASIC3CID(palo, pbarrier->acid[icid]))
            fListed = 1;
    }
    {
        int kind;
        if (pbarrier->fMode) {
            if (fListed)
                kind = 3;
            else
                kind = OverlapKindAlo__FP3ALOT0(pbarrier, palo);
        } else
            kind = fListed ? 2 : 1;
        return kind;
    }
}
