typedef int qword __attribute__((mode(TI)));typedef unsigned int uint;typedef unsigned short ushort;
union U{qword q;float f[4];int i[4];};struct FRAME{};struct REQ{uint bytes,alignment;};
struct FACE;struct EDGE{ushort vertices[2],face,other;EDGE*next;};
struct FACE{U plane;EDGE*edges;char pad14[4];int flags;};
struct NODE{uint left,right;FACE*poly;};
struct GEOMETRY{char pad0[4];U*points;char pad8[4];FACE*faces;};
struct SHAPE{char pad0[0x6C];int capacity;char pad70[4];NODE*tree;char pad78[0x90-0x78];GEOMETRY geometry;};
struct SPAN{U first,last,firstPlane,lastPlane;float from,to;int flags;FACE*firstFace,*lastFace;};
struct CONTACT{U point,plane;int kind;union{FACE*face;EDGE*edge;U*vertex;}detail;};
struct MEMO{int vertex;U point,plane;};
union SPACE{REQ request;struct{U first,second;SPAN spans[16];U scalar;}face;struct{U edge,difference,normal,closest,plane,scalar;}line;};
struct WORK{MEMO memo[256];FRAME frame;SPACE space;};
extern "C"{
 FRAME*func_001AE478(FRAME*);void func_001AE4A0(FRAME*,int);void*func_001AE318(REQ*);
 int func_00118A88(NODE*,int,qword,float,int*,NODE**);
 int func_00118668(NODE*,int,qword,qword,int,SPAN*);
 void func_00119390(U*,qword,qword);NODE*func_00119090(NODE*,int,qword);
 void func_001A9108(NODE*,int,GEOMETRY*,qword,CONTACT*,float);
}
static inline qword ScaledWithScratch(U*home,qword center,qword direction,qword scale){
 qword result;
 __asm__("sqc2 %3,%1\n\tvadda.xyzw $ACC,%2,$vf0\n\tvmaddx.xyzw %0,%4,%3x":"=j"(result),"=m"(home->q):"j"(center),"j"(scale),"j"(direction));
 return result;
}
static inline float Negative(float f){float n;__asm__("neg.s %0,%1":"=f"(n):"f"(f));return n;}
static inline qword Scalar(float f){qword q;int bits;__asm__("mfc1 %0,%1":"=r"(bits):"f"(f));__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(bits));return q;}
static inline qword AddScaled(qword a,qword b,qword k){qword q;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(q):"j"(a),"j"(b),"j"(k));return q;}
static inline qword Difference(qword a,qword b){qword q;__asm__("vsub.xyzw %0,%1,%2":"=j"(q):"j"(a),"j"(b));return q;}
static inline float Dot(qword a,qword b){qword q,one;float f;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(q),"=&j"(one):"j"(a),"j"(b));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(q));return f;}
static inline qword Normal(qword value){qword q,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(q),"=&j"(one):"j"(value));__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(q));__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(q):"j"(q),"j"(value));return q;}
static inline qword Copy(qword source){qword q;__asm__("vmove.xyzw %0,%1":"=j"(q):"j"(source));return q;}
static inline qword Point(const qword*source){return *source;}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char FRAME_Size[sizeof(FRAME)==1?1:-1];
typedef char REQ_Size[sizeof(REQ)==8?1:-1];
typedef char EDGE_Size[sizeof(EDGE)==12?1:-1];
typedef char FACE_Size[sizeof(FACE)==32?1:-1];
typedef char NODE_Size[sizeof(NODE)==12?1:-1];
typedef char GEOMETRY_Size[sizeof(GEOMETRY)==16?1:-1];
typedef char SHAPE_Size[sizeof(SHAPE)==160?1:-1];
typedef char SPAN_Size[sizeof(SPAN)==96?1:-1];
typedef char CONTACT_Size[sizeof(CONTACT)==48?1:-1];
typedef char MEMO_Size[sizeof(MEMO)==48?1:-1];
typedef char SPACE_Size[sizeof(SPACE)==1584?1:-1];
typedef char WORK_Size[sizeof(WORK)==0x3640?1:-1];
typedef char EDGE_vertices_Offset[FIELD_OFFSET(EDGE,vertices)==0?1:-1];
typedef char EDGE_other_Offset[FIELD_OFFSET(EDGE,other)==6?1:-1];
typedef char EDGE_next_Offset[FIELD_OFFSET(EDGE,next)==8?1:-1];
typedef char FACE_plane_Offset[FIELD_OFFSET(FACE,plane)==0?1:-1];
typedef char FACE_edges_Offset[FIELD_OFFSET(FACE,edges)==16?1:-1];
typedef char FACE_flags_Offset[FIELD_OFFSET(FACE,flags)==24?1:-1];
typedef char NODE_poly_Offset[FIELD_OFFSET(NODE,poly)==8?1:-1];
typedef char GEOMETRY_points_Offset[FIELD_OFFSET(GEOMETRY,points)==4?1:-1];
typedef char GEOMETRY_faces_Offset[FIELD_OFFSET(GEOMETRY,faces)==12?1:-1];
typedef char SHAPE_capacity_Offset[FIELD_OFFSET(SHAPE,capacity)==108?1:-1];
typedef char SHAPE_tree_Offset[FIELD_OFFSET(SHAPE,tree)==116?1:-1];
typedef char SHAPE_geometry_Offset[FIELD_OFFSET(SHAPE,geometry)==144?1:-1];
typedef char SPAN_first_Offset[FIELD_OFFSET(SPAN,first)==0?1:-1];
typedef char SPAN_last_Offset[FIELD_OFFSET(SPAN,last)==16?1:-1];
typedef char SPAN_from_Offset[FIELD_OFFSET(SPAN,from)==64?1:-1];
typedef char SPAN_to_Offset[FIELD_OFFSET(SPAN,to)==68?1:-1];
typedef char SPAN_firstFace_Offset[FIELD_OFFSET(SPAN,firstFace)==76?1:-1];
typedef char SPAN_lastFace_Offset[FIELD_OFFSET(SPAN,lastFace)==80?1:-1];
typedef char CONTACT_point_Offset[FIELD_OFFSET(CONTACT,point)==0?1:-1];
typedef char CONTACT_plane_Offset[FIELD_OFFSET(CONTACT,plane)==16?1:-1];
typedef char CONTACT_kind_Offset[FIELD_OFFSET(CONTACT,kind)==32?1:-1];
typedef char CONTACT_detail_Offset[FIELD_OFFSET(CONTACT,detail)==36?1:-1];
typedef char MEMO_vertex_Offset[FIELD_OFFSET(MEMO,vertex)==0?1:-1];
typedef char MEMO_point_Offset[FIELD_OFFSET(MEMO,point)==16?1:-1];
typedef char MEMO_plane_Offset[FIELD_OFFSET(MEMO,plane)==32?1:-1];
typedef char WORK_memo_Offset[FIELD_OFFSET(WORK,memo)==0?1:-1];
typedef char WORK_frame_Offset[FIELD_OFFSET(WORK,frame)==12288?1:-1];
typedef char WORK_space_Offset[FIELD_OFFSET(WORK,space)==12304?1:-1];
typedef char Trace_Buffer_Offset[FIELD_OFFSET(SPACE,face.spans)==32?1:-1];
typedef char Face_Scalar_Offset[FIELD_OFFSET(SPACE,face.scalar)==0x620?1:-1];
typedef char Edge_Normal_Offset[FIELD_OFFSET(SPACE,line.normal)==32?1:-1];
typedef char Edge_Plane_Offset[FIELD_OFFSET(SPACE,line.plane)==64?1:-1];
typedef char qword_Width[sizeof(qword)==16?1:-1];
typedef char int_Width[sizeof(int)==4?1:-1];
typedef char uint_Width[sizeof(uint)==4?1:-1];
typedef char ushort_Width[sizeof(ushort)==2?1:-1];
typedef char float_Width[sizeof(float)==4?1:-1];
typedef char pointer_Width[sizeof(void*)==4?1:-1];
typedef char qword_Alignment[__alignof__(qword)==16?1:-1];
typedef char U_Alignment[__alignof__(U)==16?1:-1];
typedef char FRAME_Alignment[__alignof__(FRAME)==1?1:-1];
typedef char REQ_Alignment[__alignof__(REQ)==4?1:-1];
typedef char EDGE_Alignment[__alignof__(EDGE)==4?1:-1];
typedef char FACE_Alignment[__alignof__(FACE)==16?1:-1];
typedef char NODE_Alignment[__alignof__(NODE)==4?1:-1];
typedef char GEOMETRY_Alignment[__alignof__(GEOMETRY)==4?1:-1];
typedef char SHAPE_Alignment[__alignof__(SHAPE)==4?1:-1];
typedef char SPAN_Alignment[__alignof__(SPAN)==16?1:-1];
typedef char CONTACT_Alignment[__alignof__(CONTACT)==16?1:-1];
typedef char MEMO_Alignment[__alignof__(MEMO)==16?1:-1];
typedef char SPACE_Alignment[__alignof__(SPACE)==16?1:-1];
typedef char WORK_Alignment[__alignof__(WORK)==16?1:-1];
typedef char SPAN_firstPlane_Offset[FIELD_OFFSET(SPAN,firstPlane)==0x20?1:-1];
typedef char SPAN_lastPlane_Offset[FIELD_OFFSET(SPAN,lastPlane)==0x30?1:-1];
typedef char SPAN_flags_Offset[FIELD_OFFSET(SPAN,flags)==0x48?1:-1];
typedef char MEMO_Array_Span[sizeof(MEMO[256])==0x3000?1:-1];
typedef char SPAN_Array_Span[sizeof(SPAN[16])==0x600?1:-1];
extern "C" int func_001A93C8(qword point,SHAPE*shape,int mask,int count,NODE*nodes,int maximum,CONTACT*out,float radius){
 WORK w;int capacity;NODE*end;int produced=0,i,memoCount,edgeBegin;FACE*face;
 memoCount=0;
 (void)func_001AE478(&w.frame);
 if(maximum<=0)goto done;
 if(!nodes){
  int limit=shape->capacity;if(limit>0x1554)limit=0x1555;capacity=limit;
  w.space.request.bytes=(uint)capacity*12u;w.space.request.alignment=16;nodes=(NODE*)func_001AE318(&w.space.request);
  end=nodes;
  int status=func_00118A88(shape->tree,mask,Point(&point),radius,&capacity,&end);
  if(status==0)goto fallback;
  if(status==1)goto done;
  count=end-nodes;
 }
 end=(NODE*)((uint)nodes+(uint)count*sizeof(NODE)-sizeof(NODE));
 {NODE*selected=nodes;i=(int)((uint)count-1u);for(;i>=0;i--)selected[i].poly->flags|=0x10;}
 {
  i=(int)((uint)count-1u);
  for(;i>=0;i--){
   NODE*entry=nodes+i;face=entry->poly;
   if(!(face->flags&0x10)||(face->flags&0x40))continue;
   face->flags|=0x40;
   qword positive=Scalar(radius),center=Point(&point);float negativeRadius=Negative(radius);qword negative=Scalar(negativeRadius);
   w.space.face.first.q=ScaledWithScratch(&w.space.face.scalar,center,entry->poly->plane.q,positive);
   w.space.face.second.q=ScaledWithScratch(&w.space.face.scalar,center,entry->poly->plane.q,negative);
   int spans=func_00118668(end,0x7FFFFFFF,w.space.face.first.q,w.space.face.second.q,16,w.space.face.spans);
   int k=0;for(;k<spans;k++){SPAN*span=w.space.face.spans+k;FACE*hit=(span->from+span->to)>1.0f?span->firstFace:span->lastFace;if(hit==face)break;}
   if(k<spans&&produced<maximum){
    CONTACT*contact=out+produced;
    qword normal=face->plane.q,center=Point(&point);qword scale=Scalar(negativeRadius);contact->point.q=ScaledWithScratch(&w.space.face.scalar,center,normal,scale);
    contact->plane.q=normal;contact->kind=6;contact->detail.face=face;produced++;
    if(produced>=maximum)goto cleanup;
    face->flags|=0x80;
   }
  }
 }
 edgeBegin=produced;
 {
  i=(int)((uint)count-1u);
  for(;i>=0;i--){
   U*points=shape->geometry.points;FACE*faces=shape->geometry.faces;
   NODE*entry=nodes+i;face=entry->poly;
   if(!(face->flags&0x10)||(face->flags&0xA0))continue;
   face->flags|=0x20;
   for(EDGE*edge=face->edges;edge;edge=edge->next){
    FACE*other=faces+edge->other;
    if(!(other->flags&0x10)||(other->flags&0x80))continue;
    U*closest=points+edge->vertices[0];U*second=points+edge->vertices[1];
    w.space.line.edge.q=Difference(second->q,closest->q);
    float square=Dot(w.space.line.edge.q,w.space.line.edge.q);
    w.space.line.difference.q=Difference(Point(&point),closest->q);
    float projection=Dot(w.space.line.difference.q,w.space.line.edge.q)/square;
    int vertex;
    if(projection<0.0001f)vertex=edge->vertices[0];
    else if(projection>0.9999f){closest=second;vertex=edge->vertices[1];w.space.line.difference.q=Difference(Point(&point),closest->q);}
    else{vertex=-1;qword scale=Scalar(projection);w.space.line.closest.q=ScaledWithScratch(&w.space.line.scalar,closest->q,w.space.line.edge.q,scale);closest=&w.space.line.closest;w.space.line.difference.q=Difference(Point(&point),closest->q);}
    float distance=Dot(w.space.line.difference.q,w.space.line.difference.q);
    qword difference=Copy(w.space.line.difference.q);
    if(distance>radius*radius)continue;
    if(vertex>=0){int k=memoCount-1;for(;k>=0;k--)if(w.memo[k].vertex==vertex)break;if(k>=0)continue;}
    w.space.line.normal.q=Normal(difference);
    func_00119390(&w.space.line.plane,w.space.line.normal.q,closest->q);
    qword scale=Scalar(-radius);qword surface=ScaledWithScratch(&w.space.line.scalar,Point(&point),w.space.line.normal.q,scale);
    if(vertex>=0){
     if((uint)memoCount<256){MEMO*memo=w.memo+memoCount;memo->vertex=vertex;memo->point.q=surface;memo->plane=w.space.line.plane;memoCount++;}
    }else if(produced<maximum){
     CONTACT*contact=out+produced;contact->point.q=surface;contact->plane=w.space.line.plane;contact->kind=5;contact->detail.edge=edge;produced++;if(produced>=maximum)goto cleanup;
    }
   }
  }
 }
 {
  int edgeEnd=produced;
  for(int k=memoCount-1;k>=0;k--){
   MEMO*memo=w.memo+k;int i=edgeBegin;
   for(;i<edgeEnd;i++){EDGE*edge=out[i].detail.edge;if(edge->vertices[0]==memo->vertex||edge->vertices[1]==memo->vertex)break;}
   if(!(i<edgeEnd)&&produced<maximum){CONTACT*contact=out+produced;contact->point=memo->point;contact->plane=memo->plane;contact->kind=4;contact->detail.vertex=shape->geometry.points+memo->vertex;produced++;if(produced>=maximum)goto cleanup;}
  }
 }
 cleanup:
 {NODE*selected=nodes;i=(int)((uint)count-1u);for(;i>=0;i--){face=selected[i].poly;face->flags&=~0xF0;}}
 fallback:
 if(!produced&&func_00119090(shape->tree,mask,Point(&point))){produced=1;func_001A9108(shape->tree,mask,&shape->geometry,Point(&point),out,radius);}
 done:
 func_001AE4A0(&w.frame,2);return produced;
}
