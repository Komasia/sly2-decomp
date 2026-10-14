typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; int i[4]; };
struct M3 { U r[3]; M3(){} M3(const M3 &m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];} M3 &operator=(const M3 &m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return *this;} };
struct LO { M3 matrix; U position; M3 rotation; char pad[0x24]; int kind; short state; char pad9A[6]; LO *parent; int stamp; char padA8[8]; U velocity; };
struct VTE { short delta,pad; qword (*fn)(void *); };
struct P { char pad[0xC]; VTE *vt; char pad10[0x4C]; LO *object; };
extern "C" M3 *func_0011B340(M3 *,const M3 *);
static inline M3 Transpose(const M3 *input) return result {func_0011B340(&result,input);}
extern "C" void NormalizeRotateMatrix3__FP7MATRIX3(M3 *);
static inline M3 Mul(const M3 &a,const M3 &b) return r
{
    qword a0=a.r[0].q,a1=a.r[1].q,a2=a.r[2].q;
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[0].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[0].q));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[1].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[1].q));
    __asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r.r[2].q):"j"(a0),"j"(a1),"j"(a2),"j"(b.r[2].q));
}
struct M4 { M3 basis; U origin; };
extern U D_002A2DD0;
extern "C" M4 *func_0022D148(M4 *,LO *,LO *);
static inline qword Pack(float x,float y,float z) {
    qword r,t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0":"=&r"(r),"=&r"(t):"f"(x),"f"(y),"f"(z));
    return r;
}
extern "C" qword func_001F4558(P *p)
{
    LO *object=p->object;
    if(!object || object->kind!=6)return D_002A2DD0.q;
    M3 normalized;
    M3 angular;M4 velocity;
    M4 *pv=&velocity;
    func_0022D148(pv,object,0);
    angular=pv->basis;
    normalized=object->rotation;
    NormalizeRotateMatrix3__FP7MATRIX3(&normalized);
    M3 relative=Mul(normalized,Transpose(&object->rotation));
    angular=Mul(relative,angular);
    U result;
    result.q=Pack(angular.r[1].f[2],angular.r[2].f[0],angular.r[0].f[1]);
    return result.q;
}
