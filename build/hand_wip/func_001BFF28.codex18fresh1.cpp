#define FIELD_OFFSET(t,m) ((uint)&(((t*)0)->m))
typedef unsigned int uint;
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];};
struct V;
struct EDGE{V*to;union{float value;uint bits;}cost;};
struct V{U position;int count;EDGE*edges;};
struct TRI{V*vertex[3];};
struct BSP;
struct G{int vertices;char pad4[8];TRI*triangles;int nodeCount;BSP*tree;};
struct REQUEST{int bytes,alignment;};
extern "C"{
TRI*func_001BF1F8(G*,BSP*,qword,int);
qword func_001BFDB0(TRI*,qword);
void*func_001AE478(void*);
void func_001AE4A0(void*,int);
void*func_001AE318(REQUEST*);
void func_001BF980(G*,V*,V*,int,int*,V**);
void func_001BFC18(G*,int*,V**);
extern float D_002C0C04;
extern qword D_002A2DA0;
}
struct MARK{MARK(){func_001AE478(this);}~MARK(){func_001AE4A0(this,2);}};
inline void*operator new(unsigned,void*p){return p;}
union SLOT{REQUEST request;qword scalar;};
struct WORK{unsigned char arena;SLOT slot;V initial,goal;int found,capacity;U*write;};
static inline void*Allocate(REQUEST*request,int bytes){request->bytes=bytes;request->alignment=16;return func_001AE318(request);}
static inline void StoreStartCost(EDGE*edge,V*vertex,qword endpoint){
 register qword delta __asm__("vf1");register uint word __asm__("$4");
 __asm__("lqc2 %0,%1":"=j"(delta):"m"(vertex->position.q));
 __asm__("vsub.xyzw %0,%1,%0\n\tvmul.xy %0,%0,%0\n\tvaddy.x %0,%0,%0y\n\tvsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(delta):"j"(endpoint));
 __asm__("qmfc2.ni %0,%1":"=r"(word):"j"(delta));
 __asm__("sw %1,%0":"=m"(edge->cost.bits):"r"(word));
}
static inline void StoreGoalCost(EDGE*edge,V*vertex,qword endpoint){
 register qword delta __asm__("vf1");register uint word __asm__("$2");
 __asm__("lqc2 %0,%1":"=j"(delta):"m"(vertex->position.q));
 __asm__("vsub.xyzw %0,%0,%1\n\tvmul.xy %0,%0,%0\n\tvaddy.x %0,%0,%0y\n\tvsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(delta):"j"(endpoint));
 __asm__("qmfc2.ni %0,%1":"=r"(word):"j"(delta));
 __asm__("sw %1,%0":"=m"(edge->cost.bits):"r"(word));
}
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char V_Size[sizeof(V)==32?1:-1];
typedef char EDGE_Size[sizeof(EDGE)==8?1:-1];
typedef char TRI_Size[sizeof(TRI)==12?1:-1];
typedef char REQUEST_Size[sizeof(REQUEST)==8?1:-1];
typedef char MARK_Size[sizeof(MARK)==1?1:-1];
typedef char V_position_Offset[FIELD_OFFSET(V,position)==0?1:-1];
typedef char V_count_Offset[FIELD_OFFSET(V,count)==16?1:-1];
typedef char V_edges_Offset[FIELD_OFFSET(V,edges)==20?1:-1];
typedef char EDGE_to_Offset[FIELD_OFFSET(EDGE,to)==0?1:-1];
typedef char EDGE_cost_Offset[FIELD_OFFSET(EDGE,cost)==4?1:-1];
typedef char TRI_vertex_Offset[FIELD_OFFSET(TRI,vertex)==0?1:-1];
typedef char G_vertices_Offset[FIELD_OFFSET(G,vertices)==0?1:-1];
typedef char G_triangles_Offset[FIELD_OFFSET(G,triangles)==12?1:-1];
typedef char G_nodeCount_Offset[FIELD_OFFSET(G,nodeCount)==16?1:-1];
typedef char G_tree_Offset[FIELD_OFFSET(G,tree)==20?1:-1];
typedef char REQUEST_bytes_Offset[FIELD_OFFSET(REQUEST,bytes)==0?1:-1];
typedef char REQUEST_alignment_Offset[FIELD_OFFSET(REQUEST,alignment)==4?1:-1];
extern "C" int func_001BFF28(G*incomingGraph,qword incomingFrom,qword incomingTo,int capacity,U*incomingOutput){
 register qword from __asm__("$16"),to __asm__("$17");
 __asm__("por %0,$zero,%1":"=r"(from):"r"(incomingFrom));
 __asm__("por %0,$zero,%1":"=r"(to):"r"(incomingTo));
 register G*g __asm__("$22");register U*out __asm__("$21");
 __asm__("daddu %0,%1,$zero":"=r"(out):"r"(incomingOutput));
 WORK work;work.capacity=capacity;
 __asm__("daddu %0,%1,$zero":"=r"(g):"r"(incomingGraph));
 register TRI*first __asm__("$20")=func_001BF1F8(incomingGraph,g->tree,from,1);
 if(!first)return 0;
 qword projectedStart=func_001BFDB0(first,from);register qword start __asm__("$18");register BSP*lastTree __asm__("$5");
 __asm__("lw %0,%2\n\tpor %1,$zero,%3":"=&r"(lastTree),"=r"(start):"m"(g->tree),"r"(projectedStart));
 TRI*last=func_001BF1F8(g,lastTree,to,1);
 if(!last)return 0;
 register qword finish __asm__("$19")=func_001BFDB0(last,to);
 register int count __asm__("$16");
 if(first==last){out[0].q=from;out[1].q=start;count=3;work.write=out+1;out[2].q=finish;}
 else{
  new(&work.arena)MARK;work.write=out+1;
  V**path=(V**)Allocate(&work.slot.request,128*sizeof(V*));
  work.initial.position.q=start;work.initial.count=3;work.initial.edges=(EDGE*)Allocate(&work.slot.request,3*sizeof(EDGE));
  int available;
  {
  register qword startVector __asm__("vf2");
  __asm__("qmtc2.ni %1,%0":"=j"(startVector):"r"(start));
  register V*goalArgument __asm__("$6")=&work.goal;register V*initialArgument __asm__("$9")=&work.initial;register int*foundArgument __asm__("$16")=&work.found;register V**firstCorner __asm__("$7")=first->vertex;
  {register int i __asm__("$5")=0;for(;i<3;i++){
   register EDGE*edge __asm__("$3")=work.initial.edges;V*vertex=*firstCorner++;register unsigned offset __asm__("$2")=(unsigned)i<<3;
   __asm__("addu %0,%0,%1":"+r"(edge):"r"(offset));
   edge->to=vertex;StoreStartCost(edge,vertex,startVector);
  }
  }
  register qword finishVector __asm__("vf2");
  work.goal.position.q=finish;
  __asm__("qmtc2.ni %1,%0":"=j"(finishVector):"r"(finish));
  work.goal.count=0;register V**corner __asm__("$7")=last->vertex;work.goal.edges=0;int k=3;
  while(--k>=0){
   register V*vertex __asm__("$4")=*corner++;register EDGE*edge __asm__("$5")=&vertex->edges[vertex->count++];
   edge->to=goalArgument;StoreGoalCost(edge,vertex,finishVector);
  }
  register G*graphArgument __asm__("$4");__asm__("daddu %0,%1,$zero":"=r"(graphArgument):"r"(g));
  func_001BF980(graphArgument,initialArgument,goalArgument,128,foundArgument,path);
  register int status __asm__("$2");__asm__("lw %0,%1":"=r"(status):"m"(work.found));
  available=work.found;if(status>=3){func_001BFC18(g,foundArgument,path);available=work.found;}
  }
  {register int limit __asm__("$4");__asm__("lw %0,%1":"=r"(limit):"m"(work.capacity));count=limit<available?limit:available;}
  if(count>0){U*dest=out;V**cur=path;int remaining=count;do{dest->q=(*cur)->position.q;dest++;cur++;}while(--remaining!=0);}
  {int k=3;V**corner=last->vertex;while(--k>=0)(*corner++)->count--;}
  ((MARK*)&work.arena)->~MARK();
 }
 {
  register unsigned byteCount __asm__("$2");__asm__("sll %0,%1,4":"=r"(byteCount):"r"(count));
  register U*write __asm__("$5")=work.write;register U*end __asm__("$7");register qword previous __asm__("vf2");
  __asm__("addu %0,%3,%4\n\tlqc2 %1,%2":"=&r"(end),"=j"(previous):"m"(out[0].q),"r"(out),"r"(byteCount));
  register U*read __asm__("$4")=write;
  if(write<end){register float threshold __asm__("$f1")=D_002C0C04;
   do{register qword value __asm__("vf1")=read->q;
    __asm__("vsub.xyzw %0,%0,%1\n\tvmul.xy %0,%0,%0\n\tvaddy.x %0,%0,%0y\n\tvsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(value):"j"(previous));
    register float rawDistance __asm__("$3");__asm__("qmfc2.ni %0,%1":"=r"(rawDistance):"j"(value));
    int accept=threshold<rawDistance;
    if(accept){register U*source __asm__("$2")=read;register U*destination __asm__("$3")=write;
     __asm__("lqc2 %0,0(%1)":"=j"(previous):"r"(source),"m"(source->q));++read;++write;destination->q=previous;
    }else ++read;
   }while(read<end);
  }
  {register int bytes __asm__("$2");__asm__("subu %0,%1,%2":"=r"(bytes):"r"(write),"r"(out));count=bytes>>4;}
 }
 if(count==1){
  register qword previous __asm__("vf2"),scalar __asm__("vf3"),axis __asm__("vf1");register uint thresholdWord __asm__("$3"),directionAddress __asm__("$2");
  __asm__("lqc2 %0,%2\n\tlui %1,%%hi(%3)":"=j"(previous),"=r"(thresholdWord):"m"(out[0].q),"i"(&D_002C0C04));
  __asm__("lw %0,%%lo(%2)(%0)\n\tlui %1,%%hi(%3)":"+r"(thresholdWord),"=r"(directionAddress):"i"(&D_002C0C04),"i"(&D_002A2DA0),"m"(*(float*)(thresholdWord+0xC04)));
  __asm__("qmtc2.ni %1,%0":"=j"(scalar):"r"(thresholdWord));
  __asm__("addiu %0,%0,%%lo(%3)\n\tsqc2 %2,%1":"+&r"(directionAddress),"=m"(out[1].q):"j"(previous),"i"(&D_002A2DA0));
  count=2;
  __asm__("sqc2 %1,%0":"=m"(work.slot.scalar):"j"(scalar));
  __asm__("lqc2 %0,%1":"=j"(axis):"m"(*(qword*)directionAddress));
  __asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(previous):"j"(axis),"j"(scalar));
  out[0].q=previous;
 }
 return count;
}

typedef char layout_PointerWidth[(sizeof(void*)==4)?1:-1];
typedef char layout_IntegerWidth[(sizeof(int)==4)?1:-1];
typedef char layout_UnsignedWidth[(sizeof(uint)==4)?1:-1];
typedef char layout_FloatWidth[(sizeof(float)==4)?1:-1];
typedef char layout_QwordWidth[(sizeof(qword)==16)?1:-1];
typedef char layout_QwordAlignment[(__alignof__(qword)==16)?1:-1];
typedef char layout_UAlignment[(__alignof__(U)==16)?1:-1];
typedef char layout_UWordOffset[(FIELD_OFFSET(U,q)==0)?1:-1];
typedef char layout_UFloatsOffset[(FIELD_OFFSET(U,f)==0)?1:-1];
typedef char layout_UFloatsSpan[(sizeof(((U*)0)->f)==16)?1:-1];
typedef char layout_VAlignment[(__alignof__(V)==16)?1:-1];
typedef char layout_EdgeAlignment[(__alignof__(EDGE)==4)?1:-1];
typedef char layout_TriAlignment[(__alignof__(TRI)==4)?1:-1];
typedef char layout_GraphPrefixSize[(sizeof(G)==24)?1:-1];
typedef char layout_GraphAlignment[(__alignof__(G)==4)?1:-1];
typedef char layout_RequestAlignment[(__alignof__(REQUEST)==4)?1:-1];
typedef char layout_MarkerAlignment[(__alignof__(MARK)==1)?1:-1];
typedef char layout_SlotSize[(sizeof(SLOT)==16)?1:-1];
typedef char layout_SlotAlignment[(__alignof__(SLOT)==16)?1:-1];
typedef char layout_SlotRequestOffset[(FIELD_OFFSET(SLOT,request)==0)?1:-1];
typedef char layout_SlotScalarOffset[(FIELD_OFFSET(SLOT,scalar)==0)?1:-1];
typedef char layout_WorkSize[(sizeof(WORK)==0x70)?1:-1];
typedef char layout_WorkAlignment[(__alignof__(WORK)==16)?1:-1];
typedef char layout_WorkArenaOffset[(FIELD_OFFSET(WORK,arena)==0)?1:-1];
typedef char layout_WorkSlotOffset[(FIELD_OFFSET(WORK,slot)==0x10)?1:-1];
typedef char layout_WorkInitialOffset[(FIELD_OFFSET(WORK,initial)==0x20)?1:-1];
typedef char layout_WorkGoalOffset[(FIELD_OFFSET(WORK,goal)==0x40)?1:-1];
typedef char layout_WorkFoundOffset[(FIELD_OFFSET(WORK,found)==0x60)?1:-1];
typedef char layout_WorkCapacityOffset[(FIELD_OFFSET(WORK,capacity)==0x64)?1:-1];
typedef char layout_WorkWriteOffset[(FIELD_OFFSET(WORK,write)==0x68)?1:-1];
typedef char layout_WorkArenaWidth[(sizeof(((WORK*)0)->arena)==sizeof(MARK))?1:-1];
typedef char layout_WorkFoundWidth[(sizeof(((WORK*)0)->found)==4)?1:-1];
typedef char layout_WorkCapacityWidth[(sizeof(((WORK*)0)->capacity)==4)?1:-1];
typedef char layout_WorkWriteWidth[(sizeof(((WORK*)0)->write)==4)?1:-1];
typedef char layout_TriangleCornerSpan[(sizeof(((TRI*)0)->vertex)==3*sizeof(V*))?1:-1];
typedef char layout_VertexPositionWidth[(sizeof(((V*)0)->position)==16)?1:-1];
typedef char layout_VertexCountWidth[(sizeof(((V*)0)->count)==4)?1:-1];
typedef char layout_VertexEdgesWidth[(sizeof(((V*)0)->edges)==4)?1:-1];
typedef char layout_EdgeValueWidth[(sizeof(((EDGE*)0)->cost.value)==4)?1:-1];
typedef char layout_EdgeBitsWidth[(sizeof(((EDGE*)0)->cost.bits)==4)?1:-1];
typedef char layout_AllocatedPathSpan[(sizeof(V*[128])==512)?1:-1];
