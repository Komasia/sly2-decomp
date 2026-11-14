// Update target-facing angles or integrate angular input.
typedef int qword __attribute__((mode(TI)));
struct M3 {qword r[3];};
union V {qword q;float f[4];};
struct BOUND {float lo,hi;};
struct CONTROL {char pad[0x10];float x,y;char pad18[8];float z;};
struct S {char pad[0x150];CONTROL *control;char pad154[0x2C];void *target;int aim;int pad188;float pitch,yaw,vpitch,vyaw;BOUND yawRange,pitchRange;char pad1ac[0x10];float strength;char pad1c0[0xC];int output;char pad1d0[8];void *rotation;};
#include "clock.h"
extern int D_003E0FE0;
extern char D_003D4A60[];
extern float D_002C4408[];
extern "C" {
qword PosOfLo(void *) asm("PosOfLo__FP2LO");
M3 func_0011B7E0(qword);
void DecomposeRotateMatrixPanTilt(const M3 *,float *,float *) asm("DecomposeRotateMatrixPanTilt__FP7MATRIX3PfT1");
float GLimitAbs(float,float) asm("GLimitAbs__Fff");
float GSmooth(float,float,float,const float *,float *) asm("GSmooth__FfffP3SMPPf");
float GLimitLm(const BOUND *,float) asm("GLimitLm__FP2LMf");
void SetCtrlPos(void *,qword) asm("SetCtrlPos__FP7CTRLPOSG9VU_VECTOR");
void Decref(void *) asm("Decref__4CRef");
}
struct CRef {int kind,value;CRef(const CRef &) __asm__("__4CRefRC4CRef");~CRef(){Decref(this);}};
extern "C" CRef NProgress(int,void *);
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Make(float x,float y,float z) {
    qword q,t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0":"=&r"(q),"=&r"(t):"f"(x),"f"(y),"f"(z));
    return q;
}
// name: SafeHouse port (UpdateTurretAim)
extern "C" void UpdateTurretAim__FP6TURRET(S *p){
    if(p->target && p->aim) {
        M3 m;
        float pitch,yaw;
        qword target;
        m=func_0011B7E0((target=PosOfLo(p->target),Sub(target,PosOfLo(p))));
        DecomposeRotateMatrixPanTilt(&m,&pitch,&yaw);
        float dp=pitch-p->pitch;
        float dy=yaw-p->yaw;
        p->pitch=pitch;p->yaw=yaw;
        p->vpitch=dp;p->vyaw=dy;
    } else {
        if(p->control) {
            float x=GLimitAbs(p->control->x+p->control->z,1.0f);
            float y=GLimitAbs(p->control->y,1.0f);
            float strength=p->strength;
            float gain=(1.0f-strength)*0.5f+strength;
            float cubic=-x*x;
            cubic=cubic*x;
            float accel=gain*10.0f;
            float ax=cubic*accel;
            float limit=strength*1.3f;
            if(ax*p->vpitch<=0.0f)p->vpitch=0.0f;
            float cubeY=y*y;
            cubeY=cubeY*y;
            float ay=cubeY*accel;
            if(!NProgress(D_003E0FE0,D_003D4A60).value)ay=-ay;
            if(ay*p->vyaw<=0.0f)p->vyaw=0.0f;
            CLOCK *clock=&g_clock;
            const float *damping=D_002C4408;
            p->vpitch=GSmooth(p->vpitch,0.0f,clock->dt,damping,0);
            p->vyaw=GSmooth(p->vyaw,0.0f,clock->dt,damping,0);
            p->vpitch=GLimitAbs(p->vpitch+ax*clock->dt,limit*0.9f);
            p->vyaw=GLimitAbs(p->vyaw+ay*clock->dt,limit*0.8f);
            p->pitch+=p->vpitch*clock->dt;
            p->yaw+=p->vyaw*clock->dt;
        }
    }
    p->pitch=GLimitLm(&p->pitchRange,p->pitch);
    p->yaw=GLimitLm(&p->yawRange,p->yaw);
    if(p->output){V v;v.q=Make(0.0f,-p->yaw,p->pitch);SetCtrlPos(p->rotation,v.q);}
}
