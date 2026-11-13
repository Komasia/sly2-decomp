/* class: PROXY (SafeHouse activate.cpp: the proxy's pool row of an instance): the row's index in the pool +0xE0 (0x50
 * bytes from +0x68), plus the pool's first index +0xC. */
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

int func_001CA930(struct PROXY *pproxy, struct PROXYROW *prow)
{
    struct PROXYPOOL *ppool = pproxy->ppool;
    return (prow - ppool->arow) + ppool->irowFirst;
}
