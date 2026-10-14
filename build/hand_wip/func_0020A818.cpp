typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct Actor { char pad[0xF30]; int blocked,ready,padF38,busy; };
struct P { char pad[0xC]; Actor *target; int kind; float unused,tolerance; int disabled; char pad20[8]; int count; Actor *actors[1]; };
struct Camera { char pad[0x90]; qword position; };
extern Camera D_002DDF40;
extern "C" {
qword func_001A62E8(Actor *);
int func_0014F850(Camera *,qword,qword);
void func_0011EF08(qword,float *,float *,float *);
float func_0020A690(P *);
float func_0011CF60(float);
}
static inline qword Load(const qword *p){qword r;__asm__("lqc2 %0,%1":"=j"(r):"m"(*p));return r;}
static inline qword Sub(qword a,qword b){__asm__("vsub.xyzw %0,%0,%1":"=j"(a):"j"(b),"0"(a));return a;}
static inline qword Scalar(U *u,float f){qword r;__asm__("mfc1 %0,%1":"=r"(r):"f"(f));u->q=r;return u->q;}
extern "C" int func_0020A818(P*p,Actor*a)
{
    U scalar;
    float angle[2];
    U position0,position1;
    if(p->disabled)goto fail;
    if(!a->blocked){
        int i,n=p->count;
        for(i=0;i<n;i++)if(p->actors[i]->busy)goto fail;
    }
    switch(p->kind){
    case 0:{
        if(a->ready)return 1;
        position0.q=func_001A62E8(a);
        Camera *camera;camera=&D_002DDF40;
        if(!func_0014F850(camera,Sub(Load(&position0.q),camera->position),Scalar(&scalar,0.0f)))goto fail;
        qword other;other=func_001A62E8(p->target);
        func_0011EF08(Sub(Load(&position0.q),other),&angle[0],0,0);
        if(p->tolerance<__builtin_fabsf(func_0011CF60(angle[0]-func_0020A690(p)))){fail:return 0;}
        return 1;
    }
    case 1:{
        position1.q=func_001A62E8(a);
        qword other;other=func_001A62E8(p->target);
        func_0011EF08(Sub(Load(&position1.q),other),&angle[1],0,0);
        if(p->tolerance<__builtin_fabsf(func_0011CF60(angle[1]-func_0020A690(p))))return 0;
        return 1;
    }
    case -1:break;
    default:break;
    }
    return 1;
}
