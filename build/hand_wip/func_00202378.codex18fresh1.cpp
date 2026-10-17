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
extern "C" void func_00202378(P *input,LO *actor)
{
    register P *p __asm__("$19");
    register LO *other __asm__("$18");
    __asm__("daddu %0,%1,$zero":"=r"(p):"r"(input));
    __asm__("daddu %0,%1,$zero":"=r"(other):"r"(actor));
    int accepted=0;
    unsigned i=0;
    FRAME frame;
    V points[4],scale;
    QUERY query;
    float radius;
    register V *point __asm__("$16");
    qword returnedPosition=func_001A62E8(other);
    register qword startVector __asm__("vf6");
    register qword queryPosition __asm__("$6"),queryStart __asm__("$5");
    __asm__("qmtc2.ni %3,%0\n\tlwc1 %1,%4\n\tlq %2,%5":"=j"(startVector),"=f"(radius),"=r"(queryPosition):"r"(returnedPosition),"m"(other->radius),"m"(p->position));
    __asm__("qmfc2.ni %0,%2\n\tsqc2 %2,%1":"=r"(queryStart),"=m"(query.start.q):"j"(startVector));
    func_0020FAA0(D_003DD490,queryStart,queryPosition,func_00202350,0,&query.count,&query.objects);
    {
        register qword origin __asm__("vf6");
        register qword difference __asm__("vf1");
        register char *cameraBase __asm__("$2");
        register qword up __asm__("vf4");
        register qword direction __asm__("vf2");
        register qword crossed __asm__("vf3"); // Retains the native incoming W lane.
        register qword factor __asm__("vf5");
        register qword lateral __asm__("vf1");
        register qword one __asm__("vf7");
        register int radiusWord __asm__("$2");
        __asm__("lqc2 %0,%3\n\tlui %1,%%hi(%4)\n\tlqc2 %2,%5":"=j"(difference),"=&r"(cameraBase),"=j"(origin):"m"(p->position),"i"(D_002DDFA0),"m"(query.start.q));
        __asm__("addiu %0,%0,%%lo(%1)":"+r"(cameraBase):"i"(D_002DDFA0));
        __asm__("vsub.xyzw %0,%0,%2\n\tlqc2 %1,%3":"+j"(difference),"=j"(up):"j"(origin),"m"(((const qword*)cameraBase)[1]));
        __asm__("vmul.xyz %0,%3,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z\n\tmfc1 %2,%4":"=&j"(direction),"+&j"(crossed),"=r"(radiusWord):"j"(difference),"f"(radius));
        __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q\n\tqmtc2.ni %2,%1":"+j"(direction),"=j"(factor):"r"(radiusWord));
        __asm__("vdiv $Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"+j"(direction):"j"(difference));
        scale.q=factor;
        factor=scale.q;
        __asm__("vopmula.xyz $ACC,%2,%3\n\tvopmsub.xyz %0,%3,%2\n\tla %1,%a4":"+j"(crossed),"=r"(point):"j"(up),"j"(direction),"p"(points));
        __asm__("vmul.xyz %0,%3,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z\n\tvmulx.xyzw %2,%2,%4x":"=&j"(lateral),"=&j"(one),"+j"(direction):"j"(crossed),"j"(factor));
        __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q\n\tvadd.xyzw %1,%1,%3\n\tvmulx.xyzw %2,%2,%4x":"+&j"(lateral),"+&j"(origin),"+j"(up):"j"(direction),"j"(factor));
        __asm__("vdiv $Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"+j"(lateral):"j"(crossed));
        __asm__("vsub.xyzw %0,%3,%1\n\tvmulx.xyzw %2,%2,%4x\n\tvadd.xyzw %2,%3,%2\n\tvadd.xyzw %1,%3,%1":"=&j"(direction),"+j"(up),"+&j"(lateral):"j"(origin),"j"(factor));
        __asm__("sqc2 %4,%0\n\tsqc2 %5,%1\n\tsqc2 %6,%2\n\tsqc2 %7,%3":"=m"(points[1].q),"=m"(points[2].q),"=m"(points[3].q),"=m"(points[0].q):"j"(up),"j"(direction),"j"(lateral),"j"(origin));
    }
    for(;i<4;++i){
        if(func_0014CC58(0,p->position,point->q,query.count,query.objects,0))++accepted;
        ++point;
    }
    switch(accepted){case 0:other->state=1;break;case 4:other->state=2;break;case 1:case 2:case 3:other->state=3;break;}
}
