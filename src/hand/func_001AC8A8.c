/* func_001AC8A8 (0x1AC8A8): writes to an open card file (sceMcWrite: fd, buffer, size), the bytes written through
 * pcb. Layout: include/h5_mc.h. */
#include "h5_mc.h"
int sceMcWrite(int fd, int pv, int cb);
void func_001AB098(void *pmemcard, int nResult, int kind, int pcb);
void func_001AC8A8(struct MC *pmc, int fd, int pv, int cb, int pcb)
{
    func_001AB098(pmc->memcard, sceMcWrite(fd, pv, cb), 6, pcb);
}
