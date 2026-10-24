/* laneH7v5 (Claude agent): fresh Lilly-style rewrite of func_00185E40, no pins, VU helper asms only. */
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];int i[4];};
struct M3{U r[3];M3(){}M3(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];}M3&operator=(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return*this;}};
struct M4{U r[4];};
struct VTE{short delta,pad;void*fn;};
struct PARAMS{float a,b,duration;};
struct CONTROL{char pad0[0x10];float y,z;int pad18;float speed;};
struct REQUEST{char pad0[0x78];float multiplier;};
struct AXIS{float weight;int active;char pad8[8];U direction;};
struct TRIREF{int index;float u,v;};
struct LIST{int count;qword planes[8];};
struct P{char pad0[0xC];VTE*vt;char pad10[0x140];CONTROL*control;char pad154[0x3C];U acceleration;char pad1A0[0x10];M3 basis;char pad1E0[0x1C30];AXIS axes[8];REQUEST*request;int pad1F14;void*mesh;TRIREF triangle;U points[3];};
struct CLOCK{float time,dt;};
struct VU_FLOAT{qword qw;VU_FLOAT(){}VU_FLOAT(float f){__asm__("mfc1 %0,%1":"=r"(qw):"f"(f));}};
extern "C"{
extern U D_002A2DC0;extern M3 D_002DDFA0;extern CLOCK D_002DDED0;extern PARAMS D_002BE920,D_002BE930,D_002BE940;
qword func_001A62E8(P*);M4*func_001A6318(P*);
void func_00185310(void*,qword,TRIREF*,TRIREF*,qword*,qword*);
M3 func_0011B830(qword,qword);M3 func_0011B340(M3*);qword*func_00256D18(qword*,qword);
void func_0011C950(M4*,M3*,PARAMS*,M3*,qword*,float);
void func_0011F088(qword,qword,PARAMS*,qword*,float);
void func_001856B8(void*,LIST*);void func_001856C0(void*,LIST*,int,U*,PARAMS*,float);
qword func_00185A80(void*,LIST*,qword);
void func_0018C250(P*,int,int);void func_001A0450(P*,AXIS*,REQUEST*);
}
static inline VU_FLOAT VuFloat(float g){VU_FLOAT v;__asm__("qmtc2.ni %1,%0":"=j"(v.qw):"r"(g));return v;}
static inline VU_FLOAT VuFloatFromMemWord(int n){VU_FLOAT v;__asm__("qmtc2.ni %1,%0":"=j"(v.qw):"rV"(n));return v;}
static inline qword QwAdd(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword QwSub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword QwScaleX(qword a,VU_FLOAT g){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(g.qw));return r;}
static inline qword QwAddScaled(qword base,qword vec,VU_FLOAT k){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(base),"j"(vec),"j"(k.qw));return r;}
static inline qword QwDot(qword a,qword b){qword r,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=j"(one):"j"(a),"j"(b));return r;}
static inline qword QwSqrt(qword a){qword r;__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(r):"j"(a));return r;}
static inline qword QwDivide(qword a,qword g){qword r;__asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(r):"j"(a),"j"(g));return r;}
static inline float GXOfQw(qword qw){float x;__asm__("mtc1 %1,%0":"=f"(x):"r"(qw));return x;}
static inline qword QwCross(qword a,qword b){qword r;__asm__("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword QwRotateVecAt(const M3*m,const qword*pv){qword r;__asm__("vmulax.xyz $ACC,%2,%1x\n\tvmadday.xyz $ACC,%3,%1y\n\tvmaddz.xyz %0,%4,%1z":"=j"(r):"j"(*pv),"j"(m->r[0].q),"j"(m->r[1].q),"j"(m->r[2].q));return r;}
static inline qword QwRotateVec(const M3*m,qword v){qword r;__asm__("vmulax.xyz $ACC,%2,%1x\n\tvmadday.xyz $ACC,%3,%1y\n\tvmaddz.xyz %0,%4,%1z":"=j"(r):"j"(v),"j"(m->r[0].q),"j"(m->r[1].q),"j"(m->r[2].q));return r;}
static inline qword QwTransformPos(M4*m,qword v){qword r;__asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(r):"j"(m->r[0].q),"j"(m->r[1].q),"j"(m->r[2].q),"j"(m->r[3].q),"j"(v));return r;}
static inline qword QwCombo(qword a,qword b,VU_FLOAT ka,VU_FLOAT kb){qword r;__asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x":"=j"(r):"j"(a),"j"(b),"j"(ka.qw),"j"(kb.qw));return r;}
static inline void BuildM4(M4*d,const M3&m,qword pos){func_00256D18(&d->r[3].q,pos);d->r[0]=m.r[0];d->r[1]=m.r[1];d->r[2]=m.r[2];d->r[0].i[3]=d->r[1].i[3]=d->r[2].i[3]=0;d->r[3].f[3]=1.0f;}
static inline M3 operator*(const M3&a,const M3&b) return r{
 r.r[2].q=QwRotateVec(&a,b.r[2].q);r.r[0].q=QwRotateVec(&a,b.r[0].q);r.r[1].q=QwRotateVec(&a,b.r[1].q);
}
static inline void ClearXyz(U*pv){pv->f[1]=0.0f;pv->f[2]=0.0f;pv->f[0]=0.0f;}
static inline void MulM3(M3*r,const M3*a,const M3*b){qword c2=QwRotateVec(a,b->r[2].q),c0=QwRotateVec(a,b->r[0].q),c1=QwRotateVec(a,b->r[1].q);r->r[0].q=c0;r->r[1].q=c1;r->r[2].q=c2;}
static inline qword QwRotateVecV(qword v,M3 m){return QwRotateVec(&m,v);}
static inline void SetVec(P*p,int slot,qword q){VTE*e=&p->vt[slot];((void(*)(void*,qword))e->fn)((char*)p+e->delta,q);}
extern "C" void func_00185E40(P*p){
 U closest,normal;
 qword position=func_001A62E8(p);
 func_00185310(p->mesh,position,&p->triangle,&p->triangle,&closest.q,&normal.q);
 M4 frame;U contacts[3];
 qword difference=QwSub(closest.q,position);
 qword direction=QwSqrt(QwDot(difference,difference));
 qword fallback=QwScaleX(normal.q,VuFloat(-1.0f));
 if(GXOfQw(direction)<0.0001f)direction=fallback;else direction=QwDivide(difference,direction);
 qword target=QwAddScaled(closest.q,direction,VuFloat(-p->points[0].f[0]));
 BuildM4(&frame,func_0011B830(direction,D_002A2DC0.q),target);
 int i;
 for(i=0;i<3;i++)func_00185310(p->mesh,QwTransformPos(&frame,p->points[i].q),&p->triangle,0,&contacts[i].q,0);
 qword surface=QwCross(QwSub(contacts[2].q,contacts[0].q),QwSub(contacts[1].q,contacts[0].q));
 qword unit=QwDivide(surface,QwSqrt(QwDot(surface,surface)));
 {M3 m=func_0011B830(unit,D_002A2DC0.q);p->basis.r[0]=m.r[0];p->basis.r[1]=m.r[1];p->basis.r[2]=m.r[2];}
 U angular,linear;
 func_0011C950(func_001A6318(p),&p->basis,&D_002BE920,0,&angular.q,D_002DDED0.dt*0.5f);
 SetVec(p,36,angular.q);
 func_0011F088(position,target,&D_002BE930,&linear.q,D_002DDED0.dt*0.5f);
 LIST planes;U samples[3];
 for(i=0;i<3;i++)samples[i].q=QwAdd(target,QwRotateVecAt(&p->basis,&p->points[i].q));
 func_001856B8(p->mesh,&planes);
 func_001856C0(p->mesh,&planes,3,samples,&D_002BE940,10.0f);
 if(0.0f<p->control->speed){
  U movement;
  movement.f[0]=0.0f;movement.f[1]=-p->control->y;movement.f[2]=p->control->z;
  M3 rotation;M3 inverse=func_0011B340(&p->basis);
  MulM3(&rotation,&inverse,&D_002DDFA0);
  movement.q=QwRotateVecV(movement.q,rotation);movement.f[0]=0.0f;
  qword len=QwSqrt(QwDot(movement.q,movement.q));
  VU_FLOAT speed=VuFloatFromMemWord(*(int*)&p->control->speed);
  qword dir;
  if(GXOfQw(len)<0.0001f)dir=D_002A2DC0.q;else dir=QwDivide(movement.q,len);
  movement.q=QwScaleX(dir,speed);
  p->acceleration.q=QwCombo(p->axes[1].direction.q,p->axes[2].direction.q,VuFloatFromMemWord(movement.i[1]),VuFloatFromMemWord(movement.i[2]));
  p->acceleration.q=QwScaleX(p->acceleration.q,VuFloatFromMemWord(*(int*)&p->request->multiplier));
 }else ClearXyz(&p->acceleration);
 if(planes.count>0){
  VU_FLOAT negative(-1.0f);
  qword projected=func_00185A80(p->mesh,&planes,QwRotateVec(&p->basis,QwScaleX(p->acceleration.q,negative)));
  M3 inverse=func_0011B340(&p->basis);
  p->acceleration.q=QwRotateVec(&inverse,QwScaleX(projected,negative));
 }
 int active=0;
 if(GXOfQw(QwDot(p->acceleration.q,p->acceleration.q))>1.0f)active=1;
 else if(p->control->speed!=0.0f)active=1;
 if(active){
  func_0018C250(p,21,11);func_001A0450(p,p->axes,p->request);
  SetVec(p,35,QwAdd(linear.q,QwRotateVec(&p->basis,QwScaleX(p->acceleration.q,VuFloat(-1.0f)))));
 }else{func_0018C250(p,21,10);SetVec(p,35,linear.q);}
}
