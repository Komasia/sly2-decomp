// Prepare contact limits and construct a horizontal response contact.
typedef int qword __attribute__((mode(TI)));
union VECTOR {qword q;float f[4];};
struct XP;
struct ENDPOINT {void *shape,*owner,*object,*lo;union VECTOR position,local;int pad[4];};
struct XP {struct ENDPOINT endpoints[2];union VECTOR normal;float distance,friction,response;int kind;float lower,upper;int tag;struct XP *next;};
struct STATE {char pad[0xD0];float mass;};
struct P {char padE8[0xE8];struct STATE *state;char padEC[0x16C];void *mesh;};
extern char D_003DD490[];
extern qword D_002A2DA0;
extern float D_002C3C60[],D_002C3C90;
void func_001F4FB0(void);
void func_001A7C18(void *,void *,void *,qword,qword,int,float,int,int,struct XP **);
static inline const struct ENDPOINT *OppositeEndpoint(struct XP *x,int side){
    register const struct ENDPOINT *result __asm__("$4");
    unsigned offset=(unsigned)(1-side)*sizeof(struct ENDPOINT);
    __asm__("addu %0,%1,%2":"=r"(result):"r"(offset),"r"(x));return result;
}
static inline const struct ENDPOINT *EndpointDifference(const struct ENDPOINT *first,const struct ENDPOINT *second,union VECTOR *home,const union VECTOR *axisHome,qword *deltaValue,qword *axisValue,qword *otherCarrier){
    register const struct ENDPOINT *primary __asm__("$2")=first;
    register const struct ENDPOINT *other __asm__("$4")=second;
    register qword a __asm__("vf1"),b __asm__("vf2"),axis __asm__("vf3");
    register const struct ENDPOINT *retained __asm__("$2");
    __asm__("lqc2 %0,%1":"=j"(a):"m"(primary->position.q));
    __asm__("lqc2 %0,16(%2)\n\tdaddu %1,%2,$zero"
       :"=j"(b),"=r"(retained):"r"(other),"m"(other->position.q));
    __asm__("vsub.xyzw %0,%0,%2\n\tlqc2 %1,%3":"+j"(a),"=j"(axis):"j"(b),"m"(axisHome->q));
    __asm__ __volatile__("sqc2 %1,%0":"=m"(home->q):"j"(a));
    *deltaValue=a;*axisValue=axis;*otherCarrier=b;return retained;
}
static __inline__ qword Scale(qword a,float f,union VECTOR *scalar){qword k;__asm__("qmtc2.ni %1,%0":"=j"(k):"r"(f));scalar->q=k;__asm__("vmulx.xyzw %0,%0,%1x":"+j"(a):"j"(scalar->q));return a;}
static __inline__ qword Normal(union VECTOR *v,qword fallback){qword a=v->q,one;register qword d __asm__("vf1");float len;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(a));__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(d):"0"(d));__asm__("qmfc2.ni %0,%1":"=r"(len):"j"(d));if(len<0.0001f){d=fallback;}else{__asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,Q":"=j"(d):"j"(d),"j"(a));}return d;}
static inline void PublishNormalAndEndpoints(union VECTOR *home,qword normal,struct XP *contact,int side,const struct ENDPOINT **firstValue,const struct ENDPOINT **otherValue,unsigned *offsetValue,union VECTOR *publicationAddress){
    register const struct ENDPOINT *first __asm__("$2"),*other __asm__("$4");
    register unsigned offset __asm__("$3");
    register union VECTOR *publication __asm__("$4")=publicationAddress;
    __asm__ volatile("addiu %1,$zero,1\n\tsqc2 %4,0(%7)\n\tsubu %1,%1,%6\n\tsll %0,%6,6\n\tsll %1,%1,6\n\taddu %0,%0,%5\n\taddu %2,%1,%5"
        :"=&r"(first),"=&r"(offset),"=r"(other),"=m"(home->q)
        :"j"(normal),"r"(contact),"r"(side),"r"(publication));
    *firstValue=first;*otherValue=other;*offsetValue=offset;
}
static __inline__ qword Dot(qword a,qword b,qword carrier,struct XP *contact,unsigned offset,const struct ENDPOINT **shapeEndpoint){register qword d __asm__("vf2")=carrier;qword one;register qword word __asm__("$9");__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(d),"=&j"(one):"j"(a),"j"(b));{register unsigned shapeAddress __asm__("$3")=offset;
__asm__("qmfc2.ni %0,%2\n\taddu %1,%3,%1":"=&r"(word),"+r"(shapeAddress):"j"(d),"r"(contact));
*shapeEndpoint=(const struct ENDPOINT *)shapeAddress;}return word;}
static inline qword PreparePoint(const struct ENDPOINT *input,qword axis,qword bits,void **meshSlot,qword *factorValue,void **worldValue,void **meshValue){
    register const struct ENDPOINT *base __asm__("$2")=input;
    register qword factor __asm__("vf2"),point __asm__("vf1");
    register void *world __asm__("$4"),*mesh __asm__("$5");
    __asm__("qmtc2.ni %4,%0\n\tlui %1,%%hi(%6)\n\tlqc2 %2,16(%5)\n\taddiu %1,%1,%%lo(%6)\n\tlw %3,%8"
      :"=j"(factor),"=&r"(world),"=j"(point),"=r"(mesh)
      :"r"(bits),"r"(base),"i"(D_003DD490),"m"(base->position.q),"m"(*meshSlot));
    __asm__("vadda.xyzw ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(point):"j"(axis),"j"(factor));
    *factorValue=factor;*worldValue=world;*meshValue=mesh;return point;
}
static inline void ShapeAndNext(const struct ENDPOINT *endpoint,struct XP *contact,void **shapeValue,struct XP ***nextValue){
    register void *shape __asm__("$6");
    register struct XP **next __asm__("$2");
    __asm__("lw %0,%2\n\taddiu %1,%3,172"
      :"=&r"(shape),"=r"(next):"m"(endpoint->shape),"r"(contact));
    *shapeValue=shape;*nextValue=next;
}
static inline void PointAndSeparation(qword bits,qword point,float *separation,qword *pointArgument){
    register float value __asm__("$f12");
    register qword argument __asm__("$7");
    __asm__("mtc1 %2,%0\n\tqmfc2.ni %1,%3":"=f"(value),"=r"(argument):"r"(bits),"j"(point));
    *separation=value;*pointArgument=argument;
}
static inline qword DirectionAndScalar(union VECTOR *scalar,qword direction,qword factor){
    register qword argument __asm__("$8");
    __asm__ volatile("qmfc2.ni %0,%2\n\tsqc2 %3,%1"
      :"=r"(argument),"=m"(scalar->q):"j"(direction),"j"(factor));
    return argument;
}
static inline qword PointAndPublication(union VECTOR *point,qword pointValue,qword argument){
    __asm__ volatile("sqc2 %1,%0":"=m"(point->q):"j"(pointValue));
    return argument;
}
static inline void WriteContact(void *world,void *mesh,void *shape,qword pointValue,qword axis,qword dot,qword factor,union VECTOR *point,union VECTOR *scalar,struct XP **next){
    float separation;
    qword pointArgument;
    PointAndSeparation(dot,pointValue,&separation,&pointArgument);
    func_001A7C18(world,mesh,shape,PointAndPublication(point,pointValue,pointArgument),DirectionAndScalar(scalar,axis,factor),10,separation,0,0,next);
}
void func_00204250(struct P *p,struct XP *x,int suppliedSide)
{
    union VECTOR direction,difference,point,scalar;
    float sign;qword dot,deltaValue,axisValue,otherCarrier;
    qword pointValue,factorValue;
    void *world,*mesh,*shape;
    struct XP **next;
    register const struct ENDPOINT *retained __asm__("$2");
    int kind,side;
    const struct ENDPOINT *shapeEndpoint,*firstEndpoint,*otherEndpoint;
    unsigned otherOffset;
    qword normalized;
    {
        register int sidePort __asm__("$17");
        __asm__("daddu %0,%1,$zero":"=r"(sidePort):"r"(suppliedSide));
        side=sidePort;
    }
    func_001F4FB0();
    kind=x->kind;x->friction=0.0f;x->response=0.0f;
    if(kind==14){
        if(x->normal.f[2]>0.7f){
            x->friction=D_002C3C90;
            x->lower=p->state->mass*-4500.0f;
            x->upper=p->state->mass*9000.0f;
        }else x->upper=p->state->mass*9000.0f;
        return;
    }
    if(kind!=3){
        if(side!=1)return;
        if(kind!=side && kind!=4 && kind!=5 && kind!=6)return;
    }
    sign=D_002C3C60[side];
    if(sign*x->normal.f[2]>0.0f){
    register union VECTOR *normalHome __asm__("$4")=&direction;
    direction.q=Scale(x->normal.q,sign,&scalar);
    direction.f[2]=0.0f;
    normalized=Normal(normalHome,D_002A2DA0);
    PublishNormalAndEndpoints(&direction,normalized,x,side,&firstEndpoint,&otherEndpoint,&otherOffset,normalHome);
    retained=EndpointDifference(firstEndpoint,otherEndpoint,&difference,&direction,&deltaValue,&axisValue,&otherCarrier);
    dot=Dot(deltaValue,axisValue,otherCarrier,x,otherOffset,&shapeEndpoint);
    pointValue=PreparePoint(retained,axisValue,dot,&p->mesh,&factorValue,&world,&mesh);
    ShapeAndNext(shapeEndpoint,x,&shape,&next);
    WriteContact(world,mesh,shape,pointValue,axisValue,dot,factorValue,&point,&scalar,next);
    }
}
