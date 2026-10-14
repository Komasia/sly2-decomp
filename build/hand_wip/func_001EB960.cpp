
#include "gifs.h"
struct RGBA {uchar r,g,b,a;};
struct PACKET {int count;QW*data;};
struct TEXTURE;
struct ENTRY {char unknown0[4];uchar kind,flags;char unknown6[6];RGBA color,secondary;char unknown14[4];TEXTURE*texture;int unknown1C;PACKET*packets;char unknown24[8];};
extern int D_003DCFE8;
extern ENTRY *D_003DCFEC;
extern uint D_002DE18C;
extern "C" void func_001EA750(TEXTURE*,int,GIFS*);
extern "C" void func_001EB960();
static inline ulong ColorWord(RGBA color,int includeAlpha){ulong value=(ulong)color.r|((ulong)color.g<<8)|((ulong)color.b<<16);if(includeAlpha)value|=(ulong)color.a<<24;return value|(1UL<<32);}
static inline void Pair(GIFS&q,int first,ulong regs){q.AddPrimBulk(first,0,4,regs,0);q.AddPrimBulk(first+1,0,4,regs,0);}
static inline void Packed(GIFS&q){q.AddPrimPack(0,1,0xE);}
static inline void End(GIFS&q){q.GIFS::EndPrim(1);q.EndDmaCnt();}
static inline ulong Alpha(ENTRY*e){return (((e->flags&1)?2UL:1UL)<<2)|0x40;}
void func_001EB960(){
 int i;
 for(i=0;i<D_003DCFE8;i++){
  ENTRY*e=D_003DCFEC+i;
  PACKET*p=e->packets;
  switch(e->kind){
  case 0:case 4:case 5:case 6:{
   GIFS q;
   q.AllocStatic(p->count,p->data);
   Pair(q,0x7C,0x4F12);
   Packed(q);
   func_001EA750(e->texture,0,&q);
   if(e->flags&0x20){
    ulong test=(e->flags&4)?0x13001UL:0x11001UL;
    test|=e->kind?0x20000UL:0x60000UL;
    q.PackAD(0x47,test);q.PackAD(0x42,0);
   }else if(e->flags&0x10){
    ulong test=0x7E1UL;if(!e->kind)test=0x7EBUL;
    if(e->flags&4)test|=0x13000UL;else test|=0x11000UL;
    test|=e->kind?0x20000UL:0x60000UL;
    q.PackAD(0x47,test);q.PackAD(0x42,((ulong)(e->flags&1)<<3)|1);
   }else if(e->flags&0x80){
    q.PackAD(0x47,0x77000);q.PackAD(0x42,0x54);
   }else{
    ulong test=0x7E1UL;if(!e->kind)test=0x7EBUL;
    if(e->flags&4)test|=0x13000UL;else test|=0x11000UL;
    test|=e->kind?0x20000UL:0x60000UL;
    q.PackAD(0x47,test);q.PackAD(0x42,Alpha(e));
   }
   q.PackAD(0x3D,(ulong)D_002DE18C);End(q);
   break;
  }
  case 3:{
   GIFS q;
   q.AllocStatic(p->count,p->data);
   if(e->flags&2){
    Pair(q,0x7C,0x4F12);Packed(q);
    func_001EA750(e->texture,0,&q);
    q.PackAD(0x47,0x71001);q.PackAD(0x42,Alpha(e));
    q.PackAD(0x3D,(ulong)D_002DE18C);
   }else{
    Pair(q,0x4C,0x4FFF);Packed(q);
    q.PackAD(0x47,0x71001);q.PackAD(0x42,0x6A);
    q.PackAD(1,(1UL<<32)|0x20);
   }
   End(q);++p;ulong one=1,two=2,mask=0x40;q.Clear();
   q.AllocStatic(p->count,p->data);++p;
   Pair(q,0x4C,0x4FFF);Packed(q);
   q.PackAD(0x47,0x71001);q.PackAD(0x42,0x6A);
   q.PackAD(1,(3UL<<32)|0x2000);End(q);q.Clear();
   q.AllocStatic(p->count,p->data);++p;
   Pair(q,0x6C,0x4FFF);q.AddPrimPack(0,5,0x12EEE);
   q.PackAD(0x47,0x75001);q.PackAD(0x42,(((e->flags&1)?two:one)<<2)|mask);
   q.PackAD(0x3D,(ulong)D_002DE18C);
   q.PackSTQ(0.f,0.f,1.f);
   {
    RGBA rounded;
    rounded.r=(e->color.r+1)>>1;rounded.g=(e->color.g+1)>>1;
    rounded.b=(e->color.b+1)>>1;rounded.a=(e->color.a+1)>>1;
    q.PackRGBA(*(uint*)&rounded);
   }
   End(q);q.Clear();
   q.AllocStatic(p->count,p->data);
   q.AddPrimBulk(0x4D,0,1,4,0);
   {
    RGBA color=e->secondary;
    Packed(q);if(e->flags&1)one=two;q.PackAD(0x42,(one<<2)|mask);
    q.PackAD(1,ColorWord(color,e->flags&2));
   }
   End(q);break;
  }
  case 2:{
   GIFS q;
   q.AllocStatic(p->count,p->data);
   q.AddGifTag(0x44,0,2,0x41,1);q.AddGifTag(0x45,0,2,0x41,1);
   Packed(q);
   if(e->flags&8)q.PackAD(0x47,0x71001);else q.PackAD(0x47,0x75001);
   q.PackAD(0x42,(1UL<<39)|0x62);++p;End(q);q.Clear();
   q.AllocStatic(p->count,p->data);
   q.AddGifTag(0x44,0,2,0x41,1);q.AddGifTag(0x45,0,2,0x41,1);
   Packed(q);
   if(e->flags&8)q.PackAD(0x47,0x31001);else q.PackAD(0x47,0x35001);
   q.PackAD(0x42,(1UL<<39)|0x68);End(q);break;
  }
  case 1:{
   GIFS q;
   q.AllocStatic(p->count,p->data);
   Pair(q,0x7C,0x4F12);Packed(q);func_001EA750(e->texture,1,&q);
   if(e->flags&0x80){
    q.PackAD(0x47,0x77000);q.PackAD(0x42,0x54);
   }else{
    q.PackAD(0x47,(e->flags&4)?0x737EB:0x717EB);q.PackAD(0x42,Alpha(e));
   }
   q.PackAD(0x3D,(ulong)D_002DE18C);++p;End(q);q.Clear();
   q.AllocStatic(p->count,p->data);
   Pair(q,0x7C,0x41F2);Packed(q);func_001EA750(e->texture,0,&q);
   if(e->flags&0x80){
    q.PackAD(0x47,0x57000);q.PackAD(0x42,0x58);
   }else{
    q.PackAD(0x47,0x51001);q.PackAD(0x42,0x48);
   }
   q.PackAD(0x3D,0);End(q);break;
  }
  case 7:{
   GIFS q;
   if(!(e->flags&0x20)){
    q.AllocStatic(p->count,p->data);++p;
    Pair(q,0x7C,0x41F2);Packed(q);func_001EA750(e->texture,2,&q);
    q.PackAD(0x47,0x5000D);q.PackAD(0x42,0x40);q.PackAD(0x3D,0);
    End(q);q.Clear();
   }
   q.AllocStatic(p->count,p->data);++p;
   Pair(q,0x7C,0x4F12);Packed(q);func_001EA750(e->texture,1,&q);
   q.PackAD(0x47,0x53001);q.PackAD(0x42,Alpha(e));q.PackAD(0x3D,(ulong)D_002DE18C);
   End(q);q.Clear();
   q.AllocStatic(p->count,p->data);
   Pair(q,0x7C,0x41F2);Packed(q);func_001EA750(e->texture,0,&q);
   q.PackAD(0x47,0x53001);q.PackAD(0x42,0x48);q.PackAD(0x3D,0);End(q);break;
  }
  }
 }
}
