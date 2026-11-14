/* libsif RPC (called by _request_end and sceSifBindRpc): a client's request finished - its +0x18 cleared and bit 0 of
 * its +0x10 flags (busy) dropped. */
typedef struct RPCCLIENT {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ unsigned int grf;
    /* 0x14 */ int n14;
    /* 0x18 */ int n18;
} RPCCLIENT;

void func_00236CD0(RPCCLIENT *pcd)
{
    pcd->n18 = 0;
    pcd->grf &= ~1;
}
