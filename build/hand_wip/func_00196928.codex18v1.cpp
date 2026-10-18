
typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];} U;
extern "C" int func_0011D508(float,float,float,float*);
static inline float Sqrt(float x){float r;__asm__("sqrt.s %0,%1":"=&f"(r):"f"(x));return r;}
static inline float Max(float a,float b){float r;__asm__("max.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline float Zin(qword v){float f;__asm__("pextuw %0,$zero,%0":"=r"(f):"0"(v));return f;}
static inline float Z(qword v){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(v));return f;}
static inline float LenXY(const qword*pv){register qword d __asm__("vf1");qword v;float r;__asm__("lqc2 %1,%2\n\tvmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=&j"(d),"=&j"(v):"m"(*pv));__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(d):"0"(d));__asm__("qmfc2.ni %0,%1":"=r"(r):"j"(d));return r;}
static inline float*RootHome(float*home){register float*result __asm__("$4");__asm__("daddu %0,%1,$zero":"=r"(result):"r"(home));return result;}
extern "C" float func_00196928(qword v,qword a,float low,float high,float slope0,float slope1){
 float r0[2] __attribute__((aligned(16))),r1[2] __attribute__((aligned(16)));float az=Z(a)*0.5f,naz=-az;float vz,best=0.0f,l,t;int n;vz=Zin(v);
 n=func_0011D508(naz,-low,vz,RootHome(r0));if(n>0)best=Max(r0[n-1],best);
 n=func_0011D508(az,-high,vz,r1);if(n>0)best=Max(r1[n-1],best);
 l=LenXY(&v);t=(slope0*l-vz)/naz;if(t>0.0f)best=Max(Sqrt(t),best);
 t=(slope1*l-vz)/az;if(t>0.0f)best=Max(Sqrt(t),best);
 return best;
}
