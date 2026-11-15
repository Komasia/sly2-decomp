// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* _alarm_bind (libkernel sifrpc): alarm handler that retries sending the answer (RPC end packet) to an IOP bind request;
   returns 0 (done) once the SIF command was queued, else the delay before the next try. */
#include "sif_rpc.h"
#define RPC_RETRY_DELAY 0x800
unsigned int isceSifSendCmd(unsigned int, void *, int, void *, void *, int);

int _alarm_bind(int id, unsigned short time, int actual, void *packet)
{
    return isceSifSendCmd(SIF_CMD_RPC_END, packet, 0x40, 0, 0, 0) ? 0 : RPC_RETRY_DELAY;
}
