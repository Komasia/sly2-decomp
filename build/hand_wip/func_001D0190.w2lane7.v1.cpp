typedef int qword __attribute__((mode(TI)));
struct M3 {qword r[3];};
struct M4 {qword r[4];};
struct POLY {float a,b,c;};
struct RIP {char pad0[0x14];float start,duration;void *material;POLY size;int unused2C;POLY opacity;char pad3C[0x34];qword position;};
struct CAMERA {char pad0[0x90];qword position;};
struct CLOCK {float time,dt;};
extern CAMERA D_002DDF40;
extern CLOCK D_002DDED0;
extern POLY D_002C1FB0,D_002C1FD0,D_002C1FF0;
extern float D_002C1FC0[2],D_002C1FE0[2],D_002BBB60[2];
extern const qword D_002A2DA0,D_002A2DC0;
extern "C" {
void func_001CE980(RIP *);
int func_0014F850(CAMERA *,qword,qword);
M3 func_0011B830(qword,qword);
M3 func_0011B500(qword,float);
M4 func_0011C288(qword,const M3 &,float);
void func_001A5EE8(void *,const M4 &,float,float);
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
static inline qword Subtract(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scale(qword a,VU_FLOAT s){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(s.q));return r;}
static inline qword BcG(float f){union{qword q;float f;}u;qword r;__asm__("mfc1 %0,%1":"=r"(r):"f"(f));u.q=r;return r;}
static inline float Length(qword v){qword d,one,l;int r;float f;
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(v));
 __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(l):"j"(d));
 __asm__("qmfc2.ni %0, %1" : "=r"(r) : "j"(l));
 __asm__("mtc1 %1, %0" : "=f"(f) : "r"(r));
 return f;}
static inline float Evaluate(const POLY &p,float t){return p.a+t*(p.b+t*p.c);}
static inline float Clamp(float v,float low,float high){if(v<low)return low;else if(high<v)return high;else return v;}
static inline M3 Multiply(const M3&a,const M3&b) return r {
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[0]):"j"(a.r[0]),"j"(a.r[1]),"j"(a.r[2]),"j"(b.r[0]));
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[1]):"j"(a.r[0]),"j"(a.r[1]),"j"(a.r[2]),"j"(b.r[1]));
 __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[2]):"j"(a.r[0]),"j"(a.r[1]),"j"(a.r[2]),"j"(b.r[2]));
}
extern "C" void func_001D0190(RIP *p)
{
    M3 basis,rotation,product;
    M4 transform;
    qword direction=Subtract(D_002DDF40.position,p->position);
    float distance=Length(direction)*0.001f;
    float time=(D_002DDED0.time-p->start)/p->duration;
    float size=Evaluate(p->size,time)*Clamp(Evaluate(D_002C1FB0,distance),D_002C1FC0[0],D_002C1FC0[1]);
    if(!func_0014F850(&D_002DDF40,Scale(direction,VU_FLOAT(-1.0f)),BcG(size*100.0f))){func_001CE980(p);return;}
    float opacity=D_002BBB60[0];
    float hi=D_002BBB60[1];
    float v=Evaluate(p->opacity,time);
    if(v<opacity)opacity=opacity;else if(hi<v)opacity=hi;else opacity=v;
    opacity*=Clamp(Evaluate(D_002C1FD0,distance),D_002C1FE0[0],D_002C1FE0[1]);
    basis=func_0011B830(direction,D_002A2DC0);
    rotation=func_0011B500(D_002A2DA0,Evaluate(D_002C1FF0,time));
    product=Multiply(basis,rotation);
    transform=func_0011C288(p->position,product,size);
    func_001A5EE8(p->material,transform,opacity,1.0f);
}
