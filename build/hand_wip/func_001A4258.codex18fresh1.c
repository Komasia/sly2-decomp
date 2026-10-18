
typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];} U;
struct SP {qword p;float radius;};
static inline float SphereDistance(const struct SP*sp,qword pos,float radius,float*sum){
 register float raw __asm__("$2"),combined __asm__("$f0");
 __asm__("lqc2 $vf1,%2\n\tlwc1 %1,%3\n\tvsub.xyzw $vf1,%4,$vf1\n\tvmul.xyz $vf1,$vf1,$vf1\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x $ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf2,$vf1z\n\tvsqrt Q,$vf1x\n\tvwaitq\n\tvaddq.x $vf1,$vf0,Q\n\tadd.s %1,%5,%1\n\tqmfc2.ni %0,$vf1":"=r"(raw),"=&f"(combined):"m"(sp->p),"m"(sp->radius),"j"(pos),"f"(radius):"vf1","vf2");
 *sum=combined;return raw;
}
int func_001A4258(qword pos,float radius,int count,struct SP*points){
 U scalar;int i=0;
 if(i<count){register qword p __asm__("vf3")=pos;do{float sum;float distance=SphereDistance(&points[i],p,radius,&sum);if(distance<sum)return 1;}while(++i<count);}
 i=1;
 if(i<count){register float one __asm__("$f5")=1.0f;register qword p __asm__("vf10")=pos;do{
  register qword a __asm__("vf6"),b __asm__("vf5"),d __asm__("vf4"),axis __asm__("vf1");
  register qword lengthVector __asm__("vf2"),perpendicular __asm__("vf2");
  register float ra __asm__("$f3"),rb __asm__("$f4");
  register float rawLength __asm__("$2"),length __asm__("$f0"),slope __asm__("$f2"),squaredSlope __asm__("$f0");
  __asm__("lqc2 %0,%4\n\tlqc2 %1,%5\n\tvsub.xyzw %2,%6,%0\n\tvsub.xyzw %3,%1,%0":"=&j"(a),"=&j"(b),"=j"(d),"=j"(axis):"m"(points[0].p),"m"(points[1].p),"j"(p));
  __asm__("lwc1 %0,%4\n\tvmul.xyz %2,%3,%3\n\tvaddw.x $vf3,$vf0,$vf0w\n\tvadday.x $ACC,%2,%2y\n\tvmaddz.x %2,$vf3,%2z\n\tlwc1 %1,%5\n\tvsqrt Q,%2x\n\tvwaitq\n\tvaddq.x %2,$vf0,Q":"=f"(ra),"=f"(rb),"=&j"(lengthVector):"j"(axis),"m"(points[0].radius),"m"(points[1].radius):"vf3");
  __asm__("vopmula.xyz $ACC,%0,%3\n\tvopmsub.xyz %0,%3,%0\n\tqmfc2.ni %1,%4\n\tsub.s %2,%5,%6":"+&j"(d),"=r"(rawLength),"=f"(slope):"j"(axis),"j"(lengthVector),"f"(ra),"f"(rb));
  __asm__("mtc1 %3,%1\n\tqmtc2.ni %3,$vf3\n\tvdiv Q,$vf0w,$vf3x\n\tvwaitq\n\tvmulq.xyzw %0,%0,Q\n\tsqc2 $vf3,%2":"+j"(axis),"=f"(length),"=m"(scalar.q):"r"(rawLength):"vf3");
  __asm__("div.s %1,%1,%3\n\tvopmula.xyz $ACC,%2,%0\n\tvopmsub.xyz %0,%0,%2":"+j"(d),"+f"(slope):"j"(axis),"f"(length));
  __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x $vf3,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,$vf3,%0z\n\tvsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q\n\tvdiv Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q\n\tmul.s %1,%3,%3":"=&j"(perpendicular),"=f"(squaredSlope):"j"(d),"f"(slope):"vf3");
  {
   register float rootArgument __asm__("$f0")=one-squaredSlope;register float transverse __asm__("$f1");
   register qword factorA __asm__("vf9"),factorB __asm__("vf8"),relative __asm__("vf2");register float rawRadiusB __asm__("$2");
   __asm__("sqrt.s %0,%1":"=f"(transverse):"f"(rootArgument));
   __asm__("mfc1 %2,%5\n\tqmtc2.ni %2,$vf4\n\tmfc1 %2,%6\n\tqmtc2.ni %2,$vf7\n\tsqc2 $vf4,%3\n\tmfc1 %2,%7\n\tvmulax.xyzw $ACC,%0,$vf4x\n\tvmaddx.xyzw %0,%4,$vf7x\n\tqmtc2.ni %2,%1\n\tsqc2 $vf7,%3\n\tmfc1 %2,%8":"+j"(axis),"=j"(factorA),"=r"(rawRadiusB),"=m"(scalar.q):"j"(perpendicular),"f"(slope),"f"(transverse),"f"(ra),"f"(rb):"vf4","vf7");
   __asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(a):"j"(axis),"j"(factorA));
   __asm__("qmtc2.ni %4,%2\n\tvsub.xyzw %1,%5,%6\n\tvadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%7,%2x\n\tsqc2 %8,%3":"+&j"(b),"=&j"(relative),"=&j"(factorB),"=m"(scalar.q):"r"(rawRadiusB),"j"(p),"j"(a),"j"(axis),"j"(factorA));
   {
    register float rawDistance __asm__("$2"),distance __asm__("$f1"),rawNumerator __asm__("$2"),rawDenominator __asm__("$2");register qword squaredLine __asm__("vf3");
    __asm__("vmul.xyz %0,%3,%0\n\tvaddw.x $vf3,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,$vf3,%0z\n\tvsub.xyzw %1,%1,%4\n\tqmfc2.ni %2,%0":"+&j"(axis),"+j"(b),"=r"(rawDistance):"j"(relative),"j"(a):"vf3");
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x $vf1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,$vf1,%0z\n\tmtc1 %3,%1":"=&j"(squaredLine),"=f"(distance):"j"(b),"r"(rawDistance):"vf1");
    __asm__("vmul.xyz %0,%0,%1\n\tvaddw.x $vf1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,$vf1,%0z":"+j"(relative):"j"(b):"vf1");
    __asm__("qmfc2.ni %0,%1":"=r"(rawNumerator):"j"(relative));
    {
     float numerator=rawNumerator,denominator;
     __asm__("sqc2 %2,%1\n\tqmfc2.ni %0,%3":"=r"(rawDenominator),"=m"(scalar.q):"j"(factorB),"j"(squaredLine));
     denominator=rawDenominator;numerator/=denominator;
     if(distance<radius){register float zero __asm__("$f0")=0.0f;if(numerator>=zero && numerator<=one)return 1;}
    }
   }
  }
 }while(points++,++i<count);}
 return 0;
}

typedef char layout_PointerWidth[(sizeof(void*)==4)?1:-1];
typedef char layout_IntegerWidth[(sizeof(int)==4)?1:-1];
typedef char layout_UnsignedWidth[(sizeof(unsigned)==4)?1:-1];
typedef char layout_FloatWidth[(sizeof(float)==4)?1:-1];
typedef char layout_QwordSize[(sizeof(qword)==16)?1:-1];
typedef char layout_QwordAlignment[(__alignof__(qword)==16)?1:-1];
typedef char layout_ScalarSize[(sizeof(U)==16)?1:-1];
typedef char layout_ScalarAlignment[(__alignof__(U)==16)?1:-1];
typedef char layout_ScalarQOffset[((unsigned)&((U*)0)->q==0)?1:-1];
typedef char layout_ScalarFloatsOffset[((unsigned)&((U*)0)->f==0)?1:-1];
typedef char layout_ScalarFloatSpan[(sizeof(((U*)0)->f)==16)?1:-1];
typedef char layout_SphereStride[(sizeof(struct SP)==32)?1:-1];
typedef char layout_SphereAlignment[(__alignof__(struct SP)==16)?1:-1];
typedef char layout_SpherePointOffset[((unsigned)&((struct SP*)0)->p==0)?1:-1];
typedef char layout_SphereRadiusOffset[((unsigned)&((struct SP*)0)->radius==16)?1:-1];
typedef char layout_SpherePointWidth[(sizeof(((struct SP*)0)->p)==16)?1:-1];
typedef char layout_SphereRadiusWidth[(sizeof(((struct SP*)0)->radius)==4)?1:-1];
