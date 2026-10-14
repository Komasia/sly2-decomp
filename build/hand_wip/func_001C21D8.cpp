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
void *func_001AE378(const REQUEST *);
void *func_001AE318(const REQUEST *);
void *func_002333B4(void *,int,unsigned int);
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
static inline qword Root(qword q){__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(q));return q;}
static inline int LowWord(qword q){register int r __asm__("$6");__asm__("qmfc2.ni %0,%1":"=r"(r):"j"(q));return r;}
static inline void BuildRequest(REQUEST *request,int size){request->size=size;request->alignment=16;}
static inline void SelectOrigin(qword &out,EDGE *incoming,qword fallback){if(incoming)out=incoming->end;else out=fallback;}
static inline qword EdgeBegin(const qword &value){register qword result __asm__("vf1");__asm__("lqc2 %0,%1":"=j"(result):"m"(value));return result;}
static inline qword PathOrigin(const qword &value){register qword result __asm__("vf4");__asm__("lqc2 %0,%1":"=j"(result):"m"(value));return result;}
static inline qword EdgeEnd(const qword &value){register qword result __asm__("vf3");__asm__("lqc2 %0,%1":"=j"(result):"m"(value));return result;}
static inline qword GoalTarget(const qword &value){register qword result __asm__("vf1");__asm__("lqc2 %0,%1":"=j"(result):"m"(value));return result;}
static inline qword ToBegin(qword a,qword b){register qword r __asm__("vf2");__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword EdgeSpan(qword a,qword b){register qword r __asm__("vf1");__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword ToGoal(qword a,qword b){register qword r __asm__("vf3");__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword FirstSquare(qword q){register qword sum __asm__("vf2")=q;register qword one __asm__("vf4");__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(sum),"=&j"(one));return sum;}
static inline qword SpanSquare(qword q){register qword sum __asm__("vf1")=q;register qword one __asm__("vf5");__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(sum),"=&j"(one));return sum;}
static inline qword GoalSquare(qword q){register qword sum __asm__("vf3")=q;register qword one __asm__("vf1");__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(sum),"=&j"(one));return sum;}
static inline qword InitialDifference(qword a,qword b){register qword r __asm__("vf1");__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword InitialSquare(qword q){register qword sum __asm__("vf1")=q;register qword one __asm__("vf2");__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(sum),"=&j"(one));return sum;}
static inline float FirstX(qword q){register int word __asm__("$2");float f;__asm__("qmfc2.ni %0,%1":"=r"(word):"j"(q));__asm__("mtc1 %1,%0":"=f"(f):"r"(word));return f;}
static inline float SpanX(qword q){register int word __asm__("$3");float f;__asm__("qmfc2.ni %0,%1":"=r"(word):"j"(q));__asm__("mtc1 %1,%0":"=f"(f):"r"(word));return f;}
static inline float GoalX(qword q){register int word __asm__("$4");float f;__asm__("qmfc2.ni %0,%1":"=r"(word):"j"(q));__asm__("mtc1 %1,%0":"=f"(f):"r"(word));return f;}
static inline int EdgeCount(const GRAPH *graph){register int count __asm__("$2");__asm__("lw %0,%1":"=r"(count):"m"(graph->edgeCount));return count;}
static inline qword PublishStart(qword&home,qword value,int&scope){register int zero __asm__("$5");__asm__("sq %2,%0\n\tdaddu %1,$zero,$zero":"=m"(home),"=r"(zero):"r"(value));scope=zero;return value;}
static inline qword InitialPointIndex(const qword&start,const NAV*source,int&index,int&state){register qword point __asm__("vf2");register int i __asm__("$2"),s __asm__("$3");__asm__("lqc2 %0,%3\n\taddiu %2,$zero,2\n\tlw %1,%4":"=j"(point),"=r"(i),"=&r"(s):"m"(start),"m"(source->index));index=i;state=s;return point;}
static inline NODE*InitialTargetNodes(const qword&target,NODE*const&nodes,qword&point){register qword value __asm__("vf3");register NODE*base __asm__("$4");__asm__("lqc2 %0,%2\n\tlw %1,%3":"=j"(value),"=r"(base):"m"(target),"m"(nodes));point=value;return base;}
extern "C" int func_001C21D8(GRAPH *graph,void *actor,qword target,int exactGoal,int maximum,EDGE **output){
 FRAME frame;OPEN open;DL closed;WORK w;w.actor=actor;w.target=target;w.exactGoal=exactGoal;w.maximum=maximum;w.output=output;func_001AE478(&frame);
 BuildRequest(&open.request,graph->count*32);
 w.nodes=(NODE*)func_001AE378(&open.request);
 BuildRequest(&open.request,EdgeCount(graph)*4);
 w.allowed=(int*)func_001AE318(&open.request);
 func_002333B4(w.allowed,255,graph->edgeCount*4);
 int scope;qword argument=PublishStart(w.start,func_001A62E8(w.actor),scope);
 NAV *source=func_001C0D70(argument,scope);w.goal=func_001C0D70(w.target,0);
 if(!source||!w.goal)return 0;
 func_0011A200(&open.list);func_0011A1F8(&open.list,24);
 func_0011A200(&closed);func_0011A1F8(&closed,24);
 int initialIndex,initialState;qword initialStart=InitialPointIndex(w.start,source,initialIndex,initialState),initialTarget;
 NODE *current=InitialTargetNodes(w.target,w.nodes,initialTarget)+initialIndex;
 qword initialLength=Root(InitialSquare(InitialDifference(initialStart,initialTarget)));
 w.initialEstimate.word=LowWord(initialLength);int initialWord=w.initialEstimate.word;current->object=source;current->estimate.word=initialWord;current->state=initialState;
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
   qword begin=EdgeBegin(edge->begin),origin=PathOrigin(w.origin),end=EdgeEnd(edge->end);
   qword toBegin=ToBegin(origin,begin),span=EdgeSpan(begin,end);
   toBegin=FirstSquare(toBegin);span=SpanSquare(span);
   qword firstLength=Root(toBegin),secondLength=Root(span);float distance=FirstX(firstLength)+SpanX(secondLength);
   NAV *destination=edge->destination;
   qword toGoal=GoalSquare(ToGoal(end,GoalTarget(w.target)));
   float cost=current->cost+distance;
   NODE *neighbor=w.nodes+destination->index;
   float estimate=cost+GoalX(Root(toGoal));
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

typedef char initial_query_layout[(__alignof__(WORK)==0x10 && sizeof(((NAV*)0)->index)==4 && sizeof(((NODE*)0)->state)==4 && sizeof(((NODE*)0)->estimate)==4 && sizeof(((WORK*)0)->start)==0x10 && sizeof(((WORK*)0)->target)==0x10)?1:-1];
