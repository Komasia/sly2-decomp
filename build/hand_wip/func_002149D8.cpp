// Deserialize one sprite descriptor and build its retained packet data.
#include "gifs.h"
#include "vifs.h"
typedef int qword __attribute__((mode(TI)));
struct BIS;
struct OWNER {char pad[0xC4];HEAP *heap;};
struct ROOT;
struct WORLD;
struct SPRITE;
struct M3 {qword r[3];};
struct M23 {float a[6];} __attribute__((aligned(16)));
struct PAIR {short x,y;};
struct RAWCOLOR {uchar r,g,b,a;};
struct VERTEX {uchar data[0x18];};
struct NESTED {int count;SPRITE *children;int floatCount;float *floats;int wordCount;uint *words;};
struct SHADER {int tag,mode,id;uint slot;float size,value,scale;int flag,special;};
struct POLYGON {M23 matrix;ushort count,pad22;VERTEX *vertices;};
struct EFFECT {int id;void *handle;int count;QW *packet;};
struct PICTURE {int id,count;QW *packet;};
struct GEOMETRY {ushort count,groups;int samples,packetCount;QW *packet;};
union PAYLOAD {int index;NESTED nested;SHADER shader;POLYGON polygon;EFFECT effect;PICTURE picture;GEOMETRY geometry;};
struct SPRITE {int id,kind;ROOT *root;int fieldC;PAYLOAD data;};
struct RECORD {int kind,id;RAWCOLOR color;uchar count,padD[3];int budget;uchar format,pad15[3];PAIR *coordinates;uchar extra,pad1D[3];uchar *extras;};
struct GROUP {int count,budget,samples;RECORD *begin,*end;};
// Native two-word member callback, stored as {delta,index,function}.
typedef void (OWNER::*PMF)(SPRITE *);
struct MARK;
extern "C" {
MARK *func_001AE478(MARK *);
void func_001AE4A0(MARK *,int);
int func_00117C20(BIS *);
uint func_00117C80(BIS *);
int func_00117BD0(BIS *);
int func_00117D50(BIS *);
int func_00117D00(BIS *);
int func_00117DB8(BIS *);
float func_00117E38(BIS *);
void func_00117ED0(BIS *,M3 *);
void func_00117968(BIS *,int,void *);
void *func_00116918(HEAP *,int,int);
void *func_001AE378(ALLOCREQ *);
void func_00214398(OWNER *,BIS *,ROOT *,int *,SPRITE **);
void func_00149A50(WORLD *,OWNER *,PMF,SPRITE *);
}
struct MARK {MARK(){func_001AE478(this);}~MARK(){func_001AE4A0(this,2);}};
struct INNERFRAME {INNERFRAME() __asm__("func_001AE478");void End(int) __asm__("func_001AE4A0");};
extern int D_002C40A4;
extern PMF D_002A8B08;
extern WORLD D_003DD490;
extern QW D_002A2E10;
extern char D_00000650[],D_00000140[];
static inline void CopyXY(M23 &dst,const M3 &src){
 const float *a=(const float *)&src.r[0],*b=(const float *)&src.r[1],*c=(const float *)&src.r[2];
 dst.a[0]=a[0];dst.a[1]=a[1];dst.a[2]=b[0];dst.a[3]=b[1];dst.a[4]=c[0];dst.a[5]=c[1];
}
extern "C" void func_002149D8(OWNER *owner,BIS *stream,ROOT *root,int,SPRITE *sprites){
 // The input matrix is live in the enclosing descriptor-read scope.
 MARK outer;M3 raw;
 int id=func_00117C20(stream);SPRITE *sprite=&sprites[id];sprite->root=root;sprite->id=id;
 sprite->kind=func_00117C80(stream);
 switch(sprite->kind){
 case 0:case 5:default:break;
 case 4:sprite->data.index=func_00117C20(stream);break;
 case 8:{
  D_002C40A4=1;
  func_00214398(owner,stream,root,&sprite->data.nested.count,&sprite->data.nested.children);
  sprite->data.nested.wordCount=func_00117C80(stream);
  sprite->data.nested.words=(uint *)func_00116918(owner->heap,sprite->data.nested.wordCount*4,0x13);
  int i=0;
  for(;i<sprite->data.nested.wordCount;i++)sprite->data.nested.words[i]=func_00117C80(stream);
  sprite->data.nested.floatCount=func_00117C80(stream);
  sprite->data.nested.floats=(float *)func_00116918(owner->heap,sprite->data.nested.floatCount*4,0x13);
  for(i=0;i<sprite->data.nested.floatCount;i++)sprite->data.nested.floats[i]=func_00117E38(stream);
  D_002C40A4=0;break;
 }
 case 3:{
  sprite->data.shader.tag=func_00117C80(stream);sprite->data.shader.slot=func_00117C80(stream);
  sprite->data.shader.size=func_00117E38(stream);sprite->data.shader.scale=func_00117E38(stream);sprite->data.shader.value=func_00117E38(stream);
  sprite->data.shader.flag=func_00117D00(stream);sprite->data.shader.mode=func_00117D00(stream);
  if(sprite->data.shader.mode==1)sprite->data.shader.id=func_00117DB8(stream);else if(sprite->data.shader.mode==0)sprite->data.shader.id=func_00117DB8(stream);
  if(sprite->data.shader.mode==1&&sprite->data.shader.id==0x2F2)sprite->data.shader.special=sprite->data.shader.mode;
  else sprite->data.shader.special=0;
  break;
 }
 case 2:{
  func_00117ED0(stream,&raw);M3 matrix=raw;CopyXY(sprite->data.polygon.matrix,matrix);
  sprite->data.polygon.count=func_00117C20(stream);
  sprite->data.polygon.vertices=(VERTEX *)func_00116918(owner->heap,sprite->data.polygon.count*sizeof(VERTEX),0x14);
  func_00117968(stream,sprite->data.polygon.count*sizeof(VERTEX),sprite->data.polygon.vertices);break;
 }
 case 6:case 7:{
  PAIR first,second;
  first.x=func_00117D50(stream);first.y=func_00117D50(stream);second.x=func_00117D50(stream);second.y=func_00117D50(stream);
  int texture=func_00117DB8(stream);
  INNERFRAME inner;GIFS gif;
  gif.AllocSw(16);gif.AddPrimPack(0,1,0xE);
  sprite->data.effect.id=texture;
  if(sprite->kind==6){sprite->data.effect.handle=0;gif.PackAD(0x47,0x5000F);gif.PackAD(0x42,0x80000000A8L);}
  else{gif.PackAD(0x42,0x44);gif.PackAD(0x47,0x50000);}
  gif.AddPrimPack(0x54,9,0x525252521L);gif.PackRGBA(0x80808080);
  if(sprite->kind==6){
   float zero=0.0f,one=1.0f;
   gif.PackSTQ(zero,zero,zero);gif.PackXYZ(first.x,first.y,0);
   gif.PackSTQ(one,zero,zero);gif.PackXYZ(second.x,first.y,0);
   gif.PackSTQ(zero,one,zero);gif.PackXYZ(first.x,second.y,0);
   gif.PackSTQ(one,one,zero);gif.PackXYZ(second.x,second.y,0);
   gif.AddPrimPack(0,1,0xE);gif.PackAD(0x42,0x44);gif.PackAD(0x47,0x50000);
  }
  else{
   float zero=0.0f,one=1.0f;
   gif.PackSTQ(zero,one,zero);gif.PackXYZ(first.x,first.y,0);
   gif.PackSTQ(one,one,zero);gif.PackXYZ(second.x,first.y,0);
   gif.PackSTQ(zero,zero,zero);gif.PackXYZ(first.x,second.y,0);
   gif.PackSTQ(one,zero,zero);gif.PackXYZ(second.x,second.y,0);
  }
  gif.EndPrim(1);
  VIFS vif;vif.AllocSw(20);vif.AddDmaCnt();
  vif.AddVifUnpack(UPK_V4_32,((uint)gif.m_pb-(uint)gif.m_ab)>>4,gif.m_ab,7);
  vif.AddVifMscal(D_00000650);vif.EndDmaCnt();vif.AddDmaRet();
  if(sprite->kind==6)vif.DetachCopySw(owner->heap,&sprite->data.effect.count,0,&sprite->data.effect.packet);
  else{vif.DetachCopySw(owner->heap,&sprite->data.picture.count,0,&sprite->data.picture.packet);func_00149A50(&D_003DD490,owner,D_002A8B08,sprite);}
  inner.End(2);break;
 }
 case 1:{
  sprite->data.geometry.count=func_00117C20(stream);
  RECORD *records;GROUP *groups;int i;
  { ALLOCREQ request;request.cb=sprite->data.geometry.count*sizeof(RECORD);request.cbAlign=16;
  records=(RECORD *)func_001AE378(&request);
  request.cb=sprite->data.geometry.count*sizeof(GROUP);request.cbAlign=16;
  groups=(GROUP *)func_001AE378(&request);
  i=0;
  for(;i<sprite->data.geometry.count;){
   int next=i+1;RECORD *record=&records[i];i=0;
   record->count=func_00117BD0(stream);record->format=func_00117BD0(stream);
   record->kind=func_00117BD0(stream);record->id=func_00117BD0(stream);record->extra=func_00117BD0(stream);
   record->budget=record->count+2;
   request.cb=record->count*sizeof(PAIR);request.cbAlign=16;record->coordinates=(PAIR *)func_001AE378(&request);
   request.cb=record->count;request.cbAlign=16;record->extras=(uchar *)func_001AE378(&request);
   for(;i<record->count;){
    PAIR *coordinate=&record->coordinates[i];*(uint *)&record->color=func_00117C80(stream);
    record->extras[i]=func_00117BD0(stream);i++;
    coordinate->x=func_00117D50(stream);coordinate->y=func_00117D50(stream);
   }
   i=next;
  }
  }
  sprite->data.geometry.groups=0;sprite->data.geometry.packetCount=0;sprite->data.geometry.samples=0;
  i=0;RECORD *cursor=records;
  while(i<sprite->data.geometry.count){
   GROUP *group=&groups[sprite->data.geometry.groups];group->count=0;group->samples=0;group->budget=0;group->begin=cursor;
   if(i<sprite->data.geometry.count&&cursor->budget<0xBD){
    do{group->budget+=cursor->budget;group->count++;group->samples+=cursor->count;i++;cursor++;group->end=cursor;}
    while(i<sprite->data.geometry.count&&group->budget+cursor->budget<0xBD);
   }
   sprite->data.geometry.packetCount+=group->samples/16+(group->samples+1)/4+(group->count*3+3)/4+3;
   sprite->data.geometry.groups++;sprite->data.geometry.samples+=group->samples;
  }
  VIFS vif;vif.AllocSw(sprite->data.geometry.packetCount*2);vif.AddDmaCnt();vif.AddVifStrow(&D_002A2E10);
  for(i=0;i<sprite->data.geometry.groups;){
   int next=i+1;GROUP *group=&groups[i];
   // V2_32 copies eight bytes; only the first header component is written.
   QW header;header.an[0]=group->count;vif.AddVifUnpack(UPK_V2_32,1,&header,7);vif.AddVifStcycl(1,2);
   uint *bytes,*colors;
   vif.UnpackHelper(UPK_V3_8,group->count,8,0,&bytes);vif.UnpackHelper(UPK_V4_8,group->count,9,0,&colors);
   vif.AddVifStcycl(1,1);
   int address=group->count*2+8,base=address;
   vif.AddVifStmask(0x50505050);
   int n=0,offset=0;
   for(RECORD *record=group->begin;record!=group->end;record++){
    uchar *header=(uchar *)bytes+offset;header[0]=record->kind;header[1]=record->count;header[2]=record->format;offset+=3;
    *(RAWCOLOR *)&colors[n]=record->color;n++;
    vif.AddVifUnpack((UPK)(UPK_V2_16+16),record->count,record->coordinates,address);address+=record->count;
   }
   vif.AddVifStmask(0x3F3F3F3F);address=base;
   for(RECORD *record=group->begin;record!=group->end;record++){
    if(record->extra)vif.AddVifUnpack((UPK)(UPK_S8+16),record->count,record->extras,address);
    address+=record->count;
   }
   vif.AddVifStmask(0);vif.AddVifMscal(D_00000140);i=next;
  }
  vif.EndDmaCnt();vif.AddDmaRet();vif.DetachCopySw(owner->heap,&sprite->data.geometry.packetCount,0,&sprite->data.geometry.packet);break;
 }
 }
}
