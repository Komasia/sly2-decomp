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
extern float D_002C3CE0,D_002C3CE8;
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
static inline qword Cross(qword a,qword b){qword r;__asm__("vopmula.xyz ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Square(qword a){qword one;__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(a),"=&j"(one));return a;}
static inline qword Root(qword a){__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(a));return a;}
static inline float X(qword a){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
static inline float Length(qword a){return X(Root(Square(a)));}
static inline qword Normalize(qword v,qword fallback){qword squared; qword one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(squared),"=&j"(one):"j"(v));qword length=Root(squared);if(X(length)<0.0001f)return fallback;qword r;__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(v),"j"(length));return r;}
static inline qword Transform(const M4 &m,qword p){qword r;__asm__("vmulax.xyz ACC,%1,%5x\n\tvmadday.xyz ACC,%2,%5y\n\tvmaddaz.xyz ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(r):"j"(m.basis.rows[0].q),"j"(m.basis.rows[1].q),"j"(m.basis.rows[2].q),"j"(m.position.q),"j"(p));return r;}
static inline qword Scalar(float f,U *out){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));out->q=q;return q;}
static inline qword AddScaled(qword p,qword v,qword k){__asm__("vadda.xyzw ACC,$vf0,%0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(p):"j"(v),"j"(k));return p;}
static inline M3 Mul(const M3 &a,const M3 &b) return r {
    qword a0=a.rows[0].q,a1=a.rows[1].q,a2=a.rows[2].q;
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.rows[0].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.rows[0].q));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.rows[1].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.rows[1].q));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.rows[2].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.rows[2].q));
}
static inline void ClearW(M3 *m){m->rows[2].i[3]=0;m->rows[1].i[3]=0;m->rows[0].i[3]=0;}
extern "C" void func_00205910(P *p,HEIGHT *height,int pointCount,const qword *localPoints)
{
    M4 current,original;
    current.Init(Rotation(D_002A2DC0,p->heading),func_001A62E8(p));
    original=current;
    float radius=D_002A85F8;
    for(int i=0;i<pointCount;i++){float length=Length(localPoints[i]);radius=(length>radius)?length:radius;}
    FRAME storage;
    FRAME *frame=&storage;
    func_001AE478(frame);
    int nearbyCount;void **nearby;
    func_0020FC60(&D_003DD490,current.position.q,radius,func_0020FA50,p->attachment,&nearbyCount,&nearby);
    U points[3];
    U point,scalar;
    M3 adjustment;
    float angle;
    for(int pass=0;pass<D_002C3CE4;pass++){
        qword up=current.basis.rows[2].q;
        for(int i=0;i<pointCount;i++){
            point.q=Transform(current,localPoints[i]);
            if(func_00173610(&point,height->max,height->min,0,0))points[i]=point;
            else points[i].q=AddScaled(point.q,up,Scalar(D_002C3CE0,&scalar));
        }
        qword first=Subtract(points[1].q,points[0].q);
        qword second=Subtract(points[2].q,points[0].q);
        qword normal=Normalize(Cross(first,second),D_002A2DC0);
        adjustment=Align(original.basis.rows[2].q,normal);
        func_0011BCF8(&adjustment,&angle,&point);
        float limit=D_002C3CE8;
        if(limit<angle)adjustment=Rotation(point.q,limit);
        current.basis=Mul(adjustment,original.basis);
        ClearW(&current.basis);
    }
    p->basis=current.basis;
    func_001AE4A0(frame,2);
}
