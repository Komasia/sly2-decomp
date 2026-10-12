#include "m2c_prelude.h"
s32 FSpooling__18CBinaryAsyncStream(void *);        /* extern */
M2C_UNK FinishSpooling__18CBinaryAsyncStream(void *); /* extern */
M2C_UNK sceCdSync(M2C_UNK);                         /* extern */
M2C_UNK sceClose(s32);                              /* extern */

void Close__18CBinaryAsyncStream(void *arg0) {
    s32 temp_a0;
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0);
    switch (temp_v1) {                              /* irregular */
    case 0:
        temp_a0 = M2C_FIELD(arg0, s32 *, 4);
        if (temp_a0 >= 0) {
            sceClose(temp_a0);
        }
        M2C_FIELD(arg0, s32 *, 4) = -1;
        break;
    case 1:
        if (FSpooling__18CBinaryAsyncStream(arg0) != 0) {
            sceCdSync(0);
            FinishSpooling__18CBinaryAsyncStream(arg0);
        }
        M2C_FIELD(arg0, s32 *, 8) = 0;
        break;
    }
    M2C_FIELD(arg0, s32 *, 0) = -1;
}
