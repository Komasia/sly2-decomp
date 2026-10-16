typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];} U;
struct LO{char pad[0x30];qword pos;char pad40[0x60];struct LO*parent;char padA4[0xC];qword velocity;};
struct ACC{char pad[0x80];qword v;};
struct O{char pad[0x58];struct LO*lo;char pad5C[0x8C];struct ACC*acc;};
struct X{char pad[0x180];struct O*object;};
struct ANIM{char pad[0x40];float rate;};
struct P{char pad[0x1030];struct ANIM*anim;char pad1034[0x3BC];struct X*x;char pad13F4[0x58];int state;};
extern qword D_002A2DC0;
extern float D_002C09C8;
qword func_0022FCC8(struct LO*,struct LO*,qword);
int func_0011D508(float,float,float,float*);
void func_00130D30(struct ANIM*,int,float,float);
static inline float Clamp(float value,float lower,const float*upper){float limit=*upper;if(value<lower)return lower;if(limit<value)return limit;return value;}
static inline float Z(qword q){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(q));return f;}
static inline qword Scale(qword v,float f,U*u){qword s,r;__asm__("qmtc2.ni %1,%0":"=j"(s):"r"(f));u->q=s;__asm__("vmulx.xyzw %0,%1,%2x":"=&j"(r):"j"(v),"j"(u->q));return r;}
static inline qword Bcast(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword AddScaled(qword a,qword b,qword s,U*u){qword r;u->q=s;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(u->q));return r;}
static inline qword AddMemory(const U*p,qword b){qword a,r;__asm__("lqc2 %1,%2\n\tvadd.xyzw %0,%1,%3":"=j"(r),"=&j"(a):"m"(p->q),"j"(b));return r;}
static inline qword AddScaledMemory(const U*p,qword b,qword s,U*u){qword a,r;u->q=s;__asm__("lqc2 %1,%2\n\tvadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%3,%4x":"=j"(r),"=&j"(a):"m"(p->q),"j"(b),"j"(u->q));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Div(qword v,qword s,U*u){qword r;u->q=s;__asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(r):"j"(u->q),"j"(v));return r;}
static inline void Store(qword*p,qword q){__asm__("sqc2 %1,%0":"=m"(*p):"j"(q));}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
typedef char U_q_Offset[FIELD_OFFSET(U,q)==0?1:-1];
typedef char U_f_Offset[FIELD_OFFSET(U,f)==0?1:-1];
typedef char LO_pos_Offset[FIELD_OFFSET(struct LO,pos)==48?1:-1];
typedef char LO_parent_Offset[FIELD_OFFSET(struct LO,parent)==160?1:-1];
typedef char LO_velocity_Offset[FIELD_OFFSET(struct LO,velocity)==176?1:-1];
typedef char ACC_v_Offset[FIELD_OFFSET(struct ACC,v)==128?1:-1];
typedef char O_lo_Offset[FIELD_OFFSET(struct O,lo)==88?1:-1];
typedef char O_acc_Offset[FIELD_OFFSET(struct O,acc)==232?1:-1];
typedef char X_object_Offset[FIELD_OFFSET(struct X,object)==384?1:-1];
typedef char ANIM_rate_Offset[FIELD_OFFSET(struct ANIM,rate)==64?1:-1];
typedef char P_anim_Offset[FIELD_OFFSET(struct P,anim)==4144?1:-1];
typedef char P_x_Offset[FIELD_OFFSET(struct P,x)==5104?1:-1];
typedef char P_state_Offset[FIELD_OFFSET(struct P,state)==5196?1:-1];
typedef char qword_PrefixSize[sizeof(qword)==16?1:-1];
typedef char U_PrefixSize[sizeof(U)==16?1:-1];
typedef char LO_PrefixSize[sizeof(struct LO)==192?1:-1];
typedef char ACC_PrefixSize[sizeof(struct ACC)==144?1:-1];
typedef char O_PrefixSize[sizeof(struct O)==236?1:-1];
typedef char X_PrefixSize[sizeof(struct X)==388?1:-1];
typedef char ANIM_PrefixSize[sizeof(struct ANIM)==68?1:-1];
typedef char P_PrefixSize[sizeof(struct P)==5200?1:-1];
void func_001B7700(struct P*p,qword goal,float*animation,float*duration,qword*outStart,qword*outEnd){
 U roots;U u;U start;
 qword end;
 switch(p->state){
 case 0:{
  struct LO*parent=p->x->object->lo->parent;
  start.q=func_0022FCC8(0,parent,Scale(D_002A2DC0,2500.0f,&roots));
  end=func_0022FCC8(0,parent,Scale(D_002A2DC0,-2000.0f,&roots));
  break;
 }
 case 1:{
  U v;
  struct O*object=p->x->object;
  struct LO*lo=object->lo;
  qword pos=lo->pos;
  qword acceleration;
  float t;
  int count;qword qt;
  v.q=lo->velocity;
  acceleration=func_0022FCC8(0,lo->parent,object->acc->v);
  count=func_0011D508(Z(acceleration)*0.5f,Z(v.q),Z(pos)-Z(goal),roots.f);
  if(!count)t=D_002C09C8;
  else t=Clamp(roots.f[count-1],D_002C09C8,duration);
  func_00130D30(p->anim,0,*animation-t*p->anim->rate,p->anim->rate);
  qt=Bcast(t);end=AddScaledMemory(&v,acceleration,qt,&u);
  *duration=t;
  {qword predicted=AddScaled(pos,AddMemory(&v,end),Bcast(t*0.5f),&u);
   qword correction=Div(Sub(goal,predicted),qt,&u);
   start.q=AddMemory(&v,correction);
   end=Add(end,correction);
  }
  break;
 }
 default:return;
 }
 *outStart=start.q;
 Store(outEnd,end);
}
