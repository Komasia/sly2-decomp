typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];int i[4];};
union F{float value;int bits;};
struct VE{short delta,pad;void*fn;};
struct M4{U row[4];};struct M3{U row[3];};
struct PATH;struct ASEG;struct ASEGA;struct EFFECT;struct SOURCE;
struct P{char pad0[12];VE*vt;char pad10[0x5C-0x10];void*group;char pad60[0x158-0x60];float low0,high0,low1,high1,lead;char pad16c[4];PATH*path;float parameter,phase;char pad17c[0x1C4-0x17C];ASEGA*animation;char pad1c8[8];F speed;int oldMode;float heading;char pad1dc[4];M3 basis;float spin[3];float ratio;int state;float changed,randomDeadline,deadline;int amount;char pad234[12];U damageOffset;};
struct WORK{U first,second,direction,velocity,scalar;float angle,parameter;};
struct CLOCK{float t,dt;};
extern "C"{
 extern CLOCK D_002DDED0;extern U D_002A2DD0,D_002A2DA0;extern char D_003DD490[],D_002DE578[];
 void func_002303A0(P*,void*,int);void func_0022C840(P*,void*);void func_0022C818(P*,void*);
 float func_0011D448(float,float);void func_0011EFB0(qword,float*,float*,float*);
 void func_001B1818(P*,float);void func_001B17B8(P*,float);
 qword func_001A62E8(P*);void func_001E6F60(PATH*,qword,void*,U*,U*,float*,float*);
 float func_001E77E8(PATH*);float func_001E6648(PATH*);P*func_001C4AF8(void*,qword);
 EFFECT*func_001FBB90(int);void func_001FB2F8(EFFECT*,SOURCE*);void func_001FB3F0(EFFECT*,qword);
 qword func_001A6F00(P*,P*,qword);void func_00154E10(void*,qword,int,int,P*);
 void func_001305B8(ASEG*,P*,float,float,int,ASEGA**);
}
static inline void SetVelocity(P*p,qword q){VE&v=p->vt[35];((void(*)(void*,qword))v.fn)((char*)p+v.delta,q);}
static inline void Call(P*p,int index){VE&v=p->vt[index];((void(*)(void*))v.fn)((char*)p+v.delta);}
static inline void SetMode(P*p){VE&v=p->vt[47];((void(*)(void*,int))v.fn)((char*)p+v.delta,4);}
static inline M4*GetMatrix(P*p){VE&v=p->vt[31];return ((M4*(*)(void*))v.fn)((char*)p+v.delta);}
static inline float MinusOne(){float f;int bits=0xBF800000;__asm__("mtc1 %1,%0":"=f"(f):"r"(bits));return f;}
static inline qword Scalar(float f){int bits;qword q;__asm__("mfc1 %0,%1":"=r"(bits):"f"(f));__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(bits));return q;}
static inline qword ScalarBits(int bits){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(bits));return q;}
static inline qword Scale(qword v,qword k){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(k));return r;}
static inline qword Difference(U*a,U*b){qword first,second;__asm__("lqc2 %0,%1":"=j"(first):"m"(a->q));__asm__("lqc2 %0,%1":"=j"(second):"m"(b->q));__asm__("vsub.xyzw %0,%0,%1":"+j"(first):"j"(second));return first;}
static inline float Distance(U*first,U*second){
 register qword delta __asm__("vf1"),other __asm__("vf2"),one __asm__("vf2");int bits;float length;
 __asm__("lqc2 %0,%1":"=j"(other):"m"(second->q));
 __asm__("lqc2 %0,%1":"=j"(delta):"m"(first->q));
 __asm__("vsub.xyzw %0,%0,%1":"+j"(delta):"j"(other));
 __asm__("vmul.xyz %0,%0,%0":"+j"(delta));
 __asm__("vaddw.x %0,$vf0,$vf0w\n\tvadday.x $ACC,%1,%1y\n\tvmaddz.x %1,%0,%1z":"=j"(one),"+j"(delta));
 __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(delta));
 __asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(delta));__asm__("mtc1 %1,%0":"=f"(length):"r"(bits));return length;
}
static inline qword Normal(U*point,qword fallback){
 register qword v __asm__("vf3")=point->q;register qword d __asm__("vf1"),one __asm__("vf2"),result __asm__("vf2");int bits;float length;
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=j"(one):"j"(v));
 __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));
 __asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(d));__asm__("mtc1 %1,%0":"=f"(length):"r"(bits));
 __asm__("qmtc2.ni %1,%0":"=j"(result):"r"(fallback));
 if(!(length<0.0001f)){__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"+j"(result):"j"(d),"j"(v));}
 return result;
}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char F_Size[sizeof(F)==4?1:-1];
typedef char VE_Size[sizeof(VE)==8?1:-1];
typedef char M3_Size[sizeof(M3)==48?1:-1];
typedef char M4_Size[sizeof(M4)==64?1:-1];
typedef char WORK_Size[sizeof(WORK)==96?1:-1];
typedef char CLOCK_Size[sizeof(CLOCK)==8?1:-1];
typedef char P_vt_Offset[FIELD_OFFSET(P,vt)==12?1:-1];
typedef char P_group_Offset[FIELD_OFFSET(P,group)==92?1:-1];
typedef char P_low0_Offset[FIELD_OFFSET(P,low0)==344?1:-1];
typedef char P_high0_Offset[FIELD_OFFSET(P,high0)==348?1:-1];
typedef char P_low1_Offset[FIELD_OFFSET(P,low1)==352?1:-1];
typedef char P_high1_Offset[FIELD_OFFSET(P,high1)==356?1:-1];
typedef char P_lead_Offset[FIELD_OFFSET(P,lead)==360?1:-1];
typedef char P_path_Offset[FIELD_OFFSET(P,path)==368?1:-1];
typedef char P_parameter_Offset[FIELD_OFFSET(P,parameter)==372?1:-1];
typedef char P_phase_Offset[FIELD_OFFSET(P,phase)==376?1:-1];
typedef char P_animation_Offset[FIELD_OFFSET(P,animation)==452?1:-1];
typedef char P_speed_Offset[FIELD_OFFSET(P,speed)==464?1:-1];
typedef char P_oldMode_Offset[FIELD_OFFSET(P,oldMode)==468?1:-1];
typedef char P_heading_Offset[FIELD_OFFSET(P,heading)==472?1:-1];
typedef char P_basis_Offset[FIELD_OFFSET(P,basis)==480?1:-1];
typedef char P_spin_Offset[FIELD_OFFSET(P,spin)==528?1:-1];
typedef char P_ratio_Offset[FIELD_OFFSET(P,ratio)==540?1:-1];
typedef char P_state_Offset[FIELD_OFFSET(P,state)==544?1:-1];
typedef char P_changed_Offset[FIELD_OFFSET(P,changed)==548?1:-1];
typedef char P_randomDeadline_Offset[FIELD_OFFSET(P,randomDeadline)==552?1:-1];
typedef char P_deadline_Offset[FIELD_OFFSET(P,deadline)==556?1:-1];
typedef char P_amount_Offset[FIELD_OFFSET(P,amount)==560?1:-1];
typedef char P_damageOffset_Offset[FIELD_OFFSET(P,damageOffset)==576?1:-1];
typedef char VE_delta_Offset[FIELD_OFFSET(VE,delta)==0?1:-1];
typedef char VE_fn_Offset[FIELD_OFFSET(VE,fn)==4?1:-1];
typedef char WORK_first_Offset[FIELD_OFFSET(WORK,first)==0?1:-1];
typedef char WORK_second_Offset[FIELD_OFFSET(WORK,second)==16?1:-1];
typedef char WORK_direction_Offset[FIELD_OFFSET(WORK,direction)==32?1:-1];
typedef char WORK_velocity_Offset[FIELD_OFFSET(WORK,velocity)==48?1:-1];
typedef char WORK_scalar_Offset[FIELD_OFFSET(WORK,scalar)==64?1:-1];
typedef char WORK_angle_Offset[FIELD_OFFSET(WORK,angle)==80?1:-1];
typedef char WORK_parameter_Offset[FIELD_OFFSET(WORK,parameter)==84?1:-1];
typedef char CLOCK_t_Offset[FIELD_OFFSET(CLOCK,t)==0?1:-1];
typedef char CLOCK_dt_Offset[FIELD_OFFSET(CLOCK,dt)==4?1:-1];
extern "C" void func_001B1328(P*p,int next){
 int old=p->state;if(old==next)return;WORK w;
 switch(old){case -1:case 0:case 2:case 3:func_002303A0(p,p->group,p->oldMode);func_0022C840(p,p->group);break;}
 switch(next){
 case 0:
  SetVelocity(p,D_002A2DD0.q);func_0022C818(p,p->group);{float now=D_002DDED0.t;p->randomDeadline=now+func_0011D448(p->low0,p->high0);}break;
 case 1:
  SetMode(p);{float now=D_002DDED0.t;p->randomDeadline=now+func_0011D448(p->low1,p->high1);}break;
 case 2:{
  p->phase=-p->phase;register float negative __asm__("$f20")=MinusOne();M4*m=GetMatrix(p);qword k=Scalar(negative);w.first.q=k;
  func_0011EFB0(Scale(m->row[0].q,k),&w.angle,0,0);func_001B1818(p,w.angle);SetVelocity(p,D_002A2DD0.q);goto group;
 }
 case 3:
  SetVelocity(p,D_002A2DD0.q);func_001B17B8(p,p->ratio+p->ratio);
 group:func_002303A0(p,p->group,1);func_0022C840(p,p->group);break;
 case 4:{
  w.first.q=func_001A62E8(p);
  if(p->path){
   func_001E6F60(p->path,w.first.q,0,&w.second,0,&p->parameter,&w.parameter);
   float phase=func_001E77E8(p->path);
   float travel=Distance(&w.first,&w.second)/p->speed.value;
   p->phase=phase;
   float end=func_001E6648(p->path);
   p->deadline=D_002DDED0.t+travel+(end-w.parameter)/p->speed.value-p->lead;
  }else{
   P*near=func_001C4AF8(D_003DD490,w.first.q);w.second=w.first;w.first.q=func_001A62E8(near);p->deadline=D_002DDED0.t+2.0f;
  }
  w.direction.q=Difference(&w.second,&w.first);w.direction.i[2]=0;
  qword direction=Normal(&w.direction,D_002A2DA0.q);qword k=ScalarBits(p->speed.bits);qword velocity=Scale(direction,k);
  w.scalar.q=k;w.velocity.q=velocity;SetVelocity(p,velocity);SetMode(p);break;
 }
 case 5:{
  EFFECT*e=func_001FBB90(0x14);func_001FB2F8(e,0);func_001FB3F0(e,func_001A62E8(p));
  func_00154E10(D_002DE578,func_001A6F00(p,0,p->damageOffset.q),p->amount,-100,p);Call(p,9);break;
 }
 }
 p->state=next;p->changed=D_002DDED0.t;
 if(next!=2){char*entry=(char*)p+next*12;ASEG*clip=*(ASEG**)(entry+0x180);int flags=*(int*)(entry+0x184);func_001305B8(clip,p,0.0f,1.0f,flags|1,&p->animation);}
}
