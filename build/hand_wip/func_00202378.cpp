typedef int qword __attribute__((mode(TI)));
union V {qword q;float f[4];};
struct QUERY {int count;struct LO **objects;V start;};
struct P {char pad20[0x20];qword position;};
struct LO {char padE4[0xE4];float radius;char padE8[0x20];int state;};
struct FRAME;
extern "C" FRAME *func_001AE478(FRAME *);
extern "C" void func_001AE4A0(FRAME *,int);
struct FRAME {FRAME(){func_001AE478(this);}~FRAME(){func_001AE4A0(this,2);}};
extern "C" qword func_001A62E8(LO *);
extern "C" int func_00202350(void *,LO *);
extern "C" void func_0020FAA0(void *,qword,qword,int (*)(void *,LO *),void *,int *,LO ***);
extern "C" LO *func_0014CC58(int,qword,qword,int,LO **,void *);
extern char D_003DD490[];
extern qword D_002DDFA0[3];
static inline qword Vector(qword q){register qword r __asm__("vf6");__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(q));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Cross(qword a,qword b){register qword r __asm__("vf3");__asm__("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scalar(float s,V *store){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(s));store->q=r;return store->q;}
static inline qword Scale(qword v,qword k){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(k));return r;}
static inline qword NormalDirection(qword v){register qword d __asm__("vf2"),one __asm__("vf3");
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(v));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));
    __asm__("vdiv $Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"+j"(d):"j"(v));return d;
}
static inline qword NormalLateral(qword v){register qword d __asm__("vf1"),one __asm__("vf7");
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(v));
    __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));
    __asm__("vdiv $Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"+j"(d):"j"(v));return d;
}
extern "C" void func_00202378(P *p,LO *other)
{
    int accepted=0;
    unsigned i=0;
    FRAME frame;
    V points[4],scale;
    QUERY query;
    float radius;
    V *point;
    query.start.q=Vector(func_001A62E8(other));
    radius=other->radius;
    func_0020FAA0(D_003DD490,query.start.q,p->position,func_00202350,0,&query.count,&query.objects);
    {
        register qword origin __asm__("vf6")=query.start.q;
        register qword up __asm__("vf4")=D_002DDFA0[1];
        register qword difference __asm__("vf1")=Sub(p->position,origin);
        register qword direction __asm__("vf2")=NormalDirection(difference);
        qword k=Scalar(radius,&scale);
        qword crossed=Cross(up,direction);
        register qword lateral __asm__("vf1")=NormalLateral(crossed);
        qword lower;
        direction=Scale(direction,k);
        origin=Add(origin,direction);
        up=Scale(up,k);
        lower=Sub(origin,up);
        lateral=Scale(lateral,k);
        lateral=Add(origin,lateral);
        up=Add(origin,up);
        points[1].q=up;points[2].q=lower;points[3].q=lateral;points[0].q=origin;
    }
    point=points;
    for(;i<4;++i){
        if(func_0014CC58(0,p->position,point->q,query.count,query.objects,0))++accepted;
        ++point;
    }
    switch(accepted){case 0:other->state=1;break;case 4:other->state=2;break;case 1:case 2:case 3:other->state=3;break;}
}
