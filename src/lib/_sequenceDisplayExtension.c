// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
typedef struct { char p0[0x154]; int matrix_coefficients; int display_hsize; int display_vsize; } D;
unsigned int _sceMpegNextBit(D *d, int n);
/* _sequenceDisplayExtension (libmpeg): parse sequence_display_extension(). */
void _sequenceDisplayExtension(D *d)
{
    _sceMpegNextBit(d, 3);                     /* video_format */
    if (_sceMpegNextBit(d, 1)) {               /* colour_description */
        _sceMpegNextBit(d, 8);                 /* colour_primaries */
        _sceMpegNextBit(d, 8);                 /* transfer_characteristics */
        d->matrix_coefficients = _sceMpegNextBit(d, 8);
    }
    d->display_hsize = _sceMpegNextBit(d, 14);
    ((void (*)(D *, int))_sceMpegNextBit)(d, 1);  /* marker_bit */
    d->display_vsize = _sceMpegNextBit(d, 14);
}
