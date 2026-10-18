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
static inline float Clamp(float value,const float*b){float low=b[0],high=b[1];if(value<low)value=low;else if(high<value)value=high;return value;}
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
static inline qword Scalar(float f,qword*out){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));*out=q;return *out;}
static inline qword Blend(qword a,qword b,qword x,qword y){__asm__("vmulax.xyzw ACC,%0,%2x\n\tvmaddx.xyzw %0,%1,%3x":"+j"(a):"j"(b),"j"(x),"j"(y));return a;}
static inline qword PackedParallel(const qword *p){register qword q __asm__("$2");__asm__("lq %0,%1":"=r"(q):"m"(*p));return q;}
static inline qword ParallelVU(qword q){register qword r __asm__("vf3");__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(q));return r;}
static inline float ScalarValue(qword q){register qword word __asm__("$7")=q;register float f __asm__("$f5");__asm__("mtc1 %1,%0":"=f"(f):"r"(word));return f;}
static inline float LengthCondition(qword q){register qword word __asm__("$3")=q;register float f __asm__("$f0");__asm__("mtc1 %1,%0":"=f"(f):"r"(word));return f;}
extern "C" void func_001D09A0(P*p)
{
    M3 spin;
    qword first=p->matrix.r[0];
    float d=ScalarValue(Dot(p->velocity,first));
    float turn=Clamp(D_002C2010[0]+d*(D_002C2010[1]+d*D_002C2010[2]),D_002C2020);
    func_0011B500(&spin,p->matrix.r[1],turn*D_002DDED0.dt);
    M3 basis;float drag;qword velocityArgument; qword*projectionFirst,*projectionSecond;
    M3 product=TurnProduct(p,spin,basis,drag,velocityArgument,projectionFirst,projectionSecond);
    p->matrix=product;
    p->drag=0.0f;
    func_0011E290(velocityArgument,first,projectionFirst,projectionSecond);
    qword parallel=ParallelVU(PackedParallel(&basis.r[0]));
    qword length=LengthVector(parallel);
    if(LengthCondition(length)<0.0001f)basis.r[0]=D_002A2DA0;
    else basis.r[0]=Normalize(parallel,length);
    float dt=D_002DDED0.dt;
    float along=D_002C2028+(ScalarValue(length)-D_002C2028)*(1.0f+D_002C202C*dt);
    float across=1.0f+drag*dt;
    qword perpendicularScale=Scalar(across,&basis.r[2]);
    qword parallelScale=Scalar(along,&basis.r[2]);
    p->velocity=Blend(basis.r[0],basis.r[1],parallelScale,perpendicularScale);
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
