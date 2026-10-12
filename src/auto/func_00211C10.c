#include "m2c_prelude.h"
M2C_UNK AddDmaCnt__4DMAS();                         /* extern */
M2C_UNK AddVifFlusha__4VIFS(s32);                   /* extern */
M2C_UNK AddVifMscal__4VIFSPv(s32, M2C_UNK *);       /* extern */
M2C_UNK EndDmaCnt__4DMAS(s32);                      /* extern */
extern M2C_UNK D_C0;

void func_00211C10(s32 arg0) {
    AddDmaCnt__4DMAS();
    AddVifMscal__4VIFSPv(arg0, &D_C0);
    AddVifFlusha__4VIFS(arg0);
    EndDmaCnt__4DMAS(arg0);
}
