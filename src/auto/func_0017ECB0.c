#include "m2c_prelude.h"
s32 NArrived__7JOBGOTO(s32);                             /* extern */
M2C_UNK Step__11JOBPATHSTEPi(void *, M2C_UNK);             /* extern */
M2C_UNK func_001EEF98();                            /* extern */

// name: SafeHouse port (JOBPATHSTEP::Update)
void Update__11JOBPATHSTEP(void *arg0) {
    func_001EEF98();
    if (NArrived__7JOBGOTO(M2C_FIELD(arg0, s32 *, 0x18)) != 0) {
        Step__11JOBPATHSTEPi(arg0, 0);
    }
}
