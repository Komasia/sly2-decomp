// (Claude agent) near miss: layout matches; ours hoists the IPU_CMD address 0x10002000 out of the do-while (extra s-reg), target rematerializes it per iteration; minor code/x12C scheduling.
// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
typedef struct {
    char p0[0x12C]; int x12C;
    char p130[0x828 - 0x130]; int x828; unsigned int cmd;
    char p830[0x848 - 0x830]; int x848; int x84C;
    char p850[0x858 - 0x850]; int mpeg2;
} D;
void _waitIpuIdle(D *d);
long _sceMpegWaitIpuIdle64(D *d);
unsigned int _sceMpegPeepBit(D *d, int n);
void func_00252390(D *d, int n);
void _sceMpegError1(D *d, const char *fmt, int code);
int _sceMpegMbAddressIncrement(D *d)
{
    int inc = 0;
    int cont;

    do {
        long r;
        unsigned int bp;
        long top;
        unsigned int code;
        unsigned int p;

        _waitIpuIdle(d);
        *(volatile unsigned int *)0x10002000 = 0x30000000;
        d->cmd = 0x30000000;
        d->x828 = 0;
        r = _sceMpegWaitIpuIdle64(d);
        bp = *(volatile unsigned int *)0x10002020;
        top = *(volatile long *)0x10002030;
        d->x848 = top;
        if (top < 0)
            d->x84C = (32 - (bp & 0x1F)) & 0x1F;
        else
            d->x84C = 32;
        code = (short)(r & 0xFFFF);
        d->x12C = (int)r == 0;
        switch (code) {
        case 0x23:
            inc += 0x21;
            cont = 1;
            break;
        case 0:
            p = _sceMpegPeepBit(d, 11);
            if (d->mpeg2 && p == 0xF) {
                func_00252390(d, 11);
                cont = 1;
                break;
            }
            _sceMpegError1(d, "Invalid macroblock_address_increment code(0x%08x)", code);
            d->x12C = 1;
            return 1;
        case 0x22:
            cont = 1;
            break;
        default:
            inc += code;
            cont = 0;
            break;
        }
    } while (cont);
    return inc;
}
