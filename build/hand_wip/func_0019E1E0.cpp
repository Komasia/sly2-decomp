typedef int qword __attribute__((mode(TI)));typedef unsigned long ulong;
union U{qword q;float f[4];int i[4];};struct VE{short delta,pad;void*fn;};
struct INPUT{char pad0[0x10];float x,y;char pad18[4];float amount;};
struct ACTION;struct ASEGA;struct ANIMATION;
struct P{char pad0[12];VE*vt;char pad10[0x150-0x10];INPUT*input;char pad154[0x2C0-0x154];char controller[0xF00-0x2C0];char action[0x1010-0xF00];U offset;char pad1020[0x10];ASEGA*asega;};
struct PATH{char pad0[0x28];ulong flags;char pad30[0xE4-0x30];int cyclic;};
struct C{P*actor;int state;float time;PATH*path;float distance,speed;int descending;float reset;int previous;char pad24[12];U offset;char pad40[0x10];float weight0;char pad54[8];float speed0,weight1;char pad64[8];float speed1;ANIMATION*animation;};
struct CLOCK{float time,dt;};struct SMP{float maximum,minimum,duration;};struct LM{float low,high;};struct WORK{U ahead,behind;union{U input;SMP smooth;}reuse;LM limit;};
extern "C"{
extern CLOCK D_002DDED0;extern U D_002A2DD0,D_002A2DC0;extern SMP D_002BF928;
qword func_0011F088(qword,qword,float,SMP*,U*);
void func_00195A00(void*,int,void*,void*);int func_001C46C0(INPUT*,int,float);int func_001C4660(INPUT*,int,float);void func_001C4738(INPUT*,int);
void func_0019CC50(void*,int,void*,void*);int func_00131968(ASEGA*);void func_0019EAB0(C*,int);
float func_001E6728(PATH*,float);void func_001E6F10(PATH*,float,U*,U*);qword func_001C4768(INPUT*,qword);
void func_0019E110(C*,LM*);float func_0011D018(float,float,float,SMP*,float*);void func_001F4BF8(P*);float func_001E6648(PATH*);float func_0011D898(float,float);void func_001384C0(ANIMATION*);
float fabsf(float);
}
static inline ulong Eligible(PATH*p){return (p->flags>>60)&1;}
static inline int CanAct(P*p,int kind){VE&v=p->vt[99];return ((int(*)(void*,int))v.fn)((char*)p+v.delta,kind);}
static inline qword Sub(qword a,qword b){qword q;__asm__("vsub.xyzw %0,%1,%2":"=j"(q):"j"(a),"j"(b));return q;}
static inline qword Direction(U*a,U*b,U*&axis){
 register qword first __asm__("vf2"),second __asm__("vf1"),direction __asm__("vf3");register U*address __asm__("$2");
 __asm__("lqc2 %0,%4\n\tlui %2,%%hi(%6)\n\tlqc2 %1,%5\n\taddiu %2,%2,%%lo(%6)\n\tvsub.xyzw %3,%0,%1":"=j"(first),"=j"(second),"=&r"(address),"=j"(direction):"m"(a->q),"m"(b->q),"i"(&D_002A2DC0));
 axis=address;return direction;
}
static inline qword Normal(qword v,U*axis){
 register qword d __asm__("vf1"),one __asm__("vf2"),r __asm__("vf1");float length;register int bits __asm__("$3");
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=j"(one):"j"(v));
 register qword fallback __asm__("$2")=axis->q;
 __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));
 __asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(d));
 __asm__("mtc1 %1,%0":"=f"(length):"r"(bits));
 if(length<0.0001f){r=fallback;}
 else{__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(r):"j"(d),"j"(v));}
 qword q;__asm__("qmfc2.ni %0,%1":"=r"(q):"j"(r));return q;
}
static inline float Z(qword q){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(q));return f;}
static inline qword XY(INPUT*p){float x=p->x,y=p->y,zero=0.0f;int a,b,z;qword q;__asm__("mfc1 %0,%1":"=r"(a):"f"(x));__asm__("mfc1 %0,%1":"=r"(b):"f"(y));__asm__("pextlw %0,%2,%1":"=r"(q):"r"(a),"r"(b));__asm__("mfc1 %0,%1":"=r"(z):"f"(zero));__asm__("pcpyld %0,%1,%0":"+r"(q):"r"(z));return q;}
static inline float Dot(qword a,qword b){qword q,one;float f;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(q),"=&j"(one):"j"(a),"j"(b));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(q));return f;}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char VE_Size[sizeof(VE)==8?1:-1];
typedef char INPUT_Size[sizeof(INPUT)==32?1:-1];
typedef char P_Size[sizeof(P)==4160?1:-1];
typedef char PATH_Size[sizeof(PATH)==232?1:-1];
typedef char C_Size[sizeof(C)==128?1:-1];
typedef char SMP_Size[sizeof(SMP)==12?1:-1];
typedef char LM_Size[sizeof(LM)==8?1:-1];
typedef char WORK_Size[sizeof(WORK)==64?1:-1];
typedef char CLOCK_Size[sizeof(CLOCK)==8?1:-1];
typedef char INPUT_x_Offset[FIELD_OFFSET(INPUT,x)==16?1:-1];
typedef char INPUT_y_Offset[FIELD_OFFSET(INPUT,y)==20?1:-1];
typedef char INPUT_amount_Offset[FIELD_OFFSET(INPUT,amount)==28?1:-1];
typedef char P_vt_Offset[FIELD_OFFSET(P,vt)==12?1:-1];
typedef char P_input_Offset[FIELD_OFFSET(P,input)==336?1:-1];
typedef char P_controller_Offset[FIELD_OFFSET(P,controller)==704?1:-1];
typedef char P_action_Offset[FIELD_OFFSET(P,action)==3840?1:-1];
typedef char P_offset_Offset[FIELD_OFFSET(P,offset)==4112?1:-1];
typedef char P_asega_Offset[FIELD_OFFSET(P,asega)==4144?1:-1];
typedef char PATH_flags_Offset[FIELD_OFFSET(PATH,flags)==40?1:-1];
typedef char PATH_cyclic_Offset[FIELD_OFFSET(PATH,cyclic)==228?1:-1];
typedef char C_actor_Offset[FIELD_OFFSET(C,actor)==0?1:-1];
typedef char C_state_Offset[FIELD_OFFSET(C,state)==4?1:-1];
typedef char C_time_Offset[FIELD_OFFSET(C,time)==8?1:-1];
typedef char C_path_Offset[FIELD_OFFSET(C,path)==12?1:-1];
typedef char C_distance_Offset[FIELD_OFFSET(C,distance)==16?1:-1];
typedef char C_speed_Offset[FIELD_OFFSET(C,speed)==20?1:-1];
typedef char C_descending_Offset[FIELD_OFFSET(C,descending)==24?1:-1];
typedef char C_reset_Offset[FIELD_OFFSET(C,reset)==28?1:-1];
typedef char C_previous_Offset[FIELD_OFFSET(C,previous)==32?1:-1];
typedef char C_offset_Offset[FIELD_OFFSET(C,offset)==48?1:-1];
typedef char C_weight0_Offset[FIELD_OFFSET(C,weight0)==80?1:-1];
typedef char C_speed0_Offset[FIELD_OFFSET(C,speed0)==92?1:-1];
typedef char C_weight1_Offset[FIELD_OFFSET(C,weight1)==96?1:-1];
typedef char C_speed1_Offset[FIELD_OFFSET(C,speed1)==108?1:-1];
typedef char C_animation_Offset[FIELD_OFFSET(C,animation)==112?1:-1];
typedef char SMP_maximum_Offset[FIELD_OFFSET(SMP,maximum)==0?1:-1];
typedef char SMP_minimum_Offset[FIELD_OFFSET(SMP,minimum)==4?1:-1];
typedef char SMP_duration_Offset[FIELD_OFFSET(SMP,duration)==8?1:-1];
typedef char LM_low_Offset[FIELD_OFFSET(LM,low)==0?1:-1];
typedef char LM_high_Offset[FIELD_OFFSET(LM,high)==4?1:-1];
typedef char WORK_ahead_Offset[FIELD_OFFSET(WORK,ahead)==0?1:-1];
typedef char WORK_behind_Offset[FIELD_OFFSET(WORK,behind)==16?1:-1];
typedef char WORK_reuse_Offset[FIELD_OFFSET(WORK,reuse)==32?1:-1];
typedef char WORK_limit_Offset[FIELD_OFFSET(WORK,limit)==48?1:-1];
typedef char CLOCK_time_Offset[FIELD_OFFSET(CLOCK,time)==0?1:-1];
typedef char CLOCK_dt_Offset[FIELD_OFFSET(CLOCK,dt)==4?1:-1];
extern "C" void func_0019E1E0(C*p){
 WORK w;float lowSpeed,highSpeed;P*actor=p->actor;actor->offset.q=func_0011F088(actor->offset.q,D_002A2DD0.q,D_002DDED0.dt,&D_002BF928,0);
 INPUT*input=p->actor->input;
 if(!Eligible(p->path)){func_00195A00(p->actor->controller,0,0,0);return;}
 if(p->state&&func_001C46C0(input,0x40,0.25f)){func_00195A00(p->actor->controller,2,0,0);return;}
 if(func_001C4660(input,0x400,0.15f)&&CanAct(p->actor,3)){func_001C4738(input,0x400);func_0019CC50(p->actor->action,0,0,0);}
 int old;do{old=p->state;if((old==0||old==4)&&func_00131968(p->actor->asega))func_0019EAB0(p,1);}while(p->state!=old);
 if(p->state==0||p->state==4)return;
 func_001E6F10(p->path,func_001E6728(p->path,p->distance+50.0f),&w.ahead,0);
 func_001E6F10(p->path,func_001E6728(p->path,p->distance-50.0f),&w.behind,0);
 U*axis;qword direction=Direction(&w.ahead,&w.behind,axis);qword normalized=Normal(direction,axis);float z=Z(normalized);
 if(fabsf(z)>0.5f){if(z>0.0f){if(p->descending)goto turn;}else if(!p->descending)goto turn;}
 if(p->reset>0.4f&&p->descending&&Z(normalized)>-0.3f)goto turn;
 if(p->reset<-0.4f&&!p->descending&&Z(normalized)<0.3f)goto turn;
 goto proceed;
 turn:func_0019EAB0(p,4);return;
 proceed:;
 qword tangent=func_001C4768(input,Sub(w.ahead.q,w.behind.q));w.reuse.input.q=XY(input);float amount=input->amount;float dot=Dot(tangent,w.reuse.input.q);
 switch(p->previous){case 0:if(amount<0.25f)p->previous=-1;else if(dot<-0.7f)p->previous=1;break;
 case 1:if(amount<0.25f)p->previous=-1;else if(dot>0.7f)p->previous=0;break;
 case -1:if(amount>0.35f)p->previous=0.0f<=dot?0:1;break;}
 int mode=-1;float blend=dot;
 switch(p->previous){case 0:mode=p->descending?3:2;blend=amount;break;case 1:mode=p->descending?2:3;blend=amount;break;case -1:mode=1;blend=0.0f;break;}
 float speed;
 if(blend>0.01f){speed=(1.0f-blend)*p->speed0+blend*p->speed1;if(mode==3)speed=-speed;}
 else{speed=0.0f;mode=1;}
 if(p->descending)speed=-speed;
 float maximum=fabsf(p->speed1);w.reuse.smooth.maximum=maximum;w.reuse.smooth.minimum=0.0f;w.reuse.smooth.duration=0.2f;
 float dt=D_002DDED0.dt;p->reset=(-dt*speed)/maximum+(1.0f-dt)*p->reset;
 if(!p->path->cyclic){func_0019E110(p,&w.limit);(void)func_0011D018(p->distance,w.limit.low,D_002DDED0.dt,&w.reuse.smooth,&lowSpeed);(void)func_0011D018(p->distance,w.limit.high,D_002DDED0.dt,&w.reuse.smooth,&highSpeed);float low=-highSpeed,high=-lowSpeed;if(speed<low)speed=low;else if(high<speed)speed=high;}
 p->speed=-speed;
 if(speed!=0.0f){p->distance+=p->speed*D_002DDED0.dt;func_001F4BF8(p->actor);}
 if(p->path->cyclic)p->distance=func_0011D898(p->distance,func_001E6648(p->path));
 float magnitude=fabsf(speed),weight;
 if(magnitude<0.01f)mode=1;else{weight=(magnitude-fabsf(p->speed0))/(fabsf(p->speed1)-fabsf(p->speed0));if(weight<0.0f)weight=0.0f;else if(1.0f<weight)weight=1.0f;p->weight0=1.0f-weight;p->weight1=weight;func_001384C0(p->animation);}
 func_0019EAB0(p,mode);
}