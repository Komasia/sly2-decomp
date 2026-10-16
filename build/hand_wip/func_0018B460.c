typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];} U;
struct M3{U r[3];};struct M4{U r[4];};struct LM{float low,high;};struct CLOCK{float time,dt;};
struct MODEL{char pad[0x1C];float base;char pad20[0x40-0x20];float scale;};
struct AIM{char pad[0x150];void*frame;};struct OWNER{char pad[0x494];struct AIM*aim;};
struct GROUP{char pad[0xA0];void*space;};struct FOCUS{char pad[0x58];struct GROUP*group;};
struct DV{char pad[0x20];qword value;};
struct P{char pad[0x60];void*space;char pad64[0x1030-0x64];struct MODEL*model;char pad1034[0x10DC-0x1034];struct OWNER*owner;char pad10E0[0x19A0-0x10E0];struct FOCUS*focus;char pad19A4[0x19EC-0x19A4];struct DV*dvResidual;char pad19F0[8];struct DV*dvYaw;struct DV*dvX;char pad1A00[0x1BD4-0x1A00];int valid;float height,time;char pad1BE0[0x10];qword anchor,position,euler,localPoint;};
struct WORK{union{struct M4 predicted;U scalar;}phase;struct M4 transform;U axis;struct M3 rotation;U relative,residual,gain;};
extern float D_002BF380,D_002BF3A0,D_002BF3B8,D_002BF3BC;
extern qword D_002BF390;extern struct LM D_002BF3A8,D_002BF3B0;extern struct CLOCK D_002DDED0;
void func_002046F0(struct P*,struct AIM*);void func_002309E8(void*,void*,struct M4*,void*,float);
qword func_0022FC48(void*,void*,qword);qword func_0022FCC8(void*,void*,qword);
float func_002458F0(float,float);float func_0011D948(struct LM*,float);
struct M3*func_0011B628(struct M3*,qword);qword*func_00256D18(qword*,qword);void func_0012DA30(struct DV*,qword);
static inline float Min(float a,float b){float r;__asm__("min.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Point(const struct M4*m,qword a){qword r;__asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=&j"(r):"j"(m->r[0].q),"j"(m->r[1].q),"j"(m->r[2].q),"j"(m->r[3].q),"j"(a));return r;}
static inline float X(qword q){float x;__asm__("mtc1 %1,%0":"=f"(x):"r"(q));return x;}
static inline float Z(qword q){float z;__asm__("pextuw %0,$zero,%1":"=r"(z):"r"(q));return z;}
static inline qword Pack(float x,float y,float z){qword q,t;__asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0":"=&r"(q),"=&r"(t):"f"(x),"f"(y),"f"(z));return q;}
static inline float Length(qword a){qword d,one;float len;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a));__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(d):"j"(d));__asm__("qmfc2.ni %0,%1":"=r"(len):"j"(d));return len;}
static inline int Near(float distance,float limit){int near=1;if(distance<limit){}else near=0;return near;}
static inline qword ScaleStored(qword a,const U*gain,U*scalar){qword raw,s;__asm__("lq %0,%1":"=r"(raw):"m"(gain->q));scalar->q=raw;__asm__("qmtc2.ni %1,%0":"=j"(s):"r"(scalar->q));__asm__("vmulx.xyzw %0,%1,%0x":"+j"(s):"j"(a));return s;}
static inline qword PointKeepW(const struct M4*m,qword point){qword r=m->r[3].q;__asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddaz.xyz $ACC,%3,%4z\n\tvmaddw.xyz %0,%0,$vf0w":"+j"(r):"j"(m->r[0].q),"j"(m->r[1].q),"j"(m->r[2].q),"j"(point));return r;}
static inline struct M4*BuildFrame(struct M4*d,const struct M3*rotation,qword position,float zero){func_00256D18(&d->r[3].q,position);d->r[0]=rotation->r[0];d->r[1]=rotation->r[1];d->r[2]=rotation->r[2];d->r[0].f[3]=d->r[1].f[3]=d->r[2].f[3]=zero;d->r[3].f[3]=1.0f;return d;}
void func_0018B460(struct P*p){
 struct WORK w;register float ratio __asm__("$f20");__asm__("div.s %0,%1,%2":"=f"(ratio):"f"(p->height-p->model->base),"f"(p->model->scale));
 if(p->owner&&p->owner->aim){
 float zero=0.0f;
 if(zero<ratio){
  qword mapped,tilt,axis;void*space;struct M4*frame;float heading;
  func_002046F0(p,p->owner->aim);
  func_002309E8(p->owner->aim->frame,0,&w.phase.predicted,0,Min(ratio,D_002BF380));
  mapped=func_0022FC48(0,p->space,Point(&w.phase.predicted,D_002BF390));
  heading=func_002458F0(-Z(mapped),D_002BF3A0*X(mapped));heading=func_0011D948(&D_002BF3A8,heading);
  tilt=Pack(zero,heading,zero);w.axis.q=tilt;
  func_0011B628(&w.rotation,Add(p->euler,w.axis.q));
  frame=BuildFrame(&w.transform,&w.rotation,p->position,zero);
  space=p->focus->group->space;
  w.relative.q=Sub(mapped,PointKeepW(frame,p->localPoint));
  heading=X(func_0022FCC8(p->space,space,w.relative.q));heading=func_0011D948(&D_002BF3B0,heading);
  axis=Pack(heading,zero,zero);w.axis.q=axis;
  w.residual.q=Sub(w.relative.q,func_0022FCC8(space,p->space,w.axis.q));
  if(Near(Length(Sub(Add(p->position,w.residual.q),p->anchor)),D_002BF3B8)){
   func_0012DA30(p->dvYaw,tilt);func_0012DA30(p->dvResidual,w.residual.q);func_0012DA30(p->dvX,axis);
   p->valid=1;p->time=D_002DDED0.time;return;
  }
 }}
 {float remaining=(p->time+D_002BF3BC)-D_002DDED0.time;float after=remaining-D_002DDED0.dt;float gain=0.0f;
  if(0.0f<after)gain=after/remaining;
  __asm__("mfc1 %0,%1":"=r"(w.gain.q):"f"(gain));
  func_0012DA30(p->dvYaw,ScaleStored(p->dvYaw->value,&w.gain,&w.phase.scalar));
  func_0012DA30(p->dvResidual,ScaleStored(p->dvResidual->value,&w.gain,&w.phase.scalar));
  func_0012DA30(p->dvX,ScaleStored(p->dvX->value,&w.gain,&w.phase.scalar));
  p->valid=0;
 }
}

typedef char qword_Size[(sizeof(qword)==16)?1:-1];
typedef char U_Size[(sizeof(U)==16)?1:-1];
typedef char M3_Size[(sizeof(struct M3)==48)?1:-1];
typedef char M4_Size[(sizeof(struct M4)==64)?1:-1];
typedef char LM_Size[(sizeof(struct LM)==8)?1:-1];
typedef char CLOCK_Size[(sizeof(struct CLOCK)==8)?1:-1];
typedef char DV_Size[(sizeof(struct DV)==48)?1:-1];
typedef char WORK_Size[(sizeof(struct WORK)==240)?1:-1];
typedef char MODEL_base_Offset[((unsigned)&((struct MODEL*)0)->base==28)?1:-1];
typedef char MODEL_scale_Offset[((unsigned)&((struct MODEL*)0)->scale==64)?1:-1];
typedef char AIM_frame_Offset[((unsigned)&((struct AIM*)0)->frame==336)?1:-1];
typedef char OWNER_aim_Offset[((unsigned)&((struct OWNER*)0)->aim==1172)?1:-1];
typedef char GROUP_space_Offset[((unsigned)&((struct GROUP*)0)->space==160)?1:-1];
typedef char FOCUS_group_Offset[((unsigned)&((struct FOCUS*)0)->group==88)?1:-1];
typedef char DV_value_Offset[((unsigned)&((struct DV*)0)->value==32)?1:-1];
typedef char P_space_Offset[((unsigned)&((struct P*)0)->space==96)?1:-1];
typedef char P_model_Offset[((unsigned)&((struct P*)0)->model==4144)?1:-1];
typedef char P_owner_Offset[((unsigned)&((struct P*)0)->owner==4316)?1:-1];
typedef char P_focus_Offset[((unsigned)&((struct P*)0)->focus==6560)?1:-1];
typedef char P_dvResidual_Offset[((unsigned)&((struct P*)0)->dvResidual==6636)?1:-1];
typedef char P_dvYaw_Offset[((unsigned)&((struct P*)0)->dvYaw==6648)?1:-1];
typedef char P_dvX_Offset[((unsigned)&((struct P*)0)->dvX==6652)?1:-1];
typedef char P_valid_Offset[((unsigned)&((struct P*)0)->valid==7124)?1:-1];
typedef char P_height_Offset[((unsigned)&((struct P*)0)->height==7128)?1:-1];
typedef char P_time_Offset[((unsigned)&((struct P*)0)->time==7132)?1:-1];
typedef char P_anchor_Offset[((unsigned)&((struct P*)0)->anchor==7152)?1:-1];
typedef char P_position_Offset[((unsigned)&((struct P*)0)->position==7168)?1:-1];
typedef char P_euler_Offset[((unsigned)&((struct P*)0)->euler==7184)?1:-1];
typedef char P_localPoint_Offset[((unsigned)&((struct P*)0)->localPoint==7200)?1:-1];
typedef char WORK_phase_Offset[((unsigned)&((struct WORK*)0)->phase==0)?1:-1];
typedef char WORK_transform_Offset[((unsigned)&((struct WORK*)0)->transform==64)?1:-1];
typedef char WORK_axis_Offset[((unsigned)&((struct WORK*)0)->axis==128)?1:-1];
typedef char WORK_rotation_Offset[((unsigned)&((struct WORK*)0)->rotation==144)?1:-1];
typedef char WORK_relative_Offset[((unsigned)&((struct WORK*)0)->relative==192)?1:-1];
typedef char WORK_residual_Offset[((unsigned)&((struct WORK*)0)->residual==208)?1:-1];
typedef char WORK_gain_Offset[((unsigned)&((struct WORK*)0)->gain==224)?1:-1];
typedef char CLOCK_time_Offset[((unsigned)&((struct CLOCK*)0)->time==0)?1:-1];
typedef char CLOCK_dt_Offset[((unsigned)&((struct CLOCK*)0)->dt==4)?1:-1];
typedef char LM_low_Offset[((unsigned)&((struct LM*)0)->low==0)?1:-1];
typedef char LM_high_Offset[((unsigned)&((struct LM*)0)->high==4)?1:-1];
