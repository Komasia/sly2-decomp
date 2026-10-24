/* (Claude agent, vu_hi4) v3: 6/265 aligned 4 (v2: 9/7). Scalar/ScalarBits words pinned to $3 (mfc1 v1, address v0 like target). Left: 3rd dt.bits word wants v0 (separate $2-pinned inline moves the address to a0); qmtc2 vf4 vs lqc2 vf1 order; output/temp sqc2 order at 0x1C54C4. */
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
struct WORK {qword position,velocity,angles,angularVelocity;M3 frame,sampled,output;};
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
struct VU_FLOAT { qword q; VU_FLOAT(float f){__asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f));} VU_FLOAT(int bits){__asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(bits));} };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v){q=v;} };
static inline qword VecCombo(VU_FLOAT f1,VU_VECTOR v1,VU_FLOAT f2,VU_VECTOR v2){qword r;__asm__("vmulax.xyzw $ACC, %2, %1x
	vmaddx.xyzw %0, %4, %3x" : "=j"(r) : "j"(f1.q), "j"(v1.q), "j"(f2.q), "j"(v2.q));return r;}
static inline qword Advance(qword value,qword velocity,VU_FLOAT time){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0
	vmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(value),"j"(velocity),"j"(time.q));return r;}
static inline qword Difference(qword a,qword b){qword result;__asm__("vsub.xyzw %0,%1,%2":"=j"(result):"j"(a),"j"(b));return result;}
static inline qword Transform(const M3 &matrix,qword value){__asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(value):"j"(matrix.rows[0]),"j"(matrix.rows[1]),"j"(matrix.rows[2]));return value;}
static inline qword PositionAdd(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Add(qword a,qword b){__asm__("vadd.xyzw %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline qword ReadA0(const qword*p){register qword v __asm__("vf3");__asm__ __volatile__("lqc2 %0,%1":"=j"(v):"m"(*p));return v;}
static inline qword ReadA1(const qword*p,unsigned page,SW**world){register qword v ;__asm__ __volatile__("lqc2 %0,%1":"=j"(v):"m"(*p));*world=&D_003DD490;return v;}
static inline qword ReadA2(const qword*p){register qword v ;__asm__ __volatile__("lqc2 %0,%1":"=j"(v):"m"(*p));return v;}
static inline qword ReadB0(const qword*p){register qword v ;__asm__ __volatile__("lqc2 %0,%1":"=j"(v):"m"(*p));return v;}
static inline qword ReadB1(const qword*p){register qword v ;__asm__ __volatile__("lqc2 %0,%1":"=j"(v):"m"(*p));return v;}
static inline qword ReadB2(const qword*p){register qword v ;__asm__ __volatile__("lqc2 %0,%1":"=j"(v):"m"(*p));return v;}
static inline M3 CopyAndMultiply(const M3&a,const M3&b,M3&sampled,unsigned page,SW**world) return result {
 qword a1=ReadA1(&a.rows[1],page,world),a2=ReadA2(&a.rows[2]);
 qword b0=ReadB0(&b.rows[0]),b1=ReadB1(&b.rows[1]),b2=ReadB2(&b.rows[2]);
 qword a0=ReadA0(&a.rows[0]);
 register qword x ,z ;
 sampled.rows[0]=b0;sampled.rows[1]=b1;sampled.rows[2]=b2;
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=&j"(x):"j"(a0),"j"(a1),"j"(a2),"j"(sampled.rows[0]));
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=&j"(z):"j"(a0),"j"(a1),"j"(a2),"j"(sampled.rows[2]));
 __asm__("vmulax.xyz $ACC,%0,%3x\n\tvmadday.xyz $ACC,%1,%3y\n\tvmaddz.xyz %0,%2,%3z":"+j"(a0):"j"(a1),"j"(a2),"j"(sampled.rows[1]));
 result.rows[0]=x;result.rows[1]=a0;result.rows[2]=z;
 return;
}
static inline void CopyBasis(const M3&source,M3&destination){destination=source;}
static inline CHANNEL *AngularDestination(P *p,const qword &source,qword &angular) {
 CHANNEL *channel;
 register qword value ;
 __asm__("lw %0,%2\n\tlqc2 %1,%3":"=&r"(channel),"=j"(value):"m"(p->orientation),"m"(source));
 angular=value;return channel;
}
static inline CHANNEL *GetChannel(P *p,int channel){VTE &e=p->vt[51];return ((CHANNEL*(*)(P *,int))e.fn)((P *)((char *)p+e.delta),channel);}
static inline void Sample(MOTION *motion,const ANIM *animation,qword *value,qword *velocity){VTE &e=motion->vt[3];((void(*)(MOTION *,float,float,qword *,qword *))e.fn)((MOTION *)((char *)motion+e.delta),animation->time,animation->duration,value,velocity);}
static inline qword *Addr(qword *q){return q;}
extern "C" void func_001C5148(P *p){
 if(p->state==6){func_001F3980(p);return;}
 float factor;
 if(p->state==0 || p->state==5)factor=1.0f+D_002C0D4C*D_002DDED0.dt.value;
 else factor=1.0f;
 p->velocity=VecCombo(VU_FLOAT(factor),VU_VECTOR(p->velocity),VU_FLOAT(D_002DDED0.dt.bits),VU_VECTOR(p->acceleration));
 unsigned worldPage=0;
 qword newPosition=Advance(p->coordinate,p->velocity,VU_FLOAT(D_002DDED0.dt.bits));
 CHANNEL *channel=p->position;
 p->coordinate=newPosition;
 func_00256D18(&channel->position,newPosition);
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
   U home,position,velocity,angles,angularVelocity;M3 frame,sampled,output;
   home.q=Difference(D_002DDF40.position,p->position->position);
   home.words[2]=0;
   func_0011B830(&output,home.q,D_002A2DC0);
   CopyBasis(output,frame);
   if(positionMotion){
    Sample(positionMotion,animation,&position.q,&velocity.q);
    channel=p->position;
    func_00256D18(&channel->position,PositionAdd(channel->position,Transform(frame,position.q)));
    *(float *)((char *)channel+0x3C)=1.0f;
    CHANNEL *current=p->position;
    current->velocity=Add(current->velocity,Transform(frame,velocity.q));
    {int stamp=++D_003DD490.stamp;p->position->stamp=stamp;}
   }
   if(orientationMotion){
    Sample(orientationMotion,animation,&angles.q,&angularVelocity.q);
    func_0011B628(&output,angles.q);
    SW*orientationWorld;
    output=CopyAndMultiply(frame,output,sampled,worldPage,&orientationWorld);
    CHANNEL *current=p->orientation;
    current->matrix=output;
    current->matrix.values[3]=0.0f;current->matrix.values[7]=0.0f;current->matrix.values[11]=0.0f;
    qword angular;
    current=AngularDestination(p,angularVelocity.q,angular);
    current->velocity=Transform(frame,angular);
    {int stamp=++orientationWorld->stamp;p->orientation->stamp=stamp;}
   }
  }
 }
 func_001F3980(p);
}

