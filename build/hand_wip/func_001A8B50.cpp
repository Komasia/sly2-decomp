typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];};struct SCALAR{qword q;};struct SCENE;struct CONTACT;
struct SPACE{char pad0[0x70];U position;};struct EDGE{unsigned short ends[2],surfaces[2];EDGE*next;int unknown;};struct SURFACE{U plane;EDGE*first;int tag,flags,unknown;};
struct SHAPE{SPACE*space;void*owner;char pad8[0x8C];U*vertices;int pad98;SURFACE*surfaces;int edgeCount;EDGE*edges;};
struct NODE{unsigned int left,right;SURFACE*surface;};
struct LSG{U point0,point1,plane0,plane1;float from,to;int flags;SURFACE*surface0,*surface1;EDGE*edge;int side;LSG*next;};
struct INDICES{int values[2][128];}__attribute__((aligned(16)));struct PATH{LSG*values[32];}__attribute__((aligned(16)));
struct WORK{int counts[2];LSG segments[2][128];int positions[2];INDICES indices;LSG*heads[2][128];LSG*free[2];PATH path;float parameters[2];U normal,points[2],scalar;SCALAR distances[6];};
extern "C"{extern U D_002A2DC0;int ClipEdges(SCENE*,SHAPE*,SHAPE*,NODE*,int,LSG*) __asm__("ClsgClipSoAllEdges__FP2SOT0P3BSPiP3LSG");int func_001A81F8(SCENE*,SHAPE*,SHAPE*,int,NODE*,int,LSG*);void Categorize(int,LSG*,int*,int*,LSG**,LSG**) __asm__("CategorizeAlsg__FiP3LSGPiT2PP3LSGT4");void func_001A87F0(SCENE*,SHAPE*,SHAPE*,int,int*,LSG**,CONTACT**);int func_001A86B8(SURFACE*,int,int,LSG*,LSG**);int func_0011EA60(qword,qword,qword,qword,float*,U*);SCALAR*func_002564B8(SCALAR*);void func_001A7C18(SCENE*,SHAPE*,SHAPE*,qword,qword,int,void*,void*,CONTACT**,float);}
struct XP{char pad0[0x9C];int kind;void*first,*second;int padA8;XP*next;};
static inline qword Scalar(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Blend(qword a,qword b,qword s,qword t){qword r;__asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x":"=j"(r):"j"(a),"j"(b),"j"(s),"j"(t));return r;}
static inline qword Lerp(qword a,qword b,float t,U*scalar){scalar->q=Scalar(1.0f-t);qword first=scalar->q;scalar->q=Scalar(t);return Blend(a,b,first,scalar->q);}
static inline float Length(qword v){qword d,one;float f;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(v));__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(d):"j"(d));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(d));return f;}
static inline qword MultiplyXYZ(qword a,qword b){__asm__("vmul.xyz %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline qword One(){qword q;__asm__("vaddw.x %0,$vf0,$vf0w":"=j"(q));return q;}
static inline qword ReduceDistance(qword product,qword one){__asm__("vadday.x $ACC,%0,%0y\n\tvmaddaz.x $ACC,%1,%0z\n\tvmsubw.x %0,%1,%0w":"+j"(product):"j"(one));return product;}
static inline float PlaneDistance(qword plane,qword point,SCALAR*dot,SCALAR*one){(void)func_002564B8(dot);(void)func_002564B8(one);qword product=MultiplyXYZ(plane,point);one->q=One();dot->q=ReduceDistance(product,one->q);float f;__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(dot->q));return f;}
static inline void Closest(qword a,qword b,qword c,qword d,float*parameters,U*normal){(void)func_0011EA60(a,b,c,d,parameters,normal);}
static inline qword Load(U*p){qword q;__asm__("lqc2 %0,%1":"=j"(q):"m"(*p));return q;}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
typedef char qword_Size[sizeof(qword)==16?1:-1];
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char SCALAR_Size[sizeof(SCALAR)==16?1:-1];
typedef char SPACE_Size[sizeof(SPACE)==128?1:-1];
typedef char EDGE_Size[sizeof(EDGE)==16?1:-1];
typedef char SURFACE_Size[sizeof(SURFACE)==32?1:-1];
typedef char SHAPE_Size[sizeof(SHAPE)==168?1:-1];
typedef char NODE_Size[sizeof(NODE)==12?1:-1];
typedef char LSG_Size[sizeof(LSG)==96?1:-1];
typedef char INDICES_Size[sizeof(INDICES)==1024?1:-1];
typedef char PATH_Size[sizeof(PATH)==128?1:-1];
typedef char WORK_Size[sizeof(WORK)==26976?1:-1];
typedef char XP_Size[sizeof(XP)==176?1:-1];
typedef char U_q_Offset[FIELD_OFFSET(U,q)==0?1:-1];
typedef char U_f_Offset[FIELD_OFFSET(U,f)==0?1:-1];
typedef char SCALAR_q_Offset[FIELD_OFFSET(SCALAR,q)==0?1:-1];
typedef char SPACE_position_Offset[FIELD_OFFSET(SPACE,position)==112?1:-1];
typedef char EDGE_ends_Offset[FIELD_OFFSET(EDGE,ends)==0?1:-1];
typedef char EDGE_surfaces_Offset[FIELD_OFFSET(EDGE,surfaces)==4?1:-1];
typedef char EDGE_next_Offset[FIELD_OFFSET(EDGE,next)==8?1:-1];
typedef char SURFACE_plane_Offset[FIELD_OFFSET(SURFACE,plane)==0?1:-1];
typedef char SURFACE_first_Offset[FIELD_OFFSET(SURFACE,first)==16?1:-1];
typedef char SURFACE_tag_Offset[FIELD_OFFSET(SURFACE,tag)==20?1:-1];
typedef char SURFACE_flags_Offset[FIELD_OFFSET(SURFACE,flags)==24?1:-1];
typedef char SHAPE_space_Offset[FIELD_OFFSET(SHAPE,space)==0?1:-1];
typedef char SHAPE_owner_Offset[FIELD_OFFSET(SHAPE,owner)==4?1:-1];
typedef char SHAPE_vertices_Offset[FIELD_OFFSET(SHAPE,vertices)==148?1:-1];
typedef char SHAPE_surfaces_Offset[FIELD_OFFSET(SHAPE,surfaces)==156?1:-1];
typedef char SHAPE_edgeCount_Offset[FIELD_OFFSET(SHAPE,edgeCount)==160?1:-1];
typedef char SHAPE_edges_Offset[FIELD_OFFSET(SHAPE,edges)==164?1:-1];
typedef char NODE_left_Offset[FIELD_OFFSET(NODE,left)==0?1:-1];
typedef char NODE_right_Offset[FIELD_OFFSET(NODE,right)==4?1:-1];
typedef char NODE_surface_Offset[FIELD_OFFSET(NODE,surface)==8?1:-1];
typedef char LSG_point0_Offset[FIELD_OFFSET(LSG,point0)==0?1:-1];
typedef char LSG_point1_Offset[FIELD_OFFSET(LSG,point1)==16?1:-1];
typedef char LSG_plane0_Offset[FIELD_OFFSET(LSG,plane0)==32?1:-1];
typedef char LSG_plane1_Offset[FIELD_OFFSET(LSG,plane1)==48?1:-1];
typedef char LSG_from_Offset[FIELD_OFFSET(LSG,from)==64?1:-1];
typedef char LSG_to_Offset[FIELD_OFFSET(LSG,to)==68?1:-1];
typedef char LSG_flags_Offset[FIELD_OFFSET(LSG,flags)==72?1:-1];
typedef char LSG_surface0_Offset[FIELD_OFFSET(LSG,surface0)==76?1:-1];
typedef char LSG_surface1_Offset[FIELD_OFFSET(LSG,surface1)==80?1:-1];
typedef char LSG_edge_Offset[FIELD_OFFSET(LSG,edge)==84?1:-1];
typedef char LSG_side_Offset[FIELD_OFFSET(LSG,side)==88?1:-1];
typedef char LSG_next_Offset[FIELD_OFFSET(LSG,next)==92?1:-1];
typedef char XP_kind_Offset[FIELD_OFFSET(XP,kind)==156?1:-1];
typedef char XP_first_Offset[FIELD_OFFSET(XP,first)==160?1:-1];
typedef char XP_second_Offset[FIELD_OFFSET(XP,second)==164?1:-1];
typedef char XP_next_Offset[FIELD_OFFSET(XP,next)==172?1:-1];
typedef char WORK_counts_Offset[FIELD_OFFSET(WORK,counts)==0?1:-1];
typedef char WORK_segments_Offset[FIELD_OFFSET(WORK,segments)==16?1:-1];
typedef char WORK_positions_Offset[FIELD_OFFSET(WORK,positions)==24592?1:-1];
typedef char WORK_indices_Offset[FIELD_OFFSET(WORK,indices)==24608?1:-1];
typedef char WORK_heads_Offset[FIELD_OFFSET(WORK,heads)==25632?1:-1];
typedef char WORK_free_Offset[FIELD_OFFSET(WORK,free)==26656?1:-1];
typedef char WORK_path_Offset[FIELD_OFFSET(WORK,path)==26672?1:-1];
typedef char WORK_parameters_Offset[FIELD_OFFSET(WORK,parameters)==26800?1:-1];
typedef char WORK_normal_Offset[FIELD_OFFSET(WORK,normal)==26816?1:-1];
typedef char WORK_points_Offset[FIELD_OFFSET(WORK,points)==26832?1:-1];
typedef char WORK_scalar_Offset[FIELD_OFFSET(WORK,scalar)==26864?1:-1];
typedef char WORK_distances_Offset[FIELD_OFFSET(WORK,distances)==26880?1:-1];
extern "C" void func_001A8B50(SCENE*scene,SHAPE*a,SHAPE*b,int nodeCount,NODE*nodes,NODE*last,CONTACT**out){WORK w;CONTACT*old=*out;
 w.counts[0]=ClipEdges(scene,b,a,last,128,w.segments[0]);int secondCount=func_001A81F8(scene,a,b,nodeCount,nodes,128,w.segments[1]);w.counts[1]=secondCount;if(!w.counts[0]&&!secondCount)return;
 int*counts=w.counts;LSG*segments=w.segments[0];int*positions=w.positions;int*indices=w.indices.values[0];LSG**heads=w.heads[0];LSG**free=w.free;
 int remaining=1;do{Categorize(*counts,segments,positions,indices,heads,free);++counts;segments+=128;++positions;indices+=128;heads+=128;++free;}while(--remaining>=0);
 func_001A87F0(scene,a,b,w.positions[0],w.indices.values[0],w.heads[0],out);func_001A87F0(scene,b,a,w.positions[1],w.indices.values[1],w.heads[1],out);
 for(LSG*segment=w.free[0];segment;segment=segment->next){
  if(!segment->surface0||!segment->surface1)continue;
  int length=func_001A86B8(b->surfaces,segment->surface0-b->surfaces,segment->surface1-b->surfaces,w.free[1],w.path.values);
  if(length>0){LSG**path=w.path.values;do{LSG*other=*path++;
    qword left0=a->vertices[segment->edge->ends[0]].q,left1=a->vertices[segment->edge->ends[1]].q,right0=b->vertices[other->edge->ends[0]].q,right1=b->vertices[other->edge->ends[1]].q;
    Closest(left0,left1,right0,right1,w.parameters,&w.normal);
    w.points[0].q=Lerp(left0,left1,w.parameters[0],&w.scalar);w.points[1].q=Lerp(right0,right1,w.parameters[1],&w.scalar);
    float distance=-Length(Sub(w.points[0].q,w.points[1].q));func_001A7C18(scene,a,b,w.points[0].q,w.normal.q,3,segment->edge,other->edge,out,distance);
   }while(--length);continue;
  }
  int i;LSG*other=w.segments[1];for(i=0;i<w.counts[1];i++,other++){SURFACE*first=a->surfaces+segment->edge->surfaces[0],*second=a->surfaces+segment->edge->surfaces[1];if(other->surface0==first||other->surface0==second||other->surface1==first||other->surface1==second)break;}
  if(i<w.counts[1])continue;
  float firstDistance=PlaneDistance(Load(&segment->plane0),a->space->position.q,&w.distances[0],&w.distances[1]);float secondDistance=PlaneDistance(Load(&segment->plane1),a->space->position.q,&w.distances[2],&w.distances[3]);
  SURFACE*surface;int endpoint;if(secondDistance<firstDistance){surface=segment->surface0;endpoint=1-segment->side;}else{surface=segment->surface1;endpoint=segment->side;}
  U*point=a->vertices+segment->edge->ends[endpoint];XP*contact=(XP*)*out;while(contact){if(contact->kind==1&&contact->first==point&&contact->second==surface)break;contact=contact->next;}
  if(contact)continue;
  qword position=point->q,normal=surface->plane.q;float distance=PlaneDistance(normal,position,&w.distances[4],&w.distances[5]);func_001A7C18(scene,a,b,position,normal,1,point,surface,out,distance);
 }
 if(old==*out&&(!w.counts[0]||!w.counts[1]))func_001A7C18(scene,a,b,a->space->position.q,D_002A2DC0.q,13,0,0,out,0.0f);
}