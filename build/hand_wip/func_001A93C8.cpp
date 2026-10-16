typedef int qword __attribute__((mode(TI)));typedef unsigned int uint;typedef unsigned short ushort;
union U{qword q;float f[4];int i[4];};struct FRAME{};struct REQ{int bytes,alignment;};
struct FACE;struct EDGE{ushort vertices[2],face,other;EDGE*next;};
struct FACE{U plane;EDGE*edges;char pad14[4];int flags;};
struct NODE{uint left,right;FACE*poly;};
struct GEOMETRY{char pad0[4];U*points;char pad8[4];FACE*faces;};
struct SHAPE{char pad0[0x6C];int capacity;char pad70[4];NODE*tree;char pad78[0x90-0x78];GEOMETRY geometry;};
struct SPAN{U first,last,firstPlane,lastPlane;float from,to;int flags;FACE*firstFace,*lastFace;};
struct CONTACT{U point,plane;int kind;union{FACE*face;EDGE*edge;U*vertex;}detail;};
struct MEMO{int vertex;U point,plane;};
union SPACE{REQ request;struct{U first,second;SPAN spans[16];U scalar;}face;struct{U edge,difference,normal,closest,plane,scalar;}line;};
struct WORK{MEMO memo[256];FRAME frame;SPACE space;int capacity;NODE*end;SHAPE*shape;int mask,count;NODE*nodes;CONTACT*out;int memoCount,edgeBegin;};
extern "C"{
 FRAME*func_001AE478(FRAME*);void func_001AE4A0(FRAME*,int);void*func_001AE318(REQ*);
 int func_00118A88(NODE*,int,qword,float,int*,NODE**);
 int func_00118668(NODE*,int,qword,qword,int,SPAN*);
 void func_00119390(U*,qword,qword);NODE*func_00119090(NODE*,int,qword);
 void func_001A9108(NODE*,int,GEOMETRY*,qword,CONTACT*,float);
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
typedef char WORK_Size[sizeof(WORK)==13936?1:-1];
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
typedef char WORK_capacity_Offset[FIELD_OFFSET(WORK,capacity)==13888?1:-1];
typedef char WORK_end_Offset[FIELD_OFFSET(WORK,end)==13892?1:-1];
typedef char WORK_shape_Offset[FIELD_OFFSET(WORK,shape)==13896?1:-1];
typedef char WORK_mask_Offset[FIELD_OFFSET(WORK,mask)==13900?1:-1];
typedef char WORK_count_Offset[FIELD_OFFSET(WORK,count)==13904?1:-1];
typedef char WORK_nodes_Offset[FIELD_OFFSET(WORK,nodes)==13908?1:-1];
typedef char WORK_out_Offset[FIELD_OFFSET(WORK,out)==13912?1:-1];
typedef char WORK_memoCount_Offset[FIELD_OFFSET(WORK,memoCount)==13916?1:-1];
typedef char WORK_edgeBegin_Offset[FIELD_OFFSET(WORK,edgeBegin)==13920?1:-1];
typedef char Trace_Buffer_Offset[FIELD_OFFSET(SPACE,face.spans)==32?1:-1];
typedef char Face_Scalar_Offset[FIELD_OFFSET(SPACE,face.scalar)==0x620?1:-1];
typedef char Edge_Normal_Offset[FIELD_OFFSET(SPACE,line.normal)==32?1:-1];
typedef char Edge_Plane_Offset[FIELD_OFFSET(SPACE,line.plane)==64?1:-1];
extern "C" int func_001A93C8(qword point,SHAPE*shape,int mask,int count,NODE*nodes,int maximum,CONTACT*out,float radius){
 WORK w;int produced=0,i;FACE*face;
 w.shape=shape;w.mask=mask;w.count=count;w.nodes=nodes;w.out=out;w.memoCount=0;
 (void)func_001AE478(&w.frame);
 if(maximum<=0)goto done;
 if(!w.nodes){
  int limit=w.shape->capacity;if(limit>0x1554)limit=0x1555;w.capacity=limit;
  w.space.request.bytes=w.capacity*12;w.space.request.alignment=16;w.nodes=(NODE*)func_001AE318(&w.space.request);
  w.end=w.nodes;
  int status=func_00118A88(w.shape->tree,w.mask,Point(&point),radius,&w.capacity,&w.end);
  if(status==0)goto fallback;
  if(status==1)goto done;
  w.count=w.end-w.nodes;
 }
 w.end=w.nodes+w.count-1;
 {NODE*selected=w.nodes;i=w.count-1;for(;i>=0;i--)selected[i].poly->flags|=0x10;}
 {
  i=w.count-1;
  for(;i>=0;i--){
   NODE*entry=w.nodes+i;face=entry->poly;
   if(!(face->flags&0x10)||(face->flags&0x40))continue;
   face->flags|=0x40;
   w.space.face.scalar.q=Scalar(radius);qword positive=w.space.face.scalar.q,center=Point(&point);float negativeRadius=Negative(radius);qword negative=Scalar(negativeRadius);
   w.space.face.first.q=AddScaled(center,entry->poly->plane.q,positive);w.space.face.scalar.q=negative;
   w.space.face.second.q=AddScaled(center,entry->poly->plane.q,w.space.face.scalar.q);
   int spans=func_00118668(w.end,0x7FFFFFFF,w.space.face.first.q,w.space.face.second.q,16,w.space.face.spans);
   int k=0;for(;k<spans;k++){SPAN*span=w.space.face.spans+k;FACE*hit=(span->from+span->to)>1.0f?span->firstFace:span->lastFace;if(hit==face)break;}
   if(k<spans&&produced<maximum){
    CONTACT*contact=w.out+produced;
    qword normal=face->plane.q,center=Point(&point);w.space.face.scalar.q=Scalar(negativeRadius);contact->point.q=AddScaled(center,normal,w.space.face.scalar.q);
    contact->plane.q=normal;contact->kind=6;contact->detail.face=face;produced++;
    if(produced>=maximum)goto cleanup;
    face->flags|=0x80;
   }
  }
 }
 w.edgeBegin=produced;
 {
  i=w.count-1;
  for(;i>=0;i--){
   U*points=w.shape->geometry.points;FACE*faces=w.shape->geometry.faces;
   NODE*entry=w.nodes+i;face=entry->poly;
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
    else{vertex=-1;w.space.line.scalar.q=Scalar(projection);w.space.line.closest.q=AddScaled(closest->q,w.space.line.edge.q,w.space.line.scalar.q);closest=&w.space.line.closest;w.space.line.difference.q=Difference(Point(&point),closest->q);}
    float distance=Dot(w.space.line.difference.q,w.space.line.difference.q);
    qword difference=Copy(w.space.line.difference.q);
    if(distance>radius*radius)continue;
    if(vertex>=0){int k=w.memoCount-1;for(;k>=0;k--)if(w.memo[k].vertex==vertex)break;if(k>=0)continue;}
    w.space.line.normal.q=Normal(difference);
    func_00119390(&w.space.line.plane,w.space.line.normal.q,closest->q);
    w.space.line.scalar.q=Scalar(-radius);qword surface=AddScaled(Point(&point),w.space.line.normal.q,w.space.line.scalar.q);
    if(vertex>=0){
     if((uint)w.memoCount<256){MEMO*memo=w.memo+w.memoCount;memo->vertex=vertex;memo->point.q=surface;memo->plane=w.space.line.plane;w.memoCount++;}
    }else if(produced<maximum){
     CONTACT*contact=w.out+produced;contact->point.q=surface;contact->plane=w.space.line.plane;contact->kind=5;contact->detail.edge=edge;produced++;if(produced>=maximum)goto cleanup;
    }
   }
  }
 }
 {
  int edgeEnd=produced;
  for(int k=w.memoCount-1;k>=0;k--){
   MEMO*memo=w.memo+k;int i=w.edgeBegin;
   for(;i<edgeEnd;i++){EDGE*edge=w.out[i].detail.edge;if(edge->vertices[0]==memo->vertex||edge->vertices[1]==memo->vertex)break;}
   if(!(i<edgeEnd)&&produced<maximum){CONTACT*contact=w.out+produced;contact->point=memo->point;contact->plane=memo->plane;contact->kind=4;contact->detail.vertex=w.shape->geometry.points+memo->vertex;produced++;if(produced>=maximum)goto cleanup;}
  }
 }
 cleanup:
 {NODE*selected=w.nodes;i=w.count-1;for(;i>=0;i--){face=selected[i].poly;face->flags&=~0xF0;}}
 fallback:
 if(!produced&&func_00119090(w.shape->tree,w.mask,Point(&point))){produced=1;func_001A9108(w.shape->tree,w.mask,&w.shape->geometry,Point(&point),w.out,radius);}
 done:
 func_001AE4A0(&w.frame,2);return produced;
}
