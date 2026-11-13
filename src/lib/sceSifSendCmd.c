// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
unsigned int _sceSifSendCmd(int cid, int mode, void *pkt, int pktsize, void *src, void *dest, int size);
unsigned int sceSifSendCmd(int cid, void *pkt, int pktsize, void *src, void *dest, int size)
{
    int mode = 0;
    return _sceSifSendCmd(cid, mode, pkt, pktsize, src, dest, size);
}
