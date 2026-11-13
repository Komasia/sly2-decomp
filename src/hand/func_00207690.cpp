typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M4 {U rows[4];M4(){}M4(const M4 &m){rows[0]=m.rows[0];rows[1]=m.rows[1];rows[2]=m.rows[2];rows[3]=m.rows[3];}M4 &operator=(const M4 &m){rows[0]=m.rows[0];rows[1]=m.rows[1];rows[2]=m.rows[2];rows[3]=m.rows[3];return *this;}};
struct SPACE {char pad0[0x40];M4 matrix;};
union FLAGS {unsigned long value;unsigned char bytes[8];};
struct P {char pad0[0x28];FLAGS flags;char pad30[0x30];SPACE *space;char pad64[0xC8];float opacity;int unused130;void *material;char pad138[0x108];float pivot[3];char pad24C[0x114];float start;};
struct CAMERA {char pad0[0x14];int mask;char pad18[0x78];U position;};
struct PROFILE {float a,b,c,unused,min,max;};
struct CLOCK {float time,dt;};
struct EFFECT;
extern CAMERA g_cm;
extern PROFILE D_003E1A60;
extern CLOCK g_clock;
extern float D_002C3D4C;
extern float D_002C3D50[3],D_002C3D60[2],g_lmZeroOne[2];
extern "C" {
void func_001F3C10(P *);
int func_0014FD50(void *);
void RenderGlob(EFFECT *,const M4 *,void *,float,float) asm("RenderGlob__FP4GLOBP7MATRIX4ffP3SHD");
void *s1_memset(void *,int,unsigned int) asm("s1_memset");
qword PosOfLo(P *) asm("PosOfLo__FP2LO");
float sinf(float);
qword *func_00256D18(qword *,qword);
M4 *MulMatrix4(M4 *,const M4 *,const M4 *) asm("MulMatrix4__FP7MATRIX4T0Pv");
M4 *InverseAffineMatrix4(M4 *,const M4 *) asm("InverseAffineMatrix4__FP7MATRIX4");
}
static inline qword Subtract(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline float Length(qword a){qword one;float f;__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(a),"=&j"(one));__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(a));__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
extern "C" void RenderStepguardSelf__FP9STEPGUARDP2CMP2RO(P *p)
{
    M4 local;
    U offset;
    M4 basis,matrix,product,inverse;
    CAMERA *camera=&g_cm;
    if(p->flags.bytes[5]&camera->mask){
        func_001F3C10(p);
        if(!func_0014FD50((char *)camera+0x3B0)){
            RenderGlob((EFFECT *)((char *)p+0x80),0,p->material,p->opacity,p->opacity);
        }else{
            s1_memset(&local,0,sizeof(M4));
            local.rows[3].f[3]=1.0f;
            local.rows[2].f[2]=1.0f;
            local.rows[1].f[1]=1.0f;
            local.rows[0].f[0]=1.0f;
            float distance=Length(Subtract(PosOfLo(p),camera->position.q));
            PROFILE *profile=&D_003E1A60;
            float gain=profile->a+distance*(profile->b+distance*profile->c);
            float min=profile->min,max=profile->max;
            if(gain<min)gain=min;else if(max<gain)gain=max;
            float elapsed=g_clock.time-p->start;
            float along=gain,across=gain;
            if(elapsed<0.85f){
                float wave=sinf(elapsed*D_002C3D4C);
                float u=elapsed*1.1764705f;
                float mix=(wave+1.0f)*0.5f;
                float magnitude=D_002C3D50[0]+u*(D_002C3D50[1]+u*D_002C3D50[2]);
                float blend=(1.0f-mix)*D_002C3D60[0]+mix*D_002C3D60[1];
                float min=g_lmZeroOne[0],max=g_lmZeroOne[1];
                if(magnitude<min)magnitude=min;else if(max<magnitude)magnitude=max;
                float strength=blend*magnitude;
                across=1.0f-strength;
                along=1.0f+strength;
            }
            local.rows[0].f[0]=across;
            local.rows[1].f[1]=across;
            local.rows[2].f[2]=along;
            offset.f[0]=(1.0f-across)*p->pivot[0];
            offset.f[2]=(1.0f-along)*p->pivot[2];
            offset.f[1]=(1.0f-across)*p->pivot[1];
            func_00256D18(&local.rows[3].q,offset.q);
            local.rows[3].f[3]=1.0f;
            M4 *productPointer=&product;
            M4 *basisPointer=&basis;
            M4 *matrixPointer=&matrix;
            basis.rows[0]=p->space->matrix.rows[0];
            basis.rows[1]=p->space->matrix.rows[1];
            basis.rows[2]=p->space->matrix.rows[2];
            basis.rows[3]=p->space->matrix.rows[3];
            MulMatrix4(productPointer,basisPointer,&local);
            M4 *inversePointer=&inverse;
            InverseAffineMatrix4(inversePointer,basisPointer);
            MulMatrix4(matrixPointer,productPointer,inversePointer);
            RenderGlob((EFFECT *)((char *)p+0x80),matrixPointer,p->material,p->opacity,p->opacity);
        }
    }
}
