/* func_001AC850 (0x1AC850): reads from an open card file (sceMcRead: fd, buffer, size), the bytes read through pcb.
 * Layout: include/h5_mc.h. */
#include "h5_mc.h"
int sceMcRead(int fd, int pv, int cb);
void func_001AB098(void *pmemcard, int nResult, int kind, int pcb);
void func_001AC850(struct MC *pmc, int fd, int pv, int cb, int pcb)
{
    func_001AB098(pmc->memcard, sceMcRead(fd, pv, cb), 5, pcb);
}
