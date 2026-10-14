typedef int qword __attribute__((mode(TI)));typedef unsigned short ushort;
union U{qword q;float f[4];int i[4];};struct EDGE;struct NODE;
struct FACE{U plane;EDGE*first,*second;int flags;};struct EDGE{ushort vertices[2],face,other;EDGE*next,*nextOther;};struct GEOMETRY{char pad0[4];U*points;char pad8[4];FACE*faces;};struct QUERY{int pad0,count,pad8;NODE*tree;};
struct SHAPE{char pad0[0x68];QUERY query;char pad78[0x18];GEOMETRY geometry;};struct P{char pad0[0x258];SHAPE*shape;};struct JT{P*actor;};
struct SPAN{U first,last,firstPlane,lastPlane;float from,to;int flags;FACE*firstFace,*lastFace;};union SPACE{EDGE*edges[64];struct{U direction;SPAN spans[2];}face;};struct WORK{SPACE space;U direction,sum;};
extern "C"{extern U D_002A2DD0,D_002A2DA0;int func_001665F0(GEOMETRY*,QUERY*,int,int,EDGE**);int func_00199408(JT*,SHAPE*,EDGE*,U*);int func_00118668(NODE*,int,qword,qword,int,SPAN*);int func_001997D8(JT*,qword,qword);}
static inline qword ReadVector(U*source){qword q;__asm__("lqc2 %0,%1":"=j"(q):"m"(source->q));return q;}
static inline qword Add(qword a,qword b){__asm__("vadd.xyzw %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline qword Normal(qword source){register qword v __asm__("vf3")=source;register qword d __asm__("vf1");register qword one __asm__("vf2");float length;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(v));__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));qword fallback=D_002A2DA0.q;int bits;__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(d));__asm__("mtc1 %1,%0":"=f"(length):"r"(bits));if(length<0.0001f){d=fallback;}else{__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(d):"j"(d),"j"(v));}return d;}
static inline qword NormalObject(U*object){register qword v __asm__("vf4")=object->q;register qword d __asm__("vf1");register qword one __asm__("vf2");float length;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(v));__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));qword fallback=D_002A2DA0.q;int bits;__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(d));__asm__("mtc1 %1,%0":"=f"(length):"r"(bits));if(length<0.0001f){d=fallback;}else{__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(d):"j"(d),"j"(object->q));}return d;}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char FACE_Size[sizeof(FACE)==32?1:-1];
typedef char EDGE_Size[sizeof(EDGE)==16?1:-1];
typedef char GEOMETRY_Size[sizeof(GEOMETRY)==16?1:-1];
typedef char QUERY_Size[sizeof(QUERY)==16?1:-1];
typedef char SHAPE_Size[sizeof(SHAPE)==160?1:-1];
typedef char P_Size[sizeof(P)==604?1:-1];
typedef char JT_Size[sizeof(JT)==4?1:-1];
typedef char SPAN_Size[sizeof(SPAN)==96?1:-1];
typedef char SPACE_Size[sizeof(SPACE)==256?1:-1];
typedef char WORK_Size[sizeof(WORK)==288?1:-1];
typedef char FACE_plane_Offset[FIELD_OFFSET(FACE,plane)==0?1:-1];
typedef char FACE_first_Offset[FIELD_OFFSET(FACE,first)==16?1:-1];
typedef char FACE_second_Offset[FIELD_OFFSET(FACE,second)==20?1:-1];
typedef char FACE_flags_Offset[FIELD_OFFSET(FACE,flags)==24?1:-1];
typedef char EDGE_vertices_Offset[FIELD_OFFSET(EDGE,vertices)==0?1:-1];
typedef char EDGE_face_Offset[FIELD_OFFSET(EDGE,face)==4?1:-1];
typedef char EDGE_other_Offset[FIELD_OFFSET(EDGE,other)==6?1:-1];
typedef char EDGE_next_Offset[FIELD_OFFSET(EDGE,next)==8?1:-1];
typedef char EDGE_nextOther_Offset[FIELD_OFFSET(EDGE,nextOther)==12?1:-1];
typedef char GEOMETRY_points_Offset[FIELD_OFFSET(GEOMETRY,points)==4?1:-1];
typedef char GEOMETRY_faces_Offset[FIELD_OFFSET(GEOMETRY,faces)==12?1:-1];
typedef char QUERY_count_Offset[FIELD_OFFSET(QUERY,count)==4?1:-1];
typedef char QUERY_tree_Offset[FIELD_OFFSET(QUERY,tree)==12?1:-1];
typedef char SHAPE_query_Offset[FIELD_OFFSET(SHAPE,query)==104?1:-1];
typedef char SHAPE_geometry_Offset[FIELD_OFFSET(SHAPE,geometry)==144?1:-1];
typedef char P_shape_Offset[FIELD_OFFSET(P,shape)==600?1:-1];
typedef char JT_actor_Offset[FIELD_OFFSET(JT,actor)==0?1:-1];
typedef char SPAN_first_Offset[FIELD_OFFSET(SPAN,first)==0?1:-1];
typedef char SPAN_last_Offset[FIELD_OFFSET(SPAN,last)==16?1:-1];
typedef char SPAN_from_Offset[FIELD_OFFSET(SPAN,from)==64?1:-1];
typedef char SPAN_to_Offset[FIELD_OFFSET(SPAN,to)==68?1:-1];
typedef char SPAN_firstFace_Offset[FIELD_OFFSET(SPAN,firstFace)==76?1:-1];
typedef char SPAN_lastFace_Offset[FIELD_OFFSET(SPAN,lastFace)==80?1:-1];
typedef char WORK_space_Offset[FIELD_OFFSET(WORK,space)==0?1:-1];
typedef char WORK_direction_Offset[FIELD_OFFSET(WORK,direction)==256?1:-1];
typedef char WORK_sum_Offset[FIELD_OFFSET(WORK,sum)==272?1:-1];
typedef char Face_Vector_Offset[FIELD_OFFSET(SPACE,face.direction)==0?1:-1];
typedef char Face_Trace_Offset[FIELD_OFFSET(SPACE,face.spans)==16?1:-1];
extern "C" int func_001999D0(JT*p,SHAPE*shape,qword point,int kind,void*info,U*out){
 WORK w;
 switch(kind){
 case 1:{
  qword sum=ReadVector(&D_002A2DD0);int found=0;
  int count=func_001665F0(&shape->geometry,&shape->query,(U*)info-shape->geometry.points,64,w.space.edges);
  for(int i=0;i<count;i++){if(func_00199408(p,shape,w.space.edges[i],&w.direction)){found=1;sum=Add(sum,w.direction.q);}}
  if(!found)return 0;out->q=Normal(sum);break;
 }
 case 3:if(!func_00199408(p,shape,(EDGE*)info,out))return 0;break;
 case 2:{
  FACE*face=(FACE*)info;if(face->plane.f[2]<0.7f)return 0;int found=0;w.sum=D_002A2DD0;
  for(EDGE*edge=face->first;edge;edge=edge->next){
   if(func_00199408(p,shape,edge,&w.space.face.direction)){
    U*points=shape->geometry.points;
    if(func_00118668(p->actor->shape->query.tree,0x7FFFFFFF,points[edge->vertices[0]].q,points[edge->vertices[1]].q,2,w.space.face.spans)>0){found=1;w.sum.q=Add(w.sum.q,w.space.face.direction.q);}
   }
  }
  for(EDGE*edge=face->second;edge;edge=edge->nextOther){
   if(func_00199408(p,shape,edge,&w.space.face.direction)){
    U*points=shape->geometry.points;
    if(func_00118668(p->actor->shape->query.tree,0x7FFFFFFF,points[edge->vertices[0]].q,points[edge->vertices[1]].q,2,w.space.face.spans)>0){found=1;w.sum.q=Add(w.sum.q,w.space.face.direction.q);}
   }
  }
  if(!found)return 0;out->q=NormalObject(&w.sum);break;
 }
 }
 return func_001997D8(p,point,out->q);
}