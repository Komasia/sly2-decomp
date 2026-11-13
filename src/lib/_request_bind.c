// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct {
    int x0, x4, x8, xc;
    unsigned int x10;
    int x14, x18, x1c;
    int x20, x24, x28, x2c, x30, x34, x38, x3c;
} Pkt;
typedef struct { int x0, x4; int x8; } Srv;
Pkt *_sceRpcGetFPacket(void *data);
Srv *_search_svdata(int sid, void *data);
unsigned int isceSifSendCmd(unsigned int cid, void *pkt, int size, int src, int dst, int n);
int iSetTimerAlarm(unsigned short t, void (*h)(void *), void *arg);
void _alarm_bind(void *);
void _request_bind(Pkt *r, void *data)
{
    Pkt *p;
    Srv *s;
    p = _sceRpcGetFPacket(data);
    {
        int b = r->x14, a = r->x1c;
        p->x1c = a;
        p->x14 = b;
    }
    p->x20 = 0x80000009;
    s = _search_svdata(r->x20, data);
    if (s == 0) {
        p->x24 = 0;
        p->x28 = 0;
    } else {
        p->x24 = (int)s;
        p->x28 = s->x8;
    }
    if (isceSifSendCmd(0x80000008, p, 0x40, 0, 0, 0) == 0)
        iSetTimerAlarm(0x800, _alarm_bind, p);
}
