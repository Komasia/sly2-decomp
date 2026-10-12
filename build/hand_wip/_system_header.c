// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder
// NOTE: logic right; target hoists 'ld pos' before the refill loop and keeps bits in a reg (56 rematerialised per iter). notes/245000.md round 9.
typedef struct {
    unsigned long buf;
    unsigned long pos;
    int pad10;
    unsigned char *cur;
    int bits;
    unsigned char *start;
    unsigned char *end;
} BS;

static inline void skipBits(BS *bs, int n)
{
    bs->buf <<= n;
    bs->bits -= n;
    while (bs->bits < 57) {
        bs->buf |= (unsigned long)*bs->cur << (56 - bs->bits);
        bs->cur++;
        if (bs->cur >= bs->end) bs->cur = bs->start;
        bs->bits += 8;
    }
    bs->pos += n;
}

int _system_header(BS *bs)
{
    skipBits(bs, 56);
    skipBits(bs, 40);
    while ((bs->buf >> 63) == 1)
        skipBits(bs, 24);
    return 1;
}
