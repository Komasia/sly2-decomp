typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];int i[4];};
struct M3 {U r[3];M3(){} M3(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];} M3&operator=(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return *this;}};
struct OWNER {M3 matrix;U position;char pad40[0x60];OWNER *parent;int stamp;char padA8[8];U velocity;};
struct VT {short delta,pad;void (*fn)(void *);};
struct P {char padC[0xC];VT *vt;char pad10[0x48];OWNER *position,*rotation;char pad60[0x88];void *enabled;char padEC[4];U force[2];};
struct G {char pad3D58[0x3D58];int stamp;};
struct CLOCK {float time,dt;};
extern CLOCK D_002DDED0;
extern G D_003DD490;
extern "C" void func_00230598(P *,OWNER *);
extern "C" qword func_0022FCC8(void *,OWNER *,qword);
extern "C" int func_0011D4D0(float,float,float);
extern qword D_002A2DD0;
extern "C" void func_001F4BF8(P *);
extern "C" qword *func_00256D18(qword *,qword);
extern "C" M3 *func_0011B570(M3 *,qword);
static inline M3 BuildRotation(qword vector) return matrix {func_0011B570(&matrix,vector);}
extern "C" void NormalizeRotateMatrix3__FP7MATRIX3(M3 *);
static inline qword Scalar(float f,U *out){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));out->q=q;return out->q;}
static inline qword AddScaled(qword p,qword v,qword k){qword r;__asm__("vadda.xyzw $ACC,$vf0,%1\n\tvmaddx.xyzw %0,%2,%3x":"=&j"(r):"j"(p),"j"(v),"j"(k));return r;}
static inline qword Scale(qword v,qword k){__asm__("vmulx.xyzw %0,%0,%1x":"+j"(v):"j"(k));return v;}
static inline M3 Mul(const M3 &a,const M3 &b) return r
{
    qword a0=a.r[0].q,a1=a.r[1].q,a2=a.r[2].q;
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[0].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[0].q));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[1].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[1].q));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[2].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[2].q));
}
static inline float X(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline float Y(qword q){float f;__asm__("prot3w %0,%1":"=r"(f):"r"(q));return f;}
static inline float Z(qword q){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(q));return f;}
static inline void Near(int *out,qword a,qword b){if(func_0011D4D0(X(a),X(b),0.0001f))if(func_0011D4D0(Y(a),Y(b),0.0001f))*out=func_0011D4D0(Z(a),Z(b),0.0001f)!=0;}
static inline qword Zero(){qword r;__asm__("vsub.xyzw %0,$vf0,$vf0":"=j"(r));return r;}
static inline qword Consume(P *p,OWNER *object,U &pending){func_00230598(p,object);qword world=func_0022FCC8(0,object->parent,pending.q);pending.i[2]=0;pending.i[1]=0;return world;}
static inline void NearVector(int *out,qword a,const qword &b){if(func_0011D4D0(X(a),X(b),0.0001f))if(func_0011D4D0(Y(a),Y(b),0.0001f))*out=func_0011D4D0(Z(a),Z(b),0.0001f)!=0;}
static inline void AddVector(U *out,const qword &q){qword r,v;__asm__("lqc2 %0,%1":"=j"(r):"m"(*out));__asm__("lqc2 %0,%1":"=j"(v):"m"(q));__asm__("vadd.xyzw %0,%0,%1":"+j"(r):"j"(v));out->q=r;}
extern "C" void func_001F9E70(P *p)
{
    U scalar;
    M3 frame;
    qword shift,turn;
    if(p->enabled){
        qword value=p->force[0].q;
        qword reference=D_002A2DD0;
        int changed=0;
        OWNER *position=p->position,*rotation=p->rotation;
        int near=0;
        Near(&near,reference,value);
        if(!near){
            shift=Consume(p,position,p->force[0]);
            changed=1;
            p->force[0].i[0]=0;
            AddVector(&position->velocity,shift);
        }else shift=Zero();
        value=p->force[1].q;reference=D_002A2DD0;
        near=0;Near(&near,reference,value);
        if(!near){
            turn=Consume(p,rotation,p->force[1]);
            changed=1;
            p->force[1].i[0]=0;
            AddVector(&rotation->velocity,turn);
        }else turn=Zero();
        if(changed){
            func_001F4BF8(p);
            int incrementNear=0;NearVector(&incrementNear,D_002A2DD0,shift);
            if(!incrementNear){
                qword point=position->position.q;
                qword k=Scalar(D_002DDED0.dt*0.5f,&scalar);
                func_00256D18(&position->position.q,AddScaled(point,shift,k));
                position->position.f[3]=1.0f;
                position->stamp=++D_003DD490.stamp;
            }
            incrementNear=0;NearVector(&incrementNear,D_002A2DD0,turn);
            if(!incrementNear){
                frame=Mul(BuildRotation(Scale(turn,Scalar(D_002DDED0.dt*0.5f,&scalar))),rotation->matrix);
                NormalizeRotateMatrix3__FP7MATRIX3(&frame);
                rotation->matrix=frame;
                rotation->matrix.r[1].i[3]=0;
                rotation->matrix.r[2].i[3]=0;
                rotation->matrix.r[0].i[3]=0;
                rotation->stamp=++D_003DD490.stamp;
            }
            p->vt[18].fn((char *)p+p->vt[18].delta);
        }
    }
}
