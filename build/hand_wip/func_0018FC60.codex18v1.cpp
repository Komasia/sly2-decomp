typedef int qword __attribute__((mode(TI)));
typedef union U{qword q;float f[4];int i[4];}U;
struct M3{U r[3];M3(){}M3(const M3&m){r[0].q=m.r[0].q;r[1].q=m.r[1].q;r[2].q=m.r[2].q;}M3&operator=(const M3&m){r[0].q=m.r[0].q;r[1].q=m.r[1].q;r[2].q=m.r[2].q;return *this;}};
typedef struct M4{U r[4];}M4;
typedef struct VTE{short delta,pad;void*fn;}VTE;
typedef struct NODE{char pad0[12];VTE*vt;char pad10[0x124];float property;}NODE;
typedef struct ACCEL{char pad0[0x80];U value;}ACCEL;
typedef struct LINK{int header;NODE*object;}LINK;
typedef struct DELTA{U first,second;}DELTA;
typedef struct P{char pad0[12];VTE*vt;char pad10[0xD8];ACCEL*accel;char padEC[0x17D8];NODE*target;char pad18C8[8];int state;float stamp;char pad18D8[0x24];int reverse;LINK*other;char pad1904[12];DELTA response[2];}P;
typedef struct POLY{float a,b,c;}POLY;
typedef struct CLAMP{float low,high;}CLAMP;
typedef struct SMPA{float a,b,duration,limit;}SMPA;
typedef struct CLOCK{float time,dt;}CLOCK;
typedef struct STATE{U direction,position,velocity;M3 rotation;}STATE;
typedef struct WORK{U anchor,displacement,anchorVelocity,axis;M3 anchorBasis;U relative,perpendicular,parallel,firstAxis,angularFirst,temporary,secondAxis,angularSecond,angular,parallelAngular,perpendicularAngular,velocity;STATE state;M3 rotation;U halfScalar;float speedOut;U savedVelocity,dtScalar,savedPoint,savedAngular,finalVelocity;}WORK;
inline void*operator new(unsigned int,void*p){return p;}
extern "C"{
qword func_001A62E8(void*);
M4*func_001A6318(void*);
qword func_0022D348(void*,void*,qword);
float func_0011E290(qword,qword,qword*,qword*);
float func_0011D1C0(float,float,float,float,SMPA*,float*);
M3 func_0011B570(qword);
void func_0018F958(P*,NODE*,qword*,float*,DELTA*);
extern U D_002A2DC0,D_002A2DA0,D_002A2DB0,D_002A2DD0;
extern POLY D_002BF4F0,D_002BF520;
extern CLAMP D_002BF500,D_002BBB60;
extern float D_002BF508,D_002BF50C,D_002BF510,D_002BF514,D_002BF540,D_002BF544;
extern SMPA D_002BF530;
extern CLOCK D_002DDED0;
}
static inline qword Transfer(qword a){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(a));return r;}
static inline qword Divide(qword a,qword s){qword r;__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(a),"j"(s));return r;}
static inline qword ResolvedUnit(qword value,qword length,float magnitude,float epsilon,qword fallback){if(magnitude<epsilon)return fallback;return Divide(value,length);}
extern "C" void func_0018FC60(P*p){
 WORK w;register float radialReturn __asm__("$f0");register float distance __asm__("$f22"),radial __asm__("$f23"),drag __asm__("$f20"),bias __asm__("$f21"),nextDistance __asm__("$f20");
 {
  register qword anchor __asm__("$2")=func_001A62E8(p->target);
  register NODE*target __asm__("$4");
  __asm__("lw %0,%1":"=r"(target):"m"(p->target));
  w.anchor.q=anchor;
  register M4*matrix __asm__("$2")=func_001A6318(target);
  register void*(*getSpace)(void*,void*) __asm__("$2");register int adjustment __asm__("$4");register void*nullSpace __asm__("$5");register NODE*selected __asm__("$6");
  __asm__("lq $4,0(%5)\n\tdaddu %2,$zero,$zero\n\tlw %3,0x18c4(%6)\n\tsq $4,0x40(%7)\n\tlq $3,0x10(%5)\n\tsq $3,0x50(%7)\n\tlq $4,0x20(%5)\n\tsq $4,0x60(%7)\n\tlw $3,0xc(%3)\n\tlh %1,0x100($3)\n\tlw %0,0x104($3)":"=r"(getSpace),"=r"(adjustment),"=r"(nullSpace),"=r"(selected),"=m"(w.anchorBasis):"r"(matrix),"r"(p),"p"(&w):"$3","memory");
  register void*space __asm__("$2")=getSpace((char*)selected+adjustment,nullSpace);
  w.anchorVelocity.q=func_0022D348(space,0,w.anchor.q);
 }
 {
  register qword position __asm__("$2")=func_001A62E8(p);
  register qword difference __asm__("vf3"),length __asm__("vf2");register U*up __asm__("$2");
  register float lengthValue __asm__("$f0"),epsilon __asm__("$f1");
  __asm__("qmtc2.ni %7,$vf2\n\tlui $3,%%hi(%9)\n\tlqc2 $vf1,%8\n\taddiu %2,$3,%%lo(%9)\n\tvsub.xyzw %0,$vf2,$vf1\n\t.set noat\n\tlui $1,0x38d1\n\tori $1,$1,0xb717\n\tmtc1 $1,%4\n\t.set at\n\tvmul.xyz $vf1,%0,%0\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf2,$vf1z\n\tsqc2 %0,%5\n\tvsqrt Q,$vf1x\n\tvwaitq\n\tvaddq.x %1,$vf0,Q\n\tsqc2 %0,%6\n\tqmfc2.ni $3,%1\n\tmtc1 $3,%3":"=j"(difference),"=j"(length),"=r"(up),"=f"(lengthValue),"=f"(epsilon),"=m"(w.axis.q),"=m"(w.displacement.q):"r"(position),"m"(w.anchor.q),"i"(&D_002A2DC0):"$1","$3","vf1");
  if(lengthValue<epsilon){register qword fallback __asm__("$2")=up->q;w.axis.q=fallback;}
  else{register qword normalized __asm__("vf1")=Divide(difference,length);w.axis.q=normalized;}
  register VTE*vtable __asm__("$3");
  __asm__("lw %0,%2\n\tqmfc2.ni $4,%3\n\tmtc1 $4,%1":"=r"(vtable),"=f"(distance):"m"(p->vt),"j"(length):"$4");
  register int adjustment __asm__("$4");register qword(*getVelocity)(void*) __asm__("$2");
  __asm__("lh %0,0x108(%2)\n\tlw %1,0x10c(%2)":"=r"(adjustment),"=r"(getVelocity):"r"(vtable));
  register qword returned __asm__("$2")=getVelocity((char*)p+adjustment);
  register qword relative __asm__("vf2"),relativeArgument __asm__("$4"),axisArgument __asm__("$5");
  register qword*parallel __asm__("$6"),*perpendicular __asm__("$7");
  __asm__("qmtc2.ni %5,$vf3\n\tlq %2,%6\n\tlqc2 $vf1,%7\n\taddiu %3,%8,0x90\n\tvsub.xyzw %0,$vf3,$vf1\n\taddiu %4,%8,0x80\n\tqmfc2.ni %1,%0":"=j"(relative),"=r"(relativeArgument),"=r"(axisArgument),"=r"(parallel),"=r"(perpendicular):"r"(returned),"m"(w.axis.q),"m"(w.anchorVelocity.q),"p"(&w):"vf1","vf3");
  w.relative.q=relative;
  radialReturn=func_0011E290(relativeArgument,axisArgument,parallel,perpendicular);
 }
 {
  /* 11E290 leaves the full relative vector in native VF3. */
  register qword cross __asm__("vf3");register unsigned firstHigh __asm__("$2");
  __asm__("lqc2 $vf2,%3\n\tmov.s %1,%5\n\tlqc2 $vf1,%4\n\tlui %2,%%hi(%6)\n\tvopmula.xyz ACC,$vf2,$vf1\n\tvopmsub.xyz %0,$vf1,$vf2":"+j"(cross),"=f"(radial),"=r"(firstHigh):"m"(w.axis.q),"m"(w.perpendicular.q),"f"(radialReturn),"i"(&D_002A2DA0):"vf1","vf2");
  register qword length __asm__("vf1"),fallback __asm__("$2");register float magnitude __asm__("$f0"),epsilon __asm__("$f1");
  __asm__(".set noat\n\tlui $1,0x38d1\n\tori $1,$1,0xb717\n\tmtc1 $1,%2\n\t.set at\n\tvmul.xyz %0,%4,%4\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,$vf2,%0z\n\taddiu %3,%5,%%lo(%6)\n\tvsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q\n\tlq %3,0(%3)\n\tqmfc2.ni $3,%0\n\tmtc1 $3,%1":"=j"(length),"=f"(magnitude),"=f"(epsilon),"=r"(fallback):"j"(cross),"r"(firstHigh),"i"(&D_002A2DA0):"$1","$3","vf2","memory");
  register qword firstAxis __asm__("vf4")=ResolvedUnit(cross,length,magnitude,epsilon,fallback);
  register unsigned secondHigh __asm__("$2");register qword perpendicularLength __asm__("vf1");
  __asm__("lqc2 %0,%3\n\tlui %1,%%hi(%5)\n\tvmul.xyz %0,%0,%0\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,$vf2,%0z\n\tsqc2 %4,%2\n\tvsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(perpendicularLength),"=r"(secondHigh),"=m"(w.firstAxis.q):"m"(w.perpendicular.q),"j"(firstAxis),"i"(&D_002A2DB0):"vf2");
  register qword radialAxis __asm__("vf3");register float speed __asm__("$f0"),ratio __asm__("$f4");register ACCEL*accel __asm__("$3");
  __asm__("lqc2 %0,%4\n\tqmfc2.ni $4,%5\n\t.set noat\n\tlui $1,0x38d1\n\tori $1,$1,0xb717\n\tmtc1 $1,%2\n\t.set at\n\tmtc1 $4,%1\n\tlw %3,%6":"=j"(radialAxis),"=f"(speed),"=f"(epsilon),"=r"(accel):"m"(w.axis.q),"j"(perpendicularLength),"m"(p->accel):"$1","$4");
  register U*secondFallback __asm__("$2");
  __asm__("div.s %0,%4,%5\n\taddiu %1,%6,%%lo(%7)\n\tmfc1 $4,%0\n\tqmtc2.ni $4,$vf1\n\tvmulx.xyzw $vf2,%8,$vf1x\n\tsqc2 $vf1,%2\n\tsqc2 $vf2,%3":"=f"(ratio),"=r"(secondFallback),"=m"(w.temporary.q),"=m"(w.angularFirst.q):"f"(speed),"f"(distance),"r"(secondHigh),"i"(&D_002A2DB0),"j"(firstAxis):"$4","vf1","vf2");
  register qword fallbackSecond __asm__("$2");
  __asm__("lqc2 $vf2,0x80(%3)\n\tvmul.xyz $vf1,$vf2,%4\n\tvaddw.x %0,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,%0,$vf1z\n\tlq %1,0(%5)\n\tvmulx.xyzw $vf1,%4,$vf1x\n\tvsub.xyzw $vf2,$vf2,$vf1\n\tvopmula.xyz ACC,%4,$vf2\n\tvopmsub.xyz %0,$vf2,%4\n\tsqc2 $vf2,%2":"+j"(firstAxis),"=r"(fallbackSecond),"=m"(w.temporary.q):"r"(accel),"j"(radialAxis),"r"(secondFallback):"vf1","vf2","memory");
  __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x $vf3,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,$vf3,%0z\n\tvsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q\n\tqmfc2.ni $3,%0\n\tmtc1 $3,%1":"=j"(length),"=f"(magnitude):"j"(firstAxis):"$3","vf3");
  register qword secondAxis __asm__("vf3")=ResolvedUnit(firstAxis,length,magnitude,epsilon,fallbackSecond);
  register unsigned polynomialHigh __asm__("$2");register POLY*polynomial __asm__("$3");register long normWord __asm__("$4");
  register float coefficientProduct __asm__("$f1"),polynomialTerm __asm__("$f2"),acceleration __asm__("$f0"),constant __asm__("$f3");
  __asm__("lui %0,%%hi(%5)\n\tlqc2 $vf1,%4\n\taddiu %1,%0,%%lo(%5)\n\tvmul.xyz $vf1,$vf1,$vf1\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf2,$vf1z\n\tlwc1 %2,8(%1)\n\tvsqrt Q,$vf1x\n\tvwaitq\n\tvaddq.x $vf1,$vf0,Q\n\tqmfc2.ni %3,$vf1":"=r"(polynomialHigh),"=r"(polynomial),"=f"(coefficientProduct),"=r"(normWord):"m"(w.temporary.q),"i"(&D_002BF4F0):"vf1","vf2","memory");
  __asm__("lwc1 %0,4(%3)\n\tmul.s %1,%4,%1\n\tmtc1 %5,%2":"=f"(polynomialTerm),"+f"(coefficientProduct),"=f"(acceleration):"r"(polynomial),"f"(ratio),"r"(normWord):"memory");
  __asm__("div.s %0,%0,%2\n\tlwc1 %1,%%lo(%4)(%3)":"+f"(acceleration),"=f"(constant):"f"(distance),"r"(polynomialHigh),"i"(&D_002BF4F0):"memory");
  register float lower __asm__("$f5"),upper __asm__("$f1");
  __asm__("lui $2,%%hi(%6)\n\tadd.s %0,%0,%4\n\tlwc1 %1,%%lo(%6)($2)\n\taddiu $2,$2,%%lo(%6)\n\tlwc1 %2,4($2)\n\tmul.s %0,%5,%0\n\tsqc2 %7,%3":"+f"(polynomialTerm),"=f"(lower),"=f"(upper),"=m"(w.secondAxis.q):"f"(coefficientProduct),"f"(ratio),"i"(&D_002BF500),"j"(secondAxis):"$2","memory");
  register qword accelerationScalar __asm__("vf2");
  __asm__("mfc1 $3,%0\n\tqmtc2.ni $3,%1\n\tadd.s %0,%3,%4\n\tvmulx.xyzw $vf1,%5,%1x\n\tsqc2 $vf1,%2":"+f"(acceleration),"=j"(accelerationScalar),"=m"(w.angularSecond.q):"f"(constant),"f"(polynomialTerm),"j"(secondAxis):"$3","vf1");
  w.angular.q=accelerationScalar;
  if(acceleration<lower)drag=lower;else if(upper<acceleration)drag=upper;else drag=acceleration;
 }
 if(p->state==0||p->state==2)bias=D_002BF508;else bias=D_002BF50C;
 register unsigned clockBase __asm__("$16"),clockHigh __asm__("$19");
 {
  register qword first __asm__("vf2"),second __asm__("vf1"),basisArgument __asm__("$5");
  __asm__("lui %0,%%hi(%8)\n\tlqc2 %1,%5\n\tdaddu %2,%0,$zero\n\tlqc2 %3,%6\n\taddiu %0,%0,%%lo(%8)\n\tlq %4,%7":"=r"(clockBase),"=j"(second),"=r"(clockHigh),"=j"(first),"=r"(basisArgument):"m"(w.angularSecond.q),"m"(w.angularFirst.q),"m"(w.anchorBasis.r[1].q),"i"(&D_002DDED0));
  register qword argument __asm__("$4");register qword*parallel __asm__("$6"),*perpendicular __asm__("$7");
  __asm__("lw %0,4(%5)\n\taddiu %1,%6,0x100\n\tqmtc2.ni %0,$vf3\n\taddiu %2,%6,0x110\n\tvadda.xyzw ACC,%3,$vf0\n\tvmaddx.xyzw %3,%7,$vf3x\n\tsqc2 $vf3,%4\n\tqmfc2.ni %0,%3":"=r"(argument),"=r"(parallel),"=r"(perpendicular),"+j"(first),"=m"(w.velocity.q):"r"(clockBase),"p"(&w),"j"(second):"vf3","memory");
  w.angular.q=first;
  func_0011E290(argument,basisArgument,parallel,perpendicular);
 }
 register int blendState __asm__("$3");register float blendDt __asm__("$f3"),one __asm__("$f2"),firstWeight __asm__("$f1"),secondWeight __asm__("$f0");
 __asm__("lwc1 %0,4(%5)\n\t.set noat\n\tlui $1,0x3f80\n\tmtc1 $1,%1\n\t.set at\n\tmul.s %2,%6,%0\n\tlw %4,%8\n\tmul.s %3,%7,%0":"=f"(blendDt),"=f"(one),"=f"(firstWeight),"=f"(secondWeight),"=r"(blendState):"r"(clockBase),"f"(drag),"f"(bias),"m"(p->state):"$1","memory");
 {
  register qword angular __asm__("vf1");
  __asm__("lqc2 $vf4,%4\n\tlqc2 $vf3,%5\n\tadd.s %2,%2,%6\n\tadd.s %3,%3,%6\n\tmfc1 $2,%2\n\tqmtc2.ni $2,%0\n\tmfc1 $4,%3\n\tqmtc2.ni $4,$vf2\n\tsqc2 %0,%1\n\tvmulax.xyzw ACC,$vf4,%0x\n\tvmaddx.xyzw %0,$vf3,$vf2x\n\tsqc2 $vf2,%1":"=j"(angular),"=m"(w.velocity.q),"+f"(firstWeight),"+f"(secondWeight):"m"(w.parallelAngular.q),"m"(w.perpendicularAngular.q),"f"(one):"$2","$4","vf2","vf3","vf4");
  w.angular.q=angular;
 }
 if(blendState==0||blendState==2){
  register float elapsed __asm__("$f0"),window __asm__("$f2");
  __asm__("lwc1 %0,%%lo(%4)(%2)\n\tlui $2,%%hi(%5)\n\tlwc1 $f1,%3\n\tlwc1 %1,%%lo(%5)($2)\n\tsub.s %0,%0,$f1":"=f"(elapsed),"=f"(window):"r"(clockHigh),"m"(p->stamp),"i"(&D_002DDED0),"i"(&D_002BF510):"$2","$f1","memory");
  if(elapsed<window){
   register float rate __asm__("$f0")=D_002BF514;
   register float amount __asm__("$f6")=blendDt*rate;
   if(blendState==0)amount=-amount;
   if(p->reverse)amount=-amount;
   register unsigned polynomialHigh __asm__("$4");register POLY*polynomial __asm__("$3");
   register float down __asm__("$f5"),halfSpeed __asm__("$f1"),speed __asm__("$f3");
   __asm__("lw $2,%5\n\tlui %0,%%hi(%7)\n\tlqc2 $vf1,%6\n\taddiu %1,%0,%%lo(%7)\n\tvmul.xyz $vf1,$vf1,$vf1\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf2,$vf1z\n\tlwc1 %2,0x88($2)\n\tvsqrt Q,$vf1x\n\tvwaitq\n\tvaddq.x $vf1,$vf0,Q\n\t.set noat\n\tlui $1,0x3f00\n\tmtc1 $1,%3\n\t.set at\n\tqmfc2.ni $2,$vf1\n\tneg.s %2,%2\n\tmtc1 $2,%4":"=r"(polynomialHigh),"=r"(polynomial),"=f"(down),"=f"(halfSpeed),"=f"(speed):"m"(p->accel),"m"(w.perpendicular.q),"i"(&D_002BF520):"$1","$2","vf1","vf2","memory");
   register float numerator __asm__("$f0"),coefficient __asm__("$f4"),term __asm__("$f2");
   __asm__("lwc1 %0,%4\n\tmul.s %1,%5,%1\n\tlwc1 %2,8(%7)\n\tmul.s %0,%6,%0\n\tlwc1 %3,4(%7)":"=f"(numerator),"+f"(halfSpeed),"=f"(coefficient),"=f"(term):"m"(w.displacement.f[2]),"f"(speed),"f"(down),"r"(polynomial):"memory");
   register CLAMP*limits __asm__("$2");register float lower __asm__("$f7"),value __asm__("$f1");
   __asm__("lui %0,%%hi(%7)\n\tmul.s %1,%1,%4\n\tlwc1 %2,%%lo(%7)(%0)\n\tlwc1 %3,%%lo(%6)(%5)\n\taddiu %0,%0,%%lo(%7)":"=r"(limits),"+f"(speed),"=f"(lower),"=f"(value):"f"(halfSpeed),"r"(polynomialHigh),"i"(&D_002BF520),"i"(&D_002BBB60):"memory");
   __asm__("add.s %0,%0,%4\n\tdiv.s %0,%0,%5\n\tmul.s %1,%0,%1\n\tadd.s %2,%2,%1\n\tmul.s %0,%0,%2\n\tadd.s %3,%3,%0":"+f"(numerator),"+f"(coefficient),"+f"(term),"+f"(value):"f"(speed),"f"(down));
   register float upper __asm__("$f8")=limits->high;
   if(value<lower)value=lower;else if(upper<value)value=upper;
   amount*=value;
   register qword angular __asm__("vf1");
   __asm__("lqc2 %0,%2\n\tlqc2 $vf2,%3\n\tmfc1 $3,%4\n\tqmtc2.ni $3,$vf3\n\tvadda.xyzw ACC,%0,$vf0\n\tvmaddx.xyzw %0,$vf2,$vf3x\n\tsqc2 $vf3,%1":"=j"(angular),"=m"(w.velocity.q):"m"(w.angular.q),"m"(w.anchorBasis.r[1].q),"f"(amount):"$3","vf2","vf3");
   w.angular.q=angular;
  }
 }
 register unsigned maximumHigh __asm__("$16"),sampleClock __asm__("$18");
 {
  register float maximum __asm__("$f0"),goal __asm__("$f14"),dt __asm__("$f15");register unsigned parameterAddress __asm__("$4");
  register NODE*sampleTarget __asm__("$2")=p->target;
  __asm__("lui %0,%%hi(%7)\n\tlwc1 %1,%%lo(%7)(%0)\n\taddiu %2,%6,%%lo(%8)\n\tlwc1 %3,0x134(%5)\n\tlui %4,%%hi(%9)":"=r"(maximumHigh),"=f"(maximum),"=r"(sampleClock),"=f"(goal),"=r"(parameterAddress):"r"(sampleTarget),"r"(clockHigh),"i"(&D_002BF544),"i"(&D_002DDED0),"i"(&D_002BF530):"memory");
  register float sampleRadial __asm__("$f13"),sampleDistance __asm__("$f12");
  __asm__("lwc1 %0,4(%2)\n\taddiu %1,%1,%%lo(%3)":"=f"(dt),"+r"(parameterAddress):"r"(sampleClock),"i"(&D_002BF530):"memory");
  __asm__("sub.s %0,%3,%0\n\tmov.s %1,%4\n\tmov.s %2,%5":"+f"(goal),"=f"(sampleRadial),"=f"(sampleDistance):"f"(maximum),"f"(radial),"f"(distance));
  register float*speedOutput __asm__("$5")=&w.speedOut;
  register float result __asm__("$f0")=func_0011D1C0(sampleDistance,sampleRadial,goal,dt,(SMPA*)parameterAddress,speedOutput);
  register float numerator __asm__("$f1"),denominator __asm__("$f0");register qword angular __asm__("vf2");
  __asm__("mov.s %0,%4\n\tlui $2,%%hi(%7)\n\tlwc1 %1,%%lo(%6)(%5)\n\tlwc1 %2,%%lo(%7)($2)\n\tmin.s %1,%1,%8\n\tlqc2 %3,%9\n\tmax.s %2,%2,%0":"=f"(nextDistance),"=f"(numerator),"=f"(denominator),"=j"(angular):"f"(result),"r"(maximumHigh),"i"(&D_002BF544),"i"(&D_002BF540),"f"(distance),"m"(w.angular.q):"$2","memory");
  register LINK*other __asm__("$3");
  __asm__("lw %0,%4\n\tdiv.s %2,%2,%5\n\tmfc1 $4,%2\n\tqmtc2.ni $4,$vf1\n\tvmulx.xyzw %1,%1,$vf1x\n\tsqc2 $vf1,%3":"=r"(other),"+j"(angular),"+f"(numerator),"=m"(w.velocity.q):"m"(p->other),"f"(denominator):"$4","vf1");
  w.angular.q=angular;
  if(other){
   register NODE*otherActor __asm__("$4");register U*zero __asm__("$2");
   /* The raw dt publication retains native V1 upper bits; only X scales vectors. */
   register qword dtWord __asm__("$3");
   __asm__("lw %0,4(%4)\n\tlui %1,%%hi(%6)\n\tlw %2,4(%5)\n\taddiu %1,%1,%%lo(%6)\n\tsq %2,%3":"=r"(otherActor),"=r"(zero),"+r"(dtWord),"=m"(w.dtScalar.q):"r"(other),"r"(sampleClock),"i"(&D_002A2DD0):"memory");
   __asm__("lqc2 $vf1,%5\n\tlqc2 $vf2,0(%7)\n\tlq $2,%6\n\tsqc2 $vf1,%0\n\tsqc2 $vf2,%1\n\tsqc2 $vf2,%2\n\tsqc2 $vf2,%3\n\tsq $2,%4":"=m"(w.savedPoint.q),"=m"(w.state.direction.q),"=m"(w.state.position.q),"=m"(w.savedAngular.q),"=m"(w.savedVelocity.q):"m"(w.anchor.q),"m"(w.anchorVelocity.q),"r"(zero):"$2","vf1","vf2");
   w.state.velocity.q=dtWord;
   register qword returned __asm__("$2")=func_001A62E8(otherActor);
   register qword desired __asm__("vf1");
   __asm__("lqc2 %0,%2\n\tqmtc2.ni %1,$vf3\n\tlqc2 $vf2,%3\n\tvsub.xyzw %0,%0,$vf3\n\tvopmula.xyz ACC,$vf2,%0\n\tvopmsub.xyz %0,%0,$vf2\n\tlqc2 $vf4,%4\n\tlqc2 $vf5,%5\n\tvadda.xyzw ACC,$vf4,$vf0\n\tvmaddax.xyzw ACC,$vf2,$vf5x\n\tvmaddx.xyzw %0,%0,$vf5x":"=j"(desired):"r"(returned),"m"(w.savedPoint.q),"m"(w.savedAngular.q),"m"(w.savedVelocity.q),"m"(w.dtScalar.q):"vf2","vf3","vf4","vf5");
   w.velocity.q=desired;
  }else w.velocity=w.anchorVelocity;
 }
 register unsigned clockWord __asm__("$16");
 __asm__("addiu %0,%1,%%lo(%2)":"=r"(clockWord):"r"(clockHigh),"i"(&D_002DDED0));
 {
  register qword turn __asm__("vf1");register M3*result __asm__("$4");
  __asm__(".set noat\n\tlui $1,0x3f00\n\tmtc1 $1,$f1\n\t.set at\n\tlwc1 $f0,4(%3)\n\taddiu %0,%4,0x190\n\tlqc2 $vf1,0xf0(%4)\n\tmul.s $f0,$f0,$f1\n\tlqc2 $vf2,0xb0(%4)\n\tvadd.xyzw $vf2,$vf2,$vf1\n\tmfc1 $2,$f0\n\tqmtc2.ni $2,$vf3\n\tvmulx.xyzw %1,$vf2,$vf3x\n\tsqc2 $vf3,%2":"=r"(result),"=j"(turn),"=m"(w.halfScalar.q):"r"(clockWord),"p"(&w):"$1","$2","$f0","$f1","vf2","vf3","memory");
  new(result)M3(func_0011B570(turn));
 }
 {
  register qword row0 __asm__("vf10"),row1 __asm__("vf9"),row2 __asm__("vf8"),axis __asm__("vf4"),radiusScalar __asm__("vf7");
  __asm__("lqc2 %0,%5\n\tlqc2 %1,%6\n\tlqc2 %2,%7\n\tmfc1 $2,%9\n\tlqc2 %3,%8\n\tqmtc2.ni $2,%4":"=j"(row0),"=j"(row1),"=j"(row2),"=j"(axis),"=j"(radiusScalar):"m"(w.rotation.r[0].q),"m"(w.rotation.r[1].q),"m"(w.rotation.r[2].q),"m"(w.axis.q),"f"(nextDistance):"$2");
  __asm__("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(axis):"j"(row0),"j"(row1),"j"(row2));
  register qword radius __asm__("vf6"),speedScalar __asm__("vf11"),cross __asm__("vf2");
  __asm__("lw $3,%5\n\tvmulx.xyzw %0,%3,%4x\n\tlqc2 %2,%6\n\tqmtc2.ni $3,%1\n\tvopmula.xyz ACC,%2,%0\n\tvopmsub.xyz %2,%0,%2":"=j"(radius),"=j"(speedScalar),"=j"(cross):"j"(axis),"j"(radiusScalar),"m"(w.speedOut),"m"(w.angular.q):"$3");
  register qword velocity __asm__("vf3"),position __asm__("vf1");
  __asm__("lqc2 %0,%5\n\tvmulx.xyzw $vf5,%2,%3x\n\tvadd.xyzw %0,%0,%4\n\tlqc2 %1,%6\n\tvadd.xyzw %0,%0,$vf5\n\tvadd.xyzw %1,%1,%7":"=j"(velocity),"=j"(position):"j"(axis),"j"(speedScalar),"j"(cross),"m"(w.velocity.q),"m"(w.anchor.q),"j"(radius):"vf5");
  __asm__("sqc2 %2,0x140(%1)\n\tsqc2 %3,0x150(%1)\n\tsqc2 %4,0x160(%1)\n\tsqc2 %5,0x170(%1)\n\tsqc2 %6,0x180(%1)\n\tsqc2 %7,0x130(%1)":"=m"(w.state):"p"(&w),"j"(position),"j"(velocity),"j"(row0),"j"(row1),"j"(row2),"j"(axis));
  register void*receiver __asm__("$4");register qword(*getVelocity)(void*) __asm__("$2");
  __asm__("lw $3,%4\n\tsqc2 %6,%2\n\tlh %0,0x108($3)\n\tlw %1,0x10c($3)\n\tsqc2 %7,%3\n\taddu %0,%5,%0":"=r"(receiver),"=r"(getVelocity),"=m"(w.rotation.r[0].q),"=m"(w.finalVelocity.q):"m"(p->vt),"r"(p),"j"(radiusScalar),"j"(velocity):"$3","memory");
  ((U*)&w.rotation)->q=speedScalar;
  register qword current __asm__("$2")=getVelocity(receiver);
  register LINK*other __asm__("$3");register qword correction __asm__("vf1");
  __asm__("lw %0,4(%0)\n\tqmtc2.ni %4,$vf1\n\tlw %1,0x1900(%5)\n\tqmtc2.ni %0,$vf2\n\tsqc2 $vf2,%2\n\tlqc2 $vf3,%6\n\tvsub.xyzw $vf3,$vf3,$vf1\n\tlw $2,0xe8(%5)\n\tvdiv Q,$vf0w,$vf2x\n\tvwaitq\n\tvmulq.xyzw $vf2,$vf3,Q\n\tlqc2 %3,0x80($2)\n\tvsub.xyzw %3,$vf2,%3":"+r"(clockWord),"=r"(other),"=m"(w.rotation.r[0].q),"=j"(correction):"r"(current),"r"(p),"m"(w.finalVelocity.q):"$2","vf2","vf3","memory");
  w.temporary.q=correction;
  if(other)func_0018F958(p,other->object,&w.anchor.q,&w.temporary.f[0],p->response);
  else p->response[0].first=w.temporary;
 }
}

typedef char layout_size_qword[(sizeof(qword)==16)?1:-1];
typedef char layout_size_voidpointer[(sizeof(void*)==4)?1:-1];
typedef char layout_size_U[(sizeof(U)==16)?1:-1];
typedef char layout_size_M3[(sizeof(M3)==48)?1:-1];
typedef char layout_size_M4[(sizeof(M4)==64)?1:-1];
typedef char layout_size_VTE[(sizeof(VTE)==8)?1:-1];
typedef char layout_size_NODE[(sizeof(NODE)==0x138)?1:-1];
typedef char layout_size_ACCEL[(sizeof(ACCEL)==0x90)?1:-1];
typedef char layout_size_LINK[(sizeof(LINK)==8)?1:-1];
typedef char layout_size_DELTA[(sizeof(DELTA)==32)?1:-1];
typedef char layout_size_P[(sizeof(P)==0x1950)?1:-1];
typedef char layout_size_POLY[(sizeof(POLY)==12)?1:-1];
typedef char layout_size_CLAMP[(sizeof(CLAMP)==8)?1:-1];
typedef char layout_size_SMPA[(sizeof(SMPA)==16)?1:-1];
typedef char layout_size_CLOCK[(sizeof(CLOCK)==8)?1:-1];
typedef char layout_size_STATE[(sizeof(STATE)==0x60)?1:-1];
typedef char layout_size_WORK[(sizeof(WORK)==0x230)?1:-1];
typedef char layout_VTE_delta[((unsigned long)&((VTE*)0)->delta==0x0)?1:-1];
typedef char layout_VTE_fn[((unsigned long)&((VTE*)0)->fn==0x4)?1:-1];
typedef char layout_NODE_vt[((unsigned long)&((NODE*)0)->vt==0xc)?1:-1];
typedef char layout_NODE_property[((unsigned long)&((NODE*)0)->property==0x134)?1:-1];
typedef char layout_ACCEL_value[((unsigned long)&((ACCEL*)0)->value==0x80)?1:-1];
typedef char layout_LINK_object[((unsigned long)&((LINK*)0)->object==0x4)?1:-1];
typedef char layout_DELTA_first[((unsigned long)&((DELTA*)0)->first==0x0)?1:-1];
typedef char layout_DELTA_second[((unsigned long)&((DELTA*)0)->second==0x10)?1:-1];
typedef char layout_P_vt[((unsigned long)&((P*)0)->vt==0xc)?1:-1];
typedef char layout_P_accel[((unsigned long)&((P*)0)->accel==0xe8)?1:-1];
typedef char layout_P_target[((unsigned long)&((P*)0)->target==0x18c4)?1:-1];
typedef char layout_P_state[((unsigned long)&((P*)0)->state==0x18d0)?1:-1];
typedef char layout_P_stamp[((unsigned long)&((P*)0)->stamp==0x18d4)?1:-1];
typedef char layout_P_reverse[((unsigned long)&((P*)0)->reverse==0x18fc)?1:-1];
typedef char layout_P_other[((unsigned long)&((P*)0)->other==0x1900)?1:-1];
typedef char layout_P_response[((unsigned long)&((P*)0)->response==0x1910)?1:-1];
typedef char layout_POLY_a[((unsigned long)&((POLY*)0)->a==0x0)?1:-1];
typedef char layout_POLY_b[((unsigned long)&((POLY*)0)->b==0x4)?1:-1];
typedef char layout_POLY_c[((unsigned long)&((POLY*)0)->c==0x8)?1:-1];
typedef char layout_CLAMP_low[((unsigned long)&((CLAMP*)0)->low==0x0)?1:-1];
typedef char layout_CLAMP_high[((unsigned long)&((CLAMP*)0)->high==0x4)?1:-1];
typedef char layout_SMPA_a[((unsigned long)&((SMPA*)0)->a==0x0)?1:-1];
typedef char layout_SMPA_b[((unsigned long)&((SMPA*)0)->b==0x4)?1:-1];
typedef char layout_SMPA_duration[((unsigned long)&((SMPA*)0)->duration==0x8)?1:-1];
typedef char layout_SMPA_limit[((unsigned long)&((SMPA*)0)->limit==0xc)?1:-1];
typedef char layout_CLOCK_time[((unsigned long)&((CLOCK*)0)->time==0x0)?1:-1];
typedef char layout_CLOCK_dt[((unsigned long)&((CLOCK*)0)->dt==0x4)?1:-1];
typedef char layout_STATE_direction[((unsigned long)&((STATE*)0)->direction==0x0)?1:-1];
typedef char layout_STATE_position[((unsigned long)&((STATE*)0)->position==0x10)?1:-1];
typedef char layout_STATE_velocity[((unsigned long)&((STATE*)0)->velocity==0x20)?1:-1];
typedef char layout_STATE_rotation[((unsigned long)&((STATE*)0)->rotation==0x30)?1:-1];
typedef char layout_WORK_anchor[((unsigned long)&((WORK*)0)->anchor==0x0)?1:-1];
typedef char layout_WORK_displacement[((unsigned long)&((WORK*)0)->displacement==0x10)?1:-1];
typedef char layout_WORK_anchorVelocity[((unsigned long)&((WORK*)0)->anchorVelocity==0x20)?1:-1];
typedef char layout_WORK_axis[((unsigned long)&((WORK*)0)->axis==0x30)?1:-1];
typedef char layout_WORK_anchorBasis[((unsigned long)&((WORK*)0)->anchorBasis==0x40)?1:-1];
typedef char layout_WORK_relative[((unsigned long)&((WORK*)0)->relative==0x70)?1:-1];
typedef char layout_WORK_perpendicular[((unsigned long)&((WORK*)0)->perpendicular==0x80)?1:-1];
typedef char layout_WORK_parallel[((unsigned long)&((WORK*)0)->parallel==0x90)?1:-1];
typedef char layout_WORK_firstAxis[((unsigned long)&((WORK*)0)->firstAxis==0xa0)?1:-1];
typedef char layout_WORK_angularFirst[((unsigned long)&((WORK*)0)->angularFirst==0xb0)?1:-1];
typedef char layout_WORK_temporary[((unsigned long)&((WORK*)0)->temporary==0xc0)?1:-1];
typedef char layout_WORK_secondAxis[((unsigned long)&((WORK*)0)->secondAxis==0xd0)?1:-1];
typedef char layout_WORK_angularSecond[((unsigned long)&((WORK*)0)->angularSecond==0xe0)?1:-1];
typedef char layout_WORK_angular[((unsigned long)&((WORK*)0)->angular==0xf0)?1:-1];
typedef char layout_WORK_parallelAngular[((unsigned long)&((WORK*)0)->parallelAngular==0x100)?1:-1];
typedef char layout_WORK_perpendicularAngular[((unsigned long)&((WORK*)0)->perpendicularAngular==0x110)?1:-1];
typedef char layout_WORK_velocity[((unsigned long)&((WORK*)0)->velocity==0x120)?1:-1];
typedef char layout_WORK_state[((unsigned long)&((WORK*)0)->state==0x130)?1:-1];
typedef char layout_WORK_rotation[((unsigned long)&((WORK*)0)->rotation==0x190)?1:-1];
typedef char layout_WORK_halfScalar[((unsigned long)&((WORK*)0)->halfScalar==0x1c0)?1:-1];
typedef char layout_WORK_speedOut[((unsigned long)&((WORK*)0)->speedOut==0x1d0)?1:-1];
typedef char layout_WORK_savedVelocity[((unsigned long)&((WORK*)0)->savedVelocity==0x1e0)?1:-1];
typedef char layout_WORK_dtScalar[((unsigned long)&((WORK*)0)->dtScalar==0x1f0)?1:-1];
typedef char layout_WORK_savedPoint[((unsigned long)&((WORK*)0)->savedPoint==0x200)?1:-1];
typedef char layout_WORK_savedAngular[((unsigned long)&((WORK*)0)->savedAngular==0x210)?1:-1];
typedef char layout_WORK_finalVelocity[((unsigned long)&((WORK*)0)->finalVelocity==0x220)?1:-1];
