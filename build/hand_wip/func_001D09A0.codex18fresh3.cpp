// Turn the particle basis and damp velocity along its previous first axis.
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M3 {qword r[3];};
struct P {char pad40[0x40];M3 matrix;char pad70[0x20];qword velocity;char padA0[0x24];float drag;};
extern struct CLOCK {float t,dt;} D_002DDED0;
extern float D_002C2010[3],D_002C2020[2],D_002C2028,D_002C202C;
extern qword D_002A2DA0;
extern "C" M3 *func_0011B500(M3*,qword,float);
extern "C" float func_0011E290(qword,qword,qword*,qword*);
extern "C" void func_001CF0A0(P*);
static inline qword Dot(qword a,qword b){qword one;
 __asm__("vmul.xyz %0,%0,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(a),"=&j"(one):"j"(b));return a;}
static inline M3 TurnProduct(P*p,const M3&spin,M3&basis,float&drag,qword&velocityArgument,qword*&projectionFirst,qword*&projectionSecond) return r {
 register qword row0 __asm__("vf3"),row1 __asm__("vf6"),row2 __asm__("vf5");
 register M3*matrix __asm__("$2");register qword*first __asm__("$6"),*second __asm__("$7");
 __asm__("lqc2 %0,%7\n\taddiu %3,%6,0x40\n\tlqc2 %1,16+%7\n\tla %4,%a8\n\tlqc2 %2,32+%7\n\tla %5,%a9":"=j"(row0),"=j"(row1),"=j"(row2),"=&r"(matrix),"=&r"(first),"=r"(second):"r"(p),"m"(spin),"p"(&basis.r[0]),"p"(&basis.r[1]));
 register qword velocity __asm__("vf1"),c0 __asm__("vf4"),c1 __asm__("vf2");
 __asm__("lqc2 %0,%5\n\tlqc2 %1,%6\n\tvmulax.xyz ACC,%2,%0x\n\tvmadday.xyz ACC,%3,%0y\n\tvmaddz.xyz %0,%4,%0z":"=&j"(velocity),"=&j"(c0):"j"(row0),"j"(row1),"j"(row2),"m"(p->velocity),"m"(p->matrix.r[0]));
 __asm__("vmulax.xyz ACC,%2,%0x\n\tvmadday.xyz ACC,%3,%0y\n\tvmaddz.xyz %0,%4,%0z\n\tsqc2 %5,%1":"+&j"(c0),"=m"(p->velocity):"j"(row0),"j"(row1),"j"(row2),"j"(velocity));
 register float actualDrag __asm__("$f20");register qword packedVelocity __asm__("$4");
 __asm__("lwc1 %0,%3\n\tqmfc2.ni %1,%4\n\tsqc2 %5,%2":"=f"(actualDrag),"=&r"(packedVelocity),"=m"(basis.r[0]):"m"(p->drag),"j"(velocity),"j"(c0));
 r.r[0]=c0;
 __asm__("lqc2 %0,%5\n\tvmulax.xyz ACC,%2,%0x\n\tvmadday.xyz ACC,%3,%0y\n\tvmaddz.xyz %0,%4,%0z\n\tsqc2 %0,%1":"=&j"(c1),"=m"(basis.r[1]):"j"(row0),"j"(row1),"j"(row2),"m"(matrix->r[1]));
 r.r[1]=c1;
 register qword ownerThird __asm__("vf1");
 __asm__("lqc2 %1,%4\n\tvmulax.xyz ACC,%0,%1x\n\tvmadday.xyz ACC,%2,%1y\n\tvmaddz.xyz %0,%3,%1z":"+j"(row0),"=&j"(ownerThird):"j"(row1),"j"(row2),"m"(matrix->r[2]));
 r.r[2]=row0;basis.r[2]=row0;
 drag=actualDrag;velocityArgument=packedVelocity;projectionFirst=first;projectionSecond=second;
}
static inline qword LengthVector(qword q){qword d,one,length;
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(q));
 __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(length):"j"(d));return length;}
static inline qword Normalize(qword q,qword length){qword n;__asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(n):"j"(length),"j"(q));return n;}
static inline qword Blend(qword a,qword b,qword x,qword y){__asm__("vmulax.xyzw ACC,%0,%2x\n\tvmaddx.xyzw %0,%1,%3x":"+j"(a):"j"(b),"j"(x),"j"(y));return a;}
static inline qword PackedParallel(const qword *p){register qword q __asm__("$2");__asm__("lq %0,%1":"=r"(q):"m"(*p));return q;}
static inline qword ParallelVU(qword q){register qword r __asm__("vf3");__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(q));return r;}
static inline float ScalarValue(qword q){register qword word __asm__("$7")=q;register float f __asm__("$f5");__asm__("mtc1 %1,%0":"=f"(f):"r"(word));return f;}
static inline float LengthCondition(qword q){register qword word __asm__("$3")=q;register float f __asm__("$f0");__asm__("mtc1 %1,%0":"=f"(f):"r"(word));return f;}
struct TURN_LIMIT_PAGE {char before2020[0x2020];float low,high;};
struct TURN_COEFFICIENT_PAGE {char before2010[0x2010];float constant,linear,quadratic;};
static inline TURN_LIMIT_PAGE*TurnLimitPage(){register TURN_LIMIT_PAGE*page __asm__("$3");__asm__("lui %0,%%hi(%1)":"=r"(page):"i"(&D_002C2020));return page;}
static inline const float*TurnLimits(TURN_LIMIT_PAGE*page){register const float*limits __asm__("$5");__asm__("addiu %0,%1,%%lo(%2)":"=r"(limits):"r"(page),"i"(&D_002C2020));return limits;}
static inline TURN_COEFFICIENT_PAGE*TurnCoefficientPage(){register TURN_COEFFICIENT_PAGE*page __asm__("$4");__asm__("lui %0,%%hi(%1)":"=r"(page):"i"(&D_002C2010));return page;}
static inline float TurnConstant(TURN_COEFFICIENT_PAGE*page){register float value __asm__("$f2");__asm__("lwc1 %0,%1":"=f"(value):"m"(page->constant));return value;}
static inline float TurnLower(TURN_LIMIT_PAGE*page){register float value __asm__("$f12");__asm__("lwc1 %0,%1":"=f"(value):"m"(page->low));return value;}
static inline const float*TurnCoefficients(TURN_COEFFICIENT_PAGE*page){register const float*coefficients __asm__("$2");__asm__("addiu %0,%1,%%lo(%2)":"=r"(coefficients):"r"(page),"i"(&D_002C2010));return coefficients;}
static inline float TurnPolynomialInputs(qword dot,const float*coefficients,P*p,float&linear,float&quadratic,qword&axis){
 register float q __asm__("$f1"),l __asm__("$f0"),d __asm__("$f5");register qword bits __asm__("$7"),second __asm__("$6");
 __asm__("lwc1 %0,%6\n\tqmfc2.ni %1,%5\n\tlwc1 %2,%7\n\tmtc1 %1,%3\n\tlq %4,%8":"=f"(q),"=&r"(bits),"=f"(l),"=f"(d),"=r"(second):"j"(dot),"m"(coefficients[2]),"m"(coefficients[1]),"m"(p->matrix.r[1]));
 linear=l;quadratic=q;axis=second;return d;
}
static inline float EvaluateTurn(float constant,float d,float linear,float quadratic){register float result __asm__("$f0")=linear;register float second __asm__("$f1")=quadratic;
 __asm__("mul.s %1,%2,%1\n\tadd.s %0,%0,%1\n\tmul.s %0,%2,%0\n\tadd.s %0,%3,%0":"+&f"(result),"+&f"(second):"f"(d),"f"(constant));return result;}
static inline float ClampTurn(float value,float low,const float*limits){float high=limits[1];if(value<low)value=low;else if(high<value)value=high;return value;}
static inline qword PerpendicularScale(float f,qword*out){register float word __asm__("$2")=f;register qword q __asm__("vf3");__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(word));*out=q;return *out;}
static inline qword ParallelScale(float f,qword*out){register float word __asm__("$3")=f;register qword q __asm__("vf1");__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(word));*out=q;return *out;}
struct DAMPING_PAGE {char before2028[0x2028];float target,rate;};
static inline const char*ParticleClockPage(){register const char*page __asm__("$16");__asm__("lui %0,%%hi(%1)":"=r"(page):"i"(&D_002DDED0));return page;}
static inline const CLOCK*ParticleClockAddress(const char*page){register const CLOCK*clock __asm__("$2");__asm__("addiu %0,%1,%%lo(%2)":"=r"(clock):"r"(page),"i"(&D_002DDED0));return clock;}
static inline float DampingPages(const char*page,const DAMPING_PAGE*&ratePage,const DAMPING_PAGE*&targetPage){
 register const CLOCK*clock __asm__("$2");register const DAMPING_PAGE*rate __asm__("$3"),*target __asm__("$4");register float dt __asm__("$f4");
 __asm__("addiu %0,%4,%%lo(%5)\n\tlui %1,0x2C\n\tlwc1 %3,4(%0)\n\tlui %2,0x2C":"=&r"(clock),"=r"(rate),"=r"(target),"=f"(dt):"r"(page),"i"(&D_002DDED0),"m"(((const CLOCK*)(page-0x2130))->dt));
 ratePage=rate;targetPage=target;return dt;
}
static inline float DampingValues(const DAMPING_PAGE*ratePage,const DAMPING_PAGE*targetPage,qword length,float&targetValue,qword&packedLength){register float rate __asm__("$f0"),target __asm__("$f2");register qword bits __asm__("$7");
 __asm__("lwc1 %0,%3\n\tqmfc2.ni %1,%4\n\tlwc1 %2,%5":"=f"(rate),"=&r"(bits),"=f"(target):"m"(ratePage->rate),"j"(length),"m"(targetPage->target));targetValue=target;packedLength=bits;return rate;}
static inline float DampingRates(float drag,float dt,float rate,float&perpendicularRate,float&unit){register float across __asm__("$f1"),along __asm__("$f0")=rate,one __asm__("$f3");
 __asm__("mul.s %0,%3,%4\n\tmul.s %1,%1,%4\n\t.set noat\n\tlui $1,0x3F80\n\tmtc1 $1,%2\n\t.set at":"=&f"(across),"+&f"(along),"=f"(one):"f"(drag),"f"(dt):"$1");perpendicularRate=across;unit=one;return along;}
static inline float DampingGeometry(qword packedLength,float target,const M3&basis,qword&parallelDirection,qword&perpendicularDirection){register float length __asm__("$f5"),difference __asm__("$f4");register qword parallel __asm__("vf2"),perpendicular __asm__("vf4");
 __asm__("mtc1 %4,%0\n\tlqc2 %1,%6\n\tsub.s %2,%0,%5\n\tlqc2 %3,%7":"=&f"(length),"=j"(parallel),"=f"(difference),"=j"(perpendicular):"r"(packedLength),"f"(target),"m"(basis.r[0]),"m"(basis.r[1]));parallelDirection=parallel;perpendicularDirection=perpendicular;return difference;}
extern "C" void func_001D09A0(P*p)
{
    M3 spin;
    TURN_LIMIT_PAGE*limitPage=TurnLimitPage();const float*limits=TurnLimits(limitPage);
    TURN_COEFFICIENT_PAGE*coefficientPage=TurnCoefficientPage();float constant=TurnConstant(coefficientPage);
    qword first=p->matrix.r[0];float lower=TurnLower(limitPage);
    const float*coefficients=TurnCoefficients(coefficientPage);
    float linear,quadratic;qword second;
    float d=TurnPolynomialInputs(Dot(p->velocity,first),coefficients,p,linear,quadratic,second);
    float turn=ClampTurn(EvaluateTurn(constant,d,linear,quadratic),lower,limits);
    const char*clockPage=ParticleClockPage();
    func_0011B500(&spin,second,turn*ParticleClockAddress(clockPage)->dt);
    M3 basis;float drag;qword velocityArgument; qword*projectionFirst,*projectionSecond;
    M3 product=TurnProduct(p,spin,basis,drag,velocityArgument,projectionFirst,projectionSecond);
    p->matrix=product;
    p->drag=0.0f;
    func_0011E290(velocityArgument,first,projectionFirst,projectionSecond);
    qword parallel=ParallelVU(PackedParallel(&basis.r[0]));
    qword length=LengthVector(parallel);
    if(LengthCondition(length)<0.0001f)basis.r[0]=D_002A2DA0;
    else basis.r[0]=Normalize(parallel,length);
    const DAMPING_PAGE*ratePage,*targetPage;float dt=DampingPages(clockPage,ratePage,targetPage);
    float target;qword packedLength;float rate=DampingValues(ratePage,targetPage,length,target,packedLength);
    float perpendicularRate,one;float parallelRate=DampingRates(drag,dt,rate,perpendicularRate,one);
    qword parallelDirection,perpendicularDirection;float difference=DampingGeometry(packedLength,target,basis,parallelDirection,perpendicularDirection);
    float along=target+difference*(parallelRate+one);
    float across=perpendicularRate+one;
    qword perpendicularScale=PerpendicularScale(across,&basis.r[2]);
    qword parallelScale=ParallelScale(along,&basis.r[2]);
    p->velocity=Blend(parallelDirection,perpendicularDirection,parallelScale,perpendicularScale);
    func_001CF0A0(p);
    p->drag=drag;
}

#define OFF(T,F) ((unsigned int)&((T*)0)->F)
typedef char native_layout_0[(sizeof(void*)==4)?1:-1];
typedef char native_layout_1[(sizeof(qword)==16)?1:-1];
typedef char native_layout_2[(sizeof(float)==4)?1:-1];
typedef char native_layout_3[(sizeof(U)==16)?1:-1];
typedef char native_layout_4[(sizeof(M3)==0x30)?1:-1];
typedef char native_layout_5[(OFF(M3,r[0])==0)?1:-1];
typedef char native_layout_6[(OFF(M3,r[1])==0x10)?1:-1];
typedef char native_layout_7[(OFF(M3,r[2])==0x20)?1:-1];
typedef char native_layout_8[(OFF(P,matrix)==0x40)?1:-1];
typedef char native_layout_9[(OFF(P,velocity)==0x90)?1:-1];
typedef char native_layout_10[(OFF(P,drag)==0xC4)?1:-1];
typedef char native_layout_11[(OFF(CLOCK,t)==0)?1:-1];
typedef char native_layout_12[(OFF(CLOCK,dt)==4)?1:-1];

typedef char actual_matrix_row1[(OFF(P,matrix.r[1])==0x50)?1:-1];
typedef char actual_matrix_row2[(OFF(P,matrix.r[2])==0x60)?1:-1];
typedef char actual_qword_alignment[(__alignof__(qword)==16)?1:-1];
typedef char actual_matrix_alignment[(__alignof__(M3)==16)?1:-1];

typedef char actual_limit_page_low[(OFF(TURN_LIMIT_PAGE,low)==0x2020)?1:-1];
typedef char actual_limit_page_high[(OFF(TURN_LIMIT_PAGE,high)==0x2024)?1:-1];
typedef char actual_coefficient_page_constant[(OFF(TURN_COEFFICIENT_PAGE,constant)==0x2010)?1:-1];
typedef char actual_coefficient_page_linear[(OFF(TURN_COEFFICIENT_PAGE,linear)==0x2014)?1:-1];
typedef char actual_coefficient_page_quadratic[(OFF(TURN_COEFFICIENT_PAGE,quadratic)==0x2018)?1:-1];

typedef char actual_damping_target[(OFF(DAMPING_PAGE,target)==0x2028)?1:-1];
typedef char actual_damping_rate[(OFF(DAMPING_PAGE,rate)==0x202C)?1:-1];

typedef char actual_clock_size[(sizeof(CLOCK)==8)?1:-1];
