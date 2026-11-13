/* DequeueLoRoot: an object root taken off the world's queue of roots (the DL at SW +0x20); when the queue walk's
 * stop point (+0x39A4) is that root, it moves on to the next. Source: SafeHouse port (activate.cpp). */
struct DL;
struct LO {
    /* 0x00 */ char pad0[4];
    /* 0x04 */ struct LO *pnext;    /* the queue's DL link */
};
struct SW {
    /* 0x0000 */ char pad0[0x20];
    /* 0x0020 */ char dlRoot[0x39a4 - 0x20];   /* SafeHouse: lsplo20, the queued roots */
    /* 0x39a4 */ struct LO *ploStop;           /* field: SafeHouse port */
};
int FFindDlEntry__FP2DLPv(void *pdl, void *pv);
void RemoveDlEntry__FP2DLPv(void *pdl, void *pv);

// name: SafeHouse port (DequeueLoRoot)
void DequeueLoRoot__FP2SWP2LO(struct SW *psw, struct LO *plo)
{
    void *pdl = psw->dlRoot;
    if (FFindDlEntry__FP2DLPv(pdl, plo)) {
        if (psw->ploStop == plo)
            psw->ploStop = plo->pnext;
        RemoveDlEntry__FP2DLPv(pdl, plo);
    }
}
