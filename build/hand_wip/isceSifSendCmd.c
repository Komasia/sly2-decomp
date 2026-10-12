// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
unsigned int func_0023AE70(int cid, int mode, void *pkt, int pktsize, void *src, void *dest, int size);
unsigned int isceSifSendCmd(int cid, void *pkt, int pktsize, void *src, void *dest, int size)
{
    return func_0023AE70(cid, 1, pkt, pktsize, src, dest, size);
}
