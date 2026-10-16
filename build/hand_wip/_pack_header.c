// SLY2_CC: tools/compilers/bundle/ee-gcc2.95.3-136
// SLY2_CFLAGS: -O2 -G0 -fstrict-aliasing
// SLY2_ASM: gnu-reorder-db
typedef struct {
    unsigned long buf,pos;
    int pad10;
    unsigned char *cur;
    int bits;
    unsigned char *start,*end;
} BS;
typedef struct {unsigned int extension,low,high,hasSystemHeader;} HEADER;
extern int _system_header(BS*,HEADER*);
static __inline__ void Skip(BS *p,int n)
{
    p->buf<<=n;
    p->bits-=n;
    if(p->bits<57){
        unsigned char *end=p->end;
        unsigned long pos=p->pos;
        int bits;
        do {
            unsigned char *cur=p->cur;
            bits=p->bits;
            p->buf|=(unsigned long)*cur<<(56-bits);
            p->cur=++cur;
            if(cur>=end)p->cur=p->start;
            p->bits=bits+8;
        }while(bits+8<57);
        p->pos=pos+n;
    }else p->pos+=n;
}
static __inline__ unsigned int Get(BS *p,int n)
{
    unsigned int value=p->buf>>(64-n);
    Skip(p,n);
    return value;
}
int _pack_header(BS *p,HEADER *out)
{
    unsigned int first,mid,last,stuffing,i;
    Skip(p,34);
    first=Get(p,3);
    Skip(p,1);
    mid=Get(p,15);
    Skip(p,1);
    last=Get(p,15);
    Skip(p,1);
    out->extension=Get(p,9);
    Skip(p,30);
    stuffing=Get(p,3);
    out->low=(first<<30)|(mid<<15)|last;
    out->high=first>>2;
    for(i=0;i<stuffing;i++)Skip(p,8);
    out->hasSystemHeader=0;
    if((int)(p->buf>>32)==0x1BB){
        out->hasSystemHeader=1;
        _system_header(p,out);
    }
    return 1;
}
