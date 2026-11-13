// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct {
    int x0, x4, x8, xc;
    unsigned int x10;
    int x14, x18, x1c;
    int x20, x24, x28, x2c, x30, x34, x38, x3c;
} Pkt;
Pkt *_sceRpcGetFPacket(void *data);
Pkt *_sceRpcGetFPacket2(void *data, int n);
unsigned int isceSifSendCmd(unsigned int cid, void *pkt, int size, int src, int dst, int n);
int iSetTimerAlarm(unsigned short t, void (*h)(void *), void *arg);
void _alarm_rdata(void *);
void _request_rdata(Pkt *r, void *data)
{
    Pkt *p;
    if (r->x10 & 4)
        p = _sceRpcGetFPacket2(data, r->x10 >> 16);
    else
        p = _sceRpcGetFPacket(data);
    {
        int a = r->x14, b = r->x1c;
        p->x14 = a;
        p->x1c = b;
    }
    p->x20 = 0x8000000C;
    p->x24 = r->x20;
    p->x28 = r->x24;
    p->x2c = r->x28;
    if (isceSifSendCmd(0x80000008, p, 0x40, r->x20, r->x24, r->x28) == 0)
        iSetTimerAlarm(0x800, _alarm_rdata, p);
}
