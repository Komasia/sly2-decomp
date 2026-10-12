// SLY2_CC: tools/compilers/ee-gcc2.96
// SLY2_CFLAGS: -O2 -G0
void _sceMpegWaitIpuIdle(void *mp);
void _waitIpuIdle(void *mp)
{
    if ((*(volatile unsigned int *)0x10002010 & 0x80004000) == 0x80000000)
        _sceMpegWaitIpuIdle(mp);
}
