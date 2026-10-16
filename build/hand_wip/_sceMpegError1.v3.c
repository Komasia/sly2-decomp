// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-114
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// SLY2_SAVES: sd
int sceVsnprintf(char *, int, const char *, void *);
void _sceMpegError(void *, char *);
void _sceMpegError1(void *mp, const char *fmt, void *ap)
{
    char buf[256];
    sceVsnprintf(buf, 256, fmt, ap);
    _sceMpegError(mp, buf);
}
