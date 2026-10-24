// func_0018F2B0 laneG10v1 (Claude agent, 2026-10-24): laneG3v1 + scalar as a VU_FLOAT from Lilly-style VuFloatBits (mfc1 into v.qw), declared AFTER the position call, AddScaled takes VU_FLOAT by value, scratch block-scoped. aligned 4 (G3v1 8), still ONE pin (heading f21). The inline v lands in 0xD0 after the M3 return temp is freed, so the lq 0x170/sq 0xD0 copy and vt load order now match. Left: mfc1 must cross the 11B500 call (ours stops after it), s4/s5 hi swap for D_003DD490/D_002BF4B8.
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];int bits[4];};
struct M3{U r[3];M3(){}M3(const M3&m){r[0]=m.r[0];r[2]=m.r[2];r[1]=m.r[1];}M3&operator=(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return *this;}};
struct M4{U r[4];};
struct VTE{short delta,pad;void*fn;};
struct P{char pad[0xC];VTE*vt;char pad10[0xD0];P*next;int padE4;int flags;};
struct G;
extern "C" qword D_002A2DC0;
extern "C" P*D_003E13B4;
extern "C" G D_003DD490;
extern "C" float D_002BF4B8;
extern "C" M3 func_0011B500(qword,float);
extern "C" qword func_001A62E8(P*);
extern "C" qword func_001A6F00(P*,void*,qword);
extern "C" void func_002309E8(void*,void*,M4*,float,M4*);
extern "C" void func_0011EE08(qword,qword,qword,qword*,float*,float*);
extern "C" int func_0015ED78(G*,int,int,P*);
extern "C" float func_002458F0(float,float);
extern "C" float func_0011CF60(float);
struct VU_FLOAT{qword qw;};
static inline VU_FLOAT VuFloatBits(float g){VU_FLOAT v;__asm__("mfc1 %0,%1":"=r"(v.qw):"f"(g));return v;}
static inline float AngleOf(U v){return func_002458F0(v.f[1],v.f[0]);}
static inline qword AddScaled(qword p,qword v,VU_FLOAT k){qword q;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%3,%2x":"=j"(q):"j"(p),"j"(k.qw),"j"(v),"j"(k.qw)/*allocation-only: VU preference spills k like the target*/);return q;}
static inline qword Rotate(const M3&m,qword v){qword q;__asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(q):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"0"(v));return q;}
static inline qword Transform(const M4&m,qword v){qword q;__asm__("vmulax.xyz ACC,%1,%5x\n\tvmadday.xyz ACC,%2,%5y\n\tvmaddaz.xyz ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(q):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(m.r[3].q),"j"(v));return q;}
static inline qword Add(qword a,qword b){qword q;__asm__("vadd.xyzw %0,%1,%2":"=j"(q):"j"(a),"j"(b));return q;}
static inline qword Sub(qword a,qword b){qword q;__asm__("vsub.xyzw %0,%1,%2":"=j"(q):"j"(a),"j"(b));return q;}
static inline float Abs(float f){float q;__asm__("abs.s %0,%1":"=f"(q):"f"(f));return q;}
static inline qword GetVelocity(P*p){VTE*e=&p->vt[33];qword(*f)(void*)=(qword(*)(void*))e->fn;return f((char*)p+e->delta);}
static inline void*GetFrame(P*p,M4*out){return ((void*(*)(void*,M4*))p->vt[32].fn)((char*)p+p->vt[32].delta,out);}
extern "C" void func_0018F2B0(P*p,float headingInput,int mask,float dtInput,U*offset,P**out,qword*outvector,float cone){
 register float heading __asm__("$f21")=headingInput; float dt=dtInput; // the one pin: heading in f21 (else f20/f21 swap)
 M3 rotation;
 U origin,reference,target,delta,candidate;
 M4 prediction;
 U answer;
 P*best=0;
 float nearest=300.0f;
 qword position;
 rotation=func_0011B500(D_002A2DC0,headingInput);
 position=func_001A62E8(p);
 VU_FLOAT scalar=VuFloatBits(dt);
 origin.q=AddScaled(position,GetVelocity(p),scalar);
 reference.q=func_001A6F00(p,0,offset->q);
 target.q=Add(Rotate(rotation,offset->q),origin.q);
 delta.q=Sub(target.q,reference.q);
 for(P*node=D_003E13B4;node;node=node->next){
  struct{U hdr;M4 m;}fx;
  float t,distance;
  if(!(node->flags&mask))continue;
  candidate.q=func_001A62E8(node);
  void*owner=GetFrame(node,&fx.m);
  func_002309E8(owner,0,&prediction,dt,0);
  func_0011EE08(target.q,candidate.q,Transform(prediction,fx.m.r[3].q),0,&t,&distance);
  if(func_0015ED78(&D_003DD490,3,0x33,node))distance+=D_002BF4B8;
  if(distance<nearest){
   qword other=candidate.q;
   U scratch;scratch.q=Sub(other,func_001A62E8(p));
   float angle=Abs(func_0011CF60(func_002458F0(scratch.f[1],scratch.f[0])-heading));
   if(cone<angle)continue;
   best=node;nearest=distance;
   answer.q=Sub(prediction.r[3].q,origin.q);
  }
 }
 *out=best;
 *outvector=answer.q;
}
