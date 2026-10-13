typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M3 {qword r[3];};
struct M4 {qword r[4];};
struct LO;
struct VE {short delta,pad;M4*(*matrix)(void*);};
struct LO {char padC[0xC];VE*vt;char pad10[0x90];LO*parent;};
struct ANIM {void*player;};
struct MOTION {char pad74[0x74];float duration;};
struct P {LO*owner;ANIM*animation;float weight;char padC[8];void*pathA,*pathC;float fraction;char pad20[8];void*pathB,*pathD;MOTION*motion;char pad34[4];LO*space;char pad3C[4];M4 matrix;void*job,*path;float time;LO*follow;int mode;char pad94[0x10];int active;};
struct CTX {P*p;qword position;};
extern "C" {
qword func_001A62E8(LO*);
void func_001E7380(void*,qword,void*,qword*,qword*,float*,float*,float);
M4 func_0011C318(M4*);
M4 *func_0011C168(M4*,const M4*,const M4*);
qword func_001A6F00(LO*,LO*,qword);
void Minimize(float(*)(void*,float),void*,float,float,float,float,float*,float*) __asm__("MinimizeRange__FPFPvf_fPvffffPfT6");
float func_001CC2B8(void*,float);
float func_001CC288(void*,float);
void func_001CC1F8(P*,qword,float*,float*,float);
void func_001CC168(P*,qword,float*,float*,float);
M3 *func_0022FD38(M3*,LO*,LO*,const M3*);
qword func_0011BFF0(const M3*);
void func_0012D108(void*,qword);
void func_00130D30(void*,int,float,float);
void func_001384C0(MOTION*);
void func_002046B0(LO*,qword);
void func_00204CA8(LO*);
void func_001CC2E8(P*);
}
static inline M3 ParentBasis(LO*a,LO*b,const M3&m) return r {func_0022FD38(&r,a,b,&m);}
static inline qword LengthXY(qword v){qword d,f;__asm__("vmul.xy %0,%1,%1":"=j"(d):"j"(v));__asm__("vaddy.x %0,%0,%0y":"+j"(d));__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(d));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(d));return f;}
static inline void StoreX(float*p,qword q){__asm__("sw %1,%0":"=m"(*p):"r"(q));}
static inline qword ToVF(qword a){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(a));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
void func_001CC2E8(P*p){
 U position;
 M3 basis;
 if(p->active==-1)return;
 switch(p->mode){
 case 0:{void*path=p->path;func_001E7380(path,func_001A62E8(p->owner),0,&position.q,0,0,&p->time,p->time);break;}
 case 1:position.q=func_001A62E8(p->follow);break;
 case 2:{
  M4 product,temporary;
  register M4*output __asm__("$18")=&temporary;
  M4*world=p->follow->vt[31].matrix((char*)p->follow+p->follow->vt[31].delta);
  M4 inverse=func_0011C318(&p->matrix);
  func_0011C168(output,world,&inverse);
  product=temporary;
  position.q=product.r[3];
  basis=*(M3*)&product;
  break;
 }
 }
 CTX context;context.p=p;
 U local;local.q=ToVF(func_001A6F00(0,p->owner,position.q));
 qword length=LengthXY(local.q);
 local.f[1]=0.0f;StoreX(&local.f[0],length);
 context.position=func_001A6F00(p->owner,0,local.q);
 float t,result,projection;
 if(p->mode==2){
  Minimize(func_001CC2B8,&context,0.5f,0.1f,0.0f,1.0f,&t,&result);
  func_001CC1F8(p,context.position,&projection,0,t);
  M3 transformed;transformed=ParentBasis(0,p->space->parent,basis);
  func_0012D108(p->job,func_0011BFF0(&transformed));
 }else{
  Minimize(func_001CC288,&context,0.5f,0.1f,0.0f,1.0f,&t,&result);
  func_001CC168(p,context.position,&projection,0,t);
 }
 func_00130D30(p->animation->player,0,t*p->motion->duration,0.0f);
 p->fraction=projection;p->weight=1.0f-projection;
 func_001384C0(p->motion);
 U saved;saved.q=position.q;
 qword delta=Sub(saved.q,ToVF(func_001A62E8(p->owner)));
 func_002046B0(p->owner,delta);
 func_00204CA8(p->owner);
}
