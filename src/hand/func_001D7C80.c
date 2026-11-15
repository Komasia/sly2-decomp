/* ValidateGameSave (SafeHouse savedata.cpp, orig 0x1D7C80): a save made for another progress layout is cleared:
 * unless it carries the layout's identity (its last record's ib and the records' byte sum), the values are zeroed
 * and the save is stamped with this layout's identity. */
#include "h3_progress.h"
void *s1_memset(void *pv, int b, int cb) asm("memset");
/* the layout's trie records as bytes */
#define PbRecords(playout) ((unsigned char *)(playout)->aent)
static inline int Sum(unsigned char *pb, unsigned int cb) { int sum = 0; while (cb) { sum += *pb++; cb--; } return sum; }

// name: SafeHouse port (ValidateGameSave)
void ValidateGameSave__FPvT0(LAYOUT *playout, GAMESAVE *pgamesave)
{
    int sum = Sum(PbRecords(playout), playout->cent * 10);
    int nLayout = *(unsigned short *)(PbRecords(playout) + playout->cent * 10 - 6);
    if (nLayout == pgamesave->nLayout && sum == pgamesave->sumLayout)
        return;
    s1_memset(pgamesave, 0, CB_GAMESAVEVALUES);
    pgamesave->nLayout = nLayout;
    pgamesave->sumLayout = sum;
}
