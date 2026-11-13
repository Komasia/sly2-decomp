// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct {
    char p0[0xFC]; int xFC; char p1[0x1B4 - 0x100]; int closed_gop; int broken_link;
    char p2[0x85C - 0x1BC]; int x85C; int x860; int x864;
} MpegD;
int _sceMpegNextBit(MpegD *d, int n);
void _extensionAndUserData(MpegD *d);
void _groupOfPicturesHeader(MpegD *d)
{
    d->xFC = 0;
    d->x864 = 1;
    d->x85C = d->x860 + 1;
    _sceMpegNextBit(d, 1);
    _sceMpegNextBit(d, 5);
    _sceMpegNextBit(d, 6);
    _sceMpegNextBit(d, 1);
    _sceMpegNextBit(d, 6);
    _sceMpegNextBit(d, 6);
    d->closed_gop = _sceMpegNextBit(d, 1);
    d->broken_link = _sceMpegNextBit(d, 1);
    _extensionAndUserData(d);
}
