#include "m2c_prelude.h"
M2C_UNK AddDmaCnt__4DMAS();                         /* extern */
M2C_UNK AddVifBaseOffset__4VIFSii(s32, M2C_UNK, M2C_UNK); /* extern */
M2C_UNK AddVifFlusha__4VIFS(s32);                   /* extern */
M2C_UNK EndDmaCnt__4DMAS(s32);                      /* extern */

void func_001681B0(s32 arg0) {
    AddDmaCnt__4DMAS();
    AddVifFlusha__4VIFS(arg0);
    AddVifBaseOffset__4VIFSii(arg0, 0x32, 0x1E7);
    EndDmaCnt__4DMAS(arg0);
}
