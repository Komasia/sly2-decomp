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
void*func_001AE318(const REQUEST*);
int func_001C6CE8(void*,int,int,P**);
int func_001C5570(void*,CANDIDATE*);
void func_0020FAA0(void*,qword,qword,int(*)(void*,CANDIDATE*),void*,int*,CANDIDATE***);
float func_0011D448(float,float);
float func_0011CF60(float);
qword func_0011E1A0(float,float,float);
float func_00196928(qword,qword,float,float,float,float);
void func_001C6BD0(P*,qword,qword,float,float);
}
static inline qword Scalar(U &home,float value){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(value));home.q=r;return home.q;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword AddScaled(qword a,qword b,qword s){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(s));return r;}
static inline qword Combine(qword a,qword b,qword sa,qword sb){qword r;__asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x":"=j"(r):"j"(a),"j"(b),"j"(sa),"j"(sb));return r;}
static inline float Z(qword a){float r;__asm__("pextuw %0,$zero,%1":"=r"(r):"r"(a));return r;}
static inline qword ReadPacked(const qword &a){qword r;__asm__("lq %0,%1":"=r"(r):"m"(a));return r;}
static inline void SetMode(P *p,int mode){VTE *vt=p->vt;((void(*)(void*,int))vt[76].fn)((char*)p+vt[76].delta,mode);}
static inline REGION*GetRegion(P *p){EXT *extension=p->extension;LINK *link=extension?extension->link:0;return link?link->region:0;}
static inline int TooFar(float distance,float limit){int r=1;if(!(distance>limit))r=0;return r;}
static inline qword Read1(const qword &q){register qword r __asm__("vf1");__asm__("lqc2 %0,%1":"=j"(r):"m"(q));return r;}
static inline qword Read2(const qword &q){register qword r __asm__("vf2");__asm__("lqc2 %0,%1":"=j"(r):"m"(q));return r;}
static inline qword Read3(const qword &q){register qword r __asm__("vf3");__asm__("lqc2 %0,%1":"=j"(r):"m"(q));return r;}
static inline qword Offset2(qword q){register qword r __asm__("vf2");__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(q));return r;}
static inline qword Fallback1(qword q){register qword r __asm__("vf1");__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(q));return r;}
static inline qword Displacement3(qword a,qword b){register qword r __asm__("vf3");__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Perp2(qword a,qword b){register qword r __asm__("vf2");__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scalar6(U &home,float value){register qword r __asm__("vf6");__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(value));home.q=r;return home.q;}
static inline qword Trial5(qword a,qword b){register qword r __asm__("vf5");__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Copy7(qword q){register qword r __asm__("vf7");__asm__("vmove.xyzw %0,%1":"=&j"(r):"j"(q));return r;}
static inline qword Projection2(qword a,qword axis){register qword d __asm__("vf2"),one __asm__("vf4");__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z\n\tvmulx.xyzw %0,%3,%0x":"=&j"(d),"=&j"(one):"j"(a),"j"(axis));return d;}
static inline float RootX1(qword q){register int word __asm__("$3");float f;__asm__("qmfc2.ni %0,%1":"=r"(word):"j"(q));__asm__("mtc1 %1,%0":"=f"(f):"r"(word));return f;}
static inline qword Normalize1(qword value,const qword &fallback){
 qword alt=ReadPacked(fallback);register qword square __asm__("vf1"),one __asm__("vf4");
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(square),"=&j"(one):"j"(value));
 register qword length __asm__("vf1");__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(square));length=square;
 if(RootX1(length)<0.0001f)return Fallback1(alt);
 register qword result __asm__("vf1");__asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(result):"j"(value),"j"(length));return result;
}
static inline qword Adjust2(qword trial,qword direction,qword scalar){register qword r __asm__("vf2");__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(trial),"j"(direction),"j"(scalar));return r;}
static inline float Clamp(float value,float lower,float upper){if(value<lower)return lower;if(value>upper)return upper;return value;}
static inline float Lower3(const float &field){register float r __asm__("$f3");__asm__("lwc1 %0,%1":"=f"(r):"m"(field));return r;}
static inline float Upper5(const float &field){register float r __asm__("$f5");__asm__("lwc1 %0,%1":"=f"(r):"m"(field));return r;}
static inline float Constant4(const float &field){register float r __asm__("$f4");__asm__("lwc1 %0,%1":"=f"(r):"m"(field));return r;}
static inline float Linear2(const float &field){register float r __asm__("$f2");__asm__("lwc1 %0,%1":"=f"(r):"m"(field));return r;}
static inline float Quadratic1(const float &field){register float r __asm__("$f1");__asm__("lwc1 %0,%1":"=f"(r):"m"(field));return r;}
static inline float Attempt0(int attempt){register float result __asm__("$f0");__asm__("mtc1 %1,%0\n\tcvt.s.w %0,%0":"=f"(result):"r"(attempt));return result;}
static inline float Value4(float a,float b){register float r __asm__("$f4")=a;__asm__("add.s %0,%0,%1":"+f"(r):"f"(b));return r;}
static inline float PrefixLengthXY(qword a,qword b){
 register qword d __asm__("vf1")=a;__asm__("vsub.xyzw %0,%0,%1":"+j"(d):"j"(b));
 __asm__("vmul.xy %0,%0,%0\n\tvaddy.x %0,%0,%0y":"+j"(d));
 __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));
 register int word __asm__("$2");float distance;
 __asm__("qmfc2.ni %0,%1":"=r"(word):"j"(d));__asm__("mtc1 %1,%0":"=f"(distance):"r"(word));return distance;
}
static inline qword Bound5(U &home,float f){register qword r __asm__("vf5");__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));home.q=r;return home.q;}
static inline qword Bound3(U &home,float f){register qword r __asm__("vf3");__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));home.q=r;return home.q;}
static inline qword Add4(qword a,qword b,qword s){register qword r __asm__("vf4");__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(s));return r;}
static inline qword Add1(qword a,qword b,qword s){register qword r __asm__("vf1");__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(s));return r;}
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
 qword snapped=Read2(snap.q);
 if(TooFar(PrefixLengthXY(Read1(original.q),snapped),D_002C0E80))return;
 if(!func_001C6DE8(-250.0f,1500.0f,D_002A775C,snapped,0,0,&snap.q))return;
 WORK work;
 work.box.request.size=requested*4;work.box.request.alignment=16;
 P **objects=(P**)func_001AE318(&work.box.request);
 int available=func_001C6CE8(world,kind,requested,objects);
 if(!available)return;
 qword center=Read1(snap.q),axis=Read2(D_002A2DE0);float extent=D_002C0E84;
 work.upper=Add4(center,axis,Bound5(work.scalar,extent));
 work.box.lower=Add1(center,axis,Bound3(work.scalar,-extent));
 func_0020FAA0(D_003DD490,work.box.lower,work.upper,func_001C5570,0,&work.count,&work.candidates);
 int attempt=0,launched=0;
 float angle=func_0011D448(-3.1415927f,3.1415927f),radius=D_002C0E8C;
 P **cursor=objects;
 while(launched<available){
  float phase=Attempt0(attempt)*0.02f;
  float quadratic=Quadratic1(D_002C0EA0[2]),linear=Linear2(D_002C0EA0[1]),constant=Constant4(D_002C0EA0[0]);
  float amplitude=Value4(constant,phase*(linear+phase*quadratic));
  amplitude=Clamp(amplitude,Lower3(D_002C0EB0[0]),Upper5(D_002C0EB0[1]));
  work.base=snap.q;
  qword offset=Offset2(func_0011E1A0(angle,radius,0.0f));
  qword amount=Scalar6(work.scalar,amplitude);
  qword trial=Trial5(Read1(work.base),offset);
  qword delta=Displacement3(trial,Read3(original.q));
  qword projected=Projection2(delta,Read1(D_002A2DC0));
  qword trialCopy=Copy7(trial);
  qword direction=Normalize1(Perp2(delta,projected),D_002A2DA0);
  work.trial=trial;work.adjusted=Adjust2(trialCopy,direction,amount);
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
