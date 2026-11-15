/* class: progress (SafeHouse menu.cpp ResetSlotKeepSettings: "the record has the layout's identity (0x1D7D30)"):
 * does the save carry this layout's identity (its last record's ib and the records' byte sum)? */
#include "h3_progress.h"
/* the layout's trie records as bytes */
#define PbRecords(playout) ((unsigned char *)(playout)->aent)
static inline int Sum(unsigned char *pb, unsigned int cb) { int sum = 0; while (cb) { sum += *pb++; cb--; } return sum; }

int func_001D7D30(LAYOUT *playout, GAMESAVE *pgamesave)
{
    int sum = Sum(PbRecords(playout), playout->cent * 10);
    return *(unsigned short *)(PbRecords(playout) + playout->cent * 10 - 6) == pgamesave->nLayout && sum == pgamesave->sumLayout;
}
