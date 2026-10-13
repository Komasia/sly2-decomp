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
struct STATE {char pad20[0x20];qword origin;float radius;DL shapes;char pad40[0x20];int kind;NODE*nodes;char pad68[8];unsigned long flags;};
struct OBJ {char padEC[0xEC];STATE*state;};
struct NODE {int pad;NODE*next;char pad8[4];OBJ*object;};
struct P;
struct PVE {short delta,pad;void(*fn)(void*);};
struct P {char padC[0xC];PVE*vt;char pad10[0xDC];STATE*state;char padF0[0x60];int mode;char pad154[8];DL rips;};
struct CLOCK {float t,dt;};
struct REQ {int cb,align;REQ(int n,int a){cb=n;align=a;}};
struct FRAME;
extern "C" {
extern DLI *D_002DD2FC;
extern CLOCK D_002DDED0;
void *func_001AE478(void*);
void func_001AE4A0(FRAME*,int);
void *func_001AE318(REQ*);
int func_00118A88(void*,int,qword,int*,ENTRY**,float);
int func_0014C6D8(SHAPE*,ENTRY*,qword,qword,int,XP*);
int func_00132B10(int,int);
int func_0011A3B0(DL*);
void func_001CE2E8(P*);
}
struct FRAME {};
static inline void Init(DLI*it,DL*list){it->list=list;it->next=(void**)list;it->offset=list->offset;it->outer=D_002DD2FC;D_002DD2FC=it;}
static inline void*Next(DLI*it){void*p=*it->next;it->next=(void**)((char*)p+it->offset);return p;}
static inline int Min(int a,int b){return a<b?a:b;}
static inline void*Alloc(const REQ&r){return func_001AE318((REQ*)&r);}
void func_001CE2E8(P*p){
 if(p->mode==1){
  NODE*node;
  for(node=p->state->nodes;node;node=node->next){
   if(node->object->state->flags&4)continue;
   int special=func_00132B10(node->object->state->kind,0x59);
   DLI shapes;Init(&shapes,&node->object->state->shapes);
   SHAPE*shape;
   while((shape=(SHAPE*)Next(&shapes))!=0){
    if((shape->flags&(1UL<<48))&&!special)continue;
    FRAME frame;func_001AE478(&frame);
    int remaining;
    ENTRY*entries=0;
    if(!(shape->flags&(1UL<<49))){
     int capacity=Min(0x1555,shape->capacity);remaining=capacity;
     entries=(ENTRY*)Alloc(REQ(capacity*12,16));
     if(func_00118A88(shape->tree,0x7FFFFFFF,p->state->origin,&remaining,&entries,p->state->radius)!=2){func_001AE4A0(&frame,2);continue;}
     entries--;
    }
    DLI ripIt;Init(&ripIt,&p->rips);
    RIP*rip;
    while((rip=(RIP*)Next(&ripIt))!=0){
     if(D_002DDED0.t<=rip->start)continue;
     XP contacts[4];
     int count=func_0014C6D8(shape,entries,rip->extra,rip->position,4,contacts);
     if(count>0){float zero=0.0f;
     int i;XP*hit;
     for(i=0,hit=contacts;i<count;i++,hit++){
      if(hit->fraction==zero)continue;
      if(rip->vt[8].fn((char*)rip+rip->vt[8].delta,shape,hit->position,hit->normal))break;
     }}
    }
    D_002DD2FC=ripIt.outer;func_001AE4A0(&frame,2);
   }
   D_002DD2FC=shapes.outer;
  }
  if(func_0011A3B0(&p->rips))p->vt[9].fn((char*)p+p->vt[9].delta);
 }
}
