typedef int qword __attribute__((mode(TI)));
struct M { qword a,b,c,d; };
struct VTE { short d; short pad; void (*pf)(); };
struct S { char pad[0xC]; struct VTE *vt; char pad2[0xE0-0x10]; int e0; char pad3[0xF4-0xE4]; qword *v; char pad4[0x140-0xF8]; qword *v140,*v144; };
union U { qword q; float f; };
int func_001E7538(struct S*,float,float*,float*);
void func_00117120(float,float,float,qword,qword,qword,qword,qword*,qword*,qword*);
static inline qword ReadTangent(const qword*p){register qword a __asm__("vf2");__asm__("lqc2 %0,%1":"=j"(a):"m"(*p));return a;}
static inline qword ReadLinearFirst(const qword*p){register qword value __asm__("vf3");__asm__("lqc2 %0,%1":"=j"(value):"m"(*p));return value;}
static inline qword ReadLinearSecond(const qword*p){register qword value __asm__("vf2");__asm__("lqc2 %0,%1":"=j"(value):"m"(*p));return value;}
static inline qword Bc(float f) { union U u; qword r; __asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f)); u.q=r; return u.q; }
static inline qword Sub(qword next,qword first){register qword a __asm__("vf2")=next,b __asm__("vf1")=first;__asm__("vsub.xyzw %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline qword Lerp(qword a,qword b,qword w0,qword w1) { __asm__("vmulax.xyzw $ACC,%1,%0x\n\tvmaddx.xyzw %0,%2,%3x":"+j"(w0):"j"(a),"j"(b),"j"(w1));return w0; }
static inline qword HermitePoint(struct M*m,qword value){register qword keep __asm__("vf2")=m->a,row1 __asm__("vf4")=m->b,row2 __asm__("vf3")=m->c,translation __asm__("vf1")=m->d,point __asm__("vf5")=value;__asm__("vmulax.xyz $ACC,%0,%4x\n\tvmadday.xyz $ACC,%1,%4y\n\tvmaddaz.xyz $ACC,%2,%4z\n\tvmaddw.xyz %0,%3,$vf0w":"+j"(keep):"j"(row1),"j"(row2),"j"(translation),"j"(point));return keep;}
static inline qword PointKept(qword keep,struct M *m,qword a) {__asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(keep):"j"(m->a),"j"(m->b),"j"(m->c),"j"(m->d),"j"(a));return keep;}
static inline void ReadRows(const struct M*matrix,qword*a,qword*b,qword*c){register qword x __asm__("vf5"),y __asm__("vf4"),z __asm__("vf3");__asm__("lqc2 %0,%1":"=j"(x):"m"(matrix->a));__asm__("lqc2 %0,%1":"=j"(y):"m"(matrix->b));__asm__("lqc2 %0,%1":"=j"(z):"m"(matrix->c));*a=x;*b=y;*c=z;}
void func_001E67B8(struct S *p,float g,qword *pos,qword *dir)
{
    struct M m;
    float elapsed,duration;
    qword row0,row1,row2;
    register qword tangent __asm__("vf2");
    int i=func_001E7538(p,g,&elapsed,&duration);
    m=* ((struct M *(*)(void*))p->vt[31].pf)((char*)p+p->vt[31].d);
    if (p->e0==0) {
        if (pos) {
            float t=elapsed/duration;
            qword w0=Bc(1.0f-t),w1=Bc(t);
            {qword first=ReadLinearFirst(p->v+i),second=ReadLinearSecond(p->v+i+1);qword blend=Lerp(first,second,w0,w1);*pos=PointKept(blend,&m,blend);}
        }
        if (!dir) return;
        ReadRows(&m,&row0,&row1,&row2);
        tangent=Sub(p->v[i+1],p->v[i]);
    } else {
        func_00117120(duration,elapsed,1.0f,p->v[i],p->v144[i],p->v[i+1],p->v140[i+1],pos,dir,0);
        if (pos) *pos=HermitePoint(&m,*pos);
        if (!dir) return;
        ReadRows(&m,&row0,&row1,&row2);
        tangent=ReadTangent(dir);
    }
    {register qword d __asm__("vf1"),one __asm__("vf6");
    __asm__("vmulax.xyz $ACC,%4,%2x\n\tvmadday.xyz $ACC,%5,%2y\n\tvmaddz.xyz %2,%6,%2z\n\tvmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z\n\tvsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q\n\tvdiv $Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q\n\tsqc2 %0,%3":"=&j"(d),"=&j"(one),"+j"(tangent),"=m"(*dir):"j"(row0),"j"(row1),"j"(row2));}
}
