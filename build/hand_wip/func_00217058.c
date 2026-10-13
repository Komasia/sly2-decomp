struct R { char pad[0xC]; unsigned char *cur; };
struct S { char pad[0x12]; unsigned short mode; char pad1[8]; int address; };
struct D { int a; int mode; int b; int xC; char pad[0x20]; };
extern struct R D_002DEA28;
static inline void CopyWords(int *d, const int *s, int n) {
    for (n-=4; n>=0; n-=4) {
        int a=s[0], b=s[1], c=s[2], e=s[3];
        d[0]=a;
        s+=4;
        d[1]=b; d[2]=c; d[3]=e;
        d+=4;
    }
}
static inline void Word(struct R *r,unsigned int word) {
    *(unsigned int *)r->cur=word;
    r->cur+=4;
}
static inline void Align(struct R *r) {
    while((int)r->cur&15) { *(int *)r->cur=0; r->cur+=4; }
}
void func_00217058(struct S *p,const int *matrix,struct D *data,int flags) {
    unsigned char *tag=D_002DEA28.cur;
    *(long *)tag=0x10000000L;
    D_002DEA28.cur+=16;
    if(flags&1) {
        Word(&D_002DEA28,0x6C04C000);
        CopyWords((int *)D_002DEA28.cur,matrix,16);
        D_002DEA28.cur+=0x40;
    } else {
        Word(&D_002DEA28,0x6C01C002);
        CopyWords((int *)D_002DEA28.cur,matrix+8,4);
        D_002DEA28.cur+=0x10;
    }
    data->xC=0x7FFF;
    data->mode=p->mode>=2;
    if((flags&2) || data->mode) {
        Word(&D_002DEA28,0x6C03C004);
        CopyWords((int *)D_002DEA28.cur,(const int *)data,12);
        D_002DEA28.cur+=0x30;
    }
    Align(&D_002DEA28);
    *(int *)tag |= ((D_002DEA28.cur-tag)>>4)-1;
    Align(&D_002DEA28);
    *(long *)D_002DEA28.cur=0x50000000L | ((long)p->address<<32);
    D_002DEA28.cur+=16;
}
