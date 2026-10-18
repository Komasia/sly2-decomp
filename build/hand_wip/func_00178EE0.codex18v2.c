typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];} U;
struct M4{qword r[4];};struct M3{qword r[3];};
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
static inline int LengthXYBits(qword a){register qword d __asm__("vf1");register int bits __asm__("$2");__asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(d):"j"(a));__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(d):"j"(d));__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(d));return bits;}
static inline float MovedX(qword q){register float f __asm__("$3");__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(q));return f;}
static inline qword MovedRoot(qword q){__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(q));return q;}
static inline int Moved(struct P*p,U*position){register qword d __asm__("vf1"),current __asm__("vf9"),one __asm__("vf2");register char*high __asm__("$2");register float threshold __asm__("$f1");register int result __asm__("$2");float distance;
 d=p->cached;__asm__("lui %0,%1":"=r"(high):"i"(0x2C));current=position->q;__asm__("vsub.xyzw %0,%1,%0":"+j"(d):"j"(current));
 __asm__("lwc1 %2,-6480(%3)\n\tvmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(d),"=j"(one),"=f"(threshold):"r"(high),"m"(*(float*)(high-6480)));
 __asm__("li %1,1\n\tvsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d),"=r"(result));distance=MovedX(d);result=threshold<distance?result:0;return result;}
static inline qword Planar(const qword*point){register qword value __asm__("vf4");__asm__("lqc2 %0,%1":"=j"(value):"m"(*point));return value;}
static inline qword Project(qword rowX,qword rowY,qword rowZ,qword a){register qword x __asm__("vf6"),y __asm__("vf5"),z __asm__("vf9"),one __asm__("vf7"),result __asm__("vf8");__asm__("vmul.xyzw %0,%5,%8\n\tvmaxw.xyzw %3,$vf0,$vf0w\n\tvmul.xyzw %1,%6,%8\n\tvmul.xyzw %2,%7,%8\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %4,%3,%0z\n\tvaddax.y $ACC,%1,%1x\n\tvmaddz.y %4,%3,%1z\n\tvaddax.z $ACC,%2,%2x\n\tvmaddy.z %4,%3,%2y":"=&j"(x),"=&j"(y),"=&j"(z),"=&j"(one),"=&j"(result):"j"(rowX),"j"(rowY),"j"(rowZ),"j"(a));return result;}
static inline qword ScaleResponse(qword direction,qword scale){qword result;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(result):"j"(direction),"j"(scale));return result;}
void func_00178EE0(struct P*p){
 func_001789F8(p);
 if((unsigned)p->mode<2){
  U scalar,position,planar;float factor;struct CHOICE*choice;qword delta;
  {qword value=func_001A62E8(p->actor);__asm__("sq %1,%0":"=m"(position.q):"r"(value));}
  {register unsigned polyHigh __asm__("$3"),upAddress __asm__("$2"),limitAddress __asm__("$2");
   register float initial __asm__("$f3"),low __asm__("$f4"),high __asm__("$f5"),b __asm__("$f1"),c __asm__("$f2"),xy __asm__("$f0");register int distanceBits __asm__("$2");register qword old __asm__("vf1"),difference __asm__("vf3"),up __asm__("vf1");
   __asm__("lui %0,%2\n\tlui %1,%%hi(%3)":"=r"(polyHigh),"=r"(upAddress):"i"(0x2C),"i"(&D_002A2DC0));
   __asm__("lwc1 %0,%4\n\tlqc2 %1,%5\n\taddiu %2,%2,%%lo(%6)\n\tlqc2 %3,%7":"=f"(initial),"=j"(old),"+r"(upAddress),"=j"(difference):"m"(*(float*)(polyHigh-0x1960)),"m"(position.q),"i"(&D_002A2DC0),"m"(p->target));
   __asm__("vsub.xyzw %0,%0,%1":"+j"(difference):"j"(old));
   __asm__("lqc2 %0,%1":"=j"(up):"m"(*(qword*)upAddress));
   {register qword rejected __asm__("vf4");
    __asm__("vmul.xyz $vf2,%3,%4\n\tvaddw.x $vf4,$vf0,$vf0w\n\tvadday.x $ACC,$vf2,$vf2y\n\tvmaddz.x $vf2,$vf4,$vf2z\n\taddiu $2,%5,-6496\n\tvmulx.xyzw $vf2,%4,$vf2x\n\tlwc1 %1,8($2)\n\tvsub.xyzw %0,%3,$vf2\n\tlwc1 %2,4($2)":"=j"(rejected),"=f"(c),"=f"(b):"j"(difference),"j"(up),"r"(polyHigh),"m"(*(float*)(polyHigh-0x1958)),"m"(*(float*)(polyHigh-0x195C)):"$2","vf2");
    delta=rejected;}
   distanceBits=LengthXYBits(delta);
   __asm__("mtc1 %2,%0\n\tmul.s %1,%0,%1":"=f"(xy),"+f"(c):"r"(distanceBits));
   __asm__("lui %0,%%hi(%1)":"=r"(limitAddress):"i"(&D_002BBB60));
   __asm__("lwc1 %0,%%lo(%3)(%1)\n\taddiu %1,%1,%%lo(%3)\n\tadd.s %2,%2,%5":"=f"(low),"+r"(limitAddress),"+f"(b):"i"(&D_002BBB60),"m"(*(float*)(limitAddress-0x44A0)),"f"(c));
   {register float value __asm__("$f12")=initial+xy*b;high=((struct LIMIT*)limitAddress)->high;if(value<low)factor=low;else if(high<value)factor=high;else factor=value;}}
  choice=p->driver->choice;
  switch(choice->kind){
  case 0:{register void*control __asm__("$4")=choice->control;void*actorControl;float angle,fx,fy;register qword words __asm__("$3");qword planarValue;float rate=p->rate*factor;
   planar.q=delta;func_00131A00(control,rate);planarValue=Planar(&planar.q);actorControl=p->actor;
   __asm__("qmfc2.ni %0,%3\n\taddiu %1,%1,4048\n\tmtc1 %0,%2":"=r"(words),"+r"(actorControl),"=f"(fx):"j"(planarValue));
   __asm__("prot3w %0,%0":"+r"(words));__asm__("mtc1 %1,%0":"=f"(fy):"r"(words));angle=func_002458F0(fy,fx);func_00209818(actorControl,angle);break;}
  case 3:{qword projected,response;register qword normalized __asm__("vf1");register struct ACTOR*actor __asm__("$4")=p->actor;register struct CONTROL*control __asm__("$4");register qword rowZ __asm__("vf3"),rowX __asm__("vf2"),rowY __asm__("vf1"),ray __asm__("vf4");register struct MODEL*model __asm__("$4");register const qword*zero __asm__("$3");struct M4*matrix;
   planar.q=delta;matrix=func_001A6318(actor);
   __asm__("lqc2 %0,32(%6)\n\tlui %5,42\n\tlqc2 %1,0(%6)\n\taddiu %5,%5,11728\n\tlqc2 %2,16(%6)\n\tlw %3,%9\n\tlqc2 %4,%8":"=j"(rowZ),"=j"(rowX),"=j"(rowY),"=r"(model),"=j"(ray),"=r"(zero):"r"(matrix),"m"(*(struct M3*)matrix),"m"(planar.q),"m"(choice->model));
   projected=Project(rowX,rowY,rowZ,ray);{register qword d __asm__("vf2"),xy __asm__("vf1"),length __asm__("vf3");register qword scale __asm__("vf2");register float strength __asm__("$f0"),speed __asm__("$f1"),len __asm__("$f2"),threshold __asm__("$f3");register qword fallback __asm__("$3");
 __asm__("lwc1 %0,%4\n\tlqc2 %3,%5\n\tvmul.xyz %1,%6,%6\n\tvaddw.x %2,$vf0,$vf0w\n\tvadday.x $ACC,%1,%1y\n\tvmaddz.x %1,%2,%1z\n\tvmul.xy %3,%3,%3\n\tvaddy.x %3,%3,%3y":"=f"(strength),"=j"(d),"=j"(length),"=j"(xy):"m"(p->rate),"m"(model->velocity),"j"(projected));
 __asm__("mul.s %3,%3,%4\n\tvsqrt $Q,%2x\n\tvwaitq\n\tvaddq.x %2,$vf0,$Q\n\tvsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %1,$vf0,$Q":"+j"(d),"+j"(length),"+j"(xy),"+f"(strength):"f"(factor));
 __asm__("qmfc2.ni $2,%2\n\tli.s %1,0.0001\n\tmtc1 $2,%0":"=f"(speed),"=f"(threshold):"j"(xy):"$1","$2");
 __asm__("lq %0,%3\n\tmul.s %1,%1,%4\n\tqmfc2.ni $2,%5\n\tmtc1 $2,%2":"=r"(fallback),"+f"(strength),"=f"(len):"m"(*zero),"f"(speed),"j"(length):"$2");
 __asm__("mfc1 $2,%1\n\tqmtc2.ni $2,%0":"=j"(scale):"f"(strength):"$2");scalar.q=scale;
 if(len<threshold){__asm__("qmtc2.ni %1,%0":"=j"(normalized):"r"(fallback));}else{__asm__ volatile("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(normalized):"j"(length),"j"(projected));}

}control=choice->control;response=ScaleResponse(normalized,scalar.q);func_0020CB28(control,response);func_00131A00(choice->control->animation,factor);break;}
  default:break;}
  {if(Moved(p,&position)){qword current;__asm__("lq %0,%1":"=r"(current):"m"(position.q));p->cached=current;p->timeout=D_002BE694;}else p->timeout-=D_002DDED4;}
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

typedef char M3_Size[(sizeof(struct M3)==48)?1:-1];
typedef char M3_r_Offset[((unsigned)&((struct M3*)0)->r==0)?1:-1];
