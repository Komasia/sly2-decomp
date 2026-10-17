
typedef int qword __attribute__((mode(TI)));typedef unsigned int uint;
union U{qword q;float f[4];int i[4];};struct M3{U row[3];};struct M4{U row[4];};struct VTE{short delta,pad;void*fn;};struct ACTOR;struct SOURCE;struct OBJECT;struct SPACE;struct CLIP;struct SUB;
struct INPUT{char pad0[0x10];float x,y,heading,amount;};struct PHYSICS{char pad0[0x80];U gravity;};
struct BODY{char pad0[0x30];U position;char pad40[0x60];SPACE*frame;char padA4[4];float deadline;char padAC[4];U initialVelocity,goal,velocity;};
struct ACTOR{char pad0[0xC];VTE*vt;char pad10[0x48];BODY*body;char pad5C[0x8C];PHYSICS*physics;char padEC[0x64];INPUT*input;char pad154[0x3C];U velocity;char pad1A0[8];float heading;char pad1AC[4];M3 local;char pad1E0[0x60];U offset;};
struct DATA{char pad0[4];float amount;};struct SOURCE{char pad0[0xC];VTE*vt;char pad10[0x104];DATA*data;char pad118[0x40];float height;char pad15C[0x18];SOURCE*next;char pad178[4];int state;};
struct OBJECT{char pad0[0xC];VTE*vt;char pad10[0xD0];OBJECT*next;char padE4[4];float radius;char padEC[0x48];int focusState;};
union WORD{int bits;float amount;};struct TRACK{int opaque;WORD control;float weight;};
struct CONTEXT{ACTOR*actor;int state,variant;void*source;float parameter,value,stamp;int mode;float time;int flags24,flags28,flags2C,actionFlag;float gain,scale,height;int combo;float time44,time48,time4C;char pad50[0x50];U desired;float lastHeading,minimumCosine,speedLimit;void*previousTarget;char padC0[0xA0];OBJECT*velocitySource;WORD velocityScale;float oldScale;OBJECT*focus,*other;int focused;CLIP*scripted;float scriptedGain;char pad180[4];TRACK tracks[4];char pad1B4[4];CLIP*multi;SOURCE*scriptFocus;float blend0,blend1;};
class WRITER{public:char bytes[0x20];virtual void f1();virtual void f2();virtual void f3(ACTOR*,U*,float*,float);};class PREFIX_E0{public:char bytes[0xE0];};class PREFIX_190{public:char bytes[0x190];};class WRITER_E0:public PREFIX_E0,public WRITER{};class WRITER_190:public PREFIX_190,public WRITER{};
struct CLOCK{float time,dt;};struct LM{float low,high;};struct SMP{float maximum,minimum,duration;};
union GOALS{struct{U desired,velocity,bestVelocity,unused;}motion;M3 basis;};
union SCRATCH{U v[10];struct{M3 first,rotation,product;}matrices;struct{M4 forecast;U point,scalar;M4 derivative;}prediction;};
struct WORK{U position,initialVelocity,point;GOALS goals;SCRATCH scratch;float duration,score,firstAlpha,firstDistance,secondAlpha,secondDistance,heading,sine,cosine;U localPoint,pending,overrideScalar,nodePosition;};
extern "C"{
extern CLOCK D_002DDED0;extern ACTOR*D_002E1E40;extern SOURCE*D_003E13E4;extern OBJECT*D_003E1420;extern U D_002A2DD0,D_002A2DC0,D_002A2DA0,D_002BF890;extern float D_002BF780[5],D_002BF730,D_002BF734,D_002BF834,D_002BF838,D_002BF83C,D_002BF840,D_002BF844,D_002BF848,D_002BF878,D_002BF87C,D_002BF880,D_002BF8A0;
extern SMP D_002BF860;extern LM D_002BF868,D_002BF850,D_002BF870,D_002BF858;
qword func_001A62E8(void*);void func_0019A4A0(CONTEXT*,qword,void*,qword,qword,float*,float*,U*,U*);void func_0011EE08(qword,qword,qword,U*,float*,float*);qword func_0022D348(SPACE*,int,qword);qword func_0022FC48(SPACE*,SPACE*,qword),func_0022FCC8(SPACE*,SPACE*,qword);void func_00195FB8(CONTEXT*,int,void*);void func_002309E8(SPACE*,SPACE*,M4*,M4*,float);void func_00117120(float,float,float,qword,qword,qword,qword,U*,U*,U*);
void func_00204660(ACTOR*,float);float func_00204740(ACTOR*);float func_0011CF60(float);void func_0011D608(float,float*,float*);float func_0011D018(SMP*,float,float,float,float*);void func_001384C0(CLIP*);void func_001E67B8(void*,float,U*,U*);void func_001CC2E8(SUB*);void func_002046B0(ACTOR*,qword);void func_001441E8(ACTOR*,float);qword func_0011E1A0(float,float,float);void func_0011BA08(M3*,qword,qword);void func_0011B500(M3*,qword,float);float func_002458F0(float,float);float func_00244E10(float);float func_0011E290(qword,qword,U*,U*);qword func_0011E9F8(qword,float);void func_00140C88(ACTOR*,OBJECT*);
}
static inline qword Read(U*p){qword q;__asm__("lqc2 %0,%1":"=j"(q):"m"(*p));return q;}
static inline void Store(U*p,qword q){__asm__("sqc2 %1,%0":"=m"(*p):"j"(q));}
static inline qword ToVector(qword q){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(q));return r;}
static inline qword Scalar(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword Sub(qword a,qword b){qword q;__asm__("vsub.xyzw %0,%1,%2":"=j"(q):"j"(a),"j"(b));return q;}
static inline qword AddScaled(qword a,qword b,qword k){qword q;__asm__("vadda.xyzw $ACC,$vf0,%1\n\tvmaddx.xyzw %0,%2,%3x":"=j"(q):"j"(a),"j"(b),"j"(k));return q;}
static inline qword Blend(qword a,qword b,qword ka,qword c,qword kc){qword q;__asm__("vadda.xyzw $ACC,$vf0,%1\n\tvmaddax.xyzw $ACC,%2,%3x\n\tvmaddx.xyzw %0,%4,%5x":"=j"(q):"j"(a),"j"(b),"j"(ka),"j"(c),"j"(kc));return q;}
static inline qword Scale(qword a,qword k){qword q;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(q):"j"(a),"j"(k));return q;}
static inline qword SquareXYZ(qword a){qword q,k;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(q),"=&j"(k):"j"(a));return q;}
static inline qword SquareXY(qword a){qword q;__asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(q):"j"(a));return q;}
static inline qword Root(qword a){qword q;__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(q):"j"(a));return q;}
static inline float X(qword a){float f;__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(a));return f;}
static inline float Z(qword a){qword q;float f;__asm__("qmfc2.ni %0,%1":"=r"(q):"j"(a));__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(q));return f;}
static inline float LengthXY(qword a){return X(Root(SquareXY(a)));}
static inline float Min(float a,float b){float f;__asm__("min.s %0,%1,%2":"=f"(f):"f"(a),"f"(b));return f;}
static inline qword Make3(float x,float y,float z){qword q;__asm__("pextlw %0,%2,%1\n\tpcpyld %0,%3,%0":"=&r"(q):"r"(x),"r"(y),"r"(z));return q;}
static inline qword Velocity(void*p){VTE*vt=((ACTOR*)p)->vt;VTE&v=vt[33];return ((qword(*)(void*))v.fn)((char*)p+v.delta);}
static inline SPACE*Frame(void*p){VTE*vt=((OBJECT*)p)->vt;VTE&v=vt[32];return ((SPACE*(*)(void*,void*))v.fn)((char*)p+v.delta,0);}
static inline int Facing(ACTOR*p){VTE&v=p->vt[92];return ((int(*)(void*))v.fn)((char*)p+v.delta);}
static inline qword Point(M4*m,qword a){__asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddaz.xyz $ACC,%3,%4z\n\tvmaddw.xyz %0,%5,$vf0w":"+j"(a):"j"(Read(&m->row[0])),"j"(Read(&m->row[1])),"j"(Read(&m->row[2])),"j"(a),"j"(Read(&m->row[3])));return a;}
static inline qword Rotate(M3*m,qword a){__asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"+j"(a):"j"(Read(&m->row[0])),"j"(Read(&m->row[1])),"j"(Read(&m->row[2])),"j"(a));return a;}
static inline M3 Mul(const M3&a,const M3&b) return r{r.row[0].q=Rotate((M3*)&a,b.row[0].q);r.row[1].q=Rotate((M3*)&a,b.row[1].q);r.row[2].q=Rotate((M3*)&a,b.row[2].q);}
static inline void MulTo(M3*r,const M3&a,const M3&b){r->row[0].q=Rotate((M3*)&a,b.row[0].q);r->row[1].q=Rotate((M3*)&a,b.row[1].q);r->row[2].q=Rotate((M3*)&a,b.row[2].q);}
static inline qword Dot(qword a,qword b){qword q,k;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(q),"=&j"(k):"j"(a),"j"(b));return q;}
static inline qword Transpose(M3*m,qword a){qword r=Read(&m->row[0]),p0,p1,p2,k;__asm__("vmul.xyzw %1,%0,%5\n\tvmaxw.xyzw %4,$vf0,$vf0w\n\tvmul.xyzw %2,%6,%5\n\tvmul.xyzw %3,%7,%5\n\tvadday.x $ACC,%1,%1y\n\tvmaddz.x %0,%4,%1z\n\tvaddax.y $ACC,%2,%2x\n\tvmaddz.y %0,%4,%2z\n\tvaddax.z $ACC,%3,%3x\n\tvmaddy.z %0,%4,%3y":"+j"(r),"=&j"(p0),"=&j"(p1),"=&j"(p2),"=&j"(k):"j"(a),"j"(Read(&m->row[1])),"j"(Read(&m->row[2])));return r;}
static inline float Normalize(U*p){qword a=Read(p),root=Root(SquareXYZ(a));float length=X(root);if(length<0.0001f)p->q=D_002A2DA0.q;else{qword q;__asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(q):"j"(a),"j"(root));Store(p,q);}return length;}
// The native scalar home stores the GPR word; only its float X lane is consumed.
static inline void StoreWord(U*p,int value){__asm__("sq %1,%0":"=m"(*p):"r"(value));}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
extern "C" void func_00197F98(CONTEXT*p){
 WORK w;INPUT*input=p->actor->input;
 switch(p->combo){
 case 0:if(0.9f<input->amount){p->combo=1;p->time48=D_002DDED0.time;}else if(D_002BF834<D_002DDED0.time-p->time44)p->flags24=1;break;
 case 1:if(input->amount<0.9f){p->combo=2;p->time4C=D_002DDED0.time;if(D_002DDED0.time-p->time48<D_002BF838)p->flags24=1;}break;
 case 3:if(0.2f<input->amount)p->flags24=1;break;
 }
 w.position.q=func_001A62E8(p->actor);w.initialVelocity.q=Velocity(p->actor);
 switch(p->mode){
 // Out-of-range modes enter this search in the native table guard.
 case 1:case 3:case 4:case 5:case 17:default:{
  SOURCE*selected=0;OBJECT*selectedOther=0;float best=1500.0f;float selectedDuration;
  for(SOURCE*node=D_003E13E4;node;node=node->next){
   if(node->state)continue;
   qword position=ToVector(func_001A62E8(node));
   if(360000.0f<X(SquareXY(Sub(position,Read(&w.position)))))continue;
   if(Z(position)+node->height<w.position.f[2])continue;
   qword local=Sub(position,Read(&p->actor->offset));Store(&w.nodePosition,position);
   func_0019A4A0(p,w.initialVelocity.q,node,local,D_002A2DD0.q,&w.duration,&w.score,&w.point,&w.goals.motion.velocity);
   if(best<w.score)continue;
   Store(&w.scratch.v[0],Sub(Read(&w.position),Read(&w.nodePosition)));
   qword initial=Read(&w.initialVelocity);Store(&w.nodePosition,initial);qword velocity=ToVector(Velocity(node));
   qword factor=Scalar(Min(0.25f,w.duration));w.scratch.v[0].f[2]=0;
   qword relative=Sub(Read(&w.nodePosition),velocity);qword closest=AddScaled(Read(&w.scratch.v[0]),relative,factor);Store(&w.scratch.v[2],closest);w.scratch.v[2].f[2]=0;Store(&w.scratch.v[1],relative);Store(&w.scratch.v[3],factor);
   func_0011EE08(D_002A2DD0.q,w.scratch.v[0].q,w.scratch.v[2].q,0,&w.firstAlpha,&w.firstDistance);
   if((D_002BF83C<w.firstDistance||w.firstAlpha==0.0f)&&(D_002BF83C*0.25f<w.firstDistance||0.0f<w.initialVelocity.f[2]))continue;
   selected=node;selectedOther=0;w.goals.motion.desired.q=w.point.q;w.goals.motion.bestVelocity.q=w.goals.motion.velocity.q;selectedDuration=w.duration;best=w.score;
  }
  for(OBJECT*node=D_003E1420;node;node=node->next){
   qword position=ToVector(func_001A62E8(node));Store(&w.scratch.v[0],position);
   if(D_002BF840*D_002BF840<X(SquareXY(Sub(Read(&w.position),position))))continue;
   func_0019A4A0(p,w.initialVelocity.q,node,Sub(position,Read(&p->actor->offset)),D_002A2DD0.q,&w.duration,&w.score,&w.point,&w.goals.motion.velocity);
   if(best<w.score)continue;
   SPACE*space=Frame(node);qword velocity=ToVector(func_0022D348(space,0,w.scratch.v[0].q));
   qword delta=Sub(Read(&w.position),Read(&w.scratch.v[0])),relative=Sub(Read(&w.initialVelocity),velocity),factor=Scalar(Min(0.25f,w.duration));
   Store(&w.scratch.v[2],delta);w.scratch.v[2].f[2]=0;Store(&w.scratch.v[4],AddScaled(delta,relative,factor));w.scratch.v[4].f[2]=0;Store(&w.scratch.v[1],velocity);Store(&w.scratch.v[3],relative);Store(&w.scratch.v[5],factor);
   func_0011EE08(D_002A2DD0.q,w.scratch.v[2].q,w.scratch.v[4].q,0,&w.secondAlpha,&w.secondDistance);
   if((node->radius<w.secondDistance||w.secondAlpha==0.0f)&&(node->radius*0.25f<w.secondDistance||0.0f<w.initialVelocity.f[2]))continue;
   selectedOther=node;selected=0;w.goals.motion.desired.q=w.point.q;w.goals.motion.bestVelocity.q=w.goals.motion.velocity.q;selectedDuration=w.duration;best=w.score;
  }
  if(selected||selectedOther){BODY*body=p->actor->body;body->deadline=D_002DDED0.time+selectedDuration;body->goal.q=func_0022FC48(0,body->frame,w.goals.motion.desired.q);
   qword velocity=Make3(w.goals.motion.bestVelocity.f[0],w.goals.motion.bestVelocity.f[1],w.initialVelocity.f[2]+selectedDuration*p->actor->physics->gravity.f[2]);
   w.scratch.v[0].q=func_0022FCC8(0,body->frame,velocity);body->velocity.q=w.scratch.v[0].q;
   if(selected)func_00195FB8(p,6,selected);else func_00195FB8(p,8,selectedOther);
  }
  break;
 }
 case 0:case 2:case 6:case 7:case 8:case 9:case 10:case 11:case 12:case 13:case 14:case 15:case 16:case 18:case 19:case 20:case 21:case 22:break;
 }
 w.heading=p->actor->heading;

 WRITER*writer;
 switch(p->mode){
 case 6:case 8:Store(&w.point,Sub(ToVector(func_001A62E8(p->source)),Read(&p->actor->offset)));
 predictSource:{BODY*body=p->actor->body;float remaining=body->deadline-D_002DDED0.time;SPACE*frame=Frame(p->source);
  func_002309E8(frame,0,&w.scratch.prediction.forecast,&w.scratch.prediction.derivative,remaining);w.localPoint.q=func_0022FC48(0,frame,w.point.q);
  qword predicted=Point(&w.scratch.prediction.forecast,ToVector(w.localPoint.q));body->goal.q=func_0022FC48(0,body->frame,predicted);
  if(p->mode!=10){Store(&w.scratch.prediction.point,Point(&w.scratch.prediction.derivative,Read(&w.localPoint)));w.scratch.prediction.point.f[2]=w.initialVelocity.f[2]+remaining*p->actor->physics->gravity.f[2];body->velocity.q=func_0022FCC8(0,body->frame,w.scratch.prediction.point.q);}
 }
  break;
 case 10:case 11:writer=(WRITER_190*)p->source;
 sampleSource:writer->f3(p->actor,&w.point,&w.heading,p->value);goto predictSource;
 case 9:writer=(WRITER_E0*)p->source;goto sampleSource;
 case 12:writer=(WRITER_E0*)p->source;goto sampleSource;
 case 13:writer=(WRITER_E0*)p->source;goto sampleSource;
 case 18:w.point.q=func_001A62E8(p->source);goto predictSource;
 default:break;
 }

 if((6<=p->mode&&p->mode<17&&p->mode!=7)||p->mode==18){BODY*body=p->actor->body;float remaining=body->deadline-D_002DDED0.time+D_002DDED0.dt;
  func_00117120(remaining,0,1,body->position.q,body->initialVelocity.q,body->goal.q,body->velocity.q,0,0,&w.goals.motion.desired);
  func_00117120(remaining,remaining,1,body->position.q,body->initialVelocity.q,body->goal.q,body->velocity.q,0,0,&w.goals.motion.velocity);
  float cost=(X(Root(SquareXYZ(Read(&w.goals.motion.desired))))+X(Root(SquareXYZ(Read(&w.goals.motion.velocity)))))*(remaining*0.5f);
  if(D_002BF844<cost)func_00195FB8(p,4,0);
 }
 float offset=D_002BF780[p->variant],heading=p->actor->heading;
 switch(p->mode){
 case 0:if(0.2f<input->amount)heading=input->heading+offset;break;
 case 11:case 12:case 13:heading=w.heading;break;
 case 20:{
  float oldHeading=func_00204740(p->actor);float difference=func_0011CF60(input->heading-oldHeading);func_0011D608(difference,&w.sine,&w.cosine);
  float lateral=w.sine*input->amount,forward=w.cosine*input->amount,mix=(forward+1.0f)*0.5f;
  if(p->scriptFocus){DATA*data=p->scriptFocus->data;data->amount=func_0011D018(&D_002BF860,data->amount,(1.0f-mix)*D_002BF868.low+mix*D_002BF868.high,D_002DDED0.dt,0);}
  p->blend0=(1.0f-mix)*D_002BF850.low+mix*D_002BF850.high;
  float turn=((1.0f-mix)*D_002BF870.low+mix*D_002BF870.high)*lateral*D_002DDED0.dt;
  p->blend1=(1.0f-mix)*D_002BF858.low+mix*D_002BF858.high;p->scriptedGain=1.0f-input->amount;
  heading=oldHeading+turn;
  if(input->amount!=0){float factor=input->amount/(__builtin_fabsf(lateral)+__builtin_fabsf(forward));
   if(lateral<0){p->tracks[0].control.amount=0;p->tracks[1].control.amount=-lateral*factor;}else{p->tracks[1].control.amount=0;p->tracks[0].control.amount=lateral*factor;}
   if(0<forward){p->tracks[3].control.amount=0;p->tracks[2].control.amount=forward*factor;}else{p->tracks[2].control.amount=0;p->tracks[3].control.amount=-forward*factor;}
  }else{p->tracks[3].control.amount=p->tracks[0].control.amount=p->tracks[1].control.amount=p->tracks[2].control.amount=0;}
  func_001384C0(p->multi);break;
 }
 case 14:case 15:
  if(p->mode==15)func_001E67B8(p->source,p->parameter,&w.goals.motion.desired,0);else w.goals.motion.desired.q=func_001A62E8(p->source);
  if(p->actor!=D_002E1E40)func_001CC2E8((SUB*)((char*)p->actor+0x900));
  func_002046B0(p->actor,Sub(Read(&w.goals.motion.desired),Read(&w.position)));heading=p->actor->heading;break;
 case 22:{
  func_001441E8(p->actor,D_002BF878);ACTOR*actor=p->actor;actor->velocity.q=func_0011E1A0(input->heading+3.14159265358979323846f,input->amount*D_002BF87C,D_002BF880);
  if(D_002BF848<LengthXY(Read(&w.initialVelocity)))p->actor->heading=func_002458F0(w.initialVelocity.f[1],w.initialVelocity.f[0])+offset;
  w.scratch.v[0].q=Scalar(0.5f);qword half=w.scratch.v[0].q;w.scratch.v[0].q=Scalar(-0.5f);qword negativeHalf=w.scratch.v[0].q;
  qword up=Read(&D_002A2DC0),initial=Read(&w.initialVelocity),desired=Read(&p->actor->velocity);
  qword a=Sub(initial,Scale(up,Dot(initial,up))),b=Sub(desired,Scale(up,Dot(desired,up)));
  func_0011BA08(&w.scratch.matrices.first,D_002A2DC0.q,Blend(Read(&D_002BF890),a,half,b,negativeHalf));w.goals.basis=w.scratch.matrices.first;
  actor=p->actor;func_0011B500(&w.scratch.matrices.rotation,D_002A2DC0.q,actor->heading);MulTo(&w.scratch.matrices.product,w.goals.basis,w.scratch.matrices.rotation);w.scratch.matrices.first=w.scratch.matrices.product;actor->local=w.scratch.matrices.first;heading=p->actor->heading;break;
 }
 case 17:case 19:break;
 case 1:case 2:case 3:case 4:case 5:case 6:case 7:case 8:case 9:case 10:case 16:case 18:case 21:default:
  if(Facing(p->actor))heading=p->actor->heading;else if(D_002BF848<LengthXY(Read(&w.initialVelocity)))heading=func_002458F0(w.initialVelocity.f[1],w.initialVelocity.f[0])+offset;break;
 }
 if(p->mode!=22)func_00204660(p->actor,heading);
 if((0<=p->mode&&p->mode<6)||p->mode==7){
  float maximum;
  switch(p->mode){case 2:case 3:maximum=D_002BF734;break;case 5:
   if(0.2f<input->amount){float factor=func_00244E10(input->heading-p->lastHeading);if(factor<0)factor=0;else if(p->minimumCosine<factor)factor=p->minimumCosine;p->minimumCosine=factor;}
   if(D_002BF730<p->speedLimit)maximum=(1.0f-p->minimumCosine)*D_002BF730+p->minimumCosine*p->speedLimit;else maximum=D_002BF730;break;
   default:maximum=D_002BF730;break;
  }
  maximum=maximum*p->scale;
  Store(&w.goals.motion.desired,func_0011E1A0(input->heading,input->amount*maximum,0));
  ACTOR*actor=p->actor;w.goals.motion.velocity.q=Scalar(-1.0f);Store(&actor->velocity,Scale(Transpose(&actor->local,Read(&w.goals.motion.desired)),w.goals.motion.velocity.q));
  if((p->mode!=0||p->combo==3)&&!p->flags24){
   w.goals.motion.velocity.q=Velocity(p->actor);w.goals.motion.velocity.f[2]=0;
   float speed=Normalize(&w.goals.motion.velocity);float projected=func_0011E290(w.goals.motion.desired.q,w.goals.motion.velocity.q,0,&w.goals.motion.bestVelocity);
   if(projected<speed&&-0.25f*speed<projected){w.scratch.v[0].q=Scalar(speed);Store(&w.goals.motion.desired,AddScaled(Read(&w.goals.motion.bestVelocity),Read(&w.goals.motion.velocity),w.scratch.v[0].q));w.goals.motion.desired.q=func_0011E9F8(w.goals.motion.desired.q,maximum);}
  }
  if(p->velocitySource){w.pending.q=w.goals.motion.desired.q;StoreWord(&w.overrideScalar,p->velocityScale.bits);w.goals.motion.velocity.q=w.overrideScalar.q;qword velocity=ToVector(Velocity(p->velocitySource));Store(&w.goals.motion.desired,AddScaled(Read(&w.pending),velocity,Read(&w.overrideScalar)));}
  p->desired.q=w.goals.motion.desired.q;
  if(p->height<w.position.f[2])p->height=w.position.f[2];
 }
 if(p->focused&&p->focus&&p->other&&p->focus->focusState==1&&w.initialVelocity.f[2]<D_002BF8A0)func_00140C88(p->actor,p->other);
}
