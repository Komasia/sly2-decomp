/* (Claude agent, vu_hi3) v2: 2/100 aligned 1 (was 14). Sub(Load(&pos),other) -> Sub(pos,other) so gcc emits the lqc2 (and schedules it like the target). Left: sq position0 vs lui &D_002DDF40 order after the first func_001A62E8 call. */
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
static inline void PlaneArguments(qword *threshold,qword *point,U *scalar,float f,const qword *camera,const qword *position){
 register qword view asm("vf1"),bits asm("$2"),local asm("vf2"),value asm("$6");
 __asm__("lqc2 %0,%3\n\tmfc1 %1,%4\n\tlqc2 %2,%5":"=j"(view),"=&r"(bits),"=j"(local):"m"(*camera),"f"(f),"m"(*position));
 scalar->q=bits;
 __asm__("por %0,$zero,%2\n\tvsub.xyzw %1,%1,%3":"=r"(value),"+j"(local):"r"(scalar->q),"j"(view));
 *threshold=value;*point=local;
}
static inline qword Load(const qword *p){qword r;__asm__("lqc2 %0,%1":"=j"(r):"m"(*p));return r;}
static inline qword Sub(qword a,qword b){__asm__("vsub.xyzw %0,%0,%1":"=j"(a):"j"(b),"0"(a));return a;}
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
        qword threshold,point;
        PlaneArguments(&threshold,&point,&scalar,0.0f,&camera->position,&position0.q);
        if(!func_0014F850(camera,point,threshold))goto fail;
        qword other;other=func_001A62E8(p->target);
        func_0011EF08(Sub(position0.q,other),&angle[0],0,0);
        if(p->tolerance<__builtin_fabsf(func_0011CF60(angle[0]-func_0020A690(p)))){fail:return 0;}
        return 1;
    }
    case 1:{
        position1.q=func_001A62E8(a);
        qword other;other=func_001A62E8(p->target);
        func_0011EF08(Sub(position1.q,other),&angle[1],0,0);
        if(p->tolerance<__builtin_fabsf(func_0011CF60(angle[1]-func_0020A690(p))))return 0;
        return 1;
    }
    case -1:break;
    default:break;
    }
    return 1;
}
