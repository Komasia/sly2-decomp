/* CopyGameSaveForSlot (SafeHouse savedata.h, orig 0x1D84B0): the save as a memory card slot holds it - a copy of
 * g_gamesave with every "from_memcard" bool entry of the layout set. */
#include "h3_progress.h"
extern GAMESAVE D_003D4A60;           /* g_gamesave */
extern char D_002A78F8[];             /* "from_memcard" */
int SymFromName__FP6LAYOUTPc(NAMETABLE *pnametable, char *pchz);
static inline int NFind(LAYOUT *playout, char *pchz) { return SymFromName__FP6LAYOUTPc(&playout->nametable, pchz); }

// name: SafeHouse port (CopyGameSaveForSlot)
void CopyGameSaveForSlot__FP6LAYOUTP8GAMESAVE(LAYOUT *playout, GAMESAVE *pgamesave)
{
    int sym;
    int ient;
    *pgamesave = D_003D4A60;
    sym = NFind(playout, D_002A78F8);
    if (sym == -1)
        return;
    for (ient = 0; ient < playout->cent; ient++) {
        PENT *pent = &playout->aent[ient];
        if (pent->ch == sym)
            pgamesave->ab[pent->ib] = 1;
    }
}
