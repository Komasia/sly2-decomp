/* func_001A5D98 (0x1A5D98): runs the LO's deferred callbacks (its run list +0x34, newest first) in the order they
 * were added (oldest first), each with (plo, pv); at most 32. */
typedef struct LORUN { void (*pfn)(void *, void *); void *pv; struct LORUN *plorunNext; } LORUN;
struct S { char pad[0x34]; LORUN *plorunFirst; };
void func_001A5D98(struct S *plo)
{
    LORUN *aplorun[32];
    LORUN *plorun = plo->plorunFirst;
    int c;
    if (!plorun)
        return;
    c = 0;
    do { aplorun[c] = plorun; c++; plorun = plorun->plorunNext; } while (plorun);
    for (c--; c >= 0; c--) { plorun = aplorun[c]; plorun->pfn(plo, plorun->pv); }
}
