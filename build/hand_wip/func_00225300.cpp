// WIP: 47/177 instruction differences; complete state-5 actor update.
// Complete reconstruction; strict comparison currently has 47 differing instructions.
typedef int qword __attribute__((mode(TI)));
typedef struct { short d,pad; void (*fn)(void *,...); } VE;
struct M3 { qword r[3]; };
struct O { char pad[0xC]; VE *vt; };
struct CONTROL {int id,state,pad;void *object;};
struct A { char pad[0xC]; VE *vt; char pad10[0xFB4]; void *color; char padFC8[8]; struct CONTROL basis; };
struct R { char pad[0x30]; int state; };
struct S { char pad[0xC]; VE *vt; char pad10[0x140]; int state; float time; char pad158[0x58]; struct O *source; struct A *actor; };
extern "C" {
extern struct CLOCK { float t,dt; } D_002DDED0;
extern float D_002C43B0,D_002C43C0[4],D_002BBB60[2];
extern char D_003DD490[],D_002DEB30[];
void func_002240B0(struct S *);
struct R *func_00205458(void *,int);
int func_0017A9C0(struct R *);
struct M3 *func_001A6318(void *);
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
static inline void Clamp(float *f,float *bounds){if(*f<bounds[0])*f=bounds[0];else if(bounds[1]<*f)*f=bounds[1];}
static inline qword Splat(float f) {
    unsigned long word; qword r;
    __asm__("pextlw %0,%1,%1" : "=r"(word) : "r"(f));
    __asm__("pextlw %0,%1,%1" : "=r"(r) : "r"(word));
    return r;
}
extern "C" void func_00225300(struct S *p) {
    int old;
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
                M3 m(*(p->source?func_001A6318(p->source):func_001A6318(p)));
                func_00209840(&p->actor->basis,&m);
                if(r->state!=4) {
                    qword pos=p->source?func_001A62E8(p->source):func_001A62E8(p);
                    qword other;
                    other=func_001A62E8(p->actor);
                    if(Length(Sub(pos,other))<100.0f)func_0017A8C8(r,4);
                }
                if(p->actor->color) {
                    float t=(D_002DDED0.t-p->time)/D_002C43B0;
                    float g=D_002C43C0[0]+t*(D_002C43C0[1]+t*D_002C43C0[2]);
                    Clamp(&g,D_002BBB60);
                    func_0012D108(p->actor->color,Splat(g));
                }
                if(D_002C43B0<D_002DDED0.t-p->time) {
                    func_001C6FD8(D_003DD490,0x5D,func_001A62E8(p->source),p,1);
                    p->actor->vt[9].fn((char*)p->actor+p->actor->vt[9].d);
                    func_001619A0(D_002DEB30,0x18,p->actor);
                    p->vt[76].fn((char*)p+p->vt[76].d,3);
                }
            }
        }
    } while(p->state!=old);
}
