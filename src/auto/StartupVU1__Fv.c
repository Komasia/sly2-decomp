#include "m2c_prelude.h"
M2C_UNK FlushCache(M2C_UNK);                        /* extern */
M2C_UNK func_00241728(s32 *, M2C_UNK *);            /* extern */
M2C_UNK func_002417F0(s32 *, M2C_UNK, M2C_UNK);     /* extern */
extern M2C_UNK D_0025E050;
extern s32 *g_pdcVif1;

void StartupVU1__Fv(void) {
    *g_pdcVif1 |= 0x40;
    FlushCache(0);
    func_00241728(g_pdcVif1, &D_0025E050);
    func_002417F0(g_pdcVif1, 0, 0);
    *g_pdcVif1 &= ~0x40;
}
