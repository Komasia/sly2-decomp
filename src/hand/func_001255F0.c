/* A splice built-in (SafeHouse gamebif.cpp: 135 / 136, the AND / OR of a list of ints, 0x1255F0 / 0x125640): the AND
 * of the list's ints, as an int CRef (tag 0x15). */
struct CPAIR {
    /* 0x00 */ char pad0[0xc];
    /* 0x0c */ int n;            /* the element's int */
    /* 0x10 */ struct CPAIR *ppairNext;
};
struct CREF {
    /* 0x0 */ int tagk;
    /* 0x4 */ union { int n; struct CPAIR *ppair; } u;
};

struct CREF *func_001255F0(struct CREF *prefResult, void *pframe, struct CREF *preflist)
{
    int n = -1;
    struct CPAIR *ppair = 0;
    if (preflist->tagk != 0) {
        ppair = preflist->u.ppair;
    }
    for (; ppair != 0; ppair = ppair->ppairNext) {
        n &= ppair->n;
    }
    prefResult->u.n = n;
    prefResult->tagk = 0x15;
    return prefResult;
}
