// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct {
    char p0[0x82C]; unsigned int cmd;
    char p830[0x868 - 0x830]; void *mp;
    char p86C[0x878 - 0x86C]; int stop;
} D;
#define R(a) (*(volatile unsigned int *)(a))
int _sceMpegDispatchMpegCbNodata(void *mp);
void _sceMpegStopIpuDma(void);
long _sceMpegWaitIpuIdle64(D *d)
{
    int cnt = 0;
    long r;

    while ((r = *(volatile long *)0x10002000) < 0 && !(R(0x10002010) & 0x4000)) {
        unsigned int bp = R(0x10002020);
        unsigned int cmd = d->cmd;
        unsigned int n = ((bp & 0xFF00) >> 1) + ((bp & 0x30000) >> 9) - (bp & 0x7F);
        if ((cmd == 0x20000000 || cmd == 0x30000000 || cmd == 0x40000000) && n < 0x20 && R(0x1000B420) == 0) {
            _sceMpegDispatchMpegCbNodata(d->mp);
            if (d->stop) { _sceMpegStopIpuDma(); break; }
            cnt = 0;
        }
        if (cnt++ > 500) {
            _sceMpegDispatchMpegCbNodata(d->mp);
            if (d->stop) { _sceMpegStopIpuDma(); break; }
            cnt = 0;
        }
    }
    d->cmd = 0;
    return r;
}
