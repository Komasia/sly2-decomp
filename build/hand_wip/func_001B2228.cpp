/* WIP: 61/92 instructions differ; by-value temporary and live-vector spill allocation remain. */
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct V { float x,y,z,w; } __attribute__((aligned(16)));
struct VT { short d,pad;void *fn; };
struct P {char pad0[0xC];VT *vt;char pad1[0x270-0x10];float g270,g274,g278;};
struct HIT { qword q[4];float t0,t1;void *p0,*p1;int other[4];};
struct CLOCK {float t,dt;};
extern "C" CLOCK D_002DDED0;
extern "C" qword D_002A2DD0;
extern "C" void func_001B1E88(P*,int,V*);
extern "C" V func_001B2398(P*,float);
extern "C" qword func_0011E9F8(qword,float);
extern "C" qword func_001A62E8(P*);
extern "C" int func_0014C748(qword,qword,qword,int,HIT*,float);
inline qword Bc(float g,U &u){qword k;__asm__("qmtc2.ni %1,%0":"=j"(k):"r"(g));u.q=k;return k;}
inline qword Scale(qword a,qword k){__asm__("vmulx.xyzw %0,%1,%2x":"=j"(k):"j"(a),"0"(k));return k;}
inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
inline qword MAdd(qword a,qword b,qword k,U &u){qword r;__asm__("vadda.xyzw $ACC,$vf0,%1\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(k));u.q=r;return r;}
inline U Scalar(float g){U r;qword q;__asm__("mfc1 %0,%1":"=r"(q):"f"(g));r.q=q;return r;}
extern "C" void func_001B2228(P*p,int n,V*pv){
 U pos;V dir;
 pos.q=*(qword*)pv;
 func_001B1E88(p,n,(V*)&pos);
 if(p->g270>0.0f) p->g278=D_002DDED0.t+p->g270;
 else {
  dir=func_001B2398(p,0.5f);
  {U vel,tmp,factor;HIT hit;
  qword k=Bc(-0.5f,tmp);
  vel.q=Scale(((qword(*)(void*))p->vt[33].fn)((char*)p+p->vt[33].d),k);
  vel.q=func_0011E9F8(vel.q,0.75f*p->g274);
  factor=Scalar(1.5f);
  qword d=Sub(*(qword*)&dir,func_001A62E8(p));
  qword acc=MAdd(vel.q,d,factor.q,tmp);
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
