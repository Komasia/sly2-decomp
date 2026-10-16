// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
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
    if (bs->bits < 57) {
        unsigned char *end=bs->end;
        unsigned long position=bs->pos;
        do {
            unsigned char *cur=bs->cur;
            int remaining=bs->bits;
            unsigned long bits=bs->buf | (unsigned long)*cur << (56-remaining);
            ++cur;
            bs->buf=bits;
            bs->cur=cur;
            if(cur>=end)bs->cur=bs->start;
            bs->bits=remaining+8;
        } while(bs->bits<57);
        bs->pos=position+n;
    } else bs->pos+=n;
}

struct HEADER;
int _system_header(BS *bs,struct HEADER *output)
{
    skipBits(bs, 56);
    skipBits(bs, 40);
    while ((bs->buf >> 63) == 1)
        skipBits(bs, 24);
    return 1;
}
