typedef int qword __attribute__((mode(TI)));
union U {qword q;float x;};
class FRAME;
struct LSG {qword a,point;char opaque[0x40];};
extern qword D_002A2DC0;
extern float D_002BE750,D_002BE754;
extern "C" FRAME*func_001AE478(FRAME*);
extern "C" void func_001AE4A0(FRAME*,int);
class FRAME {public:FRAME(){func_001AE478(this);} void Release(){func_001AE4A0(this,2);}};
extern "C" void func_001B44D8(int*,void***);
extern "C" void*func_0014CC58(int,qword,qword,int,void**,LSG*);
struct WORK {FRAME frame;U u;LSG lsg;int count;void**objects;};
extern "C" int func_0017D608(qword*pv){
 WORK work;
 register void***objectsAddress __asm__("$5")=&work.objects;
 func_001B44D8(&work.count,objectsAddress);
 const unsigned highOffset=0x2BE750,lowOffset=0x2BE754,axisLocation=0x2A2DC0;
 register char*scalarBase __asm__("$3"),*axisBase __asm__("$2");
 __asm__("lui %0,%2\n\tlui %1,%3":"=r"(scalarBase),"=r"(axisBase)
  :"i"((highOffset+0x8000)>>16),"i"((axisLocation+0x8000)>>16));
 register unsigned word __asm__("$3");
 register qword*axisAddress __asm__("$2");
 register qword a __asm__("vf4"),b __asm__("vf3"),axis __asm__("vf2"),point __asm__("vf1");
 __asm__("lw %0,%3\n\taddiu %1,%4,%5\n\tqmtc2.ni %0,%2"
  :"=r"(word),"=r"(axisAddress),"=j"(a)
  :"m"(*(unsigned*)(scalarBase+(short)(highOffset&0xffff))),"r"(axisBase),"i"((short)(axisLocation&0xffff)));
 __asm__("lqc2 %0,%2\n\tlui %1,%3":"=j"(axis),"=r"(scalarBase)
  :"m"(*axisAddress),"i"((lowOffset+0x8000)>>16));
 __asm__("lqc2 %0,%2\n\tlw %1,%3":"=j"(point),"=r"(word)
  :"m"(*pv),"m"(*(unsigned*)(scalarBase+(short)(lowOffset&0xffff))));
 register int queryFlags __asm__("$4");
 __asm__("daddu %0,%z2,%z2\n\tqmtc2.ni %3,%1":"=r"(queryFlags),"=j"(b):"J"(0),"r"(word));
 register qword endpoint __asm__("vf5");register qword endpointTo __asm__("$6");qword endpointFrom;register int count __asm__("$7");register void**objects __asm__("$8");
 __asm__ volatile("sqc2 %5,%1\n\tvadda.xyzw $ACC,%2,$vf0\n\tvmaddx.xyzw %0,%3,%4x":"=j"(endpoint),"=m"(work.u.q):"j"(point),"j"(axis),"j"(b),"j"(a));
 __asm__("lw %0,%4\n\tqmfc2.ni %1,%3\n\tlw %2,%5":"=r"(count),"=r"(endpointTo),"=r"(objects):"j"(endpoint),"m"(work.count),"m"(work.objects));
 __asm__ volatile("vadda.xyzw $ACC,%2,$vf0\n\tvmaddx.xyzw %0,%3,%4x\n\tsqc2 %5,%1":"=j"(endpoint),"=m"(work.u.q):"j"(point),"j"(axis),"j"(a),"j"(b));
 endpointFrom=endpoint;
 if(func_0014CC58(queryFlags,endpointFrom,endpointTo,count,objects,&work.lsg)){
 *pv=work.lsg.point;work.frame.Release();return 1;}
 work.frame.Release();return 0;
}

typedef char qword_size[(sizeof(qword)==16)?1:-1];
typedef char FRAME_size[(sizeof(FRAME)==1)?1:-1];
typedef char U_size[(sizeof(U)==16)?1:-1];
typedef char LSG_size[(sizeof(LSG)==0x60)?1:-1];
typedef char LSG_point[((unsigned)&((LSG*)0)->point==0x10)?1:-1];
typedef char WORK_size[(sizeof(WORK)==0x90)?1:-1];
typedef char WORK_frame[((unsigned)&((WORK*)0)->frame==0)?1:-1];
typedef char WORK_u[((unsigned)&((WORK*)0)->u==0x10)?1:-1];
typedef char WORK_lsg[((unsigned)&((WORK*)0)->lsg==0x20)?1:-1];
typedef char WORK_count[((unsigned)&((WORK*)0)->count==0x80)?1:-1];
typedef char WORK_objects[((unsigned)&((WORK*)0)->objects==0x84)?1:-1];
