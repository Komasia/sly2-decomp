// laneG3v1 (Claude agent, aligned 23, policy-clean: one pin vf1, no lw/lqc2/mfc1 instruction asms): from 188960.cpp (8, but 9 pins + lw/lqc2 asms). Negative path as plain C (resp load, Broadcast(-1), Scale, then store w.scalar) matches. Left: target loads the dt word into the dead clock pointer reg (lw s0,4(s0)) and keeps the Broadcast in vf7; ours v0, which shifts VF numbering; case-14 hi(D_002DDED0) in v0 vs v1.

typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];};
struct M3{U r[3];M3(){}M3(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];}M3&operator=(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return*this;}};
struct M4{U r[4];};struct VTE{short delta,pad;void*fn;};
struct MODEL{char pad[0x1C];float base;};
struct ACTOR{char pad[0x80];qword response;};
struct P{char pad0[0xC];VTE*vt;char pad10[0xD8];ACTOR*actor;char padEC[0xF44];MODEL*model;char pad1034[0x894];int mode,unusedCC,submode;char pad18D4[0x1B0];void*lookup;};
struct CLOCK{float time,dt;};struct WORK{U along,perp,scalar;M3 basis,rotation;};
extern "C"{
extern CLOCK D_002DDED0;extern qword D_002A2DC0;
extern float D_002BF288,D_002BF28C,D_002BF290,D_002BF294;
void func_001F9B20(P*);void func_00204108(P*);
void func_001903B8(P*);void func_0019DF70(void*);void func_00196DF8(void*);
void func_001A1148(void*);void func_00194170(void*);void func_00137248(void*);
qword func_00204E38(P*,MODEL*,float);float func_0012F990(void*,int);
void func_001FAC30(P*,qword);qword func_0011E9F8(qword,float);
M4*func_001A6318(P*);float func_0011E290(qword,qword,qword*,qword*);
M3 func_0011B500(qword,float);
}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Broadcast(float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline qword ScalarWord(const float*p){int bits=*(const int*)p;__asm__("":"+r"(bits)); /* empty asm, allocation-only: fixes the s0/s1 swap in case 24 */qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(bits));return r;}
static inline qword Scale(qword a,qword s){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(s));return r;}
static inline qword Divide(qword a,qword s){qword r;__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(a),"j"(s));return r;}
static inline float Z(qword a){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(a));return f;}
static inline qword Transform(const M3&m,qword p){__asm__("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(p):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q));return p;}
static inline qword Reject(qword a,qword axis){
 register qword v __asm__("vf1")=a; /* the one pin: velocity in vf1 fixes the VF numbering of case 24 */ qword dot;
 __asm__("vmul.xyz %0,%1,%2\n\tvaddw.x $vf8,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,$vf8,%0z":"=j"(dot):"j"(v),"j"(axis):"vf8"); /* vf8 scratch written in the asm string, clobbered */
 __asm__("vmulx.xyzw %0,%1,%0x":"+j"(dot):"j"(axis));
 return Sub(v,dot);
}
extern "C" void func_00188960(P*p){
 WORK w;
 switch(p->mode){case 3:case 8:func_001F9B20(p);break;case 21:case 22:break;default:func_00204108(p);break;}
 switch(p->mode){
 case 3:func_001903B8(p);break;
 case 8:func_0019DF70((char*)p+0xF50);break;
 case 2:func_00196DF8((char*)p+0x2C0);break;
 case 4:func_001A1148((char*)p+0xDF0);break;
 case 7:func_00194170((char*)p+0x4C0);break;
 case 6:func_00137248((char*)p+0x1FF0);break;
 case 14:{
  VTE*e=&p->vt[33];
  w.along.q=((qword(*)(void*))e->fn)((char*)p+e->delta);
  w.perp.q=func_00204E38(p,p->model,p->model->base);
  float cap=func_0012F990(p->lookup,0x16D);
  if(p->model->base<cap){
   qword resp=p->actor->response;qword s=Broadcast(-1.0f);qword r=Scale(resp,s);w.scalar.q=s;func_001FAC30(p,r);
  }else w.perp.f[2]=w.along.f[2];
  w.scalar.q=ScalarWord(&D_002DDED0.dt);
  func_001FAC30(p,func_0011E9F8(Divide(Sub(w.perp.q,w.along.q),w.scalar.q),D_002BF288));
  break;
 }
 case 24:
  if(p->submode==13){
   VTE*e=&p->vt[33];qword position=((qword(*)(void*))e->fn)((char*)p+e->delta);
   e=&p->vt[34];qword direction=((qword(*)(void*))e->fn)((char*)p+e->delta);
   M4*m=func_001A6318(p);w.basis.r[0]=m->r[0];w.basis.r[1]=m->r[1];w.basis.r[2]=m->r[2];
   float projection=func_0011E290(position,w.basis.r[0].q,&w.along.q,&w.perp.q);
   float dt=D_002DDED0.dt;
   float along=projection-D_002BF290*dt;
   float perpendicular=1.0f-D_002BF294*dt;
   float angle=Z(direction)*dt;
   w.scalar.q=Broadcast(along);w.along.q=Scale(w.basis.r[0].q,w.scalar.q);
   w.scalar.q=Broadcast(perpendicular);w.perp.q=Scale(w.perp.q,w.scalar.q);
   w.rotation=func_0011B500(D_002A2DC0,angle);
   qword moved=Sub(Transform(w.rotation,Add(w.along.q,w.perp.q)),position);
   w.scalar.q=ScalarWord(&D_002DDED0.dt);
   qword velocity=Divide(moved,w.scalar.q);
   func_001FAC30(p,func_0011E9F8(Reject(velocity,D_002A2DC0),D_002BF28C));
  }
  break;
 }
}

typedef char qword_Size[(sizeof(qword)==16)?1:-1];
typedef char Pointer_Size[(sizeof(void*)==4)?1:-1];
typedef char Unsigned_Size[(sizeof(unsigned)==4)?1:-1];
typedef char U_Size[(sizeof(U)==16)?1:-1];
typedef char M3_Size[(sizeof(M3)==0x30)?1:-1];
typedef char M4_Size[(sizeof(M4)==0x40)?1:-1];
typedef char VTE_Size[(sizeof(VTE)==8)?1:-1];
typedef char WORK_Size[(sizeof(WORK)==0x90)?1:-1];
typedef char VTE_delta_Offset[((unsigned)&((VTE*)0)->delta==0)?1:-1];
typedef char VTE_fn_Offset[((unsigned)&((VTE*)0)->fn==4)?1:-1];
typedef char MODEL_base_Offset[((unsigned)&((MODEL*)0)->base==28)?1:-1];
typedef char ACTOR_response_Offset[((unsigned)&((ACTOR*)0)->response==128)?1:-1];
typedef char P_vt_Offset[((unsigned)&((P*)0)->vt==12)?1:-1];
typedef char P_actor_Offset[((unsigned)&((P*)0)->actor==232)?1:-1];
typedef char P_model_Offset[((unsigned)&((P*)0)->model==4144)?1:-1];
typedef char P_mode_Offset[((unsigned)&((P*)0)->mode==6344)?1:-1];
typedef char P_submode_Offset[((unsigned)&((P*)0)->submode==6352)?1:-1];
typedef char P_lookup_Offset[((unsigned)&((P*)0)->lookup==6788)?1:-1];
typedef char CLOCK_dt_Offset[((unsigned)&((CLOCK*)0)->dt==4)?1:-1];
typedef char WORK_along_Offset[((unsigned)&((WORK*)0)->along==0)?1:-1];
typedef char WORK_perp_Offset[((unsigned)&((WORK*)0)->perp==16)?1:-1];
typedef char WORK_scalar_Offset[((unsigned)&((WORK*)0)->scalar==32)?1:-1];
typedef char WORK_basis_Offset[((unsigned)&((WORK*)0)->basis==48)?1:-1];
typedef char WORK_rotation_Offset[((unsigned)&((WORK*)0)->rotation==96)?1:-1];
