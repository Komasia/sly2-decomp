// Resolve object entries, compute spans and attach linked resources.
typedef int qword __attribute__((mode(TI)));
union F {float value;int bits;};
union U {qword q;float a[4];};
struct P;
struct REF {char pad[0x70];qword position;};
struct E {int id;REF *reference;int pad8;float x,y;char pad14[0x10];F lower,upper;int pad2C;U position; qword top,bottom;};
struct SIDE {int id;REF *reference;void *binding;int padC,pad10;};
struct ATTACH {char pad[0x18];int id;void *object;void *binding;char pad24[8];int meshId;REF *mesh;void *meshBinding;int extraId;void *extra;};
struct P {char pad[0x190];int count;char pad194[0xC];E entries[8];float width;int sideCount;SIDE sides[4];int attachCount;ATTACH*attachments[8];char pad51C[0x50];void *asset;void *binding;char pad574[0x38];void *path;};
extern "C" {
extern qword D_002A2DC0,D_002A2DD0;
extern char D_003DD490[];
void func_001F36A8(P *);
REF *func_001F4C58(P *,int,int);
void *func_002332B8(void *,const void *,int);
qword func_001A6F00(void *,P *,qword);
void *func_0012DC18(P *,REF *,int,int,int,qword);
void *func_0015E938(void *,int,int,P *);
void *func_001F0380(void *,P *,int,int);
void *func_001E94B0(int,int);
void func_001F1448(void *,P *,int,int,void **);
void func_001D14C0(P *);
}
static inline qword Zero(){qword r;asm("vsub.xyzw %0,$vf0,$vf0":"=j"(r));return r;}
static inline qword Scalar(int word){qword r;asm("qmtc2.ni %1,%0":"=j"(r):"r"(word));return r;}
static inline qword Min(qword a,qword b){asm("vmini.xyz %0,%1,%0":"+j"(b):"j"(a));return b;}
static inline qword Max(qword a,qword b){asm("vmax.xyz %0,%1,%0":"+j"(b):"j"(a));return b;}
static inline qword AddUp(qword pos,const qword *up,qword scalar){
 qword r,axis;
 asm("lqc2 %1,%3\n\tvadda.xyzw $ACC,$vf0,%2\n\tvmaddx.xyzw %0,%1,%4x":"=j"(r),"=&j"(axis):"j"(pos),"m"(*up),"j"(scalar));
 return r;
}
static inline qword CPU(qword value){qword result;asm("qmfc2.ni %0,%1":"=r"(result):"j"(value));return result;}
static inline float X(qword value){float r;asm("mtc1 %1,%0":"=f"(r):"r"(value));return r;}
static inline float Y(qword value){qword r;asm("prot3w %0,%1":"=r"(r):"r"(value));return X(r);}
static inline float MaxF(float a,float b){float r;asm("max.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
extern "C" void func_001D1518(P *p){
 U scalar,maximum,minimum;
 int i=0;
 {qword zero=Zero();minimum.q=CPU(zero);maximum.q=zero;}
 func_001F36A8(p);
 if(p->count>0){qword *up=&D_002A2DC0;
 E *cursor=p->entries,*next=cursor+1;
 do {
  E *e=cursor;
  REF *reference=func_001F4C58(p,e->id,13);
  e->reference=reference;
  if(!reference){
   func_002332B8(e,next,(p->count-i)*sizeof(E)-sizeof(E));
   --p->count;--i;--cursor;--next;
  }else{
   qword pos=func_001A6F00(0,p,reference->position);
   e->position.q=pos;
   qword top=Scalar(e->upper.bits);scalar.q=top;
   qword bottom=Scalar(e->lower.bits);
   minimum.q=Min(pos,minimum.q);maximum.q=Max(pos,maximum.q);
   e->top=AddUp(pos,up,scalar.q);
   scalar.q=bottom;
   e->bottom=AddUp(pos,up,scalar.q);
  }
  ++i;++cursor;++next;
 }while(i<p->count);}
 void **binding=&p->binding;
 float maxX=X(maximum.q),minX=X(minimum.q);
 p->width=maxX-minX;
 if(p->count>0){
  float xScale=MaxF(-minX,maxX);
  float yScale=MaxF(-Y(minimum.q),Y(maximum.q));
  for(i=0;i<p->count;i++){
   E *e=&p->entries[i];e->x=e->position.a[0]/xScale;e->y=e->position.a[1]/yScale;
  }
 }
 {SIDE *side=p->sides,*next=side+1;
 for(i=0;i<p->sideCount;i++,side++,next++){
  REF *reference=func_001F4C58(p,side->id,6);
  side->reference=reference;
  if(!reference){
   func_002332B8(side,next,(p->sideCount-i)*sizeof(SIDE)-sizeof(SIDE));
   --p->sideCount;--i;--side;--next;
  }else side->binding=func_0012DC18(p,reference,1,7,3,D_002A2DD0);
 }}
 {ATTACH **cursor=p->attachments;
 for(int j=0,byteOffset=0;j<p->attachCount;j++,cursor++,byteOffset+=4){
  ATTACH *attach=*cursor;
  attach->object=func_0015E938(D_003DD490,1,attach->id,p);
  if(attach->object){
   attach->mesh=func_001F4C58(p,attach->meshId,6);
   if(attach->mesh || attach->meshId==-1){
    attach->extra=func_0015E938(D_003DD490,1,attach->extraId,p);
    if(attach->extra || attach->extraId==-1){
     attach->binding=func_001F0380(attach->object,p,-1,0);
     if(attach->mesh)attach->meshBinding=func_0012DC18(p,attach->mesh,1,7,3,D_002A2DD0);
     continue;
    }
   }
  }
  func_002332B8(cursor,(char*)p->attachments+byteOffset+4,(p->attachCount-j)*4-4);
  --p->attachCount;--j;--cursor;byteOffset-=4;
 }}
 p->path=func_001E94B0(0x2C9,16);
 func_001F1448(p->asset,p,-1,0,binding);
 func_001D14C0(p);
}
