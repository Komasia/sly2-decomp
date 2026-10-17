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
static inline float Float(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline qword Dot(qword a,qword b){qword one;
 __asm__("vmul.xyz %0,%0,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(a),"=&j"(one):"j"(b));return a;}
static inline float Clamp(float value,const float*b){float low=b[0],high=b[1];if(value<low)value=low;else if(high<value)value=high;return value;}
static inline qword Rotate(const M3&m,qword q){__asm__("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(q):"j"(m.r[0]),"j"(m.r[1]),"j"(m.r[2]));return q;}
static inline M3 Mul(const M3&a,const M3&b) return r {
    qword a0=a.r[0],a1=a.r[1],a2=a.r[2];
    qword c0=b.r[0],c1=b.r[1],c2=a0;
    __asm__("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(c0):"j"(a0),"j"(a1),"j"(a2));
    r.r[0]=c0;
    __asm__("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(c1):"j"(a0),"j"(a1),"j"(a2));
    r.r[1]=c1;
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"+j"(c2):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[2]));
    r.r[2]=c2;
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
    p->velocity=Rotate(spin,p->velocity);
    M3 basis;
    M3 product=Mul(spin,p->matrix);
    basis=product;
    p->matrix=product;
    float drag=p->drag;p->drag=0.0f;
    func_0011E290(p->velocity,first,&basis.r[0],&basis.r[1]);
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
