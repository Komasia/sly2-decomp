#include "m2c_prelude.h"
extern s128 D_002A2DD0;
extern M2C_UNK g_lmZeroOne;
extern M2C_UNK D_002D9BE0;
extern M2C_UNK D_002D9C70;
extern M2C_UNK D_002D9D00;
extern s32 D_002DD5BC;
extern M2C_UNK D_002DDFA0;
extern s32 D_002E1E40;
extern s32 D_002F7900;
extern M2C_UNK D_003DD040;
extern M2C_UNK D_003DD08C;
extern M2C_UNK g_sw;

// name: SafeHouse port (CSnd::Stop)
void Stop__4CSndf(s32 arg0, f32 fparg0) {
    M2C_FIELD(arg0, f32 *, 0x48) = fparg0;
    SetDirty__4CSndUiUi(arg0, 0x1FFF, 8);
}
