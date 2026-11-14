/* class: PROXY (the inverse of 0x1CA930): the pool +0xE0's row of index i (0x50 bytes each from +0x68, the pool's
 * first index +0xC). */
struct PROXYROW {
    /* 0x00 */ char ab[0x50];
};
struct PROXYPOOL {
    /* 0x00 */ char pad0[0xc];
    /* 0x0c */ int irowFirst;
    /* 0x10 */ char pad10[0x68 - 0x10];
    /* 0x68 */ struct PROXYROW *arow;
};
struct PROXY {
    /* 0x00 */ char pad0[0xe0];
    /* 0xe0 */ struct PROXYPOOL *ppool;
};

struct PROXYROW *func_001CA958(struct PROXY *pproxy, int irow)
{
    struct PROXYPOOL *ppool = pproxy->ppool;
    return &ppool->arow[irow - ppool->irowFirst];
}
