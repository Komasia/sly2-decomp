// 104/155 instructions differ.
typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];} U;
struct LO{char pad[0x30];qword pos;char pad40[0x60];void*parent;char padA4[0xC];qword velocity;};
struct ACC{char pad[0x80];qword v;};
struct O{char pad[0x58];struct LO*lo;char pad5C[0x8C];struct ACC*acc;};
struct X{char pad[0x180];struct O*object;};
struct ANIM{char pad[0x40];float rate;};
struct P{char pad[0x1030];struct ANIM*anim;char pad1034[0x3BC];struct X*x;char pad13F4[0x58];int state;};
extern qword D_002A2DC0;
extern float D_002C09C8;
qword func_0022FCC8(void*,void*,qword);
int func_0011D508(float,float,float,float*);
void func_00130D30(struct ANIM*,int,float,float);
static inline float Clamp(float value,float lower,const float*upper){float r;if(value<lower)r=lower;else{r=value;if(*upper<value)r=*upper;}return r;}
static inline float Z(qword q){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(q));return f;}
static inline qword Scale(qword v,float f,U*u){qword s,r;__asm__("qmtc2.ni %1,%0":"=j"(s):"r"(f));__asm__("vmulx.xyzw %0,%1,%2x":"=&j"(r):"j"(v),"j"(s));u->q=s;return r;}
static inline qword AddScaled(qword a,qword b,float f,U*u){qword s,r;__asm__("qmtc2.ni %1,%0":"=j"(s):"r"(f));u->q=s;__asm__("vadda.xyzw ACC,$vf0,%1\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(s));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Div(qword v,float f,U*u){qword s,r;__asm__("qmtc2.ni %1,%0":"=j"(s):"r"(f));u->q=s;__asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(r):"j"(s),"j"(v));return r;}
static inline void Store(qword*p,qword q){__asm__("sqc2 %1,%0":"=m"(*p):"j"(q));}
void func_001B7700(struct P*p,qword goal,float*animation,float*duration,qword*outStart,qword*outEnd){
 U roots;U u;U start;
 qword end;
 switch(p->state){
 case 0:{
  void*parent=p->x->object->lo->parent;
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
  int count;
  v.q=lo->velocity;
  acceleration=func_0022FCC8(0,lo->parent,object->acc->v);
  count=func_0011D508(Z(acceleration)*0.5f,Z(v.q),Z(pos)-Z(goal),roots.f);
  if(!count)t=D_002C09C8;
  else t=Clamp(roots.f[count-1],D_002C09C8,duration);
  func_00130D30(p->anim,0,*animation-t*p->anim->rate,p->anim->rate);
  end=AddScaled(v.q,acceleration,t,&u);
  {qword predicted=AddScaled(pos,Add(v.q,end),t*0.5f,&u);
   qword correction=Div(Sub(goal,predicted),t,&u);
   *duration=t;
   start.q=Add(v.q,correction);
   end=Add(end,correction);
  }
  break;
 }
 default:return;
 }
 *outStart=start.q;
 Store(outEnd,end);
}
