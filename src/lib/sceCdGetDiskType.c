// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
/* libcdvd: the disc type, 0 when the S-command fails (sceCdGetDiskType2 returns -1 then). */
int sceCdGetDiskType2(void);
int sceCdGetDiskType(void)
{
    int r = sceCdGetDiskType2();
    return (r == -1) ? 0 : r;
}
