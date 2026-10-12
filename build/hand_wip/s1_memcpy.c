// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
typedef unsigned int size_t;
typedef int TItype __attribute__((mode(TI)));

#define UNALIGNED(X, Y) (((long)(X) | (long)(Y)) & (sizeof(TItype) - 1))
#define BIGBLOCKSIZE (sizeof(TItype) << 1)
#define LITTLEBLOCKSIZE (sizeof(long))
#define TOO_SMALL(LEN) ((LEN) < BIGBLOCKSIZE)

void *s1_memcpy(void *dst0, const void *src0, size_t len0)
{
    char *dst = dst0;
    const char *src = src0;
    long *aligned_dst;
    const long *aligned_src;
    int len = len0;

    if (!TOO_SMALL(len) && !UNALIGNED(src, dst)) {
        aligned_dst = (long *)dst;
        aligned_src = (const long *)src;
        while (len >= BIGBLOCKSIZE) {
            *(TItype *)aligned_dst = *(TItype *)aligned_src;
            aligned_dst += 2; aligned_src += 2;
            *(TItype *)aligned_dst = *(TItype *)aligned_src;
            aligned_dst += 2; aligned_src += 2;
            len -= BIGBLOCKSIZE;
        }
        while (len >= LITTLEBLOCKSIZE) {
            *aligned_dst++ = *aligned_src++;
            len -= LITTLEBLOCKSIZE;
        }
        dst = (char *)aligned_dst;
        src = (const char *)aligned_src;
    }
    while (len--)
        *dst++ = *src++;
    return dst0;
}
