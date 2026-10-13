typedef int qword __attribute__((mode(TI)));
typedef struct {qword r[3];} M3;
union U {qword q;float f[4];};
struct P {char pad180[0x180];float response;char pad184[0xC];qword velocity;char pad1a0[0x10];M3 basis;char pad1e0[0x30];float height;char pad214[0x34];float oldHeight;};
struct XP {char pad30[0x30];qword local;char pad40[0x30];qword other,normal;float distance;char pad94[8];int kind;};
struct CLK {float time,dt;};
extern struct CLK D_002DDED0;
extern float D_002C3C98[],D_002C3CA8[];
void func_001F4FC0(void);
float func_0011D018(float,float,float,float *,float *);
static __inline__ qword Sub(qword a,qword b){__asm__("vsub.xyzw %0,%1,%2":"=j"(a):"0"(a),"j"(b));return a;}
static __inline__ qword Dot(qword a,qword b){qword one;__asm__("vmul.xyz %0,%0,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(a),"=&j"(one):"j"(b));return a;}
static __inline__ float X(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static __inline__ void Scalar(union U *out,float f){qword bits;__asm__("mfc1 %0,%1":"=r"(bits):"f"(f));__asm__("qmtc2.ni %1,%0":"=j"(out->q):"r"(bits));}
static __inline__ qword Rotate(const M3*m,qword q){register qword r __asm__("vf3")=q;register qword a __asm__("vf2")=m->r[0],b __asm__("vf1")=m->r[1],c __asm__("vf5")=m->r[2];__asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(r):"j"(a),"j"(b),"j"(c));return r;}
static __inline__ qword Scale(qword q,qword f){__asm__("vmulx.xyzw %0,%0,%1x":"+j"(q):"j"(f));return q;}
static __inline__ qword Response(qword old,qword n,qword speed,qword tangent,qword gain){__asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddax.xyzw $ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x":"+j"(old):"j"(n),"j"(speed),"j"(tangent),"j"(gain));return old;}
static __inline__ qword DotNew(qword a,qword b){register qword d __asm__("vf2"),one __asm__("vf1");__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a),"j"(b));return d;}
static __inline__ qword ScaleFactor(qword v,qword f){__asm__("vmulx.xyzw %0,%1,%0x":"+j"(f):"j"(v));return f;}
static __inline__ qword ScalarAt(const float *f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(*(const int*)f));return q;}
void func_002044B0(struct P*p,struct XP*x,int side)
{
    float lower,upper,speed,delta;
    union U scalar;
    qword v,t,n,negative;
    func_001F4FC0();
    if(x->kind!=14)return;
    speed=X(Dot(Sub(x->local,x->other),x->normal));
    func_0011D018(x->distance,p->height,D_002DDED0.dt,D_002C3C98,&lower);
    func_0011D018(x->distance,0.0f,D_002DDED0.dt,D_002C3CA8,&upper);
    speed=speed>lower?speed:lower;
    if(speed<upper){float bound=D_002DDED0.dt*9000.0f;float diff=upper-speed;delta=bound<diff?bound:diff;}
    else {float bound=D_002DDED0.dt*-4500.0f;float diff=upper-speed;delta=bound>diff?bound:diff;}
    speed+=delta;
    v=Rotate(&p->basis,p->velocity);
    Scalar(&scalar,-speed);
    negative=scalar.q;
    n=x->normal;
    t=Sub(v,ScaleFactor(n,DotNew(v,n)));
    scalar.q=ScalarAt(&p->response);
    ((struct XP*)((char*)x+side*0x40))->local=Response(((struct XP*)((char*)x+side*0x40))->local,n,negative,t,scalar.q);
    x->distance+=(p->height-p->oldHeight);
}
