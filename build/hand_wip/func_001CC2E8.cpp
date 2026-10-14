typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M3 {qword r[3];};
struct M4 {qword r[4];};
struct LO;
struct VE {short delta,pad;M4*(*matrix)(void*);};
struct LO {char padC[0xC];VE*vt;};
struct FRAME {char pad40[0x40];M3 basis;};
struct SPACE {char padA0[0xA0];FRAME*frame;};
struct ANIM {void*player;};
struct MOTION {char pad74[0x74];float duration;};
struct P {LO*owner;ANIM*animation;float weight;char padC[8];void*pathA,*pathC;float fraction;char pad20[8];void*pathB,*pathD;MOTION*motion;char pad34[4];SPACE*space;char pad3C[4];M4 matrix;void*job,*path;float time;LO*follow;int mode;char pad94[0x10];int active;};
struct CTX {P*p;qword position;};

struct EARLY {M4 product, temporary, inverse;};
struct LATE {CTX context; U local; M3 transformed, temporary;};
union STAGE {EARLY early; LATE late;};
struct WORK {U position; M3 basis; STAGE stage; float t,result,projection; U saved;};

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
M3 *func_0022FD38(M3*,FRAME*,FRAME*,const M3*);
qword func_0011BFF0(const M3*);
void func_0012D108(void*,qword);
void func_00130D30(void*,int,float,float);
void func_001384C0(MOTION*);
void func_002046B0(LO*,qword);
void func_00204CA8(LO*);
void func_001CC2E8(P*);
}
static inline qword LengthXY(qword v){qword d,f;__asm__("vmul.xy %0,%1,%1":"=j"(d):"j"(v));__asm__("vaddy.x %0,%0,%0y":"+j"(d));__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(d));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(d));return f;}
static inline void StoreX(float*p,qword q){__asm__("sw %1,%0":"=m"(*p):"r"(q));}
static inline qword ToVF(qword a){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(a));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
void func_001CC2E8(P*p){
 WORK w;
 if(p->active==-1)return;
 switch(p->mode){
 case 0:{void*path=p->path;func_001E7380(path,func_001A62E8(p->owner),0,&w.position.q,0,0,&p->time,p->time);break;}
 case 1:w.position.q=func_001A62E8(p->follow);break;
 case 2:{
  M4*output=&w.stage.early.temporary;
  M4*world=p->follow->vt[31].matrix((char*)p->follow+p->follow->vt[31].delta);
  w.stage.early.inverse=func_0011C318(&p->matrix);
  func_0011C168(output,world,&w.stage.early.inverse);
  w.stage.early.product=w.stage.early.temporary;
  w.position.q=w.stage.early.product.r[3];
  w.basis=*(M3*)&w.stage.early.product;
  break;
 }
 }
 w.stage.late.context.p=p;
 w.stage.late.local.q=ToVF(func_001A6F00(0,p->owner,w.position.q));
 qword length=LengthXY(w.stage.late.local.q);
 w.stage.late.local.f[1]=0.0f;StoreX(&w.stage.late.local.f[0],length);
 w.stage.late.context.position=func_001A6F00(p->owner,0,w.stage.late.local.q);
 if(p->mode==2){
  Minimize(func_001CC2B8,&w.stage.late.context,0.5f,0.1f,0.0f,1.0f,&w.t,&w.result);
  func_001CC1F8(p,w.stage.late.context.position,&w.projection,0,w.t);
  func_0022FD38(&w.stage.late.temporary,0,p->space->frame,&w.basis);
  w.stage.late.transformed=w.stage.late.temporary;
  func_0012D108(p->job,func_0011BFF0(&w.stage.late.transformed));
 }else{
  Minimize(func_001CC288,&w.stage.late.context,0.5f,0.1f,0.0f,1.0f,&w.t,&w.result);
  func_001CC168(p,w.stage.late.context.position,&w.projection,0,w.t);
 }
 func_00130D30(p->animation->player,0,w.t*p->motion->duration,0.0f);
 p->fraction=w.projection;p->weight=1.0f-w.projection;
 func_001384C0(p->motion);
 w.saved.q=w.position.q;
 qword delta=Sub(w.saved.q,ToVF(func_001A62E8(p->owner)));
 func_002046B0(p->owner,delta);
 func_00204CA8(p->owner);
}

#define OFF(t,m) ((int)&((t*)0)->m)
typedef char path_layout[(sizeof(qword)==0x10 && sizeof(U)==0x10 && sizeof(M3)==0x30 && sizeof(M4)==0x40 && sizeof(CTX)==0x20 && sizeof(EARLY)==0xC0 && sizeof(LATE)==0x90 && sizeof(STAGE)==0xC0 && sizeof(WORK)==0x120 && sizeof(P)==0xB0 && sizeof(VE)==0x8 && sizeof(void*)==0x4 && sizeof(float)==0x4 && OFF(LO,vt)==0xC && OFF(SPACE,frame)==0xA0 && sizeof(SPACE)==0xA4 && OFF(FRAME,basis)==0x40 && sizeof(FRAME)==0x70 && OFF(ANIM,player)==0x0 && OFF(MOTION,duration)==0x74 && OFF(P,owner)==0x0 && OFF(P,animation)==0x4 && OFF(P,weight)==0x8 && OFF(P,pathA)==0x14 && OFF(P,pathC)==0x18 && OFF(P,fraction)==0x1C && OFF(P,pathB)==0x28 && OFF(P,pathD)==0x2C && OFF(P,motion)==0x30 && OFF(P,space)==0x38 && OFF(P,matrix)==0x40 && OFF(P,job)==0x80 && OFF(P,path)==0x84 && OFF(P,time)==0x88 && OFF(P,follow)==0x8C && OFF(P,mode)==0x90 && OFF(P,active)==0xA4 && OFF(CTX,p)==0x0 && OFF(CTX,position)==0x10 && OFF(EARLY,product)==0x0 && OFF(EARLY,temporary)==0x40 && OFF(EARLY,inverse)==0x80 && OFF(LATE,context)==0x0 && OFF(LATE,local)==0x20 && OFF(LATE,transformed)==0x30 && OFF(LATE,temporary)==0x60 && OFF(WORK,position)==0x0 && OFF(WORK,basis)==0x10 && OFF(WORK,stage)==0x40 && OFF(WORK,t)==0x100 && OFF(WORK,result)==0x104 && OFF(WORK,projection)==0x108 && OFF(WORK,saved)==0x110 && OFF(VE,delta)==0x0 && OFF(VE,matrix)==0x4)?1:-1];
