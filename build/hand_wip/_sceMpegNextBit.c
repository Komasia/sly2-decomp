// near-miss 15/58: scheduling only (target loads x848 after the x84C=32 store; shift uses the same 32 reg)
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
typedef struct { char p0[0x828]; int x828; unsigned int x82C; char p1[0x848 - 0x830]; unsigned int x848; int x84C; } D;
void _waitIpuIdle(D *d);
long _sceMpegWaitIpuIdle64(D *d);
unsigned int _sceMpegNextBit(D *d, int n)
{
    unsigned int r, c;
    _waitIpuIdle(d);
    if (d->x828 || d->x84C < n) {
        *(volatile unsigned int *)0x10002000 = 0x40000000;
        d->x828 = 0;
        d->x82C = 0x40000000;
        d->x848 = _sceMpegWaitIpuIdle64(d);
    }
    d->x84C = 32;
    c = n | 0x40000000;
    *(volatile unsigned int *)0x10002000 = c;
    r = d->x848 >> (32 - n);
    c &= 0xF0000000;
    d->x82C = c;
    if (c == 0x20000000 || c == 0x30000000 || c == 0x40000000)
        d->x828 = 0;
    else
        d->x828 = 1;
    d->x848 = _sceMpegWaitIpuIdle64(d);
    return r;
}
