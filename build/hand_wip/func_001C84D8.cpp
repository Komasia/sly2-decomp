typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct POINT {char pad[0x10];float x,y;};
struct TIMER {char pad[0xA8];float end;};
struct SGG;struct ALARM;
struct S {char pad[0x150];struct POINT*input;char pad154[0x188-0x154];int state;int pad18C,pad190;int index,step;SGG*alarms;void*pending;char pad1A4[0x1F0-0x1A4];int target;char pad1F4[0x204-0x1F4];struct TIMER*timer;};
extern float D_002C0FE8,D_002A7798;
extern qword D_002C0FF0[9];
extern struct CLOCK {float t,dt;} D_002DDED0;
extern "C" int func_001C46C0(void*,int,float);
extern "C" void func_001E0020(SGG*,ALARM*);
extern "C" void func_001C8918(struct S*,int);
extern "C" int func_00131968(void*);
static inline qword Pack(float x,float y,float z){register unsigned xword __asm__("$3");register unsigned yword __asm__("$2");register qword xy __asm__("$3");register qword result __asm__("$3");__asm__("mfc1 %0,%1":"=r"(xword):"f"(x));__asm__("mfc1 %0,%1":"=r"(yword):"f"(y));__asm__("pextlw %0,%2,%1":"=r"(xy):"r"(xword),"r"(yword));register unsigned zword __asm__("$2");__asm__("mfc1 %0,%1":"=r"(zword):"f"(z));__asm__("pcpyld %0,%2,%1":"=r"(result):"r"(xy),"r"(zword));return result;}
static inline qword Sub(qword a,qword b){qword d;__asm__("vsub.xyzw %0,%1,%2":"=j"(d):"j"(a),"j"(b));return d;}
static inline float Len(qword a){register qword d __asm__("vf1");register qword one __asm__("vf2");float f;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a));__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));__asm__("mtc1 %1,%0":"=f"(f):"r"(d));return f;}
static inline float ClockTime(){float t;__asm__("lwc1 %0,%1":"=f"(t):"m"(D_002DDED0.t));return t;}
extern "C" void func_001C84D8(struct S*p){
 union U point;
 int old;
 int divisor=1000;
 do{
  old=p->state;
  if(func_001C46C0(p->input,0x30,0)){
   func_001E0020(p->alarms,(ALARM*)0x655);
   func_001C8918(p,3);
  }
  switch(p->state){
  case 0:
   if(func_001C46C0(p->input,0xC0,0)){func_001C8918(p,2);break;}
   {
    int current=p->index,best=-1;
    unsigned i;
    float bias=D_002C0FE8,smallest=D_002A7798;
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
   if(p->timer->end<=ClockTime())func_001C8918(p,0);
   break;
  case 2:
   if(!p->pending||func_00131968(p->pending)){
    int next=(p->step*10)%divisor;next++;next+=p->index;
    p->step=next;
    if(next==p->target){func_001E0020(p->alarms,(ALARM*)0x655);func_001C8918(p,3);}
    else func_001C8918(p,0);
   }
   break;
  }
 }while(p->state!=old);
}

#define OFF(t,m) ((int)&((t*)0)->m)
typedef char selection_layout[(sizeof(qword)==16 && sizeof(U)==16 && sizeof(float)==4 && sizeof(void*)==4 && OFF(POINT,x)==0x10 && OFF(POINT,y)==0x14 && OFF(TIMER,end)==0xA8 && OFF(S,input)==0x150 && OFF(S,state)==0x188 && OFF(S,index)==0x194 && OFF(S,step)==0x198 && OFF(S,alarms)==0x19C && OFF(S,pending)==0x1A0 && OFF(S,target)==0x1F0 && OFF(S,timer)==0x204 && OFF(CLOCK,t)==0 && OFF(CLOCK,dt)==4 && sizeof(D_002C0FF0)==0x90)?1:-1];
