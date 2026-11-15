// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* CPair live list: push `ppair` onto the front of the list `*pppairHead`. Links are stored compactly as a
   13-bit slot index plus a 2-bit pool page; a null pointer encodes as (0, 0). */
typedef struct PAIRNODE {
    int cref;
    unsigned iPrev : 13;
    unsigned ipagePrev : 2;
    unsigned p1 : 1;
    unsigned iNext : 13;
    unsigned ipageNext : 2;
    unsigned fMark : 1;          /* gc mark */
    char pad[0x14 - 8];
} PAIRNODE;
extern PAIRNODE *D_00452098[4];  /* pair pool pages, 0x2000 slots each */
extern unsigned int D_002DD284;  /* pages in use */

/* slot index and page of `ppair` */
static inline void Handle(PAIRNODE *ppair, int *pi, int *pipage)
{
    unsigned int ipage;
    for (ipage = 0; ipage < D_002DD284; ipage++) {
        if (ppair >= D_00452098[ipage] && ppair < D_00452098[ipage] + 0x2000) {
            *pi = ppair - D_00452098[ipage];
            *pipage = ipage;
            return;
        }
    }
    *pi = 0;
    *pipage = 0;
}

void func_00254F00(PAIRNODE *ppair, PAIRNODE **pppairHead)
{
    int iSelf, ipageSelf, iHead, ipageHead;
    PAIRNODE *ppairHead;
    Handle(ppair, &iSelf, &ipageSelf);
    ppairHead = *pppairHead;
    if (ppairHead) {
        ppairHead->iPrev = iSelf;
        ppairHead->ipagePrev = ipageSelf;
    }
    Handle(*pppairHead, &iHead, &ipageHead);
    ppair->iNext = iHead;
    ppair->ipageNext = ipageHead;
    *pppairHead = ppair;
}
