// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
// 3/15 with gnu-reorder: `addiu sp,-0x10` scheduled 2 insns earlier than target (scheduler difference, see sceFsReset).
unsigned int _sceSifSendCmd(int cid, int mode, void *pkt, int pktsize, void *src, void *dest, int size);
unsigned int isceSifSendCmd(int cid, void *pkt, int pktsize, void *src, void *dest, int size)
{
    return _sceSifSendCmd(cid, 1, pkt, pktsize, src, dest, size);
}
