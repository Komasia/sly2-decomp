/* LoadProgressFromBrx (SafeHouse savedata.h: the progress layout every world file carries): read the name table
 * (count, then per name its symbol and string) and the trie records (count, then count * 10 bytes) from the world
 * file into the layout, then validate the save against it (ValidateGameSave). */
#include "h3_progress.h"
struct MSG { int cb; int nKind; };
typedef struct BIS BIS;
extern char g_heapSw[];
extern GAMESAVE D_003D4A60;           /* g_gamesave */
int U16Read(BIS *pbis) asm("U16Read__18CBinaryInputStream");
void Read__18CBinaryInputStreamiPv(BIS *pbis, int cb, void *pv);
void func_00118380(BIS *pbis, char **ppchz, void *pheap, int n);   /* read a string into a heap */
void func_001D8600(NAMETABLE *pnametable, int cname);
void func_001D8690(NAMETABLE *pnametable, char *pchz, int sym);
void *PvAllocSwImpl__Fi(struct MSG *pmsg);
void ValidateGameSave__FPvT0(LAYOUT *playout, GAMESAVE *pgamesave);

// name: SafeHouse port (LoadProgressFromBrx)
void LoadProgressFromBrx__FP2SWP18CBinaryInputStream(LAYOUT *playout, BIS *pbis)
{
    struct MSG msg;
    char *pchz;
    int iname;
    int cname;
    int cent;
    cname = U16Read(pbis);
    func_001D8600(&playout->nametable, cname);
    for (iname = 0; iname < cname; iname++) {
        int sym = U16Read(pbis);
        func_00118380(pbis, &pchz, g_heapSw, 0x2D);
        func_001D8690(&playout->nametable, pchz, sym);
    }
    cent = U16Read(pbis);
    playout->cent = cent;
    msg.cb = cent * 10;
    msg.nKind = 0x10;
    playout->aent = PvAllocSwImpl__Fi(&msg);
    Read__18CBinaryInputStreamiPv(pbis, cent * 10, playout->aent);
    ValidateGameSave__FPvT0(playout, &D_003D4A60);
}
