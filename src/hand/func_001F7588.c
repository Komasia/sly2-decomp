/* func_001F7588 (0x1F7588): SO virtual slot 74, FAbsorbSoWkr in Sly 1 (DPRIZE overrides this slot as Sly 1's
 * FAbsorbDprizeWkr does). The SO absorbs the shock wave when the WKR has any interaction flags. */
#include "so.h"

typedef struct WKR {
    /* 0x00 */ char unk_0x00[0x44];
    /* 0x44 */ int grfic;
} WKR;

int func_001F7588(SO *pso, WKR *pwkr)
{
    return pwkr->grfic != 0;
}
