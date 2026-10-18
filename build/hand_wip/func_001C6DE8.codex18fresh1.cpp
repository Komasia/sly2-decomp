typedef int qword __attribute__((mode(TI)));
register void*architecturalNull __asm__("$0");
union U {qword q;float f[4];};
struct HIT {qword a,b;U normal,otherNormal;float t,u;char pad48[0x18];};
struct FRAME {};
extern "C" {
FRAME*func_001AE478(FRAME*);
void func_001AE4A0(FRAME*,int);
struct O;int func_001C5570(void*,O*);
void func_0020FAA0(void*,qword,qword,int(*)(void*,O*),void*,int*,O***);
O*PsoHitTestLineObjects(int,qword,qword,int,O**,HIT*) __asm__("PsoHitTestLineObjects__FiP6VECTORT1iPP2SOP3LSG");
extern char D_003DD490[];
extern qword D_002A2DC0;
int func_001C6DE8(float lo,float hi,float threshold,qword point,int count,O**objects,qword*out);
}

struct WORK{HIT hit;FRAME frame;U scalar;int count;O**objects;qword point,upper,lower;};
static inline FRAME*EnterFrame(FRAME*p){register FRAME*argument __asm__("$4")=p;register FRAME*receiver __asm__("$17");__asm__("daddu %0,%1,$zero":"=r"(receiver):"r"(argument));func_001AE478(argument);return receiver;}
int func_001C6DE8(float lo,float hi,float threshold,qword point,int count,O**objects,qword*out){
 WORK work;
 work.point=point;work.objects=objects;work.count=count;
 FRAME*guard=EnterFrame(&work.frame);
 register qword high __asm__("vf2"),low __asm__("vf3"),axis __asm__("vf1"),endpoint __asm__("vf4");
 register unsigned word __asm__("$2");
 __asm__("mfc1 %0,%1":"=r"(word):"f"(hi));
 __asm__("qmtc2.ni %1,%0":"=j"(high):"r"(word));
 __asm__("lqc2 %0,%1":"=j"(axis):"m"(D_002A2DC0));
 __asm__("mfc1 %0,%1":"=r"(word):"f"(lo));
 __asm__("qmtc2.ni %1,%0":"=j"(low):"r"(word));
 __asm__ __volatile__("lqc2 %0,%3\n\tvadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%4,%5x\n\tsqc2 %6,%1\n\tsqc2 %0,%2"
  :"=&j"(endpoint),"=m"(work.scalar.q),"=m"(work.lower)
  :"m"(work.point),"j"(axis),"j"(low),"j"(high));
 register O**list __asm__("$2");
 __asm__ __volatile__("lqc2 %0,%4\n\tvadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%5,%6x\n\tlw %1,%7\n\tsqc2 %0,%2\n\tsqc2 %8,%3"
  :"=&j"(endpoint),"=r"(list),"=m"(work.upper),"=m"(work.scalar.q)
  :"m"(work.point),"j"(axis),"j"(high),"m"(work.objects),"j"(low));
 register qword collectUpper __asm__("$6")=work.upper;
 if(!list)func_0020FAA0(D_003DD490,work.point,collectUpper,func_001C5570,architecturalNull,&work.count,&work.objects);
 qword selected;
 register int releaseMode __asm__("$5");
 register int hitCount __asm__("$7")=work.count;
 if(hi>0){
  register qword upperArgument __asm__("$6")=work.upper;
  register O**objectArgument __asm__("$8")=work.objects;
  if(PsoHitTestLineObjects(0,work.point,upperArgument,hitCount,objectArgument,&work.hit)&&work.hit.t==0){
   if(work.hit.u==1||work.hit.otherNormal.f[2]<threshold)goto failure;
   selected=work.hit.b;releaseMode=2;goto accepted;
  }
 }
 hitCount=work.count;
 if(lo<0){
  register qword pointArgument __asm__("$5")=work.point;
  register O**objectArgument __asm__("$8")=work.objects;
  if(PsoHitTestLineObjects(0,pointArgument,work.lower,hitCount,objectArgument,&work.hit)){
   if(work.hit.t==0||work.hit.normal.f[2]<threshold)goto failure;
   selected=work.hit.a;releaseMode=2;goto accepted;
  }
 }
 goto original;
 failure:releaseMode=2;func_001AE4A0(guard,releaseMode);return 0;
 original:selected=work.point;releaseMode=2;
 accepted:*out=selected;func_001AE4A0(guard,releaseMode);return 1;
}

#define OFF(t,m) ((int)&((t*)0)->m)
typedef char query_layout_assert[(sizeof(U)==16 && sizeof(HIT)==0x60 && sizeof(FRAME)==1 && OFF(HIT,normal)==0x20 && OFF(HIT,otherNormal)==0x30 && OFF(HIT,t)==0x40 && OFF(HIT,u)==0x44)?1:-1];

typedef char work_layout[(sizeof(qword)==16 && sizeof(void*)==4 && OFF(HIT,a)==0 && OFF(HIT,b)==0x10 && sizeof(WORK)==0xC0 && OFF(WORK,hit)==0 && OFF(WORK,frame)==0x60 && OFF(WORK,scalar)==0x70 && OFF(WORK,count)==0x80 && OFF(WORK,objects)==0x84 && OFF(WORK,point)==0x90 && OFF(WORK,upper)==0xA0 && OFF(WORK,lower)==0xB0)?1:-1];
