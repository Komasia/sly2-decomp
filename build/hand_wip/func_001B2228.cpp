typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4];
 inline void SetQ(qword value) {__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(value));}
};
struct V { float x,y,z,w; } __attribute__((aligned(16)));
struct VT { short d,pad;void *fn; };
struct LO;struct CONTROLLER;struct ASEG;struct ASEGA;struct ACTION;
struct P {char pad0[0xC];VT *vt;char pad1[0x5C-0x10];CONTROLLER *controller;
 char pad2[0x210-0x60];LO *source;int pad3[3];V position;
 ASEG *aseg;ASEGA *asega[12];int enabled;ACTION *action;float parameter;
 float g270,g274,g278;};
struct HIT { qword q[4];float t0,t1;int count;void *owner0,*owner1;char opaque54[12];};
struct CLOCK {float t,dt;};
extern "C" CLOCK D_002DDED0;
extern "C" qword D_002A2DD0;
struct LO;
extern "C" void func_001B1E88(P*,LO*,V*);
extern "C" V func_001B2398(P*,float);
extern "C" qword func_0011E9F8(qword,float);
extern "C" qword func_001A62E8(P*);
extern "C" int func_0014C748(qword,qword,qword,int,HIT*,float);
inline qword Bc(float g,U &u){qword k;__asm__("qmtc2.ni %1,%0":"=j"(k):"r"(g));u.q=k;return u.q;}
inline qword Scale(qword a,qword k){__asm__("vmulx.xyzw %0,%1,%2x":"=j"(k):"j"(a),"0"(k));return k;}
inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
inline qword MAdd(qword a,qword b,qword k,U &u){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(k));u.q=r;return u.q;}
inline V Scalar(float g){V r;qword q;__asm__("mfc1 %0,%1":"=r"(q):"f"(g));*(qword*)&r=q;return r;}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
typedef char VT_d_Offset[FIELD_OFFSET(VT,d)==0?1:-1];
typedef char VT_fn_Offset[FIELD_OFFSET(VT,fn)==4?1:-1];
typedef char P_vt_Offset[FIELD_OFFSET(P,vt)==12?1:-1];
typedef char P_controller_Offset[FIELD_OFFSET(P,controller)==92?1:-1];
typedef char P_source_Offset[FIELD_OFFSET(P,source)==528?1:-1];
typedef char P_position_Offset[FIELD_OFFSET(P,position)==544?1:-1];
typedef char P_aseg_Offset[FIELD_OFFSET(P,aseg)==560?1:-1];
typedef char P_asega_Offset[FIELD_OFFSET(P,asega)==564?1:-1];
typedef char P_enabled_Offset[FIELD_OFFSET(P,enabled)==612?1:-1];
typedef char P_action_Offset[FIELD_OFFSET(P,action)==616?1:-1];
typedef char P_parameter_Offset[FIELD_OFFSET(P,parameter)==620?1:-1];
typedef char P_g270_Offset[FIELD_OFFSET(P,g270)==624?1:-1];
typedef char P_g274_Offset[FIELD_OFFSET(P,g274)==628?1:-1];
typedef char P_g278_Offset[FIELD_OFFSET(P,g278)==632?1:-1];
typedef char HIT_t0_Offset[FIELD_OFFSET(HIT,t0)==64?1:-1];
typedef char HIT_t1_Offset[FIELD_OFFSET(HIT,t1)==68?1:-1];
typedef char HIT_count_Offset[FIELD_OFFSET(HIT,count)==72?1:-1];
typedef char HIT_owner0_Offset[FIELD_OFFSET(HIT,owner0)==76?1:-1];
typedef char HIT_owner1_Offset[FIELD_OFFSET(HIT,owner1)==80?1:-1];
typedef char CLOCK_t_Offset[FIELD_OFFSET(CLOCK,t)==0?1:-1];
typedef char CLOCK_dt_Offset[FIELD_OFFSET(CLOCK,dt)==4?1:-1];
typedef char qword_PrefixSize[sizeof(qword)==16?1:-1];
typedef char U_PrefixSize[sizeof(U)==16?1:-1];
typedef char V_PrefixSize[sizeof(V)==16?1:-1];
typedef char VT_PrefixSize[sizeof(VT)==8?1:-1];
typedef char P_PrefixSize[sizeof(P)==640?1:-1];
typedef char HIT_PrefixSize[sizeof(HIT)==96?1:-1];
typedef char CLOCK_PrefixSize[sizeof(CLOCK)==8?1:-1];
extern "C" void func_001B2228(P*p,LO*source,V*point){
 U pos;V dir;
 pos.q=*(qword*)point;
 func_001B1E88(p,source,(V*)&pos);
 if(p->g270>0.0f) p->g278=D_002DDED0.t+p->g270;
 else {
  dir=func_001B2398(p,0.5f);
  {U vel,tmp;V factor;HIT hit;
  qword k=Bc(-0.5f,tmp);
  vel.q=Scale(((qword(*)(void*))p->vt[33].fn)((char*)p+p->vt[33].d),k);
  vel.SetQ(func_0011E9F8(vel.q,0.75f*p->g274));
  factor=Scalar(1.5f);
  qword d=Sub(*(qword*)&dir,func_001A62E8(p));
  qword acc=MAdd(vel.q,d,*(qword*)&factor,tmp);
  func_0014C748(D_002A2DD0,vel.q,acc,1,&hit,p->g274);
  register float max __asm__("$f1");
  register float lo __asm__("$f1")=0.25f;
  register float hi __asm__("$f3")=hit.t1;
  __asm__("max.s %0,%1,%2":"=f"(max):"f"(lo),"f"(hi));
  register float duration __asm__("$f2")=1.0f/max;
  p->g278=D_002DDED0.t+duration;
  }
 }
}
