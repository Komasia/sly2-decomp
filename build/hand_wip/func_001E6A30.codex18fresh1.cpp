typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M4 {qword a,b,c,d;};
struct WORK {U segment;M4 matrix;U normInput;float elapsed,duration;float*outTime,*outValue;U position;};
struct VTE {short delta,pad;void(*fn)();};
struct P {char pad0[0xC];VTE*vt;char pad10[0xE4-0x10];int cyclic,count;float*times;int padF0;qword*points;};
struct SPACE {qword axis;int mode;};
extern "C" {
int func_001E7538(P*,float,float*,float*);
qword func_001FA970(SPACE*,qword);
float func_001E63C0(P*,float);
void func_001E6A30(P*,qword,SPACE*,qword*,qword*,float*,float*,float);
}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Length(qword a){register qword d __asm__("vf1");qword one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=j"(one):"j"(a));__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));return d;}
static inline qword Norm(qword a,qword len){register qword r __asm__("vf1");__asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(r):"j"(a),"j"(len));return r;}
static inline qword Dot(qword a,qword b){register qword one __asm__("vf3");__asm__("vmul.xyz %0,%2,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(b),"=&j"(one):"j"(a));return b;}
static inline qword NormalizeMeasured(qword a,qword len,int *bits,U*home){register int word __asm__("$2");register qword r __asm__("vf1")=len;__asm__("qmfc2.ni %0,%1\n\tvdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %1,%3,$Q\n\tsqc2 %3,%2":"=&r"(word),"+&j"(r),"=m"(*home):"j"(a));*bits=word;return r;}
static inline float FromBits(int a){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
static inline float Scalar(qword a){register int word __asm__("$4");register float value __asm__("$f0");__asm__("qmfc2.ni %1,%2\n\tmtc1 %1,%0":"=f"(value),"=r"(word):"j"(a));return value;}
static inline qword Lerp(qword a,qword b,qword low,qword high){__asm__("vmulax.xyzw $ACC,%1,%0x\n\tvmaddx.xyzw %0,%2,%3x":"+j"(low):"j"(a),"j"(b),"j"(high));return low;}
static inline qword SegmentZ(const M4*input){register const M4*m __asm__("$19")=input;register qword value __asm__("vf1");__asm__("lqc2 %0,0x20(%1)":"=j"(value):"r"(m),"m"(m->c));return value;}
static inline qword FirstPoint(const qword*p){register qword value __asm__("vf6");__asm__("lqc2 %0,%1":"=j"(value):"m"(*p));return value;}
static inline qword SegmentVector(const M4*matrix,qword input,qword start,qword x,qword z){register const M4*m __asm__("$19")=matrix;register qword end __asm__("vf2")=input;register qword y __asm__("vf7");__asm__("lqc2 %1,0x10(%5)\n\tvsub.xyzw %0,%0,%2\n\tvmulax.xyz $ACC,%3,%0x\n\tvmadday.xyz $ACC,%1,%0y\n\tvmaddz.xyz %0,%4,%0z":"+&j"(end),"=&j"(y):"j"(start),"j"(x),"j"(z),"r"(m),"m"(m->b));return end;}
static inline qword SegmentPoint(const M4*m,qword x,qword input,qword segment,U*home){register qword r __asm__("vf4")=x;__asm__("lqc2 $vf5,%4\n\tlqc2 $vf1,%5\n\tlqc2 $vf3,%6\n\tvmulax.xyz $ACC,%0,%2x\n\tvmadday.xyz $ACC,$vf5,%2y\n\tvmaddaz.xyz $ACC,$vf3,%2z\n\tvmaddw.xyz %0,$vf1,$vf0w\n\tsqc2 %3,%1":"+&j"(r),"=m"(*home):"j"(input),"j"(segment),"m"(m->b),"m"(m->d),"m"(m->c):"vf1","vf3","vf5");return r;}
static inline qword PositionDelta(const U*position,qword point){register qword value __asm__("vf1");__asm__("lqc2 %1,%2\n\tvsub.xyzw %0,%1,%0":"+j"(point),"=&j"(value):"m"(*position));return point;}
static inline qword FirstAndHigh(const qword*p,qword high,U*home){register qword first __asm__("vf5");__asm__("lqc2 %0,%2\n\tsqc2 %3,%1":"=&j"(first),"=m"(*home):"m"(*p),"j"(high));return first;}
static inline qword PointRows(qword r,qword y,qword z,qword w,qword value){__asm__("vmulax.xyz $ACC,%0,%4x\n\tvmadday.xyz $ACC,%1,%4y\n\tvmaddaz.xyz $ACC,%2,%4z\n\tvmaddw.xyz %0,%3,$vf0w":"+j"(r):"j"(y),"j"(z),"j"(w),"j"(value));return r;}
static inline qword TangentX(const qword*p){register qword value __asm__("vf4");__asm__("lqc2 %0,%1":"=j"(value):"m"(*p));return value;}
static inline const qword*SecondAddress(const qword*input){register const qword*first __asm__("$4")=input;register const qword*second __asm__("$2");__asm__("daddu %0,%1,$zero":"=r"(second):"r"(first));return second;}
static inline qword TangentVector(const M4*m,qword input,qword x,qword z){register qword tangent __asm__("vf2")=input;register qword y __asm__("vf3");__asm__("lqc2 %1,%4\n\tvmulax.xyz $ACC,%2,%0x\n\tvmadday.xyz $ACC,%1,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(tangent),"=&j"(y):"j"(x),"j"(z),"m"(m->b));return tangent;}
static inline qword TangentLength(qword a){register qword d __asm__("vf1");__asm__("vmul.xyz %0,%1,%1\n\tvaddw.x $vf6,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,$vf6,%0z\n\tvsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(d):"j"(a):"vf6");return d;}
static inline qword HighAndDifference(float fraction,float*outLow){register float low __asm__("$f0")=1.0f;register int word __asm__("$4");register qword high __asm__("vf8");__asm__("mfc1 %1,%3\n\tsub.s %0,%0,%3\n\tqmtc2.ni %1,%2":"+f"(low),"=r"(word),"=j"(high):"f"(fraction));*outLow=low;return high;}
static inline qword InterpolationInputs(const P*p,const qword*matrixX,float value,const qword**outBase,int*outWord){register const qword*base __asm__("$3");register qword x __asm__("vf4");register int word __asm__("$4");register float low __asm__("$f0")=value;__asm__("lw %0,%3\n\tlqc2 %1,%4\n\tmfc1 %2,%5":"=&r"(base),"=j"(x),"=r"(word):"m"(p->points),"m"(*matrixX),"f"(low));*outBase=base;*outWord=word;return x;}
static inline qword LowAndPointAddress(unsigned offset,const qword*inputBase,int inputWord,const qword**outPoint){register unsigned address __asm__("$2")=offset;register const qword*base __asm__("$3")=inputBase;register int word __asm__("$4")=inputWord;register qword low __asm__("vf3");__asm__("addu %0,%0,%2\n\tqmtc2.ni %3,%1":"+&r"(address),"=j"(low):"r"(base),"r"(word));*outPoint=(const qword*)address;return low;}
static inline qword RowYAndLow(const qword*field,qword low,U*home){register qword y __asm__("vf7");__asm__("lqc2 %0,%2\n\tsqc2 %3,%1":"=&j"(y),"=m"(*home):"m"(*field),"j"(low));return y;}
static inline float TimeCoordinates(const P*p,int index,const float**outBase,unsigned*outOffset){register float one __asm__("$f1");register unsigned offset __asm__("$2");register const float*base __asm__("$3");register int upper __asm__("$1");__asm__(".set noat\n\tlui %3,%4\n\tmtc1 %3,%0\n\tsll %1,%5,2\n\tlw %2,%6\n\t.set at":"=f"(one),"=&r"(offset),"=r"(base),"=&r"(upper):"i"(0x3F800000u>>16),"r"(index),"m"(p->times));*outBase=base;*outOffset=offset;return one;}
static inline float TimeComplementAndAddress(float inputOne,float fraction,const float*inputBase,unsigned offset,const float**outTimes){register float low __asm__("$f1")=inputOne;register unsigned address __asm__("$2")=offset;register const float*base __asm__("$3")=inputBase;__asm__("sub.s %0,%0,%2\n\taddu %1,%1,%3":"+f"(low),"+r"(address):"f"(fraction),"r"(base));*outTimes=(const float*)address;return low;}
static inline void TimeProducts(const float*times,float*const*field,float fraction,float complement,float*outLow,float*outHigh,float**outPointer){register float low __asm__("$f1")=complement;register float high __asm__("$f0"),first __asm__("$f2");register float*pointer __asm__("$2");__asm__("lwc1 %1,%4\n\tlwc1 %3,%5\n\tmul.s %1,%6,%1\n\tlw %2,%7\n\tmul.s %0,%0,%3":"+f"(low),"=&f"(high),"=r"(pointer),"=&f"(first):"m"(times[1]),"m"(times[0]),"f"(fraction),"m"(*field));*outLow=low;*outHigh=high;*outPointer=pointer;}
static inline float*ValueOutput(float*const*field){register float*value __asm__("$4");__asm__("lw %0,%1":"=r"(value):"m"(*field));return value;}
void func_001E6A30(P*p,qword position,SPACE*space,qword*outPosition,qword*outDirection,float*outTime,float*outValue,float initial){
 WORK work;work.position.q=position;work.outTime=outTime;work.outValue=outValue;
 int backward=0,forward=0,previous;
 int index=func_001E7538(p,initial,&work.elapsed,&work.duration);
 work.matrix=*((M4*(*)(void*))p->vt[31].fn)((char*)p+p->vt[31].delta);
 register M4*basis __asm__("$19")=&work.matrix;
 register float fraction __asm__("$f12");
 for(;;){
  qword delta;
  {
   qword rowZ=SegmentZ(basis);
   register qword rowX __asm__("vf4")=work.matrix.a;
   qword start=FirstPoint(&p->points[index]);
   register qword end __asm__("vf2")=p->points[index+1];
   qword segment=SegmentVector(basis,end,start,rowX,rowZ);
   delta=PositionDelta(&work.position,SegmentPoint(&work.matrix,rowX,start,segment,&work.segment));
  }
  if(space){delta=func_001FA970(space,delta);work.segment.q=func_001FA970(space,work.segment.q);}
  qword length=Length(work.segment.q);int sizeBits;
  qword direction=NormalizeMeasured(work.segment.q,length,&sizeBits,&work.normInput);
  register qword projectedDelta __asm__("vf4")=delta;
  qword projection=Dot(direction,projectedDelta);
  float distance=Scalar(projection),size=FromBits(sizeBits);
  work.segment.q=direction;
  fraction=0;
  if(distance<fraction){
   if(forward){fraction=1;index=previous;break;}
   if(index>0)--index;
   else {if(!p->cyclic){fraction=0;break;}index=p->count-2;backward=1;}
   next:
   previous=index;continue;
  }else if(size<distance){
   if(backward){fraction=0;index=previous;break;}
   if(index<p->count-2)++index;
   else {if(!p->cyclic){fraction=1;break;}index=0;}
   forward=1;goto next;
  }else {fraction=distance/size;break;}
 }
 if(outPosition){
  unsigned offset=(unsigned)index<<4;
  float pointLow;const qword*base;int lowWord;
  qword high=HighAndDifference(fraction,&pointLow);
  qword rowX=InterpolationInputs(p,&work.matrix.a,pointLow,&base,&lowWord);
  const qword*points;
  qword low=LowAndPointAddress(offset,base,lowWord,&points);
  qword rowY=RowYAndLow(&work.matrix.b,low,&work.normInput);
  register qword rowZ __asm__("vf6")=work.matrix.c;
  register qword rowW __asm__("vf2")=work.matrix.d;
  qword first=FirstAndHigh(points,high,&work.normInput);
  register qword second __asm__("vf1")=points[1];
  *outPosition=PointRows(rowX,rowY,rowZ,rowW,Lerp(first,second,low,high));
 }
 if(outDirection){
  register const qword*first __asm__("$4")=&p->points[index];
  register qword rowZ __asm__("vf5")=basis->c;
  qword rowX=TangentX(&work.matrix.a);
  const qword*second=SecondAddress(first);
  register qword start __asm__("vf1")=*first;
  register qword end __asm__("vf2")=second[1];
  qword tangent=TangentVector(basis,Sub(end,start),rowX,rowZ);
  *outDirection=Norm(tangent,TangentLength(tangent));
 }
 const float*base;unsigned offset;
 float one=TimeCoordinates(p,index,&base,&offset);
 const float*times;
 float complement=TimeComplementAndAddress(one,fraction,base,offset,&times);
 float lowProduct,highProduct;float*destination;
 TimeProducts(times,&work.outTime,fraction,complement,&lowProduct,&highProduct,&destination);
 float time=lowProduct+highProduct;
 if(destination)*destination=time;
 if(ValueOutput(&work.outValue))*work.outValue=func_001E63C0(p,time);
}

#define OFF(t,m) ((int)&((t*)0)->m)
typedef char projection_layout[(sizeof(U)==16 && sizeof(M4)==0x40 && sizeof(VTE)==8 && sizeof(SPACE)==0x20 && sizeof(WORK)==0x80 && OFF(M4,a)==0 && OFF(M4,b)==0x10 && OFF(M4,c)==0x20 && OFF(M4,d)==0x30 && OFF(VTE,delta)==0 && OFF(VTE,fn)==4 && OFF(SPACE,axis)==0 && OFF(SPACE,mode)==0x10 && OFF(P,vt)==0xC && OFF(P,cyclic)==0xE4 && OFF(P,count)==0xE8 && OFF(P,times)==0xEC && OFF(P,points)==0xF4 && OFF(WORK,segment)==0 && OFF(WORK,matrix)==0x10 && OFF(WORK,normInput)==0x50 && OFF(WORK,elapsed)==0x60 && OFF(WORK,duration)==0x64 && OFF(WORK,outTime)==0x68 && OFF(WORK,outValue)==0x6C && OFF(WORK,position)==0x70)?1:-1];

typedef char qword_width[sizeof(qword)==16?1:-1];
typedef char scalar_width[sizeof(float)==4?1:-1];
typedef char integer_width[sizeof(int)==4?1:-1];
typedef char pointer_width[sizeof(void*)==4?1:-1];
