typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];int i[4];} V;
struct P {char pad[0x208];int enabled;};
extern qword D_002A2DC0;
void func_002057E8(struct P*,V*);
int func_0011EBB0(qword,qword,qword,qword,qword,float*,float*);
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scale(qword a,float f,V *k){qword q,r;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));k->q=q;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(q));return r;}
static inline float Normal(V*v,qword fallback){qword a=v->q,d,one;float g,r;
__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(a));
__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(one):"j"(d));
__asm__("qmfc2.ni %0,%1":"=r"(g):"j"(one));
if(g<0.0001f)a=fallback;
else __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%0,$Q":"=j"(a):"j"(one),"0"(a));
v->q=a;
__asm__("mtc1 %1,%0":"=f"(r):"r"(one));return r;}
int func_00205670(struct P*p,qword from,qword to,qword*out)
{
 V tri[6],d,k;
 float distance,length;
 V *t;
 if(!p->enabled)return 0;
 func_002057E8(p,tri);
 d.q=Sub(to,from);
 length=Normal(&d,D_002A2DC0);
 for(t=tri;t<tri+6;t+=3){
   int hit=func_0011EBB0(d.q,from,t[0].q,t[1].q,t[2].q,&distance,0);
   if(distance<=length && (hit&1)){
      *out=Add(from,Scale(d.q,distance,&k));return 1;
   }
 }
 return 0;
}
