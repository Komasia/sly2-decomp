typedef int qword __attribute__((mode(TI)));
typedef struct { short d,pad; void (*fn)(void *,...); } VE;
struct M3 { qword r[3]; };
struct M4 {M3 basis;qword position;};
struct O { char pad[0xC]; VE *vt; };
struct CONTROL {int id,state,pad;void *object;};
struct A { char pad[0xC]; VE *vt; char pad10[0xFB4]; void *color; char padFC8[8]; struct CONTROL basis; };
struct R { char pad[0x30]; int state; };
struct S { char pad[0xC]; VE *vt; char pad10[0x140]; int state; float time; char pad158[0x58]; struct O *source; struct A *actor; };
struct LM {float lo,hi;};
struct POLY {float a,b,c;};
extern "C" {
extern struct CLOCK { float t,dt; } D_002DDED0;
extern float D_002C43B0;extern POLY D_002C43C0;extern LM D_002BBB60;
extern char D_003DD490[],D_002DEB30[];
void func_002240B0(struct S *);
struct R *func_00205458(void *,int);
int func_0017A9C0(struct R *);
struct M4 *func_001A6318(void *);
void func_00209840(struct CONTROL *,const struct M3 *);
qword func_001A62E8(void *);
void func_0017A8C8(struct R *,int);
void func_0012D108(void *,qword);
void func_001C6FD8(void *,int,qword,void *,int);
void func_001619A0(void *,int,void *);
}
static inline qword Sub(qword a,qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a),"j"(b)); return r; }
static inline float Length(qword d) {
    qword one; float f;
    __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "+j"(d),"=j"(one));
    __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "+j"(d));
    __asm__("qmfc2.ni %0,%1" : "=r"(f) : "j"(d)); return f;
}
static inline void Clamp(float *f,const LM *bounds,const char *high){float upper=bounds->hi,lower=*(const float *)(high-0x44A0);if(*f<lower)*f=lower;else if(upper<*f)*f=upper;}
static inline qword Splat(float f) {
    unsigned long word; qword r;
    __asm__("pextlw %0,%1,%1" : "=r"(word) : "r"(f));
    __asm__("pextlw %0,%1,%1" : "=r"(r) : "r"(word));
    return r;
}
static inline const char *CurveHigh(){ const char *high ;asm("lui %0,%%hi(%1)":"=r"(high):"i"(&D_002C43C0));return high;}
static inline const POLY *CurveAt(const char *high){register const POLY *curve asm("$20");asm("addiu %0,%1,%%lo(%2)":"=r"(curve):"r"(high),"i"(&D_002C43C0));return curve;}
static inline const char *LimitsHigh(){ const char *high ;asm("lui %0,%%hi(%1)":"=r"(high):"i"(&D_002BBB60));return high;}
static inline const LM *LimitsAt(const char *high){register const LM *limits asm("$30");asm("addiu %0,%1,%%lo(%2)":"=r"(limits):"r"(high),"i"(&D_002BBB60));return limits;}
static inline char *NotifyHigh(){register char *high asm("$4");asm("lui %0,%%hi(%1)":"=r"(high):"i"(D_002DEB30));return high;}
static inline char *NotifyAt(char *high){register char *pointer asm("$4");asm("addiu %0,%1,%%lo(%2)":"=r"(pointer):"r"(high),"i"(D_002DEB30));return pointer;}
static inline qword ColorAndBroadcast(A *actor,float f,void *&color){
 register int bits asm("$2");asm("mfc1 %0,%1":"=r"(bits):"f"(f));
 register void *receiver asm("$4");register unsigned long pair asm("$2");
 asm("lw %1,%3\n\tpextlw %0,%2,%2":"=r"(pair),"=r"(receiver):"r"(bits),"m"(actor->color));
 qword result;asm("pextlw %0,%1,%1":"=r"(result):"r"(pair));color=receiver;return result;
}
extern "C" void func_00225300(struct S *p) {
    int old;
    const char *curveHigh=CurveHigh(),*limitsHigh=LimitsHigh();const POLY *curve=CurveAt(curveHigh);const LM *limits=LimitsAt(limitsHigh);
    func_002240B0(p);
    do {
        old=p->state;
        if(old==5) {
            struct R *r;
            if(!p->actor) {
                p->vt[76].fn((char*)p+p->vt[76].d,3);
            } else if(!(r=func_00205458(p->actor,0xB0)) || func_0017A9C0(r)) {
                p->vt[76].fn((char*)p+p->vt[76].d,2);
            } else {
                M3 m((p->source?func_001A6318(p->source):func_001A6318(p))->basis);
                func_00209840(&p->actor->basis,&m);
                if(r->state!=4) {
                    qword pos=p->source?func_001A62E8(p->source):func_001A62E8(p);
                    qword other;
                    other=func_001A62E8(p->actor);
                    if(Length(Sub(pos,other))<100.0f)func_0017A8C8(r,4);
                }
                if(p->actor->color) {
                    float t=(D_002DDED0.t-p->time)/D_002C43B0;
                    float g=*(const float *)(curveHigh+0x43C0)+t*(curve->b+t*curve->c);
                    Clamp(&g,limits,limitsHigh);
                    void *color;qword value=ColorAndBroadcast(p->actor,g,color);func_0012D108(color,value);
                }
                if(D_002C43B0<D_002DDED0.t-p->time) {
                    func_001C6FD8(D_003DD490,0x5D,func_001A62E8(p->source),p,1);
                    p->actor->vt[9].fn((char*)p->actor+p->actor->vt[9].d);
                    char *notificationHigh=NotifyHigh();
                    func_001619A0(NotifyAt(notificationHigh),0x18,p->actor);
                    p->vt[76].fn((char*)p+p->vt[76].d,3);
                }
            }
        }
    } while(p->state!=old);
}
