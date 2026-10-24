#define V_S
#define V_L1 volatile
#define V_L2
#define V_D
#define V_C volatile
#define V_N1 volatile
#define V_N2 volatile
#define V_N3 volatile
#define V_V
#define V_K
#define V_A volatile
#define V_F volatile
// func_001A4258: does a point (pos, radius) touch a chain of spheres (capsule chain)? points[i] = {center, radius}, stride 0x20.
typedef int qword __attribute__((mode(TI)));
union U {qword q; float f[4];};
struct SP {qword p; float radius;};
static inline qword ToVU(qword v){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(v));return r;}
static inline qword Sub(qword a,qword b){qword d;__asm__ V_S("vsub.xyzw %0,%1,%2":"=j"(d):"j"(a),"j"(b));return d;}
static inline qword Length(qword a)
{
    qword d,one;
    __asm__ V_L1("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a),"j"(a));
    __asm__ V_L2("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(d):"j"(d));
    return d;
}
static inline qword Dot(qword a,qword b)
{
    qword d,one;
    __asm__ V_D("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a),"j"(b));
    return d;
}
static inline float GetX(qword d){float g;__asm__("qmfc2.ni %0,%1":"=r"(g):"j"(d));return g;}
static inline qword Cross(qword a,qword b){qword r;__asm__ V_C("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Normalize(qword a)
{
    qword d,one,r;
    __asm__ V_N1("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a));
    qword l;
    __asm__ V_N2("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(l):"j"(d));
    __asm__ V_N3("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(r):"j"(a),"j"(l));
    return r;
}
static inline qword Scalar(U &home,float v){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(v));home.q=r;return home.q;}
static inline qword DivScalar(qword a,qword s){qword r;__asm__ V_V("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(r):"j"(a),"j"(s));return r;}
static inline qword Combine(qword a,qword b,qword sa,qword sb){qword r;__asm__ V_K("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x":"=j"(r):"j"(a),"j"(b),"j"(sa),"j"(sb));return r;}
static inline qword AddScaled(qword a,qword n,qword s){qword r;__asm__ V_A("vadda.xyzw $ACC,$vf0,%1\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(n),"j"(s));return r;}
static inline float SqrtF(float x){float r;__asm__ V_F("sqrt.s %0,%1":"=&f"(r):"f"(x));return r;}
extern "C" int func_001A4258(qword pos,float radius,int count,SP *points)
{
    U scalar;
    int i=0;
    if(i<count){
        qword p=ToVU(pos);
        SP *sp=points;
        do{
            qword a=sp->p;
            float r=sp->radius;
            qword dq=Length(Sub(p,a));
            float sum=radius+r;
            float d=GetX(dq);
            if(d<sum)return 1;
            sp++;
        }while(++i<count);
    }
    i=1;
    if(i<count){
        qword p=ToVU(pos);
        do{
            qword a=points[0].p;
            qword b=points[1].p;
            qword d=Sub(p,a);
            qword axis=Sub(b,a);
            float ra=points[0].radius;
            float rb=points[1].radius;
            qword lenq=Length(axis);
            qword c1=Cross(d,axis);
            float len=GetX(lenq);
            qword u=DivScalar(axis,Scalar(scalar,len));
            float s=(ra-rb)/len;
            qword perp=Normalize(Cross(u,c1));
            float root=SqrtF(1.0f-s*s);
            qword n=Combine(u,perp,Scalar(scalar,s),Scalar(scalar,root));
            qword A=AddScaled(a,n,Scalar(scalar,ra));
            qword pa=Sub(p,A);
            qword B=AddScaled(b,n,Scalar(scalar,rb));
            qword distq=Dot(pa,n);
            qword ba=Sub(B,A);
            qword denq=Dot(ba,ba);
            qword numq=Dot(pa,ba);
            float dist=GetX(distq);
            float num=GetX(numq);
            float den=GetX(denq);
            float t=num/den;
            if(dist<radius&&t>=0.0f&&t<=1.0f)return 1;
            points++;
        }while(++i<count);
    }
    return 0;
}
