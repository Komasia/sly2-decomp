// wip (Claude agent, pins15, 2026-10-17): aligned 12 (was 17). Removed the $2 pin on the second-loop tag. Left: scheduling around Write (i+1 and Copy count 8 placed early).
#include "vifs.h"
struct BLOCK {union {uint words[12];struct {int kind;float coefficients[11];} values;};};
struct P { char pad[0x120]; struct BLOCK payload; };
struct O { char pad[0x14]; int x14; unsigned char *x18; };
extern VIFS D_002DEA28;
extern struct BLOCK D_002BFC60;
extern "C" void func_001A3968(struct P *p);
static inline uint* Write(VIFS*g,uint x){unsigned char*d;*(uint*)g->m_pb=x;d=g->m_pb+4;g->m_pb=d;return(uint*)d;}
static inline void Copy(uint*d,const uint*s,int words){int j;for(j=words-4;j>=0;j-=4){uint a=s[0],b=s[1],c=s[2],e=s[3];d[0]=a;d[1]=b;d[2]=c;d[3]=e;s+=4;d+=4;}}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
typedef char BLOCK_words_Offset[FIELD_OFFSET(BLOCK,words)==0?1:-1];
typedef char BLOCK_values_Offset[FIELD_OFFSET(BLOCK,values)==0?1:-1];
typedef char P_payload_Offset[FIELD_OFFSET(P,payload)==288?1:-1];
typedef char O_x14_Offset[FIELD_OFFSET(O,x14)==20?1:-1];
typedef char O_x18_Offset[FIELD_OFFSET(O,x18)==24?1:-1];
typedef char VIFS_m_pb_Offset[FIELD_OFFSET(VIFS,m_pb)==12?1:-1];
typedef char uint_PrefixSize[sizeof(uint)==4?1:-1];
typedef char BLOCK_PrefixSize[sizeof(BLOCK)==48?1:-1];
typedef char P_PrefixSize[sizeof(P)==336?1:-1];
typedef char O_PrefixSize[sizeof(O)==28?1:-1];
typedef char VIFS_PrefixSize[sizeof(VIFS)==36?1:-1];
extern "C" void func_001A4AD8(void *a0, int n, struct P **ap, struct O *o)
{
    int i;
    o->x18 = D_002DEA28.m_pb;
    for (i = 0; i < n; i++) {
        struct P *p = ap[i];
        func_001A3968(p);
        register uint tag __asm__("$2")=0x6C03C000 | (i*3+0x15);
        uint*d=Write(&D_002DEA28,tag);
        Copy(d,p->payload.words,12);
        D_002DEA28.m_pb += 48;
    }
    for (; i < 4; i++) {
        register uint tag=0x6C03C000 | (i*3+0x15);
        uint*d=Write(&D_002DEA28,tag);
        Copy(d,D_002BFC60.words,12);
        D_002DEA28.m_pb += 48;
    }
    o->x14 = ((char *)D_002DEA28.m_pb - (char *)o->x18) >> 4;
}
