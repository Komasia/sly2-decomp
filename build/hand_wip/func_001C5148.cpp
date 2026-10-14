typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];int words[4];};
union M3 {qword rows[3];float values[12];};
struct VTE {short delta,pad;void *fn;};
struct CHANNEL {M3 matrix;qword position;char pad40[0x64];int stamp;char padA8[8];qword velocity;};
struct MOTION {VTE *vt;};
struct ENTRY {unsigned int key;MOTION *motion;};
struct ACTION {char pad5C[0x5C];int count;ENTRY *entries;};
struct ANIM {char pad14[0x14];ACTION *action;int word18;float time;char pad20[0x20];float duration;};
struct HOLDER {char pad30[0x30];ANIM *animation;};
struct P {char padC[0xC];VTE *vt;char pad10[8];int id;char pad1C[0x3C];CHANNEL *position,*orientation;char pad60[0xF0];int state;char pad154[0x14];HOLDER *holder;char pad16C[4];qword coordinate,velocity,acceleration;};
union FLOATWORD {float value;int bits;};
struct CLOCK {float time;FLOATWORD dt;};
struct CAMERA {char pad90[0x90];qword position;};
struct SW {char pad3D58[0x3D58];int stamp;};
struct WORK {U home;qword position,velocity,angles,angularVelocity;M3 frame,sampled,output;};
extern "C" {
extern CLOCK D_002DDED0;
extern CAMERA D_002DDF40;
extern SW D_003DD490;
extern float D_002C0D4C;
extern qword D_002A2DC0;
void func_001F3980(P *);
qword *func_00256D18(qword *,qword);
M3 *func_0011B830(M3 *,qword,qword);
M3 *func_0011B628(M3 *,qword);
}
static inline qword Scalar(U &home,float value){qword result;__asm__("qmtc2.ni %1,%0":"=j"(result):"r"(value));home.q=result;return home.q;}
static inline qword ScalarBits(U &home,int bits){qword result;__asm__("qmtc2.ni %1,%0":"=j"(result):"r"(bits));home.q=result;return home.q;}
static inline qword Accumulate(qword value,qword force,qword factor,qword time){__asm__("vmulax.xyzw $ACC,%0,%2x\n\tvmaddx.xyzw %0,%1,%3x":"+j"(value):"j"(force),"j"(factor),"j"(time));return value;}
static inline qword Advance(qword value,qword velocity,qword time){__asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(value):"j"(velocity),"j"(time));return value;}
static inline qword Difference(qword a,qword b){qword result;__asm__("vsub.xyzw %0,%1,%2":"=j"(result):"j"(a),"j"(b));return result;}
static inline qword Transform(const M3 &matrix,qword value){__asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(value):"j"(matrix.rows[0]),"j"(matrix.rows[1]),"j"(matrix.rows[2]));return value;}
static inline qword PositionAdd(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Add(qword a,qword b){__asm__("vadd.xyzw %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline qword ReadA0(const qword*p){register qword v __asm__("vf3");__asm__("lqc2 %0,%1":"=j"(v):"m"(*p));return v;}
static inline qword ReadA1(const qword*p){register qword v __asm__("vf2");__asm__("lqc2 %0,%1":"=j"(v):"m"(*p));return v;}
static inline qword ReadA2(const qword*p){register qword v __asm__("vf1");__asm__("lqc2 %0,%1":"=j"(v):"m"(*p));return v;}
static inline qword ReadB0(const qword*p){register qword v __asm__("vf8");__asm__("lqc2 %0,%1":"=j"(v):"m"(*p));return v;}
static inline qword ReadB1(const qword*p){register qword v __asm__("vf5");__asm__("lqc2 %0,%1":"=j"(v):"m"(*p));return v;}
static inline qword ReadB2(const qword*p){register qword v __asm__("vf6");__asm__("lqc2 %0,%1":"=j"(v):"m"(*p));return v;}
static inline M3 CopyAndMultiply(const M3&a,const M3&b,M3&sampled) return result {
 qword a1=ReadA1(&a.rows[1]),a2=ReadA2(&a.rows[2]);
 qword b0=ReadB0(&b.rows[0]),b1=ReadB1(&b.rows[1]),b2=ReadB2(&b.rows[2]);
 qword a0=ReadA0(&a.rows[0]);
 register qword x __asm__("vf4"),z __asm__("vf7");
 sampled.rows[0]=b0;sampled.rows[1]=b1;sampled.rows[2]=b2;
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=&j"(x):"j"(a0),"j"(a1),"j"(a2),"j"(sampled.rows[0]));
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=&j"(z):"j"(a0),"j"(a1),"j"(a2),"j"(sampled.rows[2]));
 __asm__("vmulax.xyz $ACC,%0,%3x\n\tvmadday.xyz $ACC,%1,%3y\n\tvmaddz.xyz %0,%2,%3z":"+j"(a0):"j"(a1),"j"(a2),"j"(sampled.rows[1]));
 result.rows[1]=a0;result.rows[2]=z;result.rows[0]=x;
 return;
}
static inline CHANNEL *GetChannel(P *p,int channel){VTE &e=p->vt[51];return ((CHANNEL*(*)(P *,int))e.fn)((P *)((char *)p+e.delta),channel);}
static inline void Sample(MOTION *motion,const ANIM *animation,qword *value,qword *velocity){VTE &e=motion->vt[3];((void(*)(MOTION *,float,float,qword *,qword *))e.fn)((MOTION *)((char *)motion+e.delta),animation->time,animation->duration,value,velocity);}
extern "C" void func_001C5148(P *p){
 WORK work;
 if(p->state==6){func_001F3980(p);return;}
 float factor;
 if(p->state==0 || p->state==5)factor=1.0f+D_002C0D4C*D_002DDED0.dt.value;
 else factor=1.0f;
 qword damping=Scalar(work.home,factor);
 qword step=ScalarBits(work.home,D_002DDED0.dt.bits);
 p->velocity=Accumulate(p->velocity,p->acceleration,damping,step);
 qword position=Advance(p->coordinate,p->velocity,ScalarBits(work.home,D_002DDED0.dt.bits));
 CHANNEL *channel=p->position;
 p->coordinate=position;
 func_00256D18(&channel->position,position);
 *(float *)((char *)channel+0x3C)=1.0f;
 p->position->velocity=p->velocity;
 {int stamp=++D_003DD490.stamp;p->position->stamp=stamp;}
 if(p->holder && p->holder->animation){
  ANIM *animation=p->holder->animation;
  ACTION *action=animation->action;
  MOTION *positionMotion=0,*orientationMotion=0;
  int i=0;
  for(;i<action->count;i++){
   ENTRY *entry=&action->entries[i];
   unsigned int key=entry->key;
   if(!(key&0x40000000U))continue;
   if(((int)(key<<12)>>12)!=p->id)continue;
   {
    CHANNEL *selected=GetChannel(p,(int)(key<<2)>>22);
    if(selected==p->position)positionMotion=entry->motion;
    else if(selected==p->orientation)orientationMotion=entry->motion;
   }
   if(positionMotion && orientationMotion)break;
  }
  if(positionMotion || orientationMotion){
   work.home.q=Difference(D_002DDF40.position,p->position->position);
   work.home.words[2]=0;
   func_0011B830(&work.output,work.home.q,D_002A2DC0);
   work.frame=work.output;
   if(positionMotion){
    Sample(positionMotion,animation,&work.position,&work.velocity);
    channel=p->position;
    func_00256D18(&channel->position,PositionAdd(channel->position,Transform(work.frame,work.position)));
    *(float *)((char *)channel+0x3C)=1.0f;
    CHANNEL *current=p->position;
    current->velocity=Add(current->velocity,Transform(work.frame,work.velocity));
    {int stamp=++D_003DD490.stamp;p->position->stamp=stamp;}
   }
   if(orientationMotion){
    Sample(orientationMotion,animation,&work.angles,&work.angularVelocity);
    func_0011B628(&work.output,work.angles);
    work.output=CopyAndMultiply(work.frame,work.output,work.sampled);
    CHANNEL *current=p->orientation;
    current->matrix=work.output;
    current->matrix.values[3]=0.0f;current->matrix.values[11]=0.0f;current->matrix.values[7]=0.0f;
    current=p->orientation;
    current->velocity=Transform(work.frame,work.angularVelocity);
    {int stamp=++D_003DD490.stamp;p->orientation->stamp=stamp;}
   }
  }
 }
 func_001F3980(p);
}

#define OFF(t,m) ((unsigned int)&((t*)0)->m)
typedef char animation_layout[(sizeof(void*)==4 && sizeof(qword)==16 && sizeof(U)==16 && sizeof(M3)==0x30 && sizeof(VTE)==8 && sizeof(ENTRY)==8 && sizeof(FLOATWORD)==4 && sizeof(CLOCK)==8 && sizeof(WORK)==0xE0 && OFF(VTE,delta)==0 && OFF(VTE,fn)==4 && OFF(CHANNEL,matrix)==0 && OFF(CHANNEL,position)==0x30 && OFF(CHANNEL,stamp)==0xA4 && OFF(CHANNEL,velocity)==0xB0 && OFF(MOTION,vt)==0 && OFF(ENTRY,key)==0 && OFF(ENTRY,motion)==4 && OFF(ACTION,count)==0x5C && OFF(ACTION,entries)==0x60 && OFF(ANIM,action)==0x14 && OFF(ANIM,time)==0x1C && OFF(ANIM,duration)==0x40 && OFF(HOLDER,animation)==0x30 && OFF(P,vt)==0xC && OFF(P,id)==0x18 && OFF(P,position)==0x58 && OFF(P,orientation)==0x5C && OFF(P,state)==0x150 && OFF(P,holder)==0x168 && OFF(P,coordinate)==0x170 && OFF(P,velocity)==0x180 && OFF(P,acceleration)==0x190 && OFF(CLOCK,time)==0 && OFF(CLOCK,dt)==4 && OFF(CAMERA,position)==0x90 && OFF(SW,stamp)==0x3D58 && OFF(WORK,home)==0 && OFF(WORK,position)==0x10 && OFF(WORK,velocity)==0x20 && OFF(WORK,angles)==0x30 && OFF(WORK,angularVelocity)==0x40 && OFF(WORK,frame)==0x50 && OFF(WORK,sampled)==0x80 && OFF(WORK,output)==0xB0)?1:-1];
