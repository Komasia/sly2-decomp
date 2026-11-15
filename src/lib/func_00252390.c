// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* libmpeg: thin wrapper of _sceMpegFlushBuf (used by _decMB0 / _sceMpegMbAddressIncrement). */
void _sceMpegFlushBuf(void *, int);
void func_00252390(void *a, int b)
{
    _sceMpegFlushBuf(a, b);
}
