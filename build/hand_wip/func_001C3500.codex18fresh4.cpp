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
static inline float X(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
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
static inline qword Sub(qword av,qword bv){register qword a __asm__("vf2")=av,b __asm__("vf1")=bv,r __asm__("vf3");__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline float Dot(qword av,qword bv){register qword a __asm__("vf3")=av,b __asm__("vf4")=bv,r __asm__("vf2"),one __asm__("vf1");__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(r),"=&j"(one):"j"(a),"j"(b));return X(r);}
static inline qword UpAndForward(const U&first,const M3&rotation,qword reference,U&forward){
 register qword vector __asm__("vf5")=first.q;
 register qword square __asm__("vf1"),carrier __asm__("vf2"),length __asm__("vf6");
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(square),"=&j"(carrier):"j"(vector));
 __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(length):"j"(square));
 qword row0=rotation.rows[0];register qword row1 __asm__("vf3"),row2 __asm__("vf1");
 register qword word __asm__("$4")=length;
 float size;__asm__("mtc1 %3,%0\n\tlqc2 %1,%4\n\tlqc2 %2,%5":"=f"(size),"=j"(row1),"=j"(row2):"r"(word),"m"(rotation.rows[1]),"m"(rotation.rows[2]));
 register qword input __asm__("vf7"),fallback __asm__("$4");
 __asm__("qmtc2.ni %2,%0\n\tlq %1,%3":"=j"(input),"=r"(fallback):"r"(reference),"m"(D_002A2DC0));
 // This XYZ result retains the actual reduction-one VF2 W carrier.
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"+j"(carrier):"j"(row0),"j"(row1),"j"(row2),"j"(input));
 forward.q=carrier;
 register qword up __asm__("vf4");
 if(size<0.0001f)up=fallback;
 else __asm__ __volatile__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(up):"j"(length),"j"(vector));
 return up;
}
static inline float SideEpsilon(){register float value __asm__("$f1");__asm__(".set noat\n\tlui $1,%1\n\tori $1,$1,%2\n\tmtc1 $1,%0\n\t.set at":"=f"(value):"I"(0x38D1),"K"(0xB717):"$1");return value;}
// The final partial XYZ result retains VF1.W, including the actual fallback call state.
static inline void FinishBasis(M3&basis,U&temporary,int forward){
 register qword side __asm__("vf4"),up __asm__("vf2"),cross __asm__("vf1");
 __asm__("lqc2 %1,%3\n\tlqc2 %2,%4\n\tvopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"=j"(cross),"=j"(side),"=j"(up):"m"(basis.rows[1]),"m"(basis.rows[2]));
 basis.rows[0]=cross;
 if(!forward){
  register qword scale __asm__("vf1"),negativeUp __asm__("vf3");
  register int word __asm__("$3");float minus=-1.0f;
  __asm__("mfc1 %0,%1":"=r"(word):"f"(minus));
  __asm__("qmtc2.ni %1,%0":"=j"(scale):"r"(word));temporary.q=scale;
  register qword factor __asm__("vf1")=temporary.q;
  __asm__("vmulx.xyzw %0,%1,%2x":"=j"(negativeUp):"j"(up),"j"(factor));
  __asm__("vmulx.xyzw %0,%1,%2x":"=j"(up):"j"(side),"j"(factor));
  basis.rows[2]=negativeUp;basis.rows[1]=up;
 }
}
static inline void PublishBasis(M3*out,const M3&basis,qword first){register qword side __asm__("$4"),up __asm__("$3");__asm__("lq %0,%5\n\tlq %1,%6\n\tsq %7,%2\n\tsq %1,%4\n\tsq %0,%3":"=&r"(side),"=&r"(up),"=m"(out->rows[0]),"=m"(out->rows[1]),"=m"(out->rows[2]):"m"(basis.rows[1]),"m"(basis.rows[2]),"r"(first));}
static inline P* CopyRotation(M3&destination,const M3&source,P*p,P*&frame){register qword x __asm__("$6"),y __asm__("$3"),z __asm__("$2");register P*receiver __asm__("$4"),*nullFrame __asm__("$5");__asm__("lq %0,%6\n\tdaddu %3,%9,$zero\n\tlq %1,%7\n\tdaddu %4,$zero,$zero\n\tlq %2,%8\n\tsq %1,16+%5\n\tsq %0,%5\n\tsq %2,32+%5":"=&r"(x),"=&r"(y),"=&r"(z),"=&r"(receiver),"=&r"(nullFrame),"=m"(destination):"m"(source.rows[0]),"m"(source.rows[1]),"m"(source.rows[2]),"r"(p));frame=nullFrame;return receiver;}
extern "C" void func_001C3500(P *p,float distance,int forward,M3 *output){
 register M3*out __asm__("$20");__asm__("daddu %0,%1,$zero":"=r"(out):"r"(output));
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
 qword reference=func_001A6FC0(receiver,frame,receiver->axis);
 qword up=UpAndForward(work.first,work.rotation,reference,work.forward);
 float sideSize,sideEpsilon;
 {
  register qword sideUp __asm__("vf4")=up,side __asm__("vf1"),length __asm__("vf2"),one __asm__("vf3");
  register float epsilon __asm__("$f1");
  __asm__(".set noat\n\tlqc2 %0,%3\n\tvopmula.xyz $ACC,%2,%0\n\tvopmsub.xyz %0,%0,%2\n\tlui $1,%4\n\tori $1,$1,%5\n\tmtc1 $1,%1\n\t.set at":"=j"(side),"=f"(epsilon):"j"(sideUp),"m"(work.forward.q),"I"(0x38D1),"K"(0xB717):"$1");
  sideEpsilon=epsilon;
  __asm__("vmul.xyz %0,%3,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z\n\tsqc2 %3,%2":"=j"(length),"=&j"(one),"=m"(work.basis.rows[1]):"j"(side));
  __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q\n\tsqc2 %2,%1":"+j"(length),"=m"(work.basis.rows[2]):"j"(sideUp));
  register qword word __asm__("$2");
  __asm__("qmfc2.ni %0,%2\n\tmtc1 %0,%1":"=r"(word),"=f"(sideSize):"j"(length));
  __asm__ __volatile__("vdiv Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"+j"(length):"j"(side));
  work.basis.rows[1]=length;work.backward.q=side;
 }
 if(sideSize<sideEpsilon)work.basis.rows[1]=func_0011E390(up);
 FinishBasis(work.basis,work.backward,forward);
 qword first=work.basis.rows[0];
 if(out)PublishBasis(out,work.basis,first);
}

#define OFF(t,m) ((unsigned int)&((t*)0)->m)
typedef char path_orientation_layout[(sizeof(void*)==4 && sizeof(qword)==16 && sizeof(U)==0x10 && sizeof(M3)==0x30 && sizeof(WORK)==0xE0 && OFF(P,cyclic)==0xE4 && OFF(P,axis)==0x1C0 && OFF(WORK,basis)==0 && OFF(WORK,tangent)==0x30 && OFF(WORK,first)==0x40 && OFF(WORK,direction)==0x50 && OFF(WORK,forward)==0x60 && OFF(WORK,backward)==0x70 && OFF(WORK,rotation)==0x80 && OFF(WORK,temporary)==0xB0)?1:-1];
