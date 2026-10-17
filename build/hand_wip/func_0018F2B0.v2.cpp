// v2 (Claude agent, aligned 6): func_002309E8 prototype (void*,void*,M4*,float,M4*) + AddScaled asm operands (p,k,v). Left: frame 0x10 short (target has a 16-byte hole at 0x100 before frame M4; M3 return temp and scratch share 0xD0), vt lw/lh order, s4/s5 global swap.
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];int bits[4];};
struct M3{U r[3];M3(){}M3(const M3&m){r[0]=m.r[0];r[2]=m.r[2];r[1]=m.r[1];}M3&operator=(const M3&m){r[0]=m.r[0];r[2]=m.r[2];r[1]=m.r[1];return *this;}};
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
static inline qword FloatBits(float f){register qword q __asm__("$2");__asm__("mfc1 %0,%1":"=r"(q):"f"(f));return q;}
static inline qword AddScaled(qword p,qword v,qword k){qword q;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%3,%2x":"=j"(q):"j"(p),"j"(k),"j"(v));return q;}
static inline qword Rotate(const M3&m,qword v){qword q;__asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(q):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"0"(v));return q;}
static inline qword Transform(const M4&m,qword v){qword q;__asm__("vmulax.xyz ACC,%1,%5x\n\tvmadday.xyz ACC,%2,%5y\n\tvmaddaz.xyz ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(q):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(m.r[3].q),"j"(v));return q;}
static inline qword Add(qword a,qword b){qword q;__asm__("vadd.xyzw %0,%1,%2":"=j"(q):"j"(a),"j"(b));return q;}
static inline qword Sub(qword a,qword b){qword q;__asm__("vsub.xyzw %0,%1,%2":"=j"(q):"j"(a),"j"(b));return q;}
static inline float Abs(float f){float q;__asm__("abs.s %0,%1":"=f"(q):"f"(f));return q;}
static inline qword GetVelocity(P*p){VTE*e=&p->vt[33];qword(*f)(void*)=(qword(*)(void*))e->fn;return f((char*)p+e->delta);}
static inline void*GetFrame(P*p,M4*out){return ((void*(*)(void*,M4*))p->vt[32].fn)((char*)p+p->vt[32].delta,out);}
extern "C" void func_0018F2B0(P*p,float headingInput,int mask,float dtInput,U*offset,P**out,qword*outvector,float cone){
 register float heading __asm__("$f21")=headingInput,dt __asm__("$f20")=dtInput;
 M3 rotation;
 U origin,reference,target,delta,candidate;
 M4 prediction;
 U answer;
 P*best=0;
 float nearest=300.0f;
 qword scalar=FloatBits(dt);
 rotation=func_0011B500(D_002A2DC0,headingInput);
 qword position=func_001A62E8(p);
 U scratch;scratch.q=scalar;
 origin.q=AddScaled(position,GetVelocity(p),scalar);
 reference.q=func_001A6F00(p,0,offset->q);
 target.q=Add(Rotate(rotation,offset->q),origin.q);
 delta.q=Sub(target.q,reference.q);
 for(P*node=D_003E13B4;node;node=node->next){
  M4 frame;
  float t,distance;
  if(!(node->flags&mask))continue;
  candidate.q=func_001A62E8(node);
  void*owner=GetFrame(node,&frame);
  func_002309E8(owner,0,&prediction,dt,0);
  func_0011EE08(target.q,candidate.q,Transform(prediction,frame.r[3].q),0,&t,&distance);
  if(func_0015ED78(&D_003DD490,3,0x33,node))distance+=D_002BF4B8;
  if(distance<nearest){
   qword other=candidate.q;
   scratch.q=Sub(other,func_001A62E8(p));
   float angle=Abs(func_0011CF60(func_002458F0(scratch.f[1],scratch.f[0])-heading));
   if(cone<angle)continue;
   best=node;nearest=distance;
   answer.q=Sub(prediction.r[3].q,origin.q);
  }
 }
 *out=best;
 *outvector=answer.q;
}
