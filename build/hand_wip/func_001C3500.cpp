// Construct the path orientation from nearby sampled directions.
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M3 {qword rows[3];};
struct P {char padE4[0xE4];int cyclic;char padE8[0xD8];qword axis;};
struct WORK {M3 basis;U tangent,first,direction,forward,backward;M3 rotation,temporary;};
extern "C" {
extern qword D_002A2DA0,D_002A2DC0;
float func_001E6620(P *);
float func_001E6648(P *);
float func_001E6610(P *);
void func_001E67B8(P *,float,qword *,qword *);
float func_0011D898(float,float);
float func_001E6728(P *,float);
void func_001E6F10(P *,float,qword *,qword *);
M3 *func_0011BA08(M3 *,qword,qword);
qword func_001A6FC0(P *,P *,qword);
qword func_0011E390(qword);
}
static inline qword ToVU(qword q){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(q));return r;}
static inline float X(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline qword Length(qword q){qword d,one;
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(q));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(d));return d;
}
static inline qword Unit(qword q,qword length){qword r;__asm__ __volatile__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(q),"j"(length));return r;}
static inline qword NormalizeInitial(qword value,qword fallback){
 register qword vector __asm__("vf3")=value;
 register qword sum __asm__("vf1"),one __asm__("vf2");
 register qword length __asm__("vf1"),result __asm__("vf1");float scalar;
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(sum),"=&j"(one):"j"(vector));
 __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(length):"j"(sum));
 __asm__("mtc1 %1,%0":"=f"(scalar):"r"(length));
 if(scalar<0.0001f)result=fallback;
 else __asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(result):"j"(length),"j"(vector));return result;
}
static inline qword NormalizeSample(qword value,qword fallback){
 register qword vector __asm__("vf3")=value;
 register qword sum __asm__("vf2"),one __asm__("vf1");
 register qword length __asm__("vf1"),result __asm__("vf1");float scalar;
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(sum),"=&j"(one):"j"(vector));
 __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(length):"j"(sum));
 register qword scalarWord __asm__("$4")=length;
    __asm__("mtc1 %1,%0":"=f"(scalar):"r"(scalarWord));
 if(scalar<0.0001f)result=fallback;
 else __asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(result):"j"(length),"j"(vector));return result;
}
static inline qword UpFallback(){qword value;__asm__("lq %0,%1":"=r"(value):"m"(D_002A2DC0));return value;}
static inline qword NormalizeUp(qword value,qword fallback){
 register qword vector __asm__("vf5")=value;
 register qword sum __asm__("vf1"),one __asm__("vf2");
 register qword length __asm__("vf6"),result __asm__("vf4");float scalar;
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(sum),"=&j"(one):"j"(vector));
 __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(length):"j"(sum));
 register qword scalarWord __asm__("$4")=length;
    __asm__("mtc1 %1,%0":"=f"(scalar):"r"(scalarWord));
 if(scalar<0.0001f)result=fallback;
 else __asm__ __volatile__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(result):"j"(length),"j"(vector));return result;
}
static inline qword Sub(qword av,qword bv){register qword a __asm__("vf2")=av,b __asm__("vf1")=bv,r __asm__("vf3");__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline float Dot(qword av,qword bv){register qword a __asm__("vf3")=av,b __asm__("vf4")=bv,r __asm__("vf2"),one __asm__("vf1");__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(r),"=&j"(one):"j"(a),"j"(b));return X(r);}
static inline qword Direction(const M3 &m,qword q){qword r;__asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r):"j"(m.rows[0]),"j"(m.rows[1]),"j"(m.rows[2]),"j"(q));return r;}
static inline qword Cross(qword a,qword b){qword r=b;__asm__("vopmula.xyz $ACC,%1,%0\n\tvopmsub.xyz %0,%0,%1":"+j"(r):"j"(a));return r;}
static inline qword Negate(U &temporary,qword q){qword scalar;__asm__("qmtc2.ni %1,%0":"=j"(scalar):"r"(-1.0f));temporary.q=scalar;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(scalar):"j"(q),"j"(temporary.q));return scalar;}
static inline P* CopyRotation(M3&destination,const M3&source,P*p,P*&frame){register qword x __asm__("$6"),y __asm__("$3"),z __asm__("$2");register P*receiver __asm__("$4"),*nullFrame __asm__("$5");__asm__("lq %0,%6\n\tdaddu %3,%9,$zero\n\tlq %1,%7\n\tdaddu %4,$zero,$zero\n\tlq %2,%8\n\tsq %1,16+%5\n\tsq %0,%5\n\tsq %2,32+%5":"=&r"(x),"=&r"(y),"=&r"(z),"=&r"(receiver),"=&r"(nullFrame),"=m"(destination):"m"(source.rows[0]),"m"(source.rows[1]),"m"(source.rows[2]),"r"(p));frame=nullFrame;return receiver;}
extern "C" void func_001C3500(P *p,float distance,int forward,M3 *out){
 WORK work;
 float low=func_001E6620(p),high=func_001E6648(p);
 float firstTime=func_001E6610(p);
 func_001E67B8(p,firstTime,0,&work.tangent.q);
 work.tangent.q=NormalizeInitial(work.tangent.q,D_002A2DA0);
 for(int i=0;;++i){
  float offset=(i&1)?10.0f*(float)(i+1):(float)i*-10.0f;
  float sample=distance+offset;
  if(!p->cyclic){if(sample<low || high<distance)continue;}
  else sample=low+func_0011D898(sample-low,high-low);
  func_001E6F10(p,func_001E6728(p,sample+50.0f),&work.forward.q,0);
  func_001E6F10(p,func_001E6728(p,sample-50.0f),&work.backward.q,0);
  work.direction.q=NormalizeSample(Sub(work.forward.q,work.backward.q),D_002A2DC0);
  if(i==0)work.first.q=work.direction.q;
  if(Dot(work.tangent.q,work.direction.q)>-0.9f)break;
 }
 func_0011BA08(&work.temporary,work.tangent.q,work.direction.q);P*frame;P*receiver=CopyRotation(work.rotation,work.temporary,p,frame);
 qword reference=ToVU(func_001A6FC0(receiver,frame,receiver->axis));
 work.forward.q=Direction(work.rotation,reference);
 qword up=NormalizeUp(work.first.q,UpFallback());
 work.basis.rows[2]=up;
 work.backward.q=Cross(up,work.forward.q);
 work.basis.rows[1]=work.backward.q;
 qword length=Length(work.backward.q);
 work.basis.rows[1]=Unit(work.backward.q,length);
 if(X(length)<1.0e-4f)work.basis.rows[1]=func_0011E390(up);
 work.basis.rows[0]=Cross(work.basis.rows[1],work.basis.rows[2]);
 if(!forward){work.basis.rows[2]=Negate(work.backward,work.basis.rows[2]);work.basis.rows[1]=Negate(work.backward,work.basis.rows[1]);}
 if(out)*out=work.basis;
}

#define OFF(t,m) ((unsigned int)&((t*)0)->m)
typedef char path_orientation_layout[(sizeof(void*)==4 && sizeof(qword)==16 && sizeof(U)==0x10 && sizeof(M3)==0x30 && sizeof(WORK)==0xE0 && OFF(P,cyclic)==0xE4 && OFF(P,axis)==0x1C0 && OFF(WORK,basis)==0 && OFF(WORK,tangent)==0x30 && OFF(WORK,first)==0x40 && OFF(WORK,direction)==0x50 && OFF(WORK,forward)==0x60 && OFF(WORK,backward)==0x70 && OFF(WORK,rotation)==0x80 && OFF(WORK,temporary)==0xB0)?1:-1];
