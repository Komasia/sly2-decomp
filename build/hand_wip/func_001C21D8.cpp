// Search the navigation graph and return the selected edge chain.
typedef int qword __attribute__((mode(TI)));
struct NAV {char pad124[0x124];int index;};
struct EDGE {char pad128[0x128];NAV *destination;qword begin,end;};
struct ADJ {int count;int *indices;};
struct GRAPH {char pad10[0x10];int count;char pad1C[8];ADJ *adjacent;int edgeCount;EDGE **edges;};
union SCALAR {float f;int word;};
struct NODE {NAV *object;EDGE *incoming;NODE *parent;float cost;SCALAR estimate;int state;NODE *next,*previous;};
struct DL {NODE *first,*last;int linkOffset;};
struct REQUEST {int size,alignment;};
union OPEN {REQUEST request;DL list;};
struct FRAME;
struct WORK {SCALAR initialEstimate;void *actor;int exactGoal,maximum;EDGE **output;NODE *nodes;int *allowed;qword start,target;NAV *goal;qword origin;};

extern "C" {
FRAME *func_001AE478(FRAME *);
void func_001AE4A0(FRAME *,int);
void *func_001AE378(REQUEST *);
void *func_001AE318(REQUEST *);
void *func_002333B4(void *,int,int);
qword func_001A62E8(void *);
NAV *func_001C0D70(qword,int);
void func_0011A200(DL *);
void func_0011A1F8(DL *,int);
void func_0011A220(DL *,NODE *);
void func_0011A2E8(DL *,NODE *);
void func_0011A280(DL *,NODE *,NODE *);
int func_0011A3B0(DL *);
int func_001C26E0(GRAPH *,EDGE *,void *);
int func_001C0920(NAV *,qword,int);
}
struct FRAME {~FRAME(){func_001AE4A0(this,2);}};
static inline qword Difference(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword SquareLength(qword q){qword sum=q,one;__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(sum),"=&j"(one));return sum;}
static inline qword Root(qword q){__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(q));return q;}
static inline float X(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline int LowWord(qword q){register int r __asm__("$6");__asm__("qmfc2.ni %0,%1":"=r"(r):"j"(q));return r;}
static inline void BuildRequest(REQUEST *request,int size){request->size=size;request->alignment=16;}
static inline void SelectOrigin(qword &out,EDGE *incoming,qword fallback){if(incoming)out=incoming->end;else out=fallback;}
extern "C" int func_001C21D8(GRAPH *graph,void *actor,qword target,int exactGoal,int maximum,EDGE **output){
 FRAME frame;OPEN open;DL closed;WORK w;w.actor=actor;w.target=target;w.exactGoal=exactGoal;w.maximum=maximum;w.output=output;func_001AE478(&frame);
 BuildRequest(&open.request,graph->count*32);
 w.nodes=(NODE*)func_001AE378(&open.request);
 BuildRequest(&open.request,graph->edgeCount*4);
 w.allowed=(int*)func_001AE318(&open.request);
 func_002333B4(w.allowed,255,graph->edgeCount*4);
 w.start=func_001A62E8(w.actor);
 NAV *source=func_001C0D70(w.start,0);w.goal=func_001C0D70(w.target,0);
 if(!source||!w.goal)return 0;
 func_0011A200(&open.list);func_0011A1F8(&open.list,24);
 func_0011A200(&closed);func_0011A1F8(&closed,24);
 NODE *current=w.nodes+source->index;
 qword initialLength=Root(SquareLength(Difference(w.start,w.target)));
 w.initialEstimate.word=LowWord(initialLength);int initialWord=w.initialEstimate.word;current->object=source;current->estimate.word=initialWord;current->state=2;
 func_0011A220(&open.list,current);
 while(!func_0011A3B0(&open.list)){
  current=open.list.first;
  if(w.exactGoal){if(current->object==w.goal)break;}
  else if(func_001C0920(current->object,w.target,1))break;
  func_0011A2E8(&open.list,current);current->state=1;func_0011A220(&closed,current);
  SelectOrigin(w.origin,current->incoming,w.start);
  ADJ *adj=graph->adjacent+current->object->index;
  for(int i=0;i<adj->count;++i){
   int edgeId=adj->indices[i];int *cache=w.allowed+edgeId;EDGE *edge=graph->edges[edgeId];
   if(*cache==-1)*cache=func_001C26E0(graph,edge,w.actor);
   if(!*cache)continue;
   qword toBegin=SquareLength(Difference(w.origin,edge->begin));
   qword edgeLength=SquareLength(Difference(edge->begin,edge->end));
   qword firstLength=Root(toBegin),secondLength=Root(edgeLength);float distance=X(firstLength)+X(secondLength);
   NAV *destination=edge->destination;
   qword toGoal=SquareLength(Difference(edge->end,w.target));
   float cost=current->cost+distance;
   NODE *neighbor=w.nodes+destination->index;
   float estimate=cost+X(Root(toGoal));
   if(neighbor->state && neighbor->estimate.f<=estimate)continue;
   switch(neighbor->state){case 1:func_0011A2E8(&closed,neighbor);break;case 2:func_0011A2E8(&open.list,neighbor);break;}
   neighbor->object=destination;neighbor->incoming=edge;neighbor->cost=cost;neighbor->parent=current;neighbor->estimate.f=estimate;neighbor->state=2;
   NODE *before=open.list.first;
   if(before && !(estimate<before->estimate.f)){
    for(before=before->next;before;before=before->next)if(neighbor->estimate.f<before->estimate.f)break;
   }
   func_0011A280(&open.list,before,neighbor);
  }
 }
 int result=0;
 if(!func_0011A3B0(&open.list)){
  if(!w.exactGoal && !current->parent){w.output[0]=0;result=1;}
  else{
   int count=0;NODE *walk=current;
   if(walk->parent)do{walk=walk->parent;++count;}while(walk->parent);
   result=count;if(!(count<w.maximum))result=w.maximum;
   NODE *node=current;
   if(node->parent){
    EDGE **slot=(EDGE**)((unsigned int)w.output+count*4-4);
    do{if(!(w.maximum<count))*slot=node->incoming;node=node->parent;--slot;--count;}while(node->parent);
   }
  }
 }
 return result;
}

#define OFF(t,m) ((unsigned int)&((t*)0)->m)
typedef char navigation_layout[(sizeof(void*)==4 && sizeof(qword)==16 && sizeof(SCALAR)==4 && sizeof(NODE)==0x20 && sizeof(ADJ)==8 && sizeof(DL)==0xC && sizeof(REQUEST)==8 && sizeof(OPEN)==0xC && sizeof(FRAME)==1 && __alignof__(FRAME)==1 && sizeof(WORK)==0x60 && OFF(NAV,index)==0x124 && OFF(EDGE,destination)==0x128 && OFF(EDGE,begin)==0x130 && OFF(EDGE,end)==0x140 && OFF(GRAPH,count)==0x10 && OFF(GRAPH,adjacent)==0x1C && OFF(GRAPH,edgeCount)==0x20 && OFF(GRAPH,edges)==0x24 && OFF(ADJ,count)==0 && OFF(ADJ,indices)==4 && OFF(NODE,object)==0 && OFF(NODE,incoming)==4 && OFF(NODE,parent)==8 && OFF(NODE,cost)==0xC && OFF(NODE,estimate)==0x10 && OFF(NODE,state)==0x14 && OFF(NODE,next)==0x18 && OFF(NODE,previous)==0x1C && OFF(DL,first)==0 && OFF(DL,last)==4 && OFF(DL,linkOffset)==8 && OFF(REQUEST,size)==0 && OFF(REQUEST,alignment)==4 && OFF(OPEN,request)==0 && OFF(OPEN,list)==0 && OFF(WORK,initialEstimate)==0 && OFF(WORK,actor)==4 && OFF(WORK,exactGoal)==8 && OFF(WORK,maximum)==0xC && OFF(WORK,output)==0x10 && OFF(WORK,nodes)==0x14 && OFF(WORK,allowed)==0x18 && OFF(WORK,start)==0x20 && OFF(WORK,target)==0x30 && OFF(WORK,goal)==0x40 && OFF(WORK,origin)==0x50)?1:-1];
