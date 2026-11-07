#include "m2c_prelude.h"
M2C_UNK ReturnThrownBooty__FP2LO(void *, M2C_UNK);             /* extern */
M2C_UNK DropActorBooty__FP5ACTORii(s32);                         /* extern */
M2C_UNK UpdateSo__FP2SOf();                            /* extern */
extern f32 g_clock;
extern f32 D_003E1BFC;

// name: SafeHouse port (UpdateBooty)
void UpdateBooty__FP2LO(void *arg0) {
    s32 temp_v1;

    UpdateSo__FP2SOf();
    temp_v1 = M2C_FIELD(arg0, s32 *, 0x184);
    switch (temp_v1) {                              /* irregular */
    case 5:
        if ((g_clock - M2C_FIELD(arg0, f32 *, 0x188)) >= 5.0f) {
            ReturnThrownBooty__FP2LO(arg0, 0);
            return;
        }
        return;
    case 4:
        if ((M2C_FIELD(M2C_FIELD(arg0, void **, 0x158), s32 *, 0xC) != 0) && (g_clock >= D_003E1BFC)) {
            DropActorBooty__FP5ACTORii(M2C_FIELD(arg0, s32 *, 0x160));
        }
        break;
    }
}
