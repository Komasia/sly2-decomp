// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
unsigned int _sceSifSendCmd(int cid, int mode, void *pkt, int pktsize, void *src, void *dest, int size);
/* isceSifSendCmd (libkernel sifcmd): sceSifSendCmd for interrupt handlers (mode SIF_CMD_M_INTR). */
unsigned int isceSifSendCmd(int cid, void *pkt, int pktsize, void *src, void *dest, int size)
{
    return _sceSifSendCmd(cid, 1, pkt, pktsize, src, dest, size);
}
