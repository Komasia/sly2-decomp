// SLY2_CC: tools/compilers/extra/ee-gcc2.9-991111
// SLY2_CFLAGS: -O2 -G0
// SLY2_ASM: gnu-reorder-db
/* _system_header (libmpeg demux): skip an MPEG-2 program stream system_header(): the fixed fields, then one
   3-byte entry per stream while the next bit is 1. Same Skip inline as _pack_header; the stream loop is
   `if (c) do ...; while (c);` (no sign-test fold, beql loop). */
typedef struct {
    unsigned long buf,pos;
    int pad10;
    unsigned char *cur;
    int bits;
    unsigned char *start,*end;
} BS;
struct HEADER;
static __inline__ void Skip(BS *p,int n)
{
    p->buf<<=n;
    p->bits-=n;
    if(p->bits<57){
        do {
            p->buf|=(unsigned long)*p->cur++<<(56-p->bits);
            if(p->cur>=p->end)p->cur=p->start;
            p->bits+=8;
        }while(p->bits<57);
    }
    p->pos+=n;
}
int _system_header(BS *p, struct HEADER *out)
{
    Skip(p, 56);   /* start code (32), header_length (16), marker + rate_bound (8 of 24) */
    Skip(p, 40);   /* rest of rate_bound, audio_bound .. reserved */
    if ((int)(p->buf >> 63) == 1)
        do
            Skip(p, 24);
        while ((int)(p->buf >> 63) == 1);
    return 1;
}
