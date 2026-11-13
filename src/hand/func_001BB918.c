/* class: the breakables (SafeHouse breakable.cpp: method 0x10C820 -> 0x1BB918, a trigger {class, on}; 8 at most). */
struct BRKTRIG {
    /* 0x0 */ int cid;
    /* 0x4 */ int fOn;
};
struct BREAKABLE {
    /* 0x000 */ char pad0[0x150];
    /* 0x150 */ int ctrig;
    /* 0x154 */ struct BRKTRIG *atrig;
};

struct BRKTRIG *func_001BB918(struct BREAKABLE *pbrk, int cid, int fOn)
{
    int i = pbrk->ctrig;
    /* (the result register first holds the room test, so a full list returns 0) */
    struct BRKTRIG *ptrig = (struct BRKTRIG *)(i < 8);
    if (ptrig != 0) {
        ptrig = &pbrk->atrig[i];
        pbrk->ctrig = i + 1;
        ptrig->fOn = fOn;
        ptrig->cid = cid;
    }
    return ptrig;
}
