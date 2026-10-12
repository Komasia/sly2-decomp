// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0
typedef unsigned int size_t;
typedef int TItype __attribute__((mode(TI)));
void *s1_memset(void *m, int c, size_t n)
{
    unsigned long buffer; TItype qbuf; int i; unsigned int d;
    unsigned long *aligned_addr;
    unsigned char *s = (unsigned char *)m;

    if (!(n < sizeof(long)) && !((long)m & 15)) {
        aligned_addr = (unsigned long *)m;
        d = c & 0xff; buffer = 0; buffer = (buffer << 8) | d; buffer = (buffer << 8) | d;
        __asm__("pcpyh %0, %1" : "=r"(buffer) : "r"(buffer));
        while (n >= sizeof(long) * 4) {
            __asm__("pcpyld %0, %1, %1" : "=r"(qbuf) : "r"(buffer));
            *(TItype *)aligned_addr = qbuf;
            n -= sizeof(long) * 4;
            aligned_addr += 2;
            *(TItype *)aligned_addr = qbuf;
            aligned_addr += 2;
        }
        while (n >= sizeof(long)) {
            *aligned_addr++ = buffer;
            n -= sizeof(long);
        }
        s = (unsigned char *)aligned_addr;
    }
    while (n--)
        *s++ = (char)c;
    return m;
}
