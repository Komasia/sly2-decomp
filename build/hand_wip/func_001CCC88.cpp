// Create position and orientation jobs for the selected animated object.
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
union M4 {qword rows[4];float values[16];};
struct M3 {qword rows[3];};
struct VTE {short delta,pad;void *fn;};
struct SPACE;
struct JOB;
struct CHANNEL {char pad90[0x90];JOB *current;char pad94[0xC];SPACE *space;int wordA4;float endTime;};
struct MOTION;
struct ANIM {char pad14[0x14];MOTION *motion;int word18;float start;char pad20[0x20];float duration;};
struct FOLLOW {char pad80[0x80];qword velocity;};
struct LO {char padC[0xC];VTE *vt;char pad10[0x48];CHANNEL *position,*orientation;SPACE *space;char pad64[0x84];FOLLOW *follow;char padEC[0xC4];M3 basis;char pad1E0[0xE50];ANIM *playing;};
struct SOURCE {char padC[0xC];VTE *vt;};
struct P {LO *owner;char pad4[0x30];SOURCE *source;char pad38[0x5C];JOB *positionJob,*otherJob,*orientationJob;};
struct CLOCK {float time,dt;};
union VIEWS {struct {M4 intermediate,product,inverse;} matrices;struct {M3 angles,converted;} basis;U scalar;};
struct WORK {M4 original,sample,start,final;VIEWS views;qword velocity,destination,delta,endVelocity;};
extern "C" {
extern qword D_002C1EE0;
extern float D_002C1EF0;
extern CLOCK D_002DDED0;
void func_0012E460(JOB **);
float func_0012F990(MOTION *,int);
void func_001300B8(MOTION *,float,float,LO *,SPACE *,SPACE *,M4 *,M4 *);
qword func_001A62E8(LO *);
qword *func_00256D18(qword *,qword);
M4 *func_0011C168(M4 *,const M4 *,const M4 *);
LO *func_001CCA40(LO *,LO *);
M4 *func_001A71B0(M4 *,LO *,LO *,const M4 *);
M4 *func_0011C318(M4 *,const M4 *);
void func_001A58D0(LO *,int,int);
float func_00196928(qword,qword,float,float,float,float);
void func_00131A00(ANIM *,float);
qword func_0022FC48(SPACE *,SPACE *,qword);
qword func_0022FCC8(SPACE *,SPACE *,qword);
JOB *func_0012DE58(LO *,CHANNEL *,int,float,qword,qword);
M3 *func_0022FD38(M3 *,SPACE *,SPACE *,const M3 *);
qword func_0011BFF0(const M3 *);
JOB *func_0012DC18(LO *,CHANNEL *,int,int,int,qword);
void func_001F6860(LO *,int);
}
static inline SPACE *SourceMatrix(SOURCE *p,M4 *out){VTE &v=p->vt[32];return ((SPACE*(*)(SOURCE *,M4 *))v.fn)((SOURCE *)((char *)p+v.delta),out);}
static inline M4 *WorldMatrix(LO *p){VTE &v=p->vt[31];return ((M4*(*)(LO *))v.fn)((LO *)((char *)p+v.delta));}
static inline qword ToVU(qword q){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(q));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline void SubInto(qword *out,qword a,qword b){qword r=Sub(a,b);__asm__("sqc2 %1,%0":"=m"(*out):"j"(r));}
static inline qword Broadcast(U &u,float value){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(value));u.q=r;return u.q;}
static inline qword Blend(qword delta,qword velocity,qword inv,qword half){qword r;__asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x":"=j"(r):"j"(delta),"j"(velocity),"j"(inv),"j"(half));return r;}
static inline float Max(float a,float b){float r;__asm__("max.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
extern "C" void func_001CCC88(P *input,LO *other){
 register P*p __asm__("$22");register LO*object __asm__("$20");
 __asm__("daddu %0,%1,$zero":"=r"(p):"r"(input));
 __asm__("daddu %0,%1,$zero":"=r"(object):"r"(other));
 WORK work;
 func_0012E460(&p->positionJob);func_0012E460(&p->otherJob);func_0012E460(&p->orientationJob);
 ANIM *anim=p->owner->playing;MOTION *motion=anim->motion;
 float time=func_0012F990(motion,0x1C7),phase=(time-anim->start)/anim->duration;
 SPACE *space=SourceMatrix(p->source,&work.original);
 func_001300B8(motion,time,0.0f,p->owner,space,p->owner->space,&work.sample,0);
 LO *owner=p->owner;
 M4 *start=&work.start;M3 *basis=&owner->basis;
 func_00256D18(&start->rows[3],func_001A62E8(owner));
 start->rows[0]=basis->rows[0];start->rows[1]=basis->rows[1];start->rows[2]=basis->rows[2];
 work.start.values[3]=0.0f;work.start.values[11]=0.0f;work.start.values[7]=0.0f;start->values[15]=1.0f;
 func_0011C168(&work.views.matrices.product,start,&work.sample);
 func_0011C168(&work.views.matrices.intermediate,&work.views.matrices.product,&work.original);
 work.final=work.views.matrices.intermediate;
 LO *counterpart=func_001CCA40(p->owner,object);
 if(counterpart){
  func_001A71B0(&work.views.matrices.product,0,object,WorldMatrix(counterpart));
  work.views.matrices.intermediate=work.views.matrices.product;
  func_0011C318(&work.views.matrices.inverse,&work.views.matrices.intermediate);
  func_0011C168(&work.views.matrices.product,&work.final,&work.views.matrices.inverse);
  work.final=work.views.matrices.product;
 }
 func_001A58D0(object,0,15);
 work.velocity=object->follow?object->follow->velocity:D_002C1EE0;
 work.destination=work.final.rows[3];
 SubInto(&work.delta,work.destination,ToVU(func_001A62E8(object)));
 float limit=D_002C1EF0;
 float duration=Max(phase,func_00196928(work.delta,work.velocity,limit,-limit,1.0f,-1.0f));
 float speed=phase/duration;phase=duration;
 func_00131A00(anim,speed);
 VTE &entry=object->vt[35];
 qword velocity=Blend(work.delta,work.velocity,Broadcast(work.views.scalar,1.0f/phase),Broadcast(work.views.scalar,-0.5f*phase));
 work.endVelocity=Blend(work.delta,work.velocity,Broadcast(work.views.scalar,1.0f/phase),Broadcast(work.views.scalar,0.5f*phase));
 ((void(*)(LO *,qword))entry.fn)((LO *)((char *)object+entry.delta),velocity);
 float endTime=D_002DDED0.time+phase;
 qword position=func_0022FC48(0,object->position->space,work.final.rows[3]);
 qword endVelocity=func_0022FCC8(0,object->position->space,work.endVelocity);
 p->positionJob=func_0012DE58(object,object->position,5,endTime,position,endVelocity);
 func_0022FD38(&work.views.basis.converted,0,object->orientation->space,(M3 *)&work.final);
 work.views.basis.angles=work.views.basis.converted;
 qword angles=func_0011BFF0(&work.views.basis.angles);
 JOB *job=func_0012DC18(object,object->orientation,5,9,2,angles);p->orientationJob=job;
 if(object->orientation->current==job)object->orientation->endTime=endTime;
 func_001F6860(object,1);
}

#define OFF(t,m) ((int)&((t*)0)->m)
typedef char motion_job_layout[(sizeof(void*)==4 && sizeof(qword)==16 && sizeof(U)==16 && sizeof(M3)==0x30 && sizeof(M4)==0x40 && sizeof(VTE)==8 && sizeof(VIEWS)==0xC0 && sizeof(WORK)==0x200 && OFF(VTE,delta)==0 && OFF(VTE,fn)==4 && OFF(CHANNEL,current)==0x90 && OFF(CHANNEL,space)==0xA0 && OFF(CHANNEL,endTime)==0xA8 && OFF(ANIM,motion)==0x14 && OFF(ANIM,start)==0x1C && OFF(ANIM,duration)==0x40 && OFF(FOLLOW,velocity)==0x80 && OFF(LO,vt)==0xC && OFF(LO,position)==0x58 && OFF(LO,orientation)==0x5C && OFF(LO,space)==0x60 && OFF(LO,follow)==0xE8 && OFF(LO,basis)==0x1B0 && OFF(LO,playing)==0x1030 && OFF(SOURCE,vt)==0xC && OFF(P,owner)==0 && OFF(P,source)==0x34 && OFF(P,positionJob)==0x94 && OFF(P,otherJob)==0x98 && OFF(P,orientationJob)==0x9C && OFF(CLOCK,time)==0 && OFF(VIEWS,matrices.intermediate)==0 && OFF(VIEWS,matrices.product)==0x40 && OFF(VIEWS,matrices.inverse)==0x80 && OFF(VIEWS,basis.angles)==0 && OFF(VIEWS,basis.converted)==0x30 && OFF(WORK,original)==0 && OFF(WORK,sample)==0x40 && OFF(WORK,start)==0x80 && OFF(WORK,final)==0xC0 && OFF(WORK,views)==0x100 && OFF(WORK,velocity)==0x1C0 && OFF(WORK,destination)==0x1D0 && OFF(WORK,delta)==0x1E0 && OFF(WORK,endVelocity)==0x1F0)?1:-1];
