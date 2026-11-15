/* class: SW, the activation pass's re-queue (SafeHouse activate.cpp UpdateSwActivation's moveToEnd, "orig
 * 0x147EE8"): a root node moved to the end of the world's queue of roots to check (SW +0x20); the first one moved
 * becomes the pass's stop point (+0x39A4), so a pass ends where the moved nodes begin. */
void RemoveDlEntry__FP2DLPv(void *pdl, int pnode);
void AppendDlEntry__FP2DLPv(void *pdl, int pnode);
struct SW {
    /* 0x0000 */ char pad[0x20];
    /* 0x0020 */ char dlQueued[0x39A4 - 0x20];   /* the queued roots (SafeHouse lsplo20; a DL) */
    /* 0x39a4 */ int pnodeStop;                  /* field: SafeHouse port (ploStop) */
};
void func_00147EE8(struct SW *psw, int pnode)
{
    RemoveDlEntry__FP2DLPv(psw->dlQueued, pnode);
    if (psw->pnodeStop == 0) psw->pnodeStop = pnode;
    AppendDlEntry__FP2DLPv(psw->dlQueued, pnode);
}
