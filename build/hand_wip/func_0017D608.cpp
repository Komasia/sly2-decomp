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
static inline qword Scalar(unsigned int value){register unsigned int word asm("$3")=value;qword q;asm("qmtc2.ni %1,%0":"=j"(q):"r"(word));return q;}
static inline qword MAdd(qword p,qword axis,qword scalar,U&u){qword r;u.q=scalar;asm("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(p),"j"(axis),"j"(u.q));return r;}
extern "C" int func_0017D608(qword*pv){
 WORK work;
 func_001B44D8(&work.count,&work.objects);
 qword a=Scalar(*(unsigned int*)&D_002BE750);
 qword b=Scalar(*(unsigned int*)&D_002BE754);
 qword axis=D_002A2DC0,point=*pv;
 if(func_0014CC58(0,MAdd(point,axis,a,work.u),MAdd(point,axis,b,work.u),work.count,work.objects,&work.lsg)){
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
