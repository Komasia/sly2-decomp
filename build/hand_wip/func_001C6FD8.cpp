typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct VTE {short delta,pad;void(*fn)();};
struct REGION;
struct LINK {char pad10[0x10];REGION *region;};
struct EXT {char padDC[0xDC];LINK *link;};
struct P {char padC[0xC];VTE *vt;char pad10[0xD8];EXT *extension;char padEC[0xEC];float radius;};
struct CANDIDATE;
struct REQUEST {int size,alignment;};
struct FRAME;
extern "C" FRAME*func_001AE478(FRAME*);
extern "C" void func_001AE4A0(FRAME*,int);
struct FRAME {FRAME(){func_001AE478(this);}~FRAME(){func_001AE4A0(this,2);}};
union BOX {REQUEST request;qword lower;};
struct WORK {FRAME frame;BOX box;qword upper;U scalar,other;int count;CANDIDATE **candidates;qword base,adjusted,landing,trial;};
extern "C" {
extern char D_003DD490[];
extern qword D_002A2DA0,D_002A2DC0,D_002A2DE0,D_002C0D60;
extern float D_002A775C,D_002A7760,D_002C0D70;
extern float D_002C0E80,D_002C0E84,D_002C0E88,D_002C0E8C,D_002C0E90,D_002C0E94;
extern float D_002C0EA0[3],D_002C0EB0[2],D_002C0EB8,D_002C0EBC,D_002C0EC0,D_002C0EC4;
int func_001C6DE8(float,float,float,qword,int,CANDIDATE**,qword*);
P*func_001C4840(void*);
REGION*func_001C0D70(qword,int);
int func_001C0940(REGION*,qword,qword*,int);
int func_001C0980(REGION*,qword,qword,int);
qword func_001A62E8(P*);
void*func_001AE318(REQUEST*);
int func_001C6CE8(void*,int,int,P**);
int func_001C5570(void*,CANDIDATE*);
void func_0020FAA0(void*,qword,qword,int(*)(void*,CANDIDATE*),void*,int*,CANDIDATE***);
float func_0011D448(float,float);
float func_0011CF60(float);
qword func_0011E1A0(float,float,float);
float func_00196928(qword,qword,float,float,float,float);
void func_001C6BD0(P*,qword,qword,float,float);
}
static inline qword CopyVU(qword value){qword r;__asm__("vmove.xyzw %0,%1":"=&j"(r):"j"(value));return r;}
static inline qword ToVU(qword value){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(value));return r;}
static inline qword Scalar(U &home,float value){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(value));home.q=r;return home.q;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword AddScaled(qword a,qword b,qword s){qword r;__asm__("vadda.xyzw $ACC,$vf0,%1\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(s));return r;}
static inline qword Combine(qword a,qword b,qword sa,qword sb){qword r;__asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x":"=j"(r):"j"(a),"j"(b),"j"(sa),"j"(sb));return r;}
static inline qword Perpendicular(qword a,qword axis){qword d,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z\n\tvmulx.xyzw %0,%3,%0x\n\tvsub.xyzw %0,%2,%0":"=&j"(d),"=&j"(one):"j"(a),"j"(axis));return d;}
static inline qword Square(qword a){qword r,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=j"(one):"j"(a));return r;}
static inline qword Root(qword a){qword r;__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(r):"j"(a));return r;}
static inline float X(qword a){float r;__asm__("mtc1 %1,%0":"=f"(r):"r"(a));return r;}
static inline float Z(qword a){float r;__asm__("pextuw %0,$zero,%1":"=r"(r):"r"(a));return r;}
static inline qword ReadPacked(const qword &a){qword r;__asm__("lq %0,%1":"=r"(r):"m"(a));return r;}
static inline qword Divide(qword a,qword length){qword r;__asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(r):"j"(a),"j"(length));return r;}
static inline qword Normalize(qword a,const qword &fallback){qword alt=ReadPacked(fallback),length=Root(Square(a));if(X(length)<0.0001f)return ToVU(alt);return Divide(a,length);}
static inline float LengthXY(qword a,qword b){qword d=Sub(a,b);__asm__("vmul.xy %0,%0,%0\n\tvaddy.x %0,%0,%0y":"+j"(d));return X(Root(d));}
static inline void SetMode(P *p,int mode){VTE *vt=p->vt;((void(*)(void*,int))vt[76].fn)((char*)p+vt[76].delta,mode);}
static inline REGION*GetRegion(P *p){EXT *extension=p->extension;LINK *link=extension?extension->link:0;return link?link->region:0;}
static inline int TooFar(float distance,float limit){int r=1;if(!(distance>limit))r=0;return r;}
extern "C" void func_001C6FD8(void *world,int kind,qword seed,P *owner,int requested){
 U original,snap;
 if(!func_001C6DE8(0.0f,300.0f,D_002A775C,seed,0,0,&original.q))return;
 P *nearest=func_001C4840(world);
 REGION *region=0;
 if(nearest)region=GetRegion(nearest);
 if(!region)region=func_001C0D70(original.q,1);
 float height;
 if(!func_001C0940(region,original.q,&snap.q,1)){
  qword position=func_001A62E8(nearest);
  if(!func_001C0940(region,position,&snap.q,1))return;
  height=Z(position);
 }else height=original.f[2];
 snap.f[2]=height;
 if(TooFar(LengthXY(original.q,snap.q),D_002C0E80))return;
 if(!func_001C6DE8(-250.0f,1500.0f,D_002A775C,snap.q,0,0,&snap.q))return;
 WORK work;
 work.box.request.size=requested*4;work.box.request.alignment=16;
 P **objects=(P**)func_001AE318(&work.box.request);
 int available=func_001C6CE8(world,kind,requested,objects);
 if(!available)return;
 work.upper=AddScaled(snap.q,D_002A2DE0,Scalar(work.scalar,D_002C0E84));
 work.box.lower=AddScaled(snap.q,D_002A2DE0,Scalar(work.scalar,-D_002C0E84));
 func_0020FAA0(D_003DD490,work.box.lower,work.upper,func_001C5570,0,&work.count,&work.candidates);
 int attempt=0,launched=0;
 float angle=func_0011D448(-3.1415927f,3.1415927f),radius=D_002C0E8C;
 P **cursor=objects;
 while(launched<available){
  float phase=(float)attempt*0.02f;
  float amplitude=D_002C0EA0[0]+phase*(D_002C0EA0[1]+phase*D_002C0EA0[2]);
  if(amplitude<D_002C0EB0[0])amplitude=D_002C0EB0[0];else if(amplitude>D_002C0EB0[1])amplitude=D_002C0EB0[1];
  work.base=snap.q;
  qword offset=ToVU(func_0011E1A0(angle,radius,0.0f));
  qword amount=Scalar(work.scalar,amplitude);
  qword trial=Add(work.base,offset);
  qword direction=Normalize(Perpendicular(Sub(trial,original.q),D_002A2DC0),D_002A2DA0);
  work.trial=trial;work.adjusted=AddScaled(CopyVU(trial),direction,amount);
  int blocked=0;
  if(!func_001C0980(region,snap.q,work.trial,0))blocked=!func_001C0980(region,work.trial,work.adjusted,0);
  if(blocked&&func_001C6DE8(-300.0f,300.0f,0.7f,work.trial,work.count,work.candidates,&work.scalar.q)){
   work.landing=AddScaled(work.scalar.q,D_002A2DC0,Scalar(work.other,(*cursor)->radius-1.0f));
   float duration=func_00196928(Sub(work.landing,original.q),D_002C0D60,D_002C0EB8,D_002C0EBC,D_002C0EC0,D_002C0EC0);
   duration+=(float)launched*D_002C0EC4;++launched;
   qword velocity=Combine(Sub(work.landing,original.q),D_002C0D60,Scalar(work.other,1.0f/duration),Scalar(work.other,-0.5f*duration));
   func_001C6BD0(*cursor++,original.q,velocity,(float)launched*D_002C0D70,D_002A7760);
  }
  angle=func_0011CF60(angle+D_002C0E94);
  radius+=D_002C0E90;if(radius>D_002C0E84)radius-=D_002C0E84-D_002C0E88;
  if(++attempt>=50)break;
 }
 int remaining=available-launched;
 P **unused=objects+launched;
 while(remaining>0){P *p=*unused++;--remaining;SetMode(p,2);}
}

#define OFF(t,m) ((unsigned int)&((t*)0)->m)
typedef char launch_layout[(sizeof(void*)==4 && sizeof(qword)==16 && sizeof(U)==16 && sizeof(VTE)==8 && sizeof(REQUEST)==8 && sizeof(BOX)==16 && sizeof(FRAME)==1 && __alignof__(FRAME)==1 && sizeof(WORK)==0xA0 && OFF(VTE,delta)==0 && OFF(VTE,fn)==4 && OFF(LINK,region)==0x10 && OFF(EXT,link)==0xDC && OFF(P,vt)==0xC && OFF(P,extension)==0xE8 && OFF(P,radius)==0x1D8 && OFF(REQUEST,size)==0 && OFF(REQUEST,alignment)==4 && OFF(WORK,frame)==0 && OFF(WORK,box)==0x10 && OFF(WORK,upper)==0x20 && OFF(WORK,scalar)==0x30 && OFF(WORK,other)==0x40 && OFF(WORK,count)==0x50 && OFF(WORK,candidates)==0x54 && OFF(WORK,base)==0x60 && OFF(WORK,adjusted)==0x70 && OFF(WORK,landing)==0x80 && OFF(WORK,trial)==0x90)?1:-1];
