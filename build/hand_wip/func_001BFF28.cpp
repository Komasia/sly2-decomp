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
static inline void*Allocate(REQUEST*request,int bytes){request->bytes=bytes;request->alignment=16;return func_001AE318(request);}
static inline qword Difference(qword a,qword b){qword d;__asm__("vsub.xyzw %0,%1,%2":"=j"(d):"j"(a),"j"(b));return d;}
static inline qword LengthXY(qword d){qword q;__asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(q):"j"(d));__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(q):"j"(q));return q;}
static inline uint DistanceBits(qword a,qword b){qword q=LengthXY(Difference(a,b));uint bits;__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(q));return bits;}
static inline float Distance(qword a,qword b){qword q=LengthXY(Difference(a,b));float f;__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(q));return f;}
static inline qword ScalarWord(const float*p){int bits;qword q;__asm__("lw %0,%1":"=r"(bits):"m"(*p));__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(bits));return q;}
static inline qword AddScaled(qword a,qword b,qword scalar){qword q;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(q):"j"(a),"j"(b),"j"(scalar));return q;}
static inline int Min(const int&a,const int&b){return a<b?a:b;}
static inline qword Vector(qword value){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(value));return q;}
static inline int Filter(U*out,int count,U*&write){
 U*end=out+count;U*read=write;qword previous=out[0].q;
 if(read<end){float threshold=D_002C0C04;
  do{
   int accept=threshold<Distance(read->q,previous);
   if(accept){previous=read->q;write->q=previous;write++;}
   read++;
  }while(read<end);
 }
 return write-out;
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
extern "C" int func_001BFF28(G*g,qword from,qword to,int capacity,U*out){
 TRI*first=func_001BF1F8(g,g->tree,from,1);
 if(!first)return 0;
 qword start=func_001BFDB0(first,from);
 TRI*last=func_001BF1F8(g,g->tree,to,1);
 if(!last)return 0;
 qword finish=func_001BFDB0(last,to);
 int count;
 U*write;
 if(first==last){write=out+1;out[0].q=from;out[1].q=start;out[2].q=finish;count=3;}
 else{
  MARK arena;write=out+1;
  REQUEST request;
  V**path=(V**)Allocate(&request,128*sizeof(V*));
  V initial,goal;
  int found;
  initial.position.q=start;initial.count=3;initial.edges=(EDGE*)Allocate(&request,3*sizeof(EDGE));
  qword startVector=Vector(start);
  for(int i=0;i<3;i++){
   V*vertex=first->vertex[i];EDGE*edge=&initial.edges[i];
   edge->to=vertex;edge->cost.bits=DistanceBits(startVector,vertex->position.q);
  }
  goal.position.q=finish;goal.count=0;goal.edges=0;
  qword finishVector=Vector(finish);
  int k=3;V**corner=last->vertex;
  while(--k>=0){
   V*vertex=*corner++;EDGE*edge=&vertex->edges[vertex->count++];
   edge->to=&goal;edge->cost.bits=DistanceBits(vertex->position.q,finishVector);
  }
  func_001BF980(g,&initial,&goal,128,&found,path);
  if(found>=3)func_001BFC18(g,&found,path);
  count=Min(capacity,found);
  U*dest=out;V**cur=path;int remaining=count;
  while(remaining-->0){dest->q=(*cur)->position.q;dest++;cur++;}
  k=3;corner=last->vertex;
  while(--k>=0)(*corner++)->count--;
 }
 count=Filter(out,count,write);
 if(count==1){
  qword previous=out[0].q;out[1].q=previous;
  U scalar;scalar.q=ScalarWord(&D_002C0C04);
  out[0].q=AddScaled(previous,D_002A2DA0,scalar.q);count=2;
 }
 return count;
}
