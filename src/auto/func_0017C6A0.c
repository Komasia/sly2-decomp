#include "m2c_prelude.h"
M2C_UNK SetState__10JOBSTATIONi(s32, M2C_UNK);                /* extern */
M2C_UNK Enter__5AIJOB();                            /* extern */

// name: SafeHouse port (JOBSTATION::Enter)
void Enter__10JOBSTATION(s32 arg0) {
    Enter__5AIJOB();
    SetState__10JOBSTATIONi(arg0, 0);
}
