// Dispatch particle contacts against linked world shapes.
typedef int qword __attribute__((mode(TI)));
struct DL {void*head,*tail;int offset;};
struct DLI {DL*list;void**next;int offset;DLI*outer;};
struct ENTRY {int a,b;void*poly;};
struct SHAPE {char pad10[0x10];unsigned long flags;char pad18[0x54];int capacity;char pad70[4];void*tree;};
struct XP {qword position,other,normal;char pad30[0x10];float fraction;char pad44[0x1C];};
struct RIP;
struct RVE {short delta,pad;int(*fn)(void*,SHAPE*,qword,qword);};
struct RIP {char pad14[0x14];float start;char pad18[0x58];qword position,extra;char pad90[0x5C];RVE*vt;};
struct NODE;
struct STATE {char pad20[0x20];qword origin;float radius;DL shapes;char pad40[0x20];void*subject;NODE*nodes;char pad68[8];unsigned long flags;};
struct OBJ {char padEC[0xEC];STATE*state;};
struct NODE {int pad;NODE*next;char pad8[4];OBJ*object;};
struct P;
struct PVE {short delta,pad;void(*fn)(void*);};
struct P {char padC[0xC];PVE*vt;char pad10[0xDC];STATE*state;char padF0[0x60];int mode;char pad154[8];DL rips;};
struct CLOCK {float t,dt;};
struct REQ {int cb,align;};
struct FRAME;
extern "C" {
extern DLI *D_002DD2FC;
extern CLOCK D_002DDED0;
FRAME *func_001AE478(FRAME*);
void func_001AE4A0(FRAME*,int);
void *func_001AE318(const REQ*);
int func_00118A88(void*,int,qword,int*,ENTRY**,float);
int func_0014C6D8(SHAPE*,ENTRY*,qword,qword,int,XP*);
int func_00132B10(void*,int);
int func_0011A3B0(DL*);
void func_001CE2E8(P*);
}
struct FRAME {};
union PHASE{REQ request;DLI rip;};
struct WORK{PHASE phase;XP contacts[4];int remaining;ENTRY*entries;int special;DL*rips;};
static inline DLI*First(){DLI*value;__asm__("lw %0,%1":"=r"(value):"m"(D_002DD2FC));return value;}
static inline void PublishFirst(DLI*value){__asm__("sw %1,%0":"=m"(D_002DD2FC):"r"(value));}
static inline float ClockTime(){float t;__asm__("lwc1 %0,%1":"=f"(t):"m"(D_002DDED0.t));return t;}
static inline void Init(DLI*it,DL*list){it->list=list;it->next=(void**)list;it->offset=list->offset;it->outer=First();PublishFirst(it);}
static inline void*Next(DLI*it){void*p=*it->next;it->next=(void**)((char*)p+it->offset);return p;}
static inline int Min(int a,int b){return a<b?a:b;}
static inline void*Alloc(const REQ&r){return func_001AE318(&r);}
void func_001CE2E8(P*p){
 if(p->mode==1){
  DLI shapes;FRAME frame;WORK work;work.rips=&p->rips;NODE*node;
  for(node=p->state->nodes;node;node=node->next){
   if(node->object->state->flags&4)continue;
   work.special=func_00132B10(node->object->state->subject,0x59);
   Init(&shapes,&node->object->state->shapes);
   SHAPE*shape;
   while((shape=(SHAPE*)Next(&shapes))!=0){
    if((shape->flags&(1UL<<48))&&!work.special)continue;
    func_001AE478(&frame);
    work.entries=0;
    if(!(shape->flags&(1UL<<49))){
     int capacity=Min(0x1555,shape->capacity);work.remaining=capacity;
     work.phase.request.cb=capacity*12;work.phase.request.align=16;
     work.entries=(ENTRY*)Alloc(work.phase.request);
     if(func_00118A88(shape->tree,0x7FFFFFFF,p->state->origin,&work.remaining,&work.entries,p->state->radius)!=2){func_001AE4A0(&frame,2);continue;}
     work.entries--;
    }
    Init(&work.phase.rip,work.rips);
    RIP*rip;
    while((rip=(RIP*)Next(&work.phase.rip))!=0){
     if(ClockTime()<=rip->start)continue;
     int count=func_0014C6D8(shape,work.entries,rip->extra,rip->position,4,work.contacts);
     if(count>0){float zero=0.0f;
     int i;XP*hit;
     for(i=0,hit=work.contacts;i<count;i++,hit++){
      if(hit->fraction==zero)continue;
      if(rip->vt[8].fn((char*)rip+rip->vt[8].delta,shape,hit->position,hit->normal))break;
     }}
    }
    PublishFirst(work.phase.rip.outer);func_001AE4A0(&frame,2);
   }
   PublishFirst(shapes.outer);
  }
  if(func_0011A3B0(work.rips))p->vt[9].fn((char*)p+p->vt[9].delta);
 }
}

#define OFF(t,m) ((int)&((t*)0)->m)
typedef char dispatch_layout[(sizeof(qword)==16 && sizeof(void*)==4 && sizeof(unsigned long)==8 && sizeof(DL)==12 && sizeof(DLI)==16 && sizeof(ENTRY)==12 && sizeof(REQ)==8 && sizeof(FRAME)==1 && sizeof(XP)==0x60 && sizeof(RVE)==8 && sizeof(PVE)==8 && OFF(DLI,list)==0 && OFF(DLI,next)==4 && OFF(DLI,offset)==8 && OFF(DLI,outer)==0xC && OFF(DL,offset)==8 && OFF(REQ,cb)==0 && OFF(REQ,align)==4 && OFF(SHAPE,flags)==0x10 && OFF(SHAPE,capacity)==0x6C && OFF(SHAPE,tree)==0x74 && OFF(XP,position)==0 && OFF(XP,normal)==0x20 && OFF(XP,fraction)==0x40 && OFF(RIP,start)==0x14 && OFF(RIP,position)==0x70 && OFF(RIP,extra)==0x80 && OFF(RIP,vt)==0xEC && OFF(STATE,origin)==0x20 && OFF(STATE,radius)==0x30 && OFF(STATE,shapes)==0x34 && OFF(STATE,subject)==0x60 && OFF(STATE,nodes)==0x64 && OFF(STATE,flags)==0x70 && OFF(OBJ,state)==0xEC && OFF(NODE,next)==4 && OFF(NODE,object)==0xC && OFF(P,vt)==0xC && OFF(P,state)==0xEC && OFF(P,mode)==0x150 && OFF(P,rips)==0x15C && OFF(RVE,delta)==0 && OFF(RVE,fn)==4 && OFF(PVE,delta)==0 && OFF(PVE,fn)==4 && OFF(CLOCK,t)==0 && OFF(CLOCK,dt)==4)?1:-1];

typedef char actual_phase_work[(sizeof(PHASE)==0x10 && sizeof(WORK)==0x1A0 && __alignof__(WORK)==16 && OFF(WORK,phase)==0 && OFF(WORK,contacts)==0x10 && OFF(WORK,remaining)==0x190 && OFF(WORK,entries)==0x194 && OFF(WORK,special)==0x198 && OFF(WORK,rips)==0x19C && OFF(PHASE,request)==0 && OFF(PHASE,rip)==0)?1:-1];
