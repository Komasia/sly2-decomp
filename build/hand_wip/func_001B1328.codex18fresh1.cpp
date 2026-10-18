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
static inline void SetZeroVelocity(P*p){
 register VE*table __asm__("$6");register unsigned address __asm__("$2");
 __asm__("lw %0,%2\n\tlui %1,%%hi(%3)\n\taddiu %1,%1,%%lo(%3)":"=r"(table),"=r"(address):"m"(p->vt),"i"(&D_002A2DD0));
 register int delta __asm__("$4");register qword zero __asm__("$5");register void(*method)(void*,qword) __asm__("$3");
 __asm__("lh %0,%3\n\tlq %1,%4\n\tlw %2,%5":"=&r"(delta),"=&r"(zero),"=r"(method):"m"(table[35].delta),"m"(*(U*)address),"m"(table[35].fn));
 method((char*)p+delta,zero);
}
static inline void Call(P*p,int index){VE&v=p->vt[index];((void(*)(void*))v.fn)((char*)p+v.delta);}
static inline void SetMode(P*p){VE&v=p->vt[47];((void(*)(void*,int))v.fn)((char*)p+v.delta,4);}
static inline M4*GetMatrix(P*p){VE&v=p->vt[31];return ((M4*(*)(void*))v.fn)((char*)p+v.delta);}


#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef char int_Size[sizeof(int)==4?1:-1];
typedef char unsigned_Size[sizeof(unsigned)==4?1:-1];
typedef char float_Size[sizeof(float)==4?1:-1];
typedef char pointer_Size[sizeof(void*)==4?1:-1];
typedef char qword_Size[sizeof(qword)==16?1:-1];
typedef char U_Alignment[__alignof__(U)==16?1:-1];
typedef char P_Prefix_Size[sizeof(P)==0x250?1:-1];
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
  p->phase=-p->phase;register float negative __asm__("$f20")=-1.0f;M4*m=GetMatrix(p);
  register qword row __asm__("vf1"),factor __asm__("vf2"),scaled __asm__("vf3");register int bits __asm__("$2");
  __asm__("lqc2 %0,%1":"=j"(row):"m"(m->row[0].q));__asm__("mfc1 %0,%1":"=r"(bits):"f"(negative));__asm__("qmtc2.ni %1,%0":"=j"(factor):"r"(bits));
  __asm__("vmulx.xyzw %0,%2,%3x\n\tsqc2 %3,%1":"=&j"(scaled),"=m"(w.first.q):"j"(row),"j"(factor));
  func_0011EFB0(scaled,&w.angle,0,0);func_001B1818(p,w.angle);SetZeroVelocity(p);goto group;
 }
 case 3:
  SetZeroVelocity(p);func_001B17B8(p,p->ratio+p->ratio);
 group:func_002303A0(p,p->group,1);func_0022C840(p,p->group);break;
 case 4:{
  w.first.q=func_001A62E8(p);
  if(p->path){
   func_001E6F60(p->path,w.first.q,0,&w.second,0,&p->parameter,&w.parameter);
   register float phase __asm__("$f0")=func_001E77E8(p->path);
   register qword other __asm__("vf2"),delta __asm__("vf1"),one __asm__("vf2");register float speed __asm__("$f1"),travel __asm__("$f20");
   __asm__("lqc2 %0,%3\n\tlqc2 %1,%4\n\tvsub.xyzw %1,%1,%0\n\tlwc1 %2,%5":"=j"(other),"=j"(delta),"=f"(speed):"m"(w.second.q),"m"(w.first.q),"m"(p->speed.value));
   __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(delta),"=j"(one));
   register PATH*endPath __asm__("$4");
   __asm__("lw %0,%3\n\tvsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %1,$vf0,$Q\n\tswc1 %4,%2":"=&r"(endPath),"+j"(delta),"=m"(p->phase):"m"(p->path),"f"(phase));
   register int bits __asm__("$2");__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(delta));__asm__("mtc1 %1,%0":"=f"(travel):"r"(bits));travel/=speed;
   float end=func_001E6648(endPath);
   p->deadline=D_002DDED0.t+travel+(end-w.parameter)/p->speed.value-p->lead;
  }else{
   P*near=func_001C4AF8(D_003DD490,w.first.q);w.second=w.first;w.first.q=func_001A62E8(near);p->deadline=D_002DDED0.t+2.0f;
  }
  register qword first __asm__("vf2"),second __asm__("vf1");register unsigned fallbackAddress __asm__("$2");
  __asm__("lqc2 %0,%3\n\tlui %2,%%hi(%5)\n\tlqc2 %1,%4\n\taddiu %2,%2,%%lo(%5)":"=j"(first),"=j"(second),"=&r"(fallbackAddress):"m"(w.first.q),"m"(w.second.q),"i"(&D_002A2DA0));
  register float threshold __asm__("$f1");
  __asm__("vsub.xyzw %0,%0,%2\n\tli.s %1,%F3":"+j"(second),"=f"(threshold):"j"(first),"F"(0.0001f));w.direction.q=second;w.direction.i[2]=0;
  register qword point __asm__("vf3"),norm __asm__("vf1"),one __asm__("vf2");register qword fallback __asm__("$2");
  __asm__("lqc2 %0,%1":"=j"(point):"m"(w.direction.q));
  register int bits __asm__("$3");register float length __asm__("$f0");
  __asm__("vmul.xyz %0,%5,%5\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z\n\tlq %2,%6\n\tvsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q\n\tqmfc2.ni %3,%0\n\tmtc1 %3,%4":"=&j"(norm),"=j"(one),"=r"(fallback),"=&r"(bits),"=f"(length):"j"(point),"m"(*(U*)fallbackAddress));
  qword direction=fallback;
  if(length<threshold)goto planar_direction_ready;
  __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(direction):"j"(norm),"j"(point));
 planar_direction_ready:;
  register int speed __asm__("$2");register qword factor __asm__("vf1"),velocity __asm__("vf2");__asm__("lw %0,%2\n\tqmtc2.ni %0,%1":"=r"(speed),"=j"(factor):"m"(p->speed.bits));
  __asm__("vmulx.xyzw %0,%1,%2x":"=j"(velocity):"j"(direction),"j"(factor));
  w.scalar.q=factor;w.velocity.q=velocity;SetVelocity(p,velocity);SetMode(p);break;
 }
 case 5:{
  EFFECT*e=func_001FBB90(0x14);func_001FB2F8(e,0);func_001FB3F0(e,func_001A62E8(p));
  func_00154E10(D_002DE578,func_001A6F00(p,0,p->damageOffset.q),p->amount,-100,p);Call(p,9);break;
 }
 }
 p->state=next;p->changed=D_002DDED0.t;
 if(next!=2){
  int offset=next*12;char*entry=(char*)p+offset;register char*clipEntry __asm__("$2");
  __asm__("daddu %0,%1,$zero":"=r"(clipEntry):"r"(entry));
  ASEG*clip=*(ASEG**)(clipEntry+0x180);int flags=*(int*)(entry+0x184);func_001305B8(clip,p,0.0f,1.0f,flags|1,&p->animation);
 }
}
