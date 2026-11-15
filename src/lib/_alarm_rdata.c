// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* _alarm_rdata (libkernel sifrpc): alarm handler that retries sending a read-data request (packet plus
   the data to DMA to the IOP); returns 0 once queued, else the delay before the next try. */
#define SIF_CMD_RPC_PACKET 0x80000008
#define RPC_RETRY_DELAY 0x800
unsigned int isceSifSendCmd(unsigned int, void *, int, void *, void *, int);
typedef struct { int header[9]; void *src; void *dest; int size; } RdataPacket;

int _alarm_rdata(int id, unsigned short time, int actual, RdataPacket *packet)
{
    return isceSifSendCmd(SIF_CMD_RPC_PACKET, packet, 0x40, packet->src, packet->dest, packet->size) ? 0 : RPC_RETRY_DELAY;
}
