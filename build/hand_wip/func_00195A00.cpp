typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];int i[4];};struct VTE{short delta,pad;void*fn;};struct ANGLES{char pad0[0x18];float heading,amount;};struct ACTOR{char pad0[12];VTE*vt;char pad10[0x140];ANGLES*angles;char pad154[0x54];float heading;char pad1AC[0xB4];float scale;char pad264[0x131C-0x264];float stamp;char pad1320[0x18F0-0x1320];int transition;};
struct CONTEXT{ACTOR*actor;int state,variant;char padC[12];float stamp;int mode;char pad20[4];int flag24,flag28,flag2C;char pad30[4];float gain,turnGain,height;int combo;float time44,time48,time4C;char pad50[0x60];float heading,radiusGain,radius;char padBC[0x168-0xBC];float oldScale;void*focus;char pad170[4];int focused;};struct CLOCK{float time,dt;};// Native state17 reads other before any write to that stack slot.
struct WORK{U velocity,other;};
extern "C"{extern CLOCK D_002DDED0;extern U D_002A2DC0,D_002BF770;extern float D_002BF750,D_002BF754,D_002BF758,D_002BF75C,D_002BF760,D_002BF764,D_002BF768,D_002BF76C,D_002BF730;
void func_00204DA8(ACTOR*,float);qword func_0019A750(CONTEXT*,int);void func_00195FB8(CONTEXT*,int,ACTOR*);qword func_0011E1A0(float,float,float);void func_00140C88(ACTOR*,void*);void func_0011EF08(qword,float*,float*,float*);int func_00132B10(ACTOR*,int);qword func_001A62E8(ACTOR*);}
static inline void Enable(ACTOR*p,int yes){VTE&v=p->vt[88];((void(*)(void*,int))v.fn)((char*)p+v.delta,yes);}
static inline void SetVelocity(ACTOR*p,qword velocity){VTE&v=p->vt[35];((void(*)(void*,qword))v.fn)((char*)p+v.delta,velocity);}
static inline qword Add(qword a,qword b){__asm__("vadd.xyzw %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline qword Horizontal(qword velocity,qword up){qword d,one,projection,r;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(velocity),"j"(up));__asm__("vmulx.xyzw %0,%1,%2x":"=j"(projection):"j"(up),"j"(d));__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(velocity),"j"(projection));return r;}
static inline float Z(qword q){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(q));return f;}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char VTE_Size[sizeof(VTE)==8?1:-1];
typedef char ANGLES_Size[sizeof(ANGLES)==32?1:-1];
typedef char ACTOR_Size[sizeof(ACTOR)==6388?1:-1];
typedef char CONTEXT_Size[sizeof(CONTEXT)==376?1:-1];
typedef char CLOCK_Size[sizeof(CLOCK)==8?1:-1];
typedef char WORK_Size[sizeof(WORK)==32?1:-1];
typedef char VTE_delta_Offset[FIELD_OFFSET(VTE,delta)==0?1:-1];
typedef char VTE_fn_Offset[FIELD_OFFSET(VTE,fn)==4?1:-1];
typedef char ANGLES_heading_Offset[FIELD_OFFSET(ANGLES,heading)==24?1:-1];
typedef char ANGLES_amount_Offset[FIELD_OFFSET(ANGLES,amount)==28?1:-1];
typedef char ACTOR_vt_Offset[FIELD_OFFSET(ACTOR,vt)==12?1:-1];
typedef char ACTOR_angles_Offset[FIELD_OFFSET(ACTOR,angles)==336?1:-1];
typedef char ACTOR_heading_Offset[FIELD_OFFSET(ACTOR,heading)==424?1:-1];
typedef char ACTOR_scale_Offset[FIELD_OFFSET(ACTOR,scale)==608?1:-1];
typedef char ACTOR_stamp_Offset[FIELD_OFFSET(ACTOR,stamp)==4892?1:-1];
typedef char ACTOR_transition_Offset[FIELD_OFFSET(ACTOR,transition)==6384?1:-1];
typedef char CONTEXT_actor_Offset[FIELD_OFFSET(CONTEXT,actor)==0?1:-1];
typedef char CONTEXT_state_Offset[FIELD_OFFSET(CONTEXT,state)==4?1:-1];
typedef char CONTEXT_variant_Offset[FIELD_OFFSET(CONTEXT,variant)==8?1:-1];
typedef char CONTEXT_stamp_Offset[FIELD_OFFSET(CONTEXT,stamp)==24?1:-1];
typedef char CONTEXT_mode_Offset[FIELD_OFFSET(CONTEXT,mode)==28?1:-1];
typedef char CONTEXT_flag24_Offset[FIELD_OFFSET(CONTEXT,flag24)==36?1:-1];
typedef char CONTEXT_flag28_Offset[FIELD_OFFSET(CONTEXT,flag28)==40?1:-1];
typedef char CONTEXT_flag2C_Offset[FIELD_OFFSET(CONTEXT,flag2C)==44?1:-1];
typedef char CONTEXT_gain_Offset[FIELD_OFFSET(CONTEXT,gain)==52?1:-1];
typedef char CONTEXT_turnGain_Offset[FIELD_OFFSET(CONTEXT,turnGain)==56?1:-1];
typedef char CONTEXT_height_Offset[FIELD_OFFSET(CONTEXT,height)==60?1:-1];
typedef char CONTEXT_combo_Offset[FIELD_OFFSET(CONTEXT,combo)==64?1:-1];
typedef char CONTEXT_time44_Offset[FIELD_OFFSET(CONTEXT,time44)==68?1:-1];
typedef char CONTEXT_time48_Offset[FIELD_OFFSET(CONTEXT,time48)==72?1:-1];
typedef char CONTEXT_time4C_Offset[FIELD_OFFSET(CONTEXT,time4C)==76?1:-1];
typedef char CONTEXT_heading_Offset[FIELD_OFFSET(CONTEXT,heading)==176?1:-1];
typedef char CONTEXT_radiusGain_Offset[FIELD_OFFSET(CONTEXT,radiusGain)==180?1:-1];
typedef char CONTEXT_radius_Offset[FIELD_OFFSET(CONTEXT,radius)==184?1:-1];
typedef char CONTEXT_oldScale_Offset[FIELD_OFFSET(CONTEXT,oldScale)==360?1:-1];
typedef char CONTEXT_focus_Offset[FIELD_OFFSET(CONTEXT,focus)==364?1:-1];
typedef char CONTEXT_focused_Offset[FIELD_OFFSET(CONTEXT,focused)==372?1:-1];
typedef char CLOCK_time_Offset[FIELD_OFFSET(CLOCK,time)==0?1:-1];
typedef char CLOCK_dt_Offset[FIELD_OFFSET(CLOCK,dt)==4?1:-1];
typedef char WORK_velocity_Offset[FIELD_OFFSET(WORK,velocity)==0?1:-1];
typedef char WORK_other_Offset[FIELD_OFFSET(WORK,other)==16?1:-1];
extern "C" void func_00195A00(CONTEXT*p,int state,int variant,ACTOR*source){WORK w;
 if(state!=6)p->state=state;p->variant=variant;Enable(p->actor,1);
 if(state!=6){p->combo=0;p->time4C=D_002DDED0.time;p->time48=p->time4C;p->time44=p->time4C;}
 if(state==9){p->oldScale=p->actor->scale;func_00204DA8(p->actor,D_002BF750);}
 w.velocity.q=func_0019A750(p,state);SetVelocity(p->actor,w.velocity.q);p->actor->stamp=D_002DDED0.time;if(state!=6)p->stamp=D_002DDED0.time;
 switch(state){
 case 0:func_00195FB8(p,4,source);p->flag28=1;p->turnGain=1.0f;p->flag24=0;break;
 case 11:func_00195FB8(p,4,source);p->flag24=1;p->turnGain=1.0f;p->flag28=0;break;
 case 3:if(p->actor->angles->amount<0.2f){p->combo=3;qword boost=func_0011E1A0(p->actor->heading,D_002BF754,0.0f);SetVelocity(p->actor,Add(w.velocity.q,boost));}func_00195FB8(p,0,source);p->flag28=1;p->gain=1.0f;p->turnGain=0.6f;p->flag24=0;break;
 case 1:case 2:case 18:func_00195FB8(p,0,source);p->flag28=1;p->turnGain=1.0f;p->flag24=0;break;
 case 9:func_00195FB8(p,0,source);p->flag24=0;p->flag28=1;func_00140C88(p->actor,p->focus);p->turnGain=D_002BF758;p->gain=D_002BF75C;p->focused=1;break;
 case 7:func_00195FB8(p,7,source);p->flag28=1;p->gain=1.0f;p->flag24=0;p->turnGain=1.0f;break;
 case 8:func_00195FB8(p,5,source);p->flag24=0;p->flag28=1;p->gain=1.0f;p->turnGain=1.0f;func_0011EF08(w.velocity.q,&p->heading,&p->radius,0);p->radiusGain=1.0f;break;
 case 6:{int mode=2;if(p->state<15){mode=p->state<13?2:3;}func_00195FB8(p,mode,source);break;}
 case 14:func_00195FB8(p,1,source);p->flag28=1;p->gain=D_002BF764;p->flag24=0;p->turnGain=D_002BF760;if(p->actor->angles->amount<0.2f){p->combo=3;qword boost=func_0011E1A0(p->actor->angles->heading,D_002BF730*p->turnGain,0.0f);SetVelocity(p->actor,Add(w.velocity.q,boost));}break;
 case 13:func_00195FB8(p,1,source);p->flag28=1;p->turnGain=D_002BF768;p->gain=D_002BF76C;p->flag24=0;break;
 case 10:p->combo=-1;func_00195FB8(p,21,source);p->flag24=0;p->flag28=0;p->gain=0.0f;p->turnGain=0.0f;break;
 case 12:func_00195FB8(p,1,source);p->combo=3;p->flag28=1;p->turnGain=1.0f;p->flag24=0;break;
 case 16:func_00195FB8(p,4,source);p->flag24=0;p->turnGain=1.0f;p->flag28=0;break;
 case 15:func_00195FB8(p,0,source);p->flag24=0;p->turnGain=1.0f;p->flag28=0;break;
 case 17:if(p->mode==-1){SetVelocity(p->actor,Add(Horizontal(w.other.q,D_002A2DC0.q),D_002BF770.q));p->flag28=1;}func_00195FB8(p,22,0);p->flag24=0;p->turnGain=1.0f;p->flag2C=0;p->gain=1.0f;break;
 default:break;
 }
 if(state!=6){if(state!=17)p->flag2C=p->flag28;if(func_00132B10(p->actor,0x35))p->actor->transition=-1;}
 p->height=Z(func_001A62E8(p->actor));
}