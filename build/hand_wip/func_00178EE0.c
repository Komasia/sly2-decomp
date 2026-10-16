typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];} U;
struct M4{qword r[4];};
struct ACTOR{char pad[0xFD0];char control[0];};
struct MODEL{char pad[0x10];qword velocity;};
struct CONTROL{char pad[0x24];void*animation;};
struct CHOICE{int kind;struct MODEL*model;struct CONTROL*control;};
struct DRIVER{char pad[0x40];struct CHOICE*choice;};
struct P{char pad[0x10];struct ACTOR*actor;int pad14;struct DRIVER*driver;char pad1C[0x4C-0x1C];int mode;char pad50[0x80-0x50];qword target;char pad90[0xC4-0x90];float rate;char padC8[8];qword cached;float timeout;};
struct POLY{float a,b,c;};struct LIMIT{float low,high;};
extern struct POLY D_002BE6A0;extern struct LIMIT D_002BBB60;
extern float D_002BE694,D_002BE6B0,D_002DDED4;
extern qword D_002A2DC0,D_002A2DD0;
void func_001789F8(struct P*);qword func_001A62E8(struct ACTOR*);struct M4*func_001A6318(struct ACTOR*);
void func_00131A00(void*,float);float func_002458F0(float,float);void func_00209818(void*,float);void func_0020CB28(struct CONTROL*,qword);
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Reject(qword a,qword up){qword d,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(a),"j"(up));__asm__("vmulx.xyzw %0,%1,%2x":"=j"(d):"j"(up),"j"(d));return Sub(a,d);}
static inline float LengthXY(qword a){qword d;float len;__asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(d):"j"(a));__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(d):"j"(d));__asm__("qmfc2.ni %0,%1":"=r"(len):"j"(d));return len;}
static inline float Length(qword a){qword d,one;float len;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a));__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(d):"j"(d));__asm__("qmfc2.ni %0,%1":"=r"(len):"j"(d));return len;}
static inline float Clamp(float x,float low,float high){if(x<low)return low;if(high<x)return high;return x;}
static inline float Angle(qword delta){qword x;int y;float fx,fy;__asm__("qmfc2.ni %0,%1":"=r"(x):"j"(delta));__asm__("prot3w %0,%1":"=r"(y):"r"(x));__asm__("mtc1 %1,%0":"=f"(fx):"r"(x));__asm__("mtc1 %1,%0":"=f"(fy):"r"(y));return func_002458F0(fy,fx);}
static inline qword Project(struct M4*frame,qword a){register qword x __asm__("vf6"),y __asm__("vf5"),z __asm__("vf9"),one __asm__("vf7"),result __asm__("vf8");__asm__("vmul.xyzw %0,%5,%8\n\tvmaxw.xyzw %3,$vf0,$vf0w\n\tvmul.xyzw %1,%6,%8\n\tvmul.xyzw %2,%7,%8\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %4,%3,%0z\n\tvaddax.y $ACC,%1,%1x\n\tvmaddz.y %4,%3,%1z\n\tvaddax.z $ACC,%2,%2x\n\tvmaddy.z %4,%3,%2y":"=&j"(x),"=&j"(y),"=&j"(z),"=&j"(one),"=&j"(result):"j"(frame->r[0]),"j"(frame->r[1]),"j"(frame->r[2]),"j"(a));return result;}
static inline qword Response(qword direction,qword modelVelocity,float strength,qword fallback,U*u){register qword d __asm__("vf2"),xy __asm__("vf1"),length __asm__("vf3");qword scale;register qword normalized __asm__("vf1");float len,speed;
 __asm__("vmul.xyz %0,%3,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z\n\tvmul.xy %2,%4,%4\n\tvaddy.x %2,%2,%2y\n\tvsqrt $Q,%2x\n\tvwaitq\n\tvaddq.x %2,$vf0,$Q\n\tvsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %1,$vf0,$Q":"=&j"(d),"=&j"(length),"=j"(xy):"j"(direction),"j"(modelVelocity));
 __asm__("qmfc2.ni %0,%1":"=r"(speed):"j"(xy));
 __asm__("qmfc2.ni %0,%1":"=r"(len):"j"(length));
 strength*=speed;__asm__("qmtc2.ni %1,%0":"=j"(scale):"r"(strength));u->q=scale;
 if(len<0.0001f)normalized=fallback;else{__asm__ __volatile__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(normalized):"j"(length),"j"(direction));}
 __asm__("vmulx.xyzw %0,%1,%2x":"=j"(direction):"j"(normalized),"j"(u->q));return direction;
}
static inline qword Displacement(const qword*target,const qword*position){register qword old __asm__("vf1"),difference __asm__("vf3");__asm__("lqc2 %0,%1":"=j"(old):"m"(*position));__asm__("lqc2 %0,%1":"=j"(difference):"m"(*target));__asm__("vsub.xyzw %0,%0,%1":"+j"(difference):"j"(old));return difference;}
void func_00178EE0(struct P*p){
 func_001789F8(p);
 if((unsigned)p->mode<2){
  U scalar,position;float distance,factor;struct CHOICE*choice;qword delta;
  {qword value=func_001A62E8(p->actor);__asm__("sq %1,%0":"=m"(position.q):"r"(value));}
  {register float initial __asm__("$f3");__asm__("lwc1 %0,%1":"=f"(initial):"m"(D_002BE6A0.a));
  delta=Reject(Displacement(&p->target,&position.q),D_002A2DC0);
  distance=LengthXY(delta);
  factor=Clamp(initial+distance*(D_002BE6A0.b+distance*D_002BE6A0.c),D_002BBB60.low,D_002BBB60.high);}
  choice=p->driver->choice;
  switch(choice->kind){case 0:func_00131A00(choice->control,p->rate*factor);func_00209818(p->actor->control,Angle(delta));break;case 3:{qword projected=Project(func_001A6318(p->actor),delta);qword response=Response(projected,choice->model->velocity,p->rate*factor,D_002A2DD0,&scalar);func_0020CB28(choice->control,response);func_00131A00(choice->control->animation,factor);break;}default:break;}
  if(D_002BE6B0<Length(Sub(position.q,p->cached))){p->cached=position.q;p->timeout=D_002BE694;}else p->timeout-=D_002DDED4;
 }
}

typedef char qword_Size[(sizeof(qword)==16)?1:-1];
typedef char U_Size[(sizeof(U)==16)?1:-1];
typedef char M4_Size[(sizeof(struct M4)==64)?1:-1];
typedef char POLY_Size[(sizeof(struct POLY)==12)?1:-1];
typedef char LIMIT_Size[(sizeof(struct LIMIT)==8)?1:-1];
typedef char ACTOR_control_Offset[((unsigned)&((struct ACTOR*)0)->control==4048)?1:-1];
typedef char MODEL_velocity_Offset[((unsigned)&((struct MODEL*)0)->velocity==16)?1:-1];
typedef char CONTROL_animation_Offset[((unsigned)&((struct CONTROL*)0)->animation==36)?1:-1];
typedef char CHOICE_kind_Offset[((unsigned)&((struct CHOICE*)0)->kind==0)?1:-1];
typedef char CHOICE_model_Offset[((unsigned)&((struct CHOICE*)0)->model==4)?1:-1];
typedef char CHOICE_control_Offset[((unsigned)&((struct CHOICE*)0)->control==8)?1:-1];
typedef char DRIVER_choice_Offset[((unsigned)&((struct DRIVER*)0)->choice==64)?1:-1];
typedef char P_actor_Offset[((unsigned)&((struct P*)0)->actor==16)?1:-1];
typedef char P_driver_Offset[((unsigned)&((struct P*)0)->driver==24)?1:-1];
typedef char P_mode_Offset[((unsigned)&((struct P*)0)->mode==76)?1:-1];
typedef char P_target_Offset[((unsigned)&((struct P*)0)->target==128)?1:-1];
typedef char P_rate_Offset[((unsigned)&((struct P*)0)->rate==196)?1:-1];
typedef char P_cached_Offset[((unsigned)&((struct P*)0)->cached==208)?1:-1];
typedef char P_timeout_Offset[((unsigned)&((struct P*)0)->timeout==224)?1:-1];
typedef char POLY_a_Offset[((unsigned)&((struct POLY*)0)->a==0)?1:-1];
typedef char POLY_b_Offset[((unsigned)&((struct POLY*)0)->b==4)?1:-1];
typedef char POLY_c_Offset[((unsigned)&((struct POLY*)0)->c==8)?1:-1];
typedef char LIMIT_low_Offset[((unsigned)&((struct LIMIT*)0)->low==0)?1:-1];
typedef char LIMIT_high_Offset[((unsigned)&((struct LIMIT*)0)->high==4)?1:-1];
typedef char M4_r_Offset[((unsigned)&((struct M4*)0)->r==0)?1:-1];
