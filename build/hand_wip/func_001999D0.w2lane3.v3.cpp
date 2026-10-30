typedef int qword __attribute__((mode(TI)));typedef unsigned short ushort;
union U{qword q;float f[4];int i[4];};struct EDGE;struct NODE;
struct FACE{U plane;EDGE*first,*second;int flags;};struct EDGE{ushort vertices[2],face,other;EDGE*next,*nextOther;};struct GEOMETRY{char pad0[4];U*points;char pad8[4];FACE*faces;};struct QUERY{int pad0,count,pad8;NODE*tree;};
struct SHAPE{char pad0[0x68];QUERY query;char pad78[0x18];GEOMETRY geometry;};struct P{char pad0[0x258];SHAPE*shape;};struct JT{P*actor;};
struct SPAN{U first,last,firstPlane,lastPlane;float from,to;int flags;FACE*firstFace,*lastFace;};union SPACE{EDGE*edges[64];struct{U direction;SPAN spans[2];}face;};struct WORK{SPACE space;U direction,sum;};
extern "C"{extern U D_002A2DD0,D_002A2DA0;int func_001665F0(GEOMETRY*,QUERY*,int,int,EDGE**);int func_00199408(JT*,SHAPE*,EDGE*,U*);int func_00118668(NODE*,int,qword,qword,int,SPAN*);int func_001997D8(JT*,qword,qword);}
/* allocation-only: the repeated "j"(v) operands below raise v's allocation priority (no code); kind 1 needs them so the running sum is caller-saved in vf3 around the calls */
static inline qword Add(qword a,qword b){__asm__("vadd.xyzw %0,%0,%1":"+j"(a):"j"(b));return a;}
/* Add2: the "vf2" clobber is allocation-only, it moves the second loop's running sum from vf2 to vf3 as in the original */
static inline qword Add2(qword a,qword b){__asm__("vadd.xyzw %0,%0,%1":"+j"(a):"j"(b):"vf2");return a;}
static inline qword Len(qword v)
{
    qword d, one, l;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v), "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    return l;
}
static inline qword Div(qword v, qword l)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v), "j"(v));
    return r;
}
static __inline__ float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
extern "C" int func_001999D0(JT*p,SHAPE*shape,qword point,int kind,void*info,U*out){
 WORK w;
 register qword res __asm__("vf1"); /* normalized direction lives in vf1 on both paths */
 switch(kind){
 case 1:{
  int found=0;
  qword sum=D_002A2DD0.q;
  GEOMETRY*geometry=&shape->geometry;
  int count=func_001665F0(geometry,&shape->query,(U*)info-geometry->points,64,w.space.edges);
  for(int index=0;index<count;++index){
   if(func_00199408(p,shape,w.space.edges[index],&w.direction)){found=1;sum=Add(sum,w.direction.q);}
  }
  if(!found)return 0;
  qword l=Len(sum);qword fallback=D_002A2DA0.q;
  if(F(l)<1.0e-4f)res=fallback;else res=Div(sum,l);
  out->q=res;break;
 }
 case 3:if(!func_00199408(p,shape,(EDGE*)info,out))return 0;break;
 case 2:{
  FACE*face=(FACE*)info;if(face->plane.f[2]<0.7f)return 0;int found=0;w.sum.q=D_002A2DD0.q;
  for(EDGE*edge=face->first;edge;edge=edge->next){
   if(func_00199408(p,shape,edge,&w.space.face.direction)){
    U*points=shape->geometry.points;
    if(func_00118668(p->actor->shape->query.tree,0x7FFFFFFF,points[edge->vertices[0]].q,points[edge->vertices[1]].q,2,w.space.face.spans)>0){found=1;w.sum.q=Add(w.sum.q,w.space.face.direction.q);}
   }
  }
  for(EDGE*edge=face->second;edge;edge=edge->nextOther){
   if(func_00199408(p,shape,edge,&w.space.face.direction)){
    U*points=shape->geometry.points;
    if(func_00118668(p->actor->shape->query.tree,0x7FFFFFFF,points[edge->vertices[0]].q,points[edge->vertices[1]].q,2,w.space.face.spans)>0){found=1;w.sum.q=Add2(w.sum.q,w.space.face.direction.q);}
   }
  }
  if(!found)return 0;
  qword l=Len(w.sum.q);__asm__("" : "+m"(w.sum.q)); /* emits nothing: stops cse from merging the two loads of w.sum, the original reloads it for the divide */qword v2=w.sum.q;qword fallback=D_002A2DA0.q;
  if(F(l)<1.0e-4f)res=fallback;else res=Div(v2,l);
  out->q=res;break;
 }
 }
 return func_001997D8(p,point,out->q);
}
