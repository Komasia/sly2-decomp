// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
unsigned int _sceMpegNextBit(void *d, int n);
/* _copyrightExtension (libmpeg): skip copyright_extension(). */
void _copyrightExtension(void *d)
{
    _sceMpegNextBit(d, 1);     /* copyright_flag */
    _sceMpegNextBit(d, 8);     /* copyright_identifier */
    _sceMpegNextBit(d, 1);     /* original_or_copy */
    _sceMpegNextBit(d, 7);     /* reserved */
    _sceMpegNextBit(d, 1);     /* marker_bit */
    _sceMpegNextBit(d, 20);    /* copyright_number_1 */
    _sceMpegNextBit(d, 1);
    _sceMpegNextBit(d, 22);    /* copyright_number_2 */
    _sceMpegNextBit(d, 1);
    _sceMpegNextBit(d, 22);    /* copyright_number_3 */
}
