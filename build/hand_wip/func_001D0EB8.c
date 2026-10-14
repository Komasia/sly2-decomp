typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct B { qword x,y; };
struct S { char pad[0x70]; qword pos; char pad80[0x10]; qword vel; };
extern qword D_002A2DD0,D_002A2DA0,D_002A2DC0;
union FLOATWORD {float value;int bits;};
struct CLOCK {float time;union FLOATWORD dt;};
extern struct CLOCK D_002DDED0;
void func_001CF0A0(struct S*);
float func_0011D448(float,float);
int func_0011D4D0(float,float,float);
void func_0011E2D8(qword,qword,qword,struct B*);
void func_0011D608(float,float*,float*);
static inline float X(qword q) {float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(q)); return f;}
static inline float Y(qword q) {float f; __asm__("prot3w %0,%1" : "=r"(f) : "r"(q)); return f;}
static inline float Z(qword q) {float f; __asm__("pextuw %0,$zero,%1" : "=r"(f) : "r"(q)); return f;}
static inline void FNear(int *pf,qword a,qword b) { if(func_0011D4D0(X(b),X(a),0.0001f)) if(func_0011D4D0(Y(b),Y(a),0.0001f)) *pf=func_0011D4D0(Z(b),Z(a),0.0001f)!=0; }
static inline void Bc(float f,union U *pu) {
    __asm__("qmtc2.ni %1,%0" : "=j"(pu->q) : "r"(f));
}
static inline void BcWord(int bits,union U*pu) {
    __asm__("qmtc2.ni %1,%0" : "=j"(pu->q) : "r"(bits));
}
static inline qword Norm(qword a) {
    register qword d __asm__("vf2"); qword one,r;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d),"=&j"(one) : "j"(a));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(d) : "j"(d));
    __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(r) : "j"(d),"j"(a));
    return r;
}
void func_001D0EB8(struct S*p) {
    int near=0,choose=0;
    float roll;
    func_001CF0A0(p);
    roll=func_0011D448(0.0f,1.0f);
    FNear(&near,p->vel,D_002A2DD0);
    if(!near&&roll<0.3f) choose=1;
    if(choose) {
        union U norm;
        struct B basis;
        union U dir,scalar;
        float speed,angle,cs[2];
        qword kx,ky,kt,r;
        norm.q=Norm(p->vel);
        func_0011E2D8(norm.q,D_002A2DA0,D_002A2DC0,&basis);
        speed=func_0011D448(100.0f,100.0f+(1.0f-roll*3.33333325386f)*300.0f);
        angle=func_0011D448(0.0f,6.28318548203f);
        func_0011D608(angle,&cs[0],&cs[1]);
        Bc(cs[0]*speed,&scalar); kx=scalar.q; Bc(cs[1]*speed,&scalar); ky=scalar.q; BcWord(D_002DDED0.dt.bits,&scalar); kt=scalar.q;
        __asm__("vmulax.xyzw $ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x" : "=j"(dir.q) : "j"(basis.x),"j"(kx),"j"(basis.y),"j"(ky));
        __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(p->pos),"j"(dir.q),"j"(kt));
        p->pos=r;
    }
}
