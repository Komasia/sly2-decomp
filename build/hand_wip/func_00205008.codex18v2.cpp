typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M3 {U row[3];};
struct XP;
struct P;
struct NODE {XP *contacts;NODE *next;XP **output;P *target;};
struct ATT {char pad0[0x34];void *head;char pad38[0x28];P *owner;NODE *list;XP *contacts;};
struct P {char pad0[0x10];P *parent;char pad14[0xD8];ATT *attachment;char padF0[0x168];void *mesh;};
extern char D_003DD490[];
extern qword D_002A2DC0;
extern "C" P *func_001A5BF0(P *);
extern "C" M3 *func_0011B830(M3 *,qword,qword);
extern "C" void func_001A7C18(void *,void *,void *,qword,qword,int,float,int,int,XP **);
static inline qword Difference(const qword *point,const qword *other){
    qword first,second,delta;
    __asm__ __volatile__("lqc2 %1,%3\n\tlqc2 %0,%4\n\tvsub.xyzw %2,%1,%0"
       :"=&j"(first),"=&j"(second),"=&j"(delta)
       :"m"(*point),"m"(*other));
    return delta;
}
static inline qword Load(const qword *q){qword r;__asm__ __volatile__("lqc2 %0,%1":"=j"(r):"m"(*q));return r;}
static inline qword Project(qword delta,qword x,qword y,qword z){
    qword px,py,pz,one,result;
    __asm__("vmul.xyzw %1,%6,%5\n\tvmaxw.xyzw %0,$vf0,$vf0w\n\tvmul.xyzw %2,%7,%5\n\tvmul.xyzw %3,%8,%5\n\tvadday.x $ACC,%1,%1y\n\tvmaddz.x %4,%0,%1z\n\tvaddax.y $ACC,%2,%2x\n\tvmaddz.y %4,%0,%2z\n\tvaddax.z $ACC,%3,%3x\n\tvmaddy.z %4,%0,%3y"
        :"=&j"(one),"=&j"(px),"=&j"(py),"=&j"(pz),"=&j"(result)
        :"j"(delta),"j"(x),"j"(y),"j"(z));
    return result;
}
static inline float X(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline float Y(qword q){float f;int w;__asm__("prot3w %0,%1":"=r"(w):"r"(q));__asm__("mtc1 %1,%0":"=f"(f):"r"(w));return f;}
static inline float Z(qword q){float f;int w;__asm__("pextuw %0,$zero,%1":"=r"(w):"r"(q));__asm__("mtc1 %1,%0":"=f"(f):"r"(w));return f;}
template<int Axis,int Otherwise>
static inline void EmitPlaneContact(qword row,const qword *point,P *object,void *head,int selected,qword distance,XP **chain){
    float component=Axis==1?Y(distance):Z(distance);
    func_001A7C18(D_003DD490,object->mesh,head,*point,row,selected?11:Otherwise,component,0,0,chain);
}
extern "C" void func_00205008(P *p,int flags,P *owner,qword other,qword direction,qword point)
{
    int keptFlags;
    {
        register int value __asm__("$17");
        __asm__("daddu %0,%1,$zero":"=r"(value):"r"(flags));
        keptFlags=value;
    }
    flags=keptFlags;
    qword keptDirection;
    {
        register qword value __asm__("$30");
        __asm__("por %0,$zero,%1":"=r"(value):"r"(direction));
        keptDirection=value;
    }
    M3 basis;
    XP **chain,**output;
    void *head;
    int x,y,z;
    qword delta,axis,yrow,zrow;
    {
    P *object=func_001A5BF0(owner);
    register M3 *matrix __asm__("$16")=&basis;
    if(!object)goto fallback;
    {
        ATT *target=object->attachment;
        ATT *source=p->attachment;
        x=flags&1;y=flags&2;z=flags&4;
        if(!target){
            while((object=object->parent)!=0){target=object->attachment;if(target)break;}
        }
        if(!object)goto fallback;
        P *group=target->owner;
        NODE *node=source->list;
        while(node && node->target!=group)node=node->next;
        chain=&node->contacts;output=node->output;
        head=group->attachment->head;
        goto linked;
    }
fallback:
    head=0;chain=output=&p->attachment->contacts;x=flags&1;y=flags&2;z=flags&4;
linked:
      func_0011B830(&basis,keptDirection,D_002A2DC0);
      delta=Difference(&point,&other);
      axis=Load(&basis.row[0].q);
      yrow=matrix->row[1].q;zrow=matrix->row[2].q;
    }
    qword distance=Project(delta,axis,yrow,zrow);
    if(x || ((flags&8) && X(distance)<0.0001f))
        func_001A7C18(D_003DD490,p->mesh,head,point,axis,x?11:10,X(distance),0,0,chain);
    if(y || ((flags&16) && Y(distance)<0.0001f))
        EmitPlaneContact<1,10>(basis.row[1].q,&point,p,head,y,distance,chain);
    if(z || ((flags&32) && Z(distance)<0.0001f))
        EmitPlaneContact<2,14>(basis.row[2].q,&point,p,head,z,distance,chain);
    *output=*chain;
}
