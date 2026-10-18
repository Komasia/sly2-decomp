typedef int qword __attribute__((mode(TI)));
typedef union U U;typedef struct TRI TRI;typedef union NODE NODE;typedef struct GRAPH GRAPH;typedef struct STATE STATE;typedef struct ROW ROW;typedef struct WORK WORK;
union U{qword q;float f[4];};
struct TRI{void*vertex[3];};
union NODE{U plane;struct{char pad[12];unsigned short child[2];}entry;};
struct GRAPH{char pad[12];TRI*leaves;int count;NODE*nodes;};
struct STATE{NODE*node;TRI*leaf;float parameter;U plane;};
struct ROW{U begin,end,beginPlane,endPlane;float low,high;int flags;TRI*leaf;char tail[16];};
struct WORK{STATE current,stack[32];U scalar;int capacity,flags,mask;U from,fromPlane,to,toPlane;};
extern void*func_002333B4(void*,int,unsigned int);extern int func_001BF398(float);
static inline void StorePacked(U*p,qword value){__asm__("sq %1,%0":"=m"(p->q):"r"(value):"memory");}
static inline void StoreMask(int*p,int value){__asm__("sw %1,%0":"=m"(*p):"r"(value));}
static inline int ReadCapacity(int*p){int value;__asm__("lw %0,%1":"=r"(value):"m"(*p));return value;}
static inline qword Make(float x,float y,float z){qword q,t;__asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0":"=&r"(q),"=&r"(t):"f"(x),"f"(y),"f"(z));return q;}
static inline qword PackXY(qword value){register float x __asm__("$f2"),y __asm__("$f0");__asm__("mtc1 %1,%0":"=f"(x):"r"(value));__asm__("prot3w %0,%0":"+r"(value));__asm__("mtc1 %1,%0":"=f"(y):"r"(value));return Make(x,y,-1.0f);}
static inline qword Scalar(float f){int bits;qword q;__asm__("mfc1 %0,%1":"=r"(bits):"f"(f));__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(bits));return q;}
static inline qword Lerp(U*a,U*b,float t,U*scalar){
 qword k=Scalar(t),complement=Scalar(1.0f-t),first=a->q,second=b->q,result;
 __asm__("sqc2 %1,%0":"=m"(scalar->q):"j"(complement):"memory");__asm__("sqc2 %1,%0":"=m"(scalar->q):"j"(k):"memory");
 __asm__("vmulax.xyzw $ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(result):"j"(first),"j"(complement),"j"(second),"j"(k));return result;
}
static inline void Future(STATE*s,TRI*leaves,NODE*nodes,NODE*end,unsigned int child,int mask){
 if(child&0x8000){s->node=end;if(child&mask)s->leaf=leaves+(child&0x3FFF);else s->leaf=0;}
 else{s->leaf=0;s->node=nodes+child;}
}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char NODE_Size[sizeof(NODE)==16?1:-1];
typedef char TRI_Size[sizeof(TRI)==12?1:-1];
typedef char GRAPH_Size[sizeof(GRAPH)==24?1:-1];
typedef char STATE_Size[sizeof(STATE)==32?1:-1];
typedef char ROW_Size[sizeof(ROW)==96?1:-1];
typedef char WORK_Size[sizeof(WORK)==1152?1:-1];
typedef char GRAPH_leaves_Offset[FIELD_OFFSET(GRAPH,leaves)==12?1:-1];
typedef char GRAPH_count_Offset[FIELD_OFFSET(GRAPH,count)==16?1:-1];
typedef char GRAPH_nodes_Offset[FIELD_OFFSET(GRAPH,nodes)==20?1:-1];
typedef char NODE_plane_Offset[FIELD_OFFSET(NODE,plane)==0?1:-1];
typedef char NODE_entry_child_Offset[FIELD_OFFSET(NODE,entry.child)==12?1:-1];
typedef char STATE_node_Offset[FIELD_OFFSET(STATE,node)==0?1:-1];
typedef char STATE_leaf_Offset[FIELD_OFFSET(STATE,leaf)==4?1:-1];
typedef char STATE_parameter_Offset[FIELD_OFFSET(STATE,parameter)==8?1:-1];
typedef char STATE_plane_Offset[FIELD_OFFSET(STATE,plane)==16?1:-1];
typedef char ROW_begin_Offset[FIELD_OFFSET(ROW,begin)==0?1:-1];
typedef char ROW_end_Offset[FIELD_OFFSET(ROW,end)==16?1:-1];
typedef char ROW_beginPlane_Offset[FIELD_OFFSET(ROW,beginPlane)==32?1:-1];
typedef char ROW_endPlane_Offset[FIELD_OFFSET(ROW,endPlane)==48?1:-1];
typedef char ROW_low_Offset[FIELD_OFFSET(ROW,low)==64?1:-1];
typedef char ROW_high_Offset[FIELD_OFFSET(ROW,high)==68?1:-1];
typedef char ROW_flags_Offset[FIELD_OFFSET(ROW,flags)==72?1:-1];
typedef char ROW_leaf_Offset[FIELD_OFFSET(ROW,leaf)==76?1:-1];
typedef char ROW_tail_Offset[FIELD_OFFSET(ROW,tail)==80?1:-1];
typedef char WORK_current_Offset[FIELD_OFFSET(WORK,current)==0?1:-1];
typedef char WORK_stack_Offset[FIELD_OFFSET(WORK,stack)==32?1:-1];
typedef char WORK_scalar_Offset[FIELD_OFFSET(WORK,scalar)==1056?1:-1];
typedef char WORK_capacity_Offset[FIELD_OFFSET(WORK,capacity)==1072?1:-1];
typedef char WORK_flags_Offset[FIELD_OFFSET(WORK,flags)==1076?1:-1];
typedef char WORK_mask_Offset[FIELD_OFFSET(WORK,mask)==1080?1:-1];
typedef char WORK_from_Offset[FIELD_OFFSET(WORK,from)==1088?1:-1];
typedef char WORK_fromPlane_Offset[FIELD_OFFSET(WORK,fromPlane)==1104?1:-1];
typedef char WORK_to_Offset[FIELD_OFFSET(WORK,to)==1120?1:-1];
typedef char WORK_toPlane_Offset[FIELD_OFFSET(WORK,toPlane)==1136?1:-1];
typedef char qword_Width[sizeof(qword)==16?1:-1];
typedef char int_Width[sizeof(int)==4?1:-1];
typedef char unsigned_Width[sizeof(unsigned int)==4?1:-1];
typedef char ushort_Width[sizeof(unsigned short)==2?1:-1];
typedef char float_Width[sizeof(float)==4?1:-1];
typedef char pointer_Width[sizeof(void*)==4?1:-1];
typedef char qword_Alignment[__alignof__(qword)==16?1:-1];
typedef char U_Alignment[__alignof__(U)==16?1:-1];
typedef char TRI_Alignment[__alignof__(TRI)==4?1:-1];
typedef char NODE_Alignment[__alignof__(NODE)==16?1:-1];
typedef char GRAPH_Alignment[__alignof__(GRAPH)==4?1:-1];
typedef char STATE_Alignment[__alignof__(STATE)==16?1:-1];
typedef char ROW_Alignment[__alignof__(ROW)==16?1:-1];
typedef char WORK_Alignment[__alignof__(WORK)==16?1:-1];
typedef char STATE_Stack_Span[sizeof(STATE[32])==0x400?1:-1];
typedef char ROW_OpaqueTail_Span[sizeof(((ROW*)0)->tail)==16?1:-1];
typedef char NODE_Children_Span[sizeof(((NODE*)0)->entry.child)==4?1:-1];
int func_001BF3D8(GRAPH*g,qword from,qword to,int capacity,ROW*out,int flags){
 WORK w;ROW*previous=0;int depth=0;qword firstPacked,secondPacked;int count=0;
 NODE*nodes=g->nodes,*end=nodes+g->count;TRI*leaves=g->leaves;
 w.capacity=capacity;w.flags=flags;StoreMask(&w.mask,0x4000);w.mask=(flags&1)?0x8000:w.mask;w.from.q=from;w.to.q=to;
 (void)func_002333B4(&w.current,0,sizeof(STATE));w.current.node=nodes;
 (void)func_002333B4(&w.stack[0],0,sizeof(STATE));
 firstPacked=PackXY(w.from.q);w.fromPlane.q=firstPacked;w.stack[depth].parameter=1.0f;StorePacked(&w.scalar,firstPacked);
 secondPacked=PackXY(w.to.q);w.toPlane.q=secondPacked;StorePacked(&w.scalar,secondPacked);
 for(;;){
  float first,second;int sign0,sign1,negative,positive;unsigned int child;
  if(w.current.node==end){
   if(w.current.leaf){
    if(previous&&w.current.parameter==previous->high&&((w.flags&2)||w.current.leaf==previous->leaf)){
     previous->end.q=Lerp(&w.from,&w.to,w.stack[depth].parameter,&w.scalar);
     previous->high=w.stack[depth].parameter;previous->endPlane=w.stack[depth].plane;
    }else{
     float low,high;
     if(count>=w.capacity)goto full;
     previous=out++;(void)func_002333B4(previous,0,sizeof(ROW));
     low=w.current.parameter;high=w.stack[depth].parameter;
     previous->begin.q=Lerp(&w.from,&w.to,low,&w.scalar);previous->end.q=Lerp(&w.from,&w.to,high,&w.scalar);
     previous->low=low;previous->high=high;previous->flags=3;previous->beginPlane=w.current.plane;previous->endPlane=w.stack[depth].plane;previous->leaf=w.current.leaf;count++;
    }
   }
   if(depth==0)return count;
   w.current=w.stack[depth--];continue;
  }
  {
 qword plane=w.current.node->plane.q,firstPoint=w.fromPlane.q,secondPoint=w.toPlane.q,d0,d1,one;
 __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d0),"=&j"(one):"j"(plane),"j"(firstPoint));
 __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d1),"=&j"(one):"j"(plane),"j"(secondPoint));
 __asm__("qmfc2.ni %0,%1":"=r"(first):"j"(d0));__asm__("qmfc2.ni %0,%1":"=r"(second):"j"(d1));
 }
  sign0=func_001BF398(first);sign1=func_001BF398(second);
  negative=sign0==1||sign1==1;positive=sign0==0||sign1==0;
  if(!(negative&&positive)){child=w.current.node->entry.child[positive];
   if(child&0x8000){w.current.node=end;if(child&w.mask)w.current.leaf=leaves+(child&0x3FFF);else w.current.leaf=0;}
  else w.current.node=nodes+child;
   continue;
  }
  {
   int nearNegative;float cross=first/(first-second);
   float low=w.current.parameter,high=w.stack[depth].parameter;
   float lowDistance=(1.0f-low)*first+low*second,highDistance=(1.0f-high)*first+high*second;
   if(low<cross&&cross<high){
    unsigned int other;
    ++depth;w.stack[depth].parameter=cross;
    w.stack[depth].plane.f[0]=w.current.node->plane.f[0];w.stack[depth].plane.f[1]=w.current.node->plane.f[1];w.stack[depth].plane.f[2]=0;w.stack[depth].plane.f[3]=w.current.node->plane.f[2];
    other=w.current.node->entry.child[lowDistance<=0.0f];Future(&w.stack[depth],leaves,nodes,end,other,w.mask);
   }
   nearNegative=lowDistance<0.0f||(lowDistance==0.0f&&highDistance<=0.0f);
   child=w.current.node->entry.child[!nearNegative];
  }
  if(child&0x8000){w.current.node=end;if(child&w.mask)w.current.leaf=leaves+(child&0x3FFF);else w.current.leaf=0;}
  else w.current.node=nodes+child;
 }
full:
 return ReadCapacity(&w.capacity);
}
