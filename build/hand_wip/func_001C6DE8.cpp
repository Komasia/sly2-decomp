typedef int qword __attribute__((mode(TI)));
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
static inline qword High(float f,U&s){qword q;__asm__("qmtc2 %1,%0":"=j"(q):"r"(f));s.q=q;return s.q;}
static inline qword Low(float f,U&s){qword q;__asm__("qmtc2 %1,%0":"=j"(q):"r"(f));s.q=q;return s.q;}

static inline qword Axis(const qword&value){register qword q __asm__("vf1");__asm__("lqc2 %0,%1":"=j"(q):"m"(value));return q;}
static inline qword Point(const qword&value){register qword q __asm__("vf4");__asm__ volatile("lqc2 %0,%1":"=j"(q):"m"(value));return q;}
static inline qword AddScaled(qword point,qword axis,qword scale){register qword out __asm__("vf4")=point;__asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(out):"j"(axis),"j"(scale));return out;}

static inline qword Packed(const qword&value){register qword q __asm__("$6");__asm__("lq %0,%1":"=r"(q):"m"(value));return q;}
int func_001C6DE8(float lo,float hi,float threshold,qword point,int count,O**objects,qword*out){
 qword result;WORK work;work.point=point;work.count=count;work.objects=objects;
 FRAME*guard=EnterFrame(&work.frame);
 qword h=High(hi,work.scalar);qword direction=Axis(D_002A2DC0);qword l=Low(lo,work.scalar);
 work.lower=AddScaled(Point(work.point),direction,l);
 work.upper=AddScaled(Point(work.point),direction,h);
 if(!work.objects)func_0020FAA0(D_003DD490,work.point,Packed(work.upper),func_001C5570,0,&work.count,&work.objects);
 if(hi>0){
  if(PsoHitTestLineObjects(0,work.point,work.upper,work.count,work.objects,&work.hit)&&work.hit.t==0){
   if(work.hit.u==1||work.hit.otherNormal.f[2]<threshold)goto failure;
   result=work.hit.b;goto success;
  }
 }
 if(lo<0){
  if(PsoHitTestLineObjects(0,work.point,work.lower,work.count,work.objects,&work.hit)){
   if(work.hit.t==0||work.hit.normal.f[2]<threshold)goto failure;
   result=work.hit.a;goto success;
  }
 }
 result=work.point;
 success:*out=result;func_001AE4A0(guard,2);return 1;
 failure:func_001AE4A0(guard,2);return 0;
}

#define OFF(t,m) ((int)&((t*)0)->m)
typedef char query_layout_assert[(sizeof(U)==16 && sizeof(HIT)==0x60 && sizeof(FRAME)==1 && OFF(HIT,normal)==0x20 && OFF(HIT,otherNormal)==0x30 && OFF(HIT,t)==0x40 && OFF(HIT,u)==0x44)?1:-1];

typedef char work_layout[(sizeof(qword)==16 && sizeof(void*)==4 && OFF(HIT,a)==0 && OFF(HIT,b)==0x10 && sizeof(WORK)==0xC0 && OFF(WORK,hit)==0 && OFF(WORK,frame)==0x60 && OFF(WORK,scalar)==0x70 && OFF(WORK,count)==0x80 && OFF(WORK,objects)==0x84 && OFF(WORK,point)==0x90 && OFF(WORK,upper)==0xA0 && OFF(WORK,lower)==0xB0)?1:-1];
