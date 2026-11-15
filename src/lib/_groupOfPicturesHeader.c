// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct {
    char p0[0xFC]; int xFC; char p1[0x1B4 - 0x100]; int closed_gop; int broken_link;
    char p2[0x85C - 0x1BC]; int tr_base; int tr_max; int tr_first;    /* 0x85C temporal reference tracking */
} MpegD;
int _sceMpegNextBit(MpegD *d, int n);
void _extensionAndUserData(MpegD *d);
/* _groupOfPicturesHeader (libmpeg): parse group_of_pictures_header(); the time code is skipped, temporal
   references restart after the highest one seen so far. */
void _groupOfPicturesHeader(MpegD *d)
{
    d->xFC = 0;
    d->tr_first = 1;
    d->tr_base = d->tr_max + 1;
    _sceMpegNextBit(d, 1);     /* drop_frame_flag */
    _sceMpegNextBit(d, 5);     /* time_code_hours */
    _sceMpegNextBit(d, 6);     /* time_code_minutes */
    _sceMpegNextBit(d, 1);     /* marker_bit */
    _sceMpegNextBit(d, 6);     /* time_code_seconds */
    _sceMpegNextBit(d, 6);     /* time_code_pictures */
    d->closed_gop = _sceMpegNextBit(d, 1);
    d->broken_link = _sceMpegNextBit(d, 1);
    _extensionAndUserData(d);
}
