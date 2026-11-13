/* PvAllocStackImpl (Sly 1 memory.c): a block from the stack heap, which grows down from s_pvStackMin: the size
 * rounded up to 16 bytes, then the address aligned down (Sly 2 takes the size and the alignment in a record; a size
 * of 0 gives null). */
struct STACKREQ {
    /* 0x0 */ int cb;
    /* 0x4 */ int cbAlign;   /* a power of two */
};
extern int s_pvStackMin;
void CheckForOutOfMemory__Fv(int cb);

// name: Sly 1 (PvAllocStackImpl)
int PvAllocStackImpl__Fi(struct STACKREQ *preq)
{
    int cb = preq->cb;
    int pv = 0;
    if (cb != 0) {
        CheckForOutOfMemory__Fv(cb);
        pv = (s_pvStackMin - ((preq->cb + 0xF) & ~0xF)) & -preq->cbAlign;
        s_pvStackMin = pv;
    }
    return pv;
}
