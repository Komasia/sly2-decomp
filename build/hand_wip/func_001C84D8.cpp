typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct POINT {char pad[0x10];float x,y;};
struct TIMER {char pad[0xA8];float end;};
struct S {char pad[0x150];struct POINT*input;char pad154[0x188-0x154];int state;int pad18C,pad190;int index,step;void*message;void*wait;char pad1A4[0x1F0-0x1A4];int target;char pad1F4[0x204-0x1F4];struct TIMER*timer;};
extern float D_002C0FE8,D_002A7798;
extern qword D_002C0FF0[9];
extern struct CLOCK {float t,dt;} D_002DDED0;
extern "C" int func_001C46C0(void*,int,float);
extern "C" void func_001E0020(void*,int);
extern "C" void func_001C8918(struct S*,int);
extern "C" int func_00131968(void*);
static inline qword Pack(float x,float y,float z){qword q;__asm__("pextlw %0,%2,%1\n\tpcpyld %0,%3,%0":"=&r"(q):"r"(x),"r"(y),"r"(z));return q;}
static inline qword Sub(qword a,qword b){qword d;__asm__("vsub.xyzw %0,%1,%2":"=j"(d):"j"(a),"j"(b));return d;}
static inline float Len(qword a){qword d,one;float f;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a));__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));__asm__("mtc1 %1,%0":"=f"(f):"r"(d));return f;}
extern "C" void func_001C84D8(struct S*p){
 union U point;
 int old;
 int divisor=1000;
 do{
  old=p->state;
  if(func_001C46C0(p->input,0x30,0)){
   func_001E0020(p->message,0x655);
   func_001C8918(p,3);
  }
  switch(p->state){
  case 0:
   if(func_001C46C0(p->input,0xC0,0)){func_001C8918(p,2);break;}
   {
    int current=p->index,best=-1;
    unsigned i;
    float smallest=D_002A7798,bias=D_002C0FE8;
    point.q=Pack(p->input->x,p->input->y,0);
    for(i=0;i<9;i++){
     float distance=Len(Sub(point.q,D_002C0FF0[i]));
     if(i==current)distance*=bias;
     if(distance<smallest){smallest=distance;best=i;}
    }
    if(best!=current){p->index=best;func_001C8918(p,1);}
   }
   break;
  case 1:
   if(p->timer->end<=D_002DDED0.t)func_001C8918(p,0);
   break;
  case 2:
   if(!p->wait||func_00131968(p->wait)){
    int next=(p->step*10)%divisor;next++;next+=p->index;
    p->step=next;
    if(next==p->target){func_001E0020(p->message,0x655);func_001C8918(p,3);}
    else func_001C8918(p,0);
   }
   break;
  }
 }while(p->state!=old);
}
