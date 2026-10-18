typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];int i[4];};
struct M3 {U rows[3];M3(){}M3(const M3&m){rows[0]=m.rows[0];rows[1]=m.rows[1];rows[2]=m.rows[2];}M3 &operator=(const M3&m){rows[0]=m.rows[0];rows[1]=m.rows[1];rows[2]=m.rows[2];return *this;}};
extern "C" qword *func_00256D18(qword *,qword);
struct M4 {M3 basis;U position;M4(){}void Init(const M3 &r,qword p){func_00256D18(&position.q,p);basis=r;position.f[3]=1.0f;basis.rows[2].i[3]=0;basis.rows[1].i[3]=0;basis.rows[0].i[3]=0;}M4(const M4&m){basis=m.basis;position=m.position;}M4 &operator=(const M4&m){basis=m.basis;position=m.position;return *this;}};
struct FRAME {FRAME(){}~FRAME(){}};
struct P {char pad0[0xEC];void *attachment;char padF0[0xB8];float heading;char pad1AC[4];M3 basis;};
struct HEIGHT {float min,max;};
struct GAME;
extern GAME D_003DD490;
extern qword D_002A2DC0;
extern const float D_002A85F8;
union FLOATWORD {float value;int bits;};
extern FLOATWORD D_002C3CE0;
extern float D_002C3CE8;
extern int D_002C3CE4;
extern "C" {
M3 *func_0011B500(M3 *,qword,float);
qword func_001A62E8(P *);
qword *func_00256D18(qword *,qword);
FRAME *func_001AE478(FRAME *);
void func_001AE4A0(FRAME *,int);
void func_0020FC60(GAME *,qword,float,int (*)(void *,void *),void *,int *,void ***);
int func_0020FA50(void *,void *);
int func_00173610(U *,float,float,int,void *);
M3 *func_0011BA08(M3 *,qword,qword);
void func_0011BCF8(M3 *,float *,U *);
}
static inline M3 Rotation(qword axis,float angle) return r {func_0011B500(&r,axis,angle);}
static inline M3 Align(qword from,qword to) return r {func_0011BA08(&r,from,to);}
static inline qword Subtract(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Cross(qword a,qword b,qword r){__asm__("vopmula.xyz ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"+j"(r):"j"(a),"j"(b));return r;}
static inline qword Square(qword a){qword one;__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(a),"=&j"(one));return a;}
static inline qword Root(qword a){__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(a));return a;}
static inline float X(qword a){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
static inline float Length(qword a){return X(Root(Square(a)));}
static inline qword Normalize(qword v,const qword *fallback) {
    register const qword *address __asm__("$4")=fallback;
    register qword fallbackValue __asm__("$6");
    __asm__("lq %0,0(%1)":"=r"(fallbackValue):"r"(address),"m"(*fallback));
    register qword value __asm__("vf1"),one __asm__("vf2");
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(value),"=&j"(one):"j"(v));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(value));
    register qword lengthWord __asm__("$7");
    float length;
    __asm__("qmfc2.ni %0,%1":"=r"(lengthWord):"j"(value));
    __asm__("mtc1 %1,%0":"=f"(length):"r"(lengthWord));
    if(length<0.0001f)value=fallbackValue;
    else __asm__("vdiv $Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"+j"(value):"j"(v));
    return value;
}
static inline qword Transform(const M4 &m,qword p){qword r=m.basis.rows[0].q;__asm__("vmulax.xyz ACC,%0,%4x\n\tvmadday.xyz ACC,%1,%4y\n\tvmaddaz.xyz ACC,%2,%4z\n\tvmaddw.xyz %0,%3,$vf0w":"+j"(r):"j"(m.basis.rows[1].q),"j"(m.basis.rows[2].q),"j"(m.position.q),"j"(p));return r;}
static inline qword Scalar(float f,U *out){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));out->q=q;return out->q;}
static inline qword AddScaled(qword p,qword v,qword k){__asm__("vadda.xyzw ACC,$vf0,%0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(p):"j"(v),"j"(k));return p;}
static inline void ClearW(M3 *m){m->rows[2].i[3]=0;m->rows[1].i[3]=0;m->rows[0].i[3]=0;}
static inline void PublishProduct(U *first,U *second,qword value) {
    __asm__ volatile("sqc2 %2,%0\n\tsqc2 %2,%1":"=m"(first->q),"=m"(second->q):"j"(value));
}
static inline void UpdateBasis(M3 *current,const M3 *adjustment,M3 *returned,M3 *product,const M3 *original,const M3 *originalBasis) {
    register qword a0 __asm__("vf3")=adjustment->rows[0].q;
    register qword a1 __asm__("vf6")=adjustment->rows[1].q;
    register qword a2 __asm__("vf5")=adjustment->rows[2].q;
    register qword r0 __asm__("vf4")=original->rows[0].q;
    register qword r1 __asm__("vf2");
    register qword b2 __asm__("vf1");
    __asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(r0):"j"(a0),"j"(a1),"j"(a2));
    PublishProduct(&returned->rows[0],&product->rows[0],r0);
    __asm__("lqc2 %0,16(%1)":"=j"(r1):"r"(originalBasis),"m"(originalBasis->rows[1].q));
    __asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(r1):"j"(a0),"j"(a1),"j"(a2));
    PublishProduct(&returned->rows[1],&product->rows[1],r1);
    __asm__("lqc2 %0,32(%1)":"=j"(b2):"r"(originalBasis),"m"(originalBasis->rows[2].q));
    __asm__("vmulax.xyz $ACC,%0,%3x\n\tvmadday.xyz $ACC,%1,%3y\n\tvmaddz.xyz %0,%2,%3z":"+j"(a0):"j"(a1),"j"(a2),"j"(b2));
    current->rows[0].q=r0;current->rows[1].q=r1;current->rows[2].q=a0;
    PublishProduct(&product->rows[2],&returned->rows[2],a0);
}

static inline qword OffsetPoint(const U *point,qword up,int word,U *scalar) {
    register int bits __asm__("$3")=word;
    register qword factor __asm__("vf1"),result __asm__("vf2");
    __asm__("lqc2 %0,%2\n\tqmtc2.ni %3,%1":"=j"(result),"=j"(factor):"m"(point->q),"r"(bits));
    scalar->q=factor;
    __asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(result):"j"(up),"j"(scalar->q));
    return result;
}
extern "C" void func_00205910(P *p,HEIGHT *height,int pointCount,const qword *localPoints)
{
    M4 current,original;
    current.Init(Rotation(D_002A2DC0,p->heading),func_001A62E8(p));
    original=current;
    float radius=D_002A85F8;
    for(int i=0;i<pointCount;i++){float length=Length(localPoints[i]);radius=(radius>length)?radius:length;}
    FRAME storage;
    FRAME *frame=&storage;
    func_001AE478(frame);
    int nearbyCount;void **nearby;
    func_0020FC60(&D_003DD490,current.position.q,radius,func_0020FA50,p->attachment,&nearbyCount,&nearby);
    U points[3],point,scalar;
    M3 adjustment,returnedValue,productValue;
    float angle;
    int pass=0,again;
    if(D_002C3CE4>0)do{
        register int nextPass __asm__("$21")=pass+1;
        register const M3 *originalBasis __asm__("$22")=&original.basis;
        register M3 *returned __asm__("$23");
        __asm__("la %0,%a1":"=r"(returned):"p"(&returnedValue));
        qword up=current.basis.rows[2].q;
        for(int i=0;i<pointCount;i++){
            point.q=Transform(current,localPoints[i]);
            if(func_00173610(&point,height->max,height->min,0,0))points[i].q=point.q;
            else points[i].q=OffsetPoint(&point,up,D_002C3CE0.bits,&scalar);
        }
        qword origin=points[0].q;
        qword first=Subtract(points[1].q,origin);
        qword second=Subtract(points[2].q,origin);
        qword normal=Normalize(Cross(first,second,origin),&D_002A2DC0);
        func_0011BA08(returned,original.basis.rows[2].q,normal);
        adjustment=returnedValue;
        func_0011BCF8(&adjustment,&angle,&point);
        float limit=D_002C3CE8;
        if(limit<angle){func_0011B500(returned,point.q,limit);adjustment=returnedValue;}
        {register int future __asm__("$3");
         __asm__("daddu %0,%1,$zero":"=r"(future):"r"(nextPass));
         pass=future;}
        again=pass<D_002C3CE4;
        UpdateBasis(&current.basis,&adjustment,&returnedValue,&productValue,&original.basis,originalBasis);
        ClearW(&current.basis);
    }while(again);
    p->basis.rows[0].q=current.basis.rows[0].q;
    p->basis.rows[1].q=current.basis.rows[1].q;
    p->basis.rows[2].q=current.basis.rows[2].q;
    func_001AE4A0(frame,2);
}
