typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M3 {U rows[3];M3(){} M3(const M3&m){rows[0]=m.rows[0];rows[1]=m.rows[1];rows[2]=m.rows[2];} M3&operator=(const M3&m){rows[0]=m.rows[0];rows[1]=m.rows[1];rows[2]=m.rows[2];return *this;}};
struct OWNER {M3 matrix;char pad30[0x70];OWNER *parent;char padA4[0xC];qword velocity;char padC0[0x30];qword force;};
struct P {char pad5C[0x5C];OWNER *owner;};
struct COEF {float a,b,c;};
struct CLOCK {float time,dt;};
extern CLOCK g_clock;
extern "C" M3 MatConvertXfs(OWNER *,OWNER *,const M3 *) asm("MatConvertXfs__FP2XFT0P7MATRIX3Pv");
extern "C" void NormalizeRotateMatrix3__FP7MATRIX3(M3 *);
extern "C" M3 MulMat3TransposeA(const M3 *,const M3 *) asm("MulMat3TransposeA__FP7MATRIX3T0Pv");
extern "C" void DecomposeRotateMatrixRad(const M3 *,float *,qword *) asm("DecomposeRotateMatrixRad__FP7MATRIX3PfP6VECTOR");
extern "C" qword VecConvertXfs(OWNER *,OWNER *,qword) asm("VecConvertXfs__FP2XFT0G9VU_VECTOR");
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline float Length(qword a){qword d,one;float f;
__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(a));
__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(d):"0"(d));
__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(d));return f;}
static inline qword Scalar(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword AddScaled(qword old,qword v,qword s){__asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(old):"j"(v),"j"(s));return old;}
// name: SafeHouse port (AccelAloTowardRotation)
extern "C" void AccelAloTowardRotation__FP3ALOP7MATRIX3P3CLQG9VU_VECTORT2(P*p,const M3*orientation,const COEF*c,qword velocity,const COEF*d)
{
    OWNER *owner=p->owner;
    if(c){
        M3 frame,relative;
        U axis;
        float angle;
        frame=MatConvertXfs(0,owner->parent,orientation);
        NormalizeRotateMatrix3__FP7MATRIX3(&frame);
        relative=MulMat3TransposeA(&owner->matrix,&frame);
        DecomposeRotateMatrixRad(&relative,&angle,&axis.q);
        if(0.0001f<angle){
            float gain=c->c*angle*angle+c->b*angle+c->a;
            U scalar;
            qword k=Scalar(gain);
            {qword result=AddScaled(owner->force,axis.q,k);scalar.q=k;owner->force=result;}
        }
    }
    if(d){
        qword transformed=VecConvertXfs(0,owner->parent,velocity);
        qword direction=Sub(transformed,owner->velocity);
        float length=Length(direction);
        if(0.0001f<length){
            float gain=(d->c*length+d->b)+d->a/length;
            float limit=1.0f/g_clock.dt;
            U scalar;
            qword k;
            if(limit<gain)gain=limit;
            k=Scalar(gain);
            {qword result=AddScaled(owner->force,direction,k);scalar.q=k;owner->force=result;}
        }
    }
}
