#include "m2c_prelude.h"
M2C_UNK FinishSpooling__18CBinaryAsyncStream(s32 *); /* extern */
M2C_UNK StartSpooling__18CBinaryAsyncStream(s32 *); /* extern */

void Spool__18CBinaryAsyncStream(s32 *arg0) {
    s32 temp_v1;

    temp_v1 = *arg0;
    switch (temp_v1) {                              /* irregular */
    case 0:
        StartSpooling__18CBinaryAsyncStream(arg0);
        FinishSpooling__18CBinaryAsyncStream(arg0);
        return;
    case 1:
        FinishSpooling__18CBinaryAsyncStream(arg0);
        StartSpooling__18CBinaryAsyncStream(arg0);
        return;
    }
}
