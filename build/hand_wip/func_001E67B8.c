typedef int qword __attribute__((mode(TI)));
struct M { qword a,b,c,d; };
struct VTE { short d; short pad; void (*pf)(); };
struct S { char pad[0xC]; struct VTE *vt; char pad2[0xE0-0x10]; int e0; char pad3[0xF4-0xE4]; qword *v; char pad4[0x140-0xF8]; qword *v140,*v144; };
union U { qword q; float f; };
int func_001E7538(struct S*,float,float*,float*);
void func_00117120(float,float,float,qword,qword,qword,qword,qword*,qword*,qword*);
static inline qword Bc(float f) { union U u; qword r; __asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f)); u.q=r; return u.q; }
static inline qword Sub(qword a,qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r; }
static inline qword Lerp(qword a,qword b,qword w0,qword w1) { __asm__("vmulax.xyzw $ACC,%1,%0x\n\tvmaddx.xyzw %0,%2,%3x":"+j"(w0):"j"(a),"j"(b),"j"(w1));return w0; }
static inline qword PointKept(qword keep,struct M *m,qword a) {__asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(keep):"j"(m->a),"j"(m->b),"j"(m->c),"j"(m->d),"j"(a));return keep;}
static inline qword Dir(struct M *m,qword a) { __asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(a):"j"(m->a),"j"(m->b),"j"(m->c));return a; }
static inline qword Norm(qword a) {qword d,one;
__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z\n\tvsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q\n\tvdiv $Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=&j"(d),"=&j"(one):"j"(a));return d;}
void func_001E67B8(struct S *p,float g,qword *pos,qword *dir)
{
    struct M m;
    float elapsed,duration; qword tangent;
    int i=func_001E7538(p,g,&elapsed,&duration);
    m=* ((struct M *(*)(void*))p->vt[31].pf)((char*)p+p->vt[31].d);
    if (p->e0==0) {
        if (pos) {
            float t=elapsed/duration;
            qword w0=Bc(1.0f-t),w1=Bc(t);
            {qword blend=Lerp(p->v[i],p->v[i+1],w0,w1);*pos=PointKept(blend,&m,blend);}
        }
        if (!dir) return;
        tangent=Sub(p->v[i+1],p->v[i]);
    } else {
        func_00117120(duration,elapsed,1.0f,p->v[i],p->v144[i],p->v[i+1],p->v140[i+1],pos,dir,0);
        if (pos) *pos=PointKept(m.a,&m,*pos);
        if (!dir) return;
        tangent=*dir;
    }
    *dir=Norm(Dir(&m,tangent));
}
