typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M3 {qword rows[3];};
struct M4 {qword rows[4];};
struct POLY {float a,b,c;};
inline void* operator new(unsigned int,void*place){return place;}
union TEMP {struct {U scalar;M3 facing;} face;M3 rotation;M4 transform;};
struct WORK {M3 basis,rotation,product;M4 transform;TEMP temporary;M3 productReturn;U direction;};
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
// XYZ products retain the post-rotation W lanes.
static inline M3 Multiply(const M3&a,const M3&b) return r {
 register qword row0 __asm__("vf4"),row1 __asm__("vf3")=a.rows[0],row2 __asm__("vf5");
 register qword left1 __asm__("vf2")=a.rows[1],left2 __asm__("vf1")=a.rows[2],column0 __asm__("vf8")=b.rows[0],column1 __asm__("vf7")=b.rows[1],column2 __asm__("vf6")=b.rows[2];
 __asm__("vmulax.xyz ACC,%2,%6x\n\tvmadday.xyz ACC,%3,%6y\n\tvmaddz.xyz %1,%4,%6z\n\tvmulax.xyz ACC,%2,%5x\n\tvmadday.xyz ACC,%3,%5y\n\tvmaddz.xyz %0,%4,%5z":"+j"(row0),"+j"(row2):"j"(row1),"j"(left1),"j"(left2),"j"(column0),"j"(column2));
 __asm__("vmulax.xyz ACC,%0,%3x\n\tvmadday.xyz ACC,%1,%3y\n\tvmaddz.xyz %0,%2,%3z":"+j"(row1):"j"(left1),"j"(left2),"j"(column1));
 r.rows[0]=row0;r.rows[1]=row1;r.rows[2]=row2;
}
extern "C" void func_001D0190(RIP *p)
{
    WORK work;
    CAMERA *camera=&D_002DDF40;
    work.direction.q=Subtract(VectorLoad(&camera->position.q),VectorLoad(&p->position.q));
    float distance=Length(work.direction.q)*0.001f;
    float time=(D_002DDED0.time-p->start)/p->duration;
    float size=Evaluate(p->size,time)*Clamp(Evaluate(D_002C1FB0,distance),D_002C1FC0[0],D_002C1FC0[1]);
    work.temporary.face.scalar.q=Scalar(-1.0f);
    qword backward=Scale(work.direction.q,work.temporary.face.scalar.q);
    work.temporary.face.scalar.q=CPUScalar(size*100.0f);
    if(!func_0014F850(camera,backward,work.temporary.face.scalar.q)){RemoveRip(p);return;}
    float opacity=Clamp(Evaluate(p->opacity,time),D_002BBB60[0],D_002BBB60[1]);
    opacity*=Clamp(Evaluate(D_002C1FD0,distance),D_002C1FE0[0],D_002C1FE0[1]);
    ::new((void*)&work.temporary.face.facing) M3(Facing(work.direction.q,D_002A2DC0));
    work.basis=work.temporary.face.facing;
    ::new((void*)&work.temporary.rotation) M3(Rotation(D_002A2DA0,Evaluate(D_002C1FF0,time)));
    work.rotation=work.temporary.rotation;
    ::new((void*)&work.productReturn) M3(Multiply(work.basis,work.rotation));
    work.product=work.productReturn;
    ::new((void*)&work.temporary.transform) M4(Transform(p->position.q,work.product,size));
    work.transform=work.temporary.transform;
    func_001A5EE8(p->material,&work.transform,opacity,1.0f);
}
#define OFF(t,m) ((unsigned)&((t*)0)->m)
typedef char native_work_layout[(sizeof(void*)==4 && sizeof(qword)==16 && sizeof(U)==16 && sizeof(M3)==0x30 && sizeof(M4)==0x40 && sizeof(TEMP)==0x40 && sizeof(WORK)==0x150 && OFF(WORK,basis)==0 && OFF(WORK,rotation)==0x30 && OFF(WORK,product)==0x60 && OFF(WORK,transform)==0x90 && OFF(WORK,temporary)==0xD0 && OFF(WORK,productReturn)==0x110 && OFF(WORK,direction)==0x140 && OFF(TEMP,face.scalar)==0 && OFF(TEMP,face.facing)==0x10 && OFF(TEMP,rotation)==0 && OFF(TEMP,transform)==0 && OFF(RIP,start)==0x14 && OFF(RIP,duration)==0x18 && OFF(RIP,material)==0x1C && OFF(RIP,size)==0x20 && OFF(RIP,opacity)==0x30 && OFF(RIP,position)==0x70 && OFF(CAMERA,position)==0x90)?1:-1];
