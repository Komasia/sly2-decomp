typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M3 {qword rows[3];};
struct M4 {qword rows[4];};
struct POLY {float a,b,c;};
struct RIP {char pad0[0x14];float start,duration;void *material;POLY size;int unused2C;POLY opacity;char pad3C[0x34];U position;};
struct CAMERA {char pad0[0x90];U position;};
struct CLOCK {float time,dt;};
extern CAMERA D_002DDF40;
extern CLOCK D_002DDED0;
extern POLY D_002C1FB0,D_002C1FD0,D_002C1FF0;
extern float D_002C1FC0[2],D_002C1FE0[2],D_002BBB60[2];
extern const qword D_002A2DA0,D_002A2DC0;
void RemoveRip(RIP *);
extern "C" {
int func_0014F850(CAMERA *,qword,qword);
M3 *func_0011B830(M3 *,qword,qword);
M3 *func_0011B500(M3 *,qword,float);
M4 *func_0011C288(M4 *,qword,const M3 *,float);
void func_001A5EE8(void *,const M4 *,float,float);
}
static inline qword VectorLoad(const qword *p){qword r;__asm__("lqc2 %0,%1":"=j"(r):"m"(*p));return r;}
static inline qword Subtract(qword a,qword b){register qword camera __asm__("vf2")=a,particle __asm__("vf1")=b,result __asm__("vf3");__asm__("vsub.xyzw %0,%1,%2":"=j"(result):"j"(camera),"j"(particle));return result;}
static inline qword Scalar(float f){qword r;__asm__("qmtc2 %1,%0":"=j"(r):"r"(f));return r;}
static inline qword CPUScalar(float f){qword r;__asm__("por %0,$zero,%1":"=r"(r):"r"(f));return r;}
static inline qword Scale(qword a,qword b){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(b));return r;}
static inline float Length(qword v){register qword d __asm__("vf1"),one __asm__("vf2"),input __asm__("vf3") = v;float f;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(input));__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(d));__asm__("mtc1 %1,%0":"=f"(f):"r"(d));return f;}
static inline float Evaluate(const POLY &p,float t){return p.a+t*(p.b+t*p.c);}
static inline float Clamp(float v,float low,float high){if(v<low)return low;else if(high<v)return high;else return v;}
static inline M3 Facing(qword direction,qword up) return r {func_0011B830(&r,direction,up);}
static inline M3 Rotation(qword axis,float angle) return r {func_0011B500(&r,axis,angle);}
static inline M4 Transform(qword position,const M3 &basis,float size) return r {func_0011C288(&r,position,&basis,size);}
static inline M3 Multiply(const M3 &a,const M3 &b) return r {
 __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.rows[0]):"j"(a.rows[0]),"j"(a.rows[1]),"j"(a.rows[2]),"j"(b.rows[0]));
 __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.rows[1]):"j"(a.rows[0]),"j"(a.rows[1]),"j"(a.rows[2]),"j"(b.rows[1]));
 __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.rows[2]):"j"(a.rows[0]),"j"(a.rows[1]),"j"(a.rows[2]),"j"(b.rows[2]));
}
extern "C" void func_001D0190(RIP *p)
{
    M3 basis,rotation,product;
    M4 transform;
    U scalar;
    CAMERA *camera=&D_002DDF40;
    qword direction=Subtract(VectorLoad(&camera->position.q),VectorLoad(&p->position.q));
    float distance=Length(direction)*0.001f;
    float time=(D_002DDED0.time-p->start)/p->duration;
    float size=Evaluate(p->size,time)*Clamp(Evaluate(D_002C1FB0,distance),D_002C1FC0[0],D_002C1FC0[1]);
    scalar.q=Scalar(-1.0f);
    qword backward=Scale(direction,scalar.q);
    scalar.q=CPUScalar(size*100.0f);
    if(!func_0014F850(camera,backward,scalar.q)){RemoveRip(p);return;}
    float opacity=Clamp(Evaluate(p->opacity,time),D_002BBB60[0],D_002BBB60[1]);
    opacity*=Clamp(Evaluate(D_002C1FD0,distance),D_002C1FE0[0],D_002C1FE0[1]);
    basis=Facing(direction,D_002A2DC0);
    rotation=Rotation(D_002A2DA0,Evaluate(D_002C1FF0,time));
    product=Multiply(basis,rotation);
    transform=Transform(p->position.q,product,size);
    func_001A5EE8(p->material,&transform,opacity,1.0f);
}
