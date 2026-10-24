// Angular braking and bounded angular-velocity correction.
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M3 {U rows[3];M3(){} M3(const M3&m){rows[0]=m.rows[0];rows[1]=m.rows[1];rows[2]=m.rows[2];} M3&operator=(const M3&m){rows[0]=m.rows[0];rows[1]=m.rows[1];rows[2]=m.rows[2];return *this;}};
struct SPACE;
struct OWNER {M3 matrix;char pad30[0x70];SPACE *parent;char padA4[0xC];qword velocity;char padC0[0x30];qword force;};
struct P {char pad5C[0x5C];OWNER *owner;};
struct COEF {float a,b,c;};
struct CLOCK {float time,dt;};
extern CLOCK D_002DDED0;
extern "C" M3 *func_0022FD38(M3 *,SPACE *,SPACE *,const M3 *);
static inline M3 BuildFrame(SPACE*parent,const M3*orientation) return result {func_0022FD38(&result,0,parent,orientation);}
extern "C" void NormalizeRotateMatrix3__FP7MATRIX3(M3 *);
extern "C" void func_0011BC00(M3 *,const M3 *,const M3 *);
extern "C" void func_0011BCF8(const M3 *,float *,qword *);
extern "C" float func_0011CFE0(float,float);
static inline qword Sub(qword a,qword b){register qword r __asm__("vf4");__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Add(qword a,qword b){__asm__("vadd.xyzw %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline qword Scalar(float f,U *out){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));__asm__("sqc2 %1,%0":"=m"(out->q):"j"(q));return q;}
static inline qword Scale(qword source,qword k){register qword v __asm__("vf3")=source;__asm__("vmulx.xyzw %0,%0,%1x":"+j"(v):"j"(k));return v;}
static inline qword ScaleFactor(qword v,qword k){__asm__("vmulx.xyzw %0,%1,%0x":"+j"(k):"j"(v));return k;}
static inline qword ScaleNew(qword v,qword k){register qword r __asm__("vf2");__asm__("vmulx.xyzw %0,%1,%2x":"=&j"(r):"j"(v),"j"(k));return r;}
static inline qword AddScaled(qword a,qword b,qword k){__asm__("vadda.xyzw ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(a):"j"(b),"j"(k));return a;}
static inline float Dot(qword value,qword normal){register qword d __asm__("vf2")=value,b __asm__("vf1")=normal,one __asm__("vf3");float f;__asm__("vmul.xyz %0,%0,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(d),"=&j"(one):"j"(b));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(d));return f;}
static inline float Length(qword a){qword d,one;float f;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a));__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(d):"0"(d));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(d));return f;}
static inline float Product(float x,float y){register float a __asm__("$f1")=x,b __asm__("$f2")=y;__asm__("mul.s %0,%0,%1":"+f"(a):"f"(b));return a;}
extern "C" void func_001F59A0(P *p,const M3 *orientation,const COEF *c)
{
    M3 frame,relative;
    U axis,wanted,change,predicted;
    float angle;
    float maximum=c->a;
    float acceleration=(maximum-c->b)/c->c;
    float square=maximum*maximum;
    float stopAngle;
    OWNER *owner=p->owner;
    float speed=Length(owner->velocity);
    stopAngle=square/(acceleration+acceleration);
    float desired,projected;float remaining,length,gain;
    CLOCK *clock;
    if(maximum<speed){
        U scalar;float correction=((maximum-speed)*2.5f)/speed;
        change.q=ScaleFactor(owner->velocity,Scalar(correction,&scalar));
        owner->force=Add(owner->force,change.q);
    }
    frame=BuildFrame(owner->parent,orientation);
    NormalizeRotateMatrix3__FP7MATRIX3(&frame);
    {M3 out;func_0011BC00(&out,&owner->matrix,&frame);relative=out;}
    func_0011BCF8(&relative,&angle,&axis.q);
    desired=func_0011CFE0((angle/stopAngle)*maximum,maximum);
    projected=Dot(owner->velocity,axis.q);
    clock=&D_002DDED0;
    remaining=angle-(projected+desired)*Product(clock->dt,0.5f);
    if(remaining<stopAngle)desired=func_0011CFE0((remaining/stopAngle)*maximum,maximum);
    U scalar;
    {qword k=Scalar(desired,&scalar);wanted.q=Scale(axis.q,k);}
    {qword k=Scalar(clock->dt,&scalar);predicted.q=AddScaled(owner->velocity,owner->force,k);}
    change.q=Sub(wanted.q,predicted.q);
    length=Length(change.q);
    if(length<acceleration*clock->dt)gain=1.0f/clock->dt;
    else gain=acceleration/length;
    change.q=ScaleNew(change.q,Scalar(gain,&scalar));
    owner->force=Add(owner->force,change.q);
}

typedef char check_qword_size[(sizeof(qword)==16)?1:-1];
typedef char check_vector_size[(sizeof(U)==16)?1:-1];
typedef char check_matrix_size[(sizeof(M3)==0x30)?1:-1];
typedef char check_row_1[((unsigned)&((M3*)0)->rows[1]==0x10)?1:-1];
typedef char check_row_2[((unsigned)&((M3*)0)->rows[2]==0x20)?1:-1];
typedef char check_float_size[(sizeof(float)==4)?1:-1];
typedef char check_pointer_size[(sizeof(void*)==4)?1:-1];
typedef char check_owner_matrix[((unsigned)&((OWNER*)0)->matrix==0)?1:-1];
typedef char check_owner_parent[((unsigned)&((OWNER*)0)->parent==0xA0)?1:-1];
typedef char check_owner_velocity[((unsigned)&((OWNER*)0)->velocity==0xB0)?1:-1];
typedef char check_owner_force[((unsigned)&((OWNER*)0)->force==0xF0)?1:-1];
typedef char check_owner_size[(sizeof(OWNER)==0x100)?1:-1];
typedef char check_object_owner[((unsigned)&((P*)0)->owner==0x5C)?1:-1];
typedef char check_coef_size[(sizeof(COEF)==12)?1:-1];
typedef char check_coef_a[((unsigned)&((COEF*)0)->a==0)?1:-1];
typedef char check_coef_b[((unsigned)&((COEF*)0)->b==4)?1:-1];
typedef char check_coef_c[((unsigned)&((COEF*)0)->c==8)?1:-1];
typedef char check_clock_size[(sizeof(CLOCK)==8)?1:-1];
typedef char check_clock_dt[((unsigned)&((CLOCK*)0)->dt==4)?1:-1];
