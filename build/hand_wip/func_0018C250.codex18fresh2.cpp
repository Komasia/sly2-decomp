typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
union U{qword q;float f[4];};struct M3{U r[3];};struct M4{U r[4];};
struct VE{short delta,pad;void*fn;};
struct TABLE{char pad0[0x74];float duration,rate;};
struct MODEL{char pad0[12];VE*vt;char pad10[4];TABLE*table;char pad18[4];float base;};
struct INPUT{char pad0[0x18];float heading,amount;};
struct NODE{char pad0[12];VE*vt;char pad10[0x50];void*context;char pad64[0x9C];NODE*owner;char pad104[12];NODE*secondary;char pad114[16];int orientation;char pad128[4];int effect;};
struct POINT{char pad0[0x20];float velocity[3];};struct LINK{int unknown;NODE*object;};
struct TRIREF{int index;float u,v;};struct SM;struct FX;
struct CLOCK{float time,dt;};
struct WORK{U scalar;M4 frame;float angle;int effect;SM*state;uint flags;int keep;U cached,origin,quotient,result;};
struct P{
 char pad0[0xc];
 VE* vt;
 char pad10[0x48];
 NODE* leftPart;
 NODE* rightPart;
 void* context;
 char pad64[0xec];
 INPUT* input;
 char pad154[0x3c];
 U velocity;
 float progress;
 char pad1A4[0x4];
 float heading;
 char pad1AC[0x4];
 M3 basis;
 char pad1E0[0x20];
 float speed;
 char pad204[0xbc];
 char control[0x3C];
 float height;
 char pad300[0x7c];
 NODE* focus;
 char pad380[0x140];
 char gate[8];
 int gateState;
 char pad4CC[0x924];
 char track[0x110];
 char launch[0x50];
 char alternate[12];
 NODE* gateTarget;
 char padF60[0xc4];
 NODE* linkedOwner;
 SM* idle;
 SM* quiet;
 MODEL* model;
 NODE* component;
 int modelKey;
 char pad103C[0x50];
 int busy;
 char pad1090[0x4c];
 NODE* owner;
 int flags;
 char pad10E4[0xcc];
 char special[4];
 char pad11B4[0x16c];
 char motion[4];
 TABLE* motionClip;
 char pad1328[0x1a8];
 TABLE* axisA;
 char pad14D4[0x4];
 int axisAlternate;
 char pad14DC[0x38];
 int reset;
 char pad1518[0x3a8];
 int surface;
 NODE* target;
 int mode;
 float modeTime;
 int submode;
 float submodeTime;
 int state;
 char pad18DC[0x8];
 int finished;
 int ready;
 char pad18EC[0x4];
 int fall;
 float transitionTime;
 int transitionId;
 int reverse;
 LINK* link;
 char pad1904[0x4c];
 SM* run;
 char pad1954[0xc];
 U relative;
 char pad1970[0x24];
 TABLE* rideClip;
 float incoming;
 float outgoing;
 char pad19A0[0x4];
 NODE* rider;
 char pad19A8[0x8];
 float deadline;
 char pad19B4[0xc];
 POINT* point;
 char pad19C4[0x3c];
 POINT* otherPoint;
 char pad1A04[0x50];
 int responseAvailable;
 char pad1A58[0x18];
 int responseAllowed;
 char pad1A74[0x8];
 TABLE* clip9;
 TABLE* clip13;
 TABLE* clip14;
 char pad1A88[0x8];
 void* surfaceRef;
 char pad1A94[0x14];
 NODE* normalNode;
 NODE* alternateNode;
 char pad1AB0[0x110];
 TABLE* axisB;
 SM* axisState;
 TABLE* clip11;
 char pad1BCC[0x8];
 int pulse;
 char pad1BD8[0x58];
 char control12[4];
 TABLE* clip12;
 char pad1C38[0xd0];
 TABLE* clip6;
 TABLE* clip7;
 TABLE* clip8;
 char pad1D14[0x8];
 TABLE* ownerClip;
 char pad1D20[0xc];
 int ownerEnabled;
 int enabled;
 TABLE* clip17;
 char pad1D38[0x1d8];
 TABLE* clip11State;
 SM* extraState;
 NODE* anchor;
 TRIREF reference;
 char pad1F28[0x68];
 TABLE* clip22;
 char pad1F94[0x54];
 TABLE* clip9State;
 char pad1FEC[0x4];
 char joint[4];
 char pad1FF4[0x20];
 float left;
 char pad2018[0x8];
 float middle;
 char pad2024[0x8];
 float right;
 char pad2030[0x8];
 TABLE* blend;
 char pad203C[0x14];
 TABLE* specialClip;
};
extern "C"{
extern CLOCK D_002DDED0;extern char D_003DD490[],D_002DEB30[];extern qword D_002A2DD0;
extern float D_002BF358,D_002BF35C,D_002BF3E0,D_002BF3E4,D_002BF3E8;
FX*func_001FBB90(int);void func_001FB2F8(FX*,P*);void func_001FB1F8(FX*,float);void func_001FB4F0(FX*,float,float);void func_001FB3F0(FX*,qword);
void func_0018E540(P*,int);void func_0015C150(NODE*);void func_00195FB8(void*,int,int);
void func_00133448(NODE*,P*);void func_001333C0(NODE*,P*);
void func_00230100(P*,POINT*,POINT*);void func_00229738(NODE*);void func_002296C0(void*,LINK*);void func_00140C88(P*,NODE*);
void func_0019EAB0(void*,int);void func_00192BD8(void*,int);void func_001A0B40(void*,int);void func_002206C8(void*,int);void func_001375D0(void*,int);
void func_001F2A60(P*,void*);void func_002303A0(P*,NODE*,int);void func_00142880(P*);int func_00131968(MODEL*);void func_00209EE0(NODE*);
void func_001F5720(P*,int);void func_001619A0(void*,int,P*);
qword func_001A62E8(void*);int func_001F0400(SM*,int);uint func_001430C8(P*);void func_00142868(P*,int);
int func_001374F0(void*);void func_00230018(P*,POINT*,POINT*);qword func_00190C58(P*);void func_00190E18(P*);void func_00190BE0(P*,float*);
float func_0011CF60(float);void func_00204660(P*,float);void func_0018FC60(P*);void func_0019CD38(void*,int);void func_0018DF50(P*,int);
void func_0018F688(P*);void func_0018F740(P*);void func_0020BD68(void*);int func_001DAEA8(int);void func_0018E1E0(P*);void func_00204CA8(P*);
void func_002046B0(P*,qword);float func_0012F990(TABLE*,int);
void func_001300B8(TABLE*,P*,void*,void*,float,float,M4*,M4*);
void func_00185310(NODE*,qword,void*,TRIREF*,qword*,qword*);
void func_001384C0(TABLE*);qword func_0011E1A0(float,float,float);
void func_0018C120(P*,uint);void func_00130B18(MODEL*);void func_001F0598(NODE*);
void func_0012F9B8(TABLE*,P*,float,float,int,MODEL**);NODE*func_001F03A8(SM*,P*,int,int,uint);
}
static __inline__ void*At(P*p,int offset){return(char*)p+offset;}
static __inline__ void VirtualVoid(void*object,int slot){NODE*p=(NODE*)object;VE&e=p->vt[slot];((void(*)(void*))e.fn)((char*)p+e.delta);}
static __inline__ void Message(NODE*p,int kind){VE&e=p->vt[3];((void(*)(void*,int,void*,void*,void*,void*))e.fn)((char*)p+e.delta,kind,0,0,0,0);}
static __inline__ qword VirtualVector(NODE*p,int slot){VE&e=p->vt[slot];return((qword(*)(void*))e.fn)((char*)p+e.delta);}
static __inline__ void SetVector(P*p,int slot,qword v){VE&e=p->vt[slot];((void(*)(void*,qword))e.fn)((char*)p+e.delta,v);}
static __inline__ qword Scalar(float f){int bits;qword r;__asm__("mfc1 %0,%1":"=r"(bits):"f"(f));__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(bits));return r;}
static __inline__ qword RawScalar(float f){qword bits;__asm__("mfc1 %0,%1":"=r"(bits):"f"(f));return bits;}
static __inline__ float Z(qword q){float r;__asm__("pextuw %0,$zero,%1":"=r"(r):"r"(q));return r;}
static inline qword ReadVector(const U*home){qword value;__asm__("lqc2 %0,%1":"=j"(value):"m"(home->q));return value;}
static inline qword VectorValue(qword raw){qword value;__asm__("qmtc2.ni %1,%0":"=j"(value):"r"(raw));return value;}
static inline void PublishRaw(U*home,qword raw){__asm__ __volatile__("sq %1,%0":"=m"(home->q):"r"(raw));}
static inline qword RawVectorBits(qword vector){register qword raw __asm__("$2");__asm__("qmfc2.ni %0,%1":"=r"(raw):"j"(vector));return raw;}
struct OWNER_SNAPSHOT{U elapsed,position;};
typedef char snapshot_width[(sizeof(OWNER_SNAPSHOT)==32)?1:-1];
typedef char snapshot_adjacent[((unsigned)&((WORK*)0)->result-(unsigned)&((WORK*)0)->quotient==16)?1:-1];
static inline qword OwnerRelativeAndQuery(P*p,const OWNER_SNAPSHOT*snapshot,qword velocity,const U*home,U*result){
 register qword point __asm__("vf2"),row0 __asm__("vf4"),row1 __asm__("vf1"),row2 __asm__("vf5"),frame __asm__("vf3");
 register const M3*address __asm__("$3");register P*receiver __asm__("$4");
 __asm__("lqc2 %0,16+%9\n\taddiu %4,%6,0x1b0\n\tlqc2 %2,%9\n\tdaddu %5,%6,$zero\n\tqmtc2.ni %8,%1\n\tvadda.xyzw ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x\n\tlqc2 %3,0x20(%4)\n\tlqc2 %2,0x10(%4)\n\tlqc2 %1,0x1b0(%6)"
 :"=&j"(point),"=&j"(row0),"=&j"(row1),"=&j"(row2),"=&r"(address),"=&r"(receiver)
 :"r"(p),"m"(p->basis),"r"(velocity),"m"(*snapshot));
 __asm__("lqc2 %1,%5\n\tvmulax.xyz ACC,%2,%1x\n\tvmadday.xyz ACC,%3,%1y\n\tvmaddz.xyz %1,%4,%1z\n\tvsub.xyzw %0,%0,%1"
 :"+j"(point),"=&j"(frame):"j"(row0),"j"(row1),"j"(row2),"m"(home->q));
 result->q=point;
 return func_001A62E8(receiver);
}
static __inline__ qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static __inline__ qword Scale(qword a,qword f){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(f));return r;}
static __inline__ qword RotatePartial(const M3&m,qword value){register qword r __asm__("vf6");__asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(value));return r;}
static __inline__ qword Divide(qword value,qword divisor){qword r;__asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(r):"j"(value),"j"(divisor));return r;}
static __inline__ void ClearVelocity(P*p){p->velocity.f[1]=0.0f;p->velocity.f[2]=0.0f;p->velocity.f[0]=0.0f;}
static inline int ReadMode(const P*p){int value;__asm__("lw %0,%1":"=r"(value):"m"(p->mode));return value;}
extern "C" void func_0018C250(P*p,int mode,int submode){
 WORK w;TABLE*clip=0;void*reset;uint joy=0;int key=-1,kind=1;float seek=0.0f,rate=1.0f;
 w.effect=-1;w.state=0;w.flags=0xFFFC;w.keep=0;
 int oldMode=p->mode;
 if(oldMode==mode&&p->submode==submode)return;
 if(oldMode!=mode){
  if(mode==2){
   switch(oldMode){case 3:case 22:p->focus=p->target;break;case 8:p->focus=p->gateTarget;break;case 21:p->focus=p->anchor;break;default:p->focus=0;break;}
  }
  oldMode=ReadMode(p);
  switch(oldMode){
  case 2:{
   switch(mode){
   case 3:case 8:case 18:break;
   case 7:
    if(p->gateState==1)break;
   default:
    {FX*fx=func_001FBB90(0x3D);func_001FB2F8(fx,p);func_001FB1F8(fx,0.7f);func_001FB4F0(fx,500.0f,1000.0f);}break;
   }
   if(p->state==0&&mode!=8&&mode!=3&&mode!=22)func_0018E540(p,-1);
   if(!p->busy){
    NODE*node=0;
    switch(mode){
    case 0:case 1:case 5:case 9:case 24:node=p->normalNode;break;
    case 7:if(p->gateState==1)break;if(p->gateState>0){if(p->gateState<5){node=p->gateState>=3?p->alternateNode:p->normalNode;break;}}node=p->normalNode;break;
    case 2:case 3:case 4:case 6:case 8:case 10:case 11:case 12:case 13:case 14:case 15:case 16:case 17:case 18:case 19:case 20:case 21:case 22:case 23:break;
    default:break;
    }
    if(node){VirtualVoid(node,8);func_0015C150(node);VirtualVoid(node,9);}
   }
   func_00195FB8(At(p,0x2C0),-1,0);break;
  }
  case 3:
   Message(p->target,6);func_00133448(p->target,p);func_0018E540(p,-1);func_00230100(p,p->point,p->otherPoint);
   if(p->link){func_00229738(p->link->object);func_002296C0(D_003DD490,p->link);p->link=0;}
   func_00140C88(p,0);break;
  case 8:func_0019EAB0(At(p,0xF50),-1);func_0018E540(p,(mode==2&&p->axisAlternate)?11:-1);break;
  case 7:func_00192BD8(At(p,0x4C0),-1);break;
  case 4:func_001A0B40(At(p,0xDF0),-1);break;
  case 23:func_002206C8(At(p,0x11B0),-1);break;
  case 6:func_001375D0(At(p,0x1FF0),-1);break;
  case 9:p->surface=0;func_001F2A60(p,p->surfaceRef);break;
  case 0:
   func_002303A0(p,p->leftPart,2);func_002303A0(p,p->rightPart,2);
   switch(p->state){case 6:func_0018E540(p,4);break;case 7:func_0018E540(p,5);break;case 8:case 9:func_0018E540(p,-1);break;case 10:case 11:break;case 12:if(submode!=6)func_0018E540(p,14);break;case 13:if(submode!=7)func_0018E540(p,15);break;default:break;}
   func_00142880(p);break;
  case 11:p->flags&=~2;break;
  case 1:case 10:case 12:p->progress=p->model->base/p->model->table->duration;break;
  case 16:if(p->model&&!func_00131968(p->model))func_00209EE0(p->owner);p->ownerEnabled=0;p->flags&=~4;break;
  case 18:case 19:case 20:func_002303A0(p,p->leftPart,2);func_002303A0(p,p->rightPart,2);break;
  case 21:
   func_001F5720(p,0);Message(p->anchor,6);if(p->linkedOwner==p->anchor->secondary)func_00140C88(p,0);p->anchor=0;break;
  case 22:func_001F5720(p,0);Message(p->target,6);func_00133448(p->target,p);p->target=0;func_00140C88(p,0);break;
  case 17:p->enabled=0;func_001619A0(D_002DEB30,0x38,p);break;
  case 24:p->speed=1.0f;p->input->heading=p->heading;break;
  case 13:p->surface=0;break;
  case 5:case 14:case 15:default:break;
  }
  switch(mode){
  case 0:
   w.state=p->idle;func_002303A0(p,p->leftPart,1);func_002303A0(p,p->rightPart,1);p->reset=0;
   switch(p->mode){
   case 12:key=0x176;break;
   default:key=0x175;break;
   case 10:key=0x177;break;
   case 2:{
    int fall=p->fall;
    if(fall==-1)fall=p->height-Z(func_001A62E8(p))>D_002BF3E0;
    key=fall==1?0x179:0x178;
    break;}
   }
   if(func_001F0400(w.state,key)<0)key=-1;
   w.flags=func_001430C8(p);ClearVelocity(p);joy=0x1F;
   if(p->responseAvailable&&p->responseAllowed){switch(p->state){case 4:func_0018E540(p,6);joy=0x1F;break;case 5:func_0018E540(p,7);joy=0x1F;break;default:break;}}
   func_00142868(p,1);break;
  case 1:
   clip=p->motionClip;kind=9;reset=At(p,0x1320);goto resetMotion;
  case 6:w.keep=1;func_001375D0(At(p,0x1FF0),func_001374F0(At(p,0x1FF0)));break;
  case 3:{
   p->transitionId=-1;p->incoming=p->outgoing=1.0f;p->transitionTime=D_002DDED0.time;clip=p->rideClip;
   p->otherPoint->velocity[1]=0.0f;p->otherPoint->velocity[2]=0.0f;p->otherPoint->velocity[0]=0.0f;seek=0.5f;rate=0.0f;
   func_00230018(p,p->point,p->otherPoint);
   w.cached.q=func_001A62E8(p->rider);p->relative.q=Sub(w.cached.q,func_00190C58(p));func_00190E18(p);
   Message(p->target,5);func_001333C0(p->target,p);func_00190BE0(p,&w.angle);
   float reverseHeading=func_0011CF60(w.angle+3.14159265f);int orientation=p->target?p->target->orientation:1;
   switch(orientation){
   case 0:if(__builtin_fabsf(func_0011CF60(w.angle-p->input->heading))<1.57079637f){func_00204660(p,w.angle);p->reverse=0;}else{func_00204660(p,reverseHeading);p->reverse=1;}break;
   case 1:func_00204660(p,w.angle);p->reverse=0;break;
   case 2:func_00204660(p,reverseHeading);p->reverse=1;break;
   default:break;
   }
   w.effect=p->target->effect;func_0018E540(p,1);ClearVelocity(p);func_0018FC60(p);func_00140C88(p,p->target->owner);break;
  }
  case 8:func_0019EAB0(At(p,0xF50),0);w.keep=1;break;
  case 4:func_0019CD38(At(p,0xF00),-1);func_0018DF50(p,0);break;
  case 7:if(p->gateState<5)joy=p->gateState<3?0:7;break;
  case 23:w.keep=1;break;
  case 9:func_0018E540(p,-1);func_0018F688(p);clip=p->clip9;break;
  case 13:func_0018E540(p,-1);ClearVelocity(p);func_0018F740(p);p->deadline=D_002DDED0.time+D_002BF3E4;clip=p->clip13;break;
  case 14:func_0018E540(p,-1);ClearVelocity(p);clip=p->clip14;break;
  case 10:clip=p->axisB;kind=9;p->modelKey=-1;seek=p->progress*clip->duration;break;
  case 11:clip=p->clip11;p->flags|=2;joy=0x64;p->velocity.q=D_002A2DD0;p->pulse=0;break;
  case 12:clip=p->clip12;kind=9;reset=At(p,0x1C30);
resetMotion:
   seek=p->progress*clip->duration;func_0020BD68(reset);break;
  case 16:
   p->flags|=4;
   if(func_001DAEA8(0x1C)){
    clip=p->specialClip;func_0018E1E0(p);w.scalar.q=Scalar(-1.0f);
    SetVector(p,35,RotatePartial(p->basis,Scale(p->velocity.q,w.scalar.q)));func_00204CA8(p);
   }else{
    clip=p->ownerClip;w.origin.q=func_001A62E8(p->owner);
    qword currentPosition=func_001A62E8(p);
    w.scalar.q=Scalar(-1.0f);
    func_002046B0(p,Scale(Sub(ReadVector(&w.origin),VectorValue(currentPosition)),w.scalar.q));func_00204CA8(p);
    float advance=func_0012F990(clip,0x173);float zero=0.0f;
    func_001300B8(clip,p,p->rider->context,p->context,advance,zero,&w.frame,0);
    float elapsed=advance/clip->rate;
    qword ownerPosition=func_001A62E8(p->owner);
    qword elapsedBits=RawScalar(elapsed);
    w.quotient.q=elapsedBits;
    PublishRaw(&w.scalar,elapsedBits);
    w.result.q=VectorValue(ownerPosition);
    qword ownerVelocity=VirtualVector(p->owner,33);
    qword position=OwnerRelativeAndQuery(p,(const OWNER_SNAPSHOT*)&w.quotient,ownerVelocity,&w.frame.r[3],&w.result);
    qword divisor=ReadVector(&w.quotient),relative=ReadVector(&w.result);
    qword delta=Sub(relative,VectorValue(position));
    qword divisorBits=RawVectorBits(divisor);
    PublishRaw(&w.scalar,divisorBits);
    p->velocity.q=Divide(delta,divisor);p->velocity.f[2]=zero;SetVector(p,35,p->velocity.q);
   }break;
  case 18:w.state=p->quiet;func_002303A0(p,p->leftPart,1);func_002303A0(p,p->rightPart,1);ClearVelocity(p);func_0018E540(p,-1);
  case 19:func_002303A0(p,p->leftPart,1);func_002303A0(p,p->rightPart,1);ClearVelocity(p);func_0018E540(p,-1);break;
  case 20:func_002303A0(p,p->leftPart,2);func_002303A0(p,p->rightPart,2);ClearVelocity(p);func_0018E540(p,-1);break;
  case 17:clip=p->clip17;kind=9;func_001619A0(D_002DEB30,0x37,p);break;
  case 21:
   func_00185310(p->anchor,func_001A62E8(p),0,&p->reference,0,0);func_001F5720(p,1);SetVector(p,35,D_002A2DD0);SetVector(p,36,D_002A2DD0);ClearVelocity(p);Message(p->anchor,5);if(p->anchor->secondary)func_00140C88(p,p->anchor->secondary);break;
  case 22:
   clip=p->clip22;kind=9;func_0018E540(p,-1);func_001F5720(p,1);SetVector(p,35,D_002A2DD0);SetVector(p,36,D_002A2DD0);ClearVelocity(p);Message(p->target,5);func_001333C0(p->target,p);func_00140C88(p,p->target->owner);break;
  case 24:
   kind=9;joy=0x18;p->right=0.0f;p->left=0.0f;p->middle=1.0f;func_001384C0(p->blend);clip=p->blend;
   func_00204660(p,p->input->heading);SetVector(p,35,func_0011E1A0(p->heading,D_002BF3E8,0.0f));ClearVelocity(p);break;
  case 2:case 5:case 15:default:break;
  }
 }
 if(p->submode!=submode){
  switch(submode){
  case 0:case 1:case 2:
   if(p->model&&p->model->table==p->rideClip)w.keep=1;
   else{clip=p->rideClip;seek=clip->duration*0.5f;rate=0.0f;}break;
  case 3:w.state=p->run;break;
  case 4:w.state=p->axisState;ClearVelocity(p);break;
  case 5:clip=p->axisA;p->modelKey=-1;ClearVelocity(p);kind=9;break;
  case 6:func_0018E540(p,-1);clip=p->clip6;ClearVelocity(p);p->ready=0;p->finished=0;break;
  case 7:func_0018E540(p,-1);clip=p->clip7;ClearVelocity(p);p->ready=0;p->finished=0;break;
  case 8:case 9:clip=submode==8?p->clip8:p->clip9State;p->finished=0;ClearVelocity(p);break;
  case 10:w.state=p->extraState;break;
  case 11:clip=p->clip11State;kind=9;break;
  case 12:joy=0x18;p->speed=D_002BF358;break;
  case 13:joy=0x18;w.keep=1;p->speed=D_002BF35C;break;
  case -1:default:break;
  }
 }
 if(p->mode!=mode){p->mode=mode;p->modeTime=D_002DDED0.time;}
 if(p->submode!=submode){p->submode=submode;p->submodeTime=D_002DDED0.time;}
 VirtualVoid(p,90);func_0018C120(p,joy);
 if(w.effect!=-1){FX*fx=func_001FBB90(w.effect);func_001FB2F8(fx,0);func_001FB3F0(fx,func_001A62E8(p));}
 if(w.keep)return;
 if(p->model){func_00130B18(p->model);VirtualVoid(p->model,2);p->model=0;}
 else if(p->component){func_001F0598(p->component);VirtualVoid(p->component,2);p->component=0;}
 if(clip){func_0012F9B8(clip,p,seek,rate,kind,&p->model);VirtualVoid(p->model,1);}
 else if(w.state){p->component=func_001F03A8(w.state,p,key,kind,w.flags);VirtualVoid(p->component,1);}
}

typedef char layout_pointer[(sizeof(void*)==4)?1:-1];
typedef char layout_qword[(sizeof(qword)==16)?1:-1];
typedef char layout_U[(sizeof(U)==16)?1:-1];
typedef char layout_M3[(sizeof(M3)==0x30)?1:-1];
typedef char layout_M4[(sizeof(M4)==0x40)?1:-1];
typedef char layout_VE[(sizeof(VE)==8)?1:-1];
typedef char layout_TABLE_prefix[(sizeof(TABLE)==0x7C)?1:-1];
typedef char layout_MODEL_prefix[(sizeof(MODEL)==0x20)?1:-1];
typedef char layout_INPUT[(sizeof(INPUT)==0x20)?1:-1];
typedef char layout_NODE_prefix[(sizeof(NODE)==0x130)?1:-1];
typedef char layout_POINT_prefix[(sizeof(POINT)==0x2C)?1:-1];
typedef char layout_LINK_prefix[(sizeof(LINK)==8)?1:-1];
typedef char layout_TRIREF[(sizeof(TRIREF)==12)?1:-1];
typedef char layout_CLOCK_prefix[(sizeof(CLOCK)==8)?1:-1];
typedef char layout_WORK[(sizeof(WORK)==0xB0)?1:-1];
typedef char layout_P_prefix[(sizeof(P)==0x2060)?1:-1];
typedef char layout_U_q[((unsigned long)&((U*)0)->q==0x0)?1:-1];
typedef char layout_U_f[((unsigned long)&((U*)0)->f==0x0)?1:-1];
typedef char layout_VE_delta[((unsigned long)&((VE*)0)->delta==0x0)?1:-1];
typedef char layout_VE_fn[((unsigned long)&((VE*)0)->fn==0x4)?1:-1];
typedef char layout_TABLE_duration[((unsigned long)&((TABLE*)0)->duration==0x74)?1:-1];
typedef char layout_TABLE_rate[((unsigned long)&((TABLE*)0)->rate==0x78)?1:-1];
typedef char layout_MODEL_vt[((unsigned long)&((MODEL*)0)->vt==0xc)?1:-1];
typedef char layout_MODEL_table[((unsigned long)&((MODEL*)0)->table==0x14)?1:-1];
typedef char layout_MODEL_base[((unsigned long)&((MODEL*)0)->base==0x1c)?1:-1];
typedef char layout_INPUT_heading[((unsigned long)&((INPUT*)0)->heading==0x18)?1:-1];
typedef char layout_INPUT_amount[((unsigned long)&((INPUT*)0)->amount==0x1c)?1:-1];
typedef char layout_NODE_vt[((unsigned long)&((NODE*)0)->vt==0xc)?1:-1];
typedef char layout_NODE_context[((unsigned long)&((NODE*)0)->context==0x60)?1:-1];
typedef char layout_NODE_owner[((unsigned long)&((NODE*)0)->owner==0x100)?1:-1];
typedef char layout_NODE_secondary[((unsigned long)&((NODE*)0)->secondary==0x110)?1:-1];
typedef char layout_NODE_orientation[((unsigned long)&((NODE*)0)->orientation==0x124)?1:-1];
typedef char layout_NODE_effect[((unsigned long)&((NODE*)0)->effect==0x12c)?1:-1];
typedef char layout_POINT_velocity[((unsigned long)&((POINT*)0)->velocity==0x20)?1:-1];
typedef char layout_LINK_object[((unsigned long)&((LINK*)0)->object==0x4)?1:-1];
typedef char layout_TRIREF_index[((unsigned long)&((TRIREF*)0)->index==0x0)?1:-1];
typedef char layout_TRIREF_u[((unsigned long)&((TRIREF*)0)->u==0x4)?1:-1];
typedef char layout_TRIREF_v[((unsigned long)&((TRIREF*)0)->v==0x8)?1:-1];
typedef char layout_CLOCK_time[((unsigned long)&((CLOCK*)0)->time==0x0)?1:-1];
typedef char layout_CLOCK_dt[((unsigned long)&((CLOCK*)0)->dt==0x4)?1:-1];
typedef char layout_WORK_scalar[((unsigned long)&((WORK*)0)->scalar==0x0)?1:-1];
typedef char layout_WORK_frame[((unsigned long)&((WORK*)0)->frame==0x10)?1:-1];
typedef char layout_WORK_angle[((unsigned long)&((WORK*)0)->angle==0x50)?1:-1];
typedef char layout_WORK_effect[((unsigned long)&((WORK*)0)->effect==0x54)?1:-1];
typedef char layout_WORK_state[((unsigned long)&((WORK*)0)->state==0x58)?1:-1];
typedef char layout_WORK_flags[((unsigned long)&((WORK*)0)->flags==0x5c)?1:-1];
typedef char layout_WORK_keep[((unsigned long)&((WORK*)0)->keep==0x60)?1:-1];
typedef char layout_WORK_cached[((unsigned long)&((WORK*)0)->cached==0x70)?1:-1];
typedef char layout_WORK_origin[((unsigned long)&((WORK*)0)->origin==0x80)?1:-1];
typedef char layout_WORK_quotient[((unsigned long)&((WORK*)0)->quotient==0x90)?1:-1];
typedef char layout_WORK_result[((unsigned long)&((WORK*)0)->result==0xa0)?1:-1];
typedef char layout_P_vt[((unsigned long)&((P*)0)->vt==0xc)?1:-1];
typedef char layout_P_leftPart[((unsigned long)&((P*)0)->leftPart==0x58)?1:-1];
typedef char layout_P_rightPart[((unsigned long)&((P*)0)->rightPart==0x5c)?1:-1];
typedef char layout_P_context[((unsigned long)&((P*)0)->context==0x60)?1:-1];
typedef char layout_P_input[((unsigned long)&((P*)0)->input==0x150)?1:-1];
typedef char layout_P_velocity[((unsigned long)&((P*)0)->velocity==0x190)?1:-1];
typedef char layout_P_progress[((unsigned long)&((P*)0)->progress==0x1a0)?1:-1];
typedef char layout_P_heading[((unsigned long)&((P*)0)->heading==0x1a8)?1:-1];
typedef char layout_P_basis[((unsigned long)&((P*)0)->basis==0x1b0)?1:-1];
typedef char layout_P_speed[((unsigned long)&((P*)0)->speed==0x200)?1:-1];
typedef char layout_P_control[((unsigned long)&((P*)0)->control==0x2c0)?1:-1];
typedef char layout_P_height[((unsigned long)&((P*)0)->height==0x2fc)?1:-1];
typedef char layout_P_focus[((unsigned long)&((P*)0)->focus==0x37c)?1:-1];
typedef char layout_P_gate[((unsigned long)&((P*)0)->gate==0x4c0)?1:-1];
typedef char layout_P_gateState[((unsigned long)&((P*)0)->gateState==0x4c8)?1:-1];
typedef char layout_P_track[((unsigned long)&((P*)0)->track==0xdf0)?1:-1];
typedef char layout_P_launch[((unsigned long)&((P*)0)->launch==0xf00)?1:-1];
typedef char layout_P_alternate[((unsigned long)&((P*)0)->alternate==0xf50)?1:-1];
typedef char layout_P_gateTarget[((unsigned long)&((P*)0)->gateTarget==0xf5c)?1:-1];
typedef char layout_P_linkedOwner[((unsigned long)&((P*)0)->linkedOwner==0x1024)?1:-1];
typedef char layout_P_idle[((unsigned long)&((P*)0)->idle==0x1028)?1:-1];
typedef char layout_P_quiet[((unsigned long)&((P*)0)->quiet==0x102c)?1:-1];
typedef char layout_P_model[((unsigned long)&((P*)0)->model==0x1030)?1:-1];
typedef char layout_P_component[((unsigned long)&((P*)0)->component==0x1034)?1:-1];
typedef char layout_P_modelKey[((unsigned long)&((P*)0)->modelKey==0x1038)?1:-1];
typedef char layout_P_busy[((unsigned long)&((P*)0)->busy==0x108c)?1:-1];
typedef char layout_P_owner[((unsigned long)&((P*)0)->owner==0x10dc)?1:-1];
typedef char layout_P_flags[((unsigned long)&((P*)0)->flags==0x10e0)?1:-1];
typedef char layout_P_special[((unsigned long)&((P*)0)->special==0x11b0)?1:-1];
typedef char layout_P_motion[((unsigned long)&((P*)0)->motion==0x1320)?1:-1];
typedef char layout_P_motionClip[((unsigned long)&((P*)0)->motionClip==0x1324)?1:-1];
typedef char layout_P_axisA[((unsigned long)&((P*)0)->axisA==0x14d0)?1:-1];
typedef char layout_P_axisAlternate[((unsigned long)&((P*)0)->axisAlternate==0x14d8)?1:-1];
typedef char layout_P_reset[((unsigned long)&((P*)0)->reset==0x1514)?1:-1];
typedef char layout_P_surface[((unsigned long)&((P*)0)->surface==0x18c0)?1:-1];
typedef char layout_P_target[((unsigned long)&((P*)0)->target==0x18c4)?1:-1];
typedef char layout_P_mode[((unsigned long)&((P*)0)->mode==0x18c8)?1:-1];
typedef char layout_P_modeTime[((unsigned long)&((P*)0)->modeTime==0x18cc)?1:-1];
typedef char layout_P_submode[((unsigned long)&((P*)0)->submode==0x18d0)?1:-1];
typedef char layout_P_submodeTime[((unsigned long)&((P*)0)->submodeTime==0x18d4)?1:-1];
typedef char layout_P_state[((unsigned long)&((P*)0)->state==0x18d8)?1:-1];
typedef char layout_P_finished[((unsigned long)&((P*)0)->finished==0x18e4)?1:-1];
typedef char layout_P_ready[((unsigned long)&((P*)0)->ready==0x18e8)?1:-1];
typedef char layout_P_fall[((unsigned long)&((P*)0)->fall==0x18f0)?1:-1];
typedef char layout_P_transitionTime[((unsigned long)&((P*)0)->transitionTime==0x18f4)?1:-1];
typedef char layout_P_transitionId[((unsigned long)&((P*)0)->transitionId==0x18f8)?1:-1];
typedef char layout_P_reverse[((unsigned long)&((P*)0)->reverse==0x18fc)?1:-1];
typedef char layout_P_link[((unsigned long)&((P*)0)->link==0x1900)?1:-1];
typedef char layout_P_run[((unsigned long)&((P*)0)->run==0x1950)?1:-1];
typedef char layout_P_relative[((unsigned long)&((P*)0)->relative==0x1960)?1:-1];
typedef char layout_P_rideClip[((unsigned long)&((P*)0)->rideClip==0x1994)?1:-1];
typedef char layout_P_incoming[((unsigned long)&((P*)0)->incoming==0x1998)?1:-1];
typedef char layout_P_outgoing[((unsigned long)&((P*)0)->outgoing==0x199c)?1:-1];
typedef char layout_P_rider[((unsigned long)&((P*)0)->rider==0x19a4)?1:-1];
typedef char layout_P_deadline[((unsigned long)&((P*)0)->deadline==0x19b0)?1:-1];
typedef char layout_P_point[((unsigned long)&((P*)0)->point==0x19c0)?1:-1];
typedef char layout_P_otherPoint[((unsigned long)&((P*)0)->otherPoint==0x1a00)?1:-1];
typedef char layout_P_responseAvailable[((unsigned long)&((P*)0)->responseAvailable==0x1a54)?1:-1];
typedef char layout_P_responseAllowed[((unsigned long)&((P*)0)->responseAllowed==0x1a70)?1:-1];
typedef char layout_P_clip9[((unsigned long)&((P*)0)->clip9==0x1a7c)?1:-1];
typedef char layout_P_clip13[((unsigned long)&((P*)0)->clip13==0x1a80)?1:-1];
typedef char layout_P_clip14[((unsigned long)&((P*)0)->clip14==0x1a84)?1:-1];
typedef char layout_P_surfaceRef[((unsigned long)&((P*)0)->surfaceRef==0x1a90)?1:-1];
typedef char layout_P_normalNode[((unsigned long)&((P*)0)->normalNode==0x1aa8)?1:-1];
typedef char layout_P_alternateNode[((unsigned long)&((P*)0)->alternateNode==0x1aac)?1:-1];
typedef char layout_P_axisB[((unsigned long)&((P*)0)->axisB==0x1bc0)?1:-1];
typedef char layout_P_axisState[((unsigned long)&((P*)0)->axisState==0x1bc4)?1:-1];
typedef char layout_P_clip11[((unsigned long)&((P*)0)->clip11==0x1bc8)?1:-1];
typedef char layout_P_pulse[((unsigned long)&((P*)0)->pulse==0x1bd4)?1:-1];
typedef char layout_P_control12[((unsigned long)&((P*)0)->control12==0x1c30)?1:-1];
typedef char layout_P_clip12[((unsigned long)&((P*)0)->clip12==0x1c34)?1:-1];
typedef char layout_P_clip6[((unsigned long)&((P*)0)->clip6==0x1d08)?1:-1];
typedef char layout_P_clip7[((unsigned long)&((P*)0)->clip7==0x1d0c)?1:-1];
typedef char layout_P_clip8[((unsigned long)&((P*)0)->clip8==0x1d10)?1:-1];
typedef char layout_P_ownerClip[((unsigned long)&((P*)0)->ownerClip==0x1d1c)?1:-1];
typedef char layout_P_ownerEnabled[((unsigned long)&((P*)0)->ownerEnabled==0x1d2c)?1:-1];
typedef char layout_P_enabled[((unsigned long)&((P*)0)->enabled==0x1d30)?1:-1];
typedef char layout_P_clip17[((unsigned long)&((P*)0)->clip17==0x1d34)?1:-1];
typedef char layout_P_clip11State[((unsigned long)&((P*)0)->clip11State==0x1f10)?1:-1];
typedef char layout_P_extraState[((unsigned long)&((P*)0)->extraState==0x1f14)?1:-1];
typedef char layout_P_anchor[((unsigned long)&((P*)0)->anchor==0x1f18)?1:-1];
typedef char layout_P_reference[((unsigned long)&((P*)0)->reference==0x1f1c)?1:-1];
typedef char layout_P_clip22[((unsigned long)&((P*)0)->clip22==0x1f90)?1:-1];
typedef char layout_P_clip9State[((unsigned long)&((P*)0)->clip9State==0x1fe8)?1:-1];
typedef char layout_P_joint[((unsigned long)&((P*)0)->joint==0x1ff0)?1:-1];
typedef char layout_P_left[((unsigned long)&((P*)0)->left==0x2014)?1:-1];
typedef char layout_P_middle[((unsigned long)&((P*)0)->middle==0x2020)?1:-1];
typedef char layout_P_right[((unsigned long)&((P*)0)->right==0x202c)?1:-1];
typedef char layout_P_blend[((unsigned long)&((P*)0)->blend==0x2038)?1:-1];
typedef char layout_P_specialClip[((unsigned long)&((P*)0)->specialClip==0x2050)?1:-1];
