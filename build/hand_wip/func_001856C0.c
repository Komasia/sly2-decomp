
typedef int qword __attribute__((mode(TI)));
typedef union U{qword q;float f[4];int i[4];}U;
typedef struct M4{U r[4];}M4;
typedef struct VTE{short delta,pad;void*fn;}VTE;
typedef struct I3{int index[3];}I3;
typedef struct MESH{char pad0[0xC];VTE*vt;char pad10[0xD4];qword*vertices;int triangleCount;I3*triangles,*neighbors;}MESH;
typedef struct LIST{int count;char pad4[0xC];qword planes[1];}LIST;
typedef struct PARAMS{float a,b,duration;}PARAMS;
typedef struct IO{float distance,clamped;int count;qword*points;}IO;
typedef struct WORK{M4 matrix;U vertices[3],closest,plane;IO query;U triangleNormal,edgeStart,edgeEnd;int nextTriangle,twiceTriangle;U normal,edgePlane,point;}WORK;
extern float D_002DDED4,D_002A5688;
extern void func_0011EE08(qword,qword,qword,qword*,float*,float*);
extern float func_0011D018(PARAMS*,float,float,float,float*);
extern void func_001193C0(qword*,qword,float);
static inline float Product(float a,float b){float r;__asm__("mul.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword PointInput(const M4*m,qword p){__asm__("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddaz.xyz ACC,%3,%0z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(p):"j"(m->r[0].q),"j"(m->r[1].q),"j"(m->r[2].q),"j"(m->r[3].q));return p;}
static inline qword PointRow(const M4*m,qword p){qword r=m->r[0].q;__asm__("vmulax.xyz ACC,%0,%4x\n\tvmadday.xyz ACC,%1,%4y\n\tvmaddaz.xyz ACC,%2,%4z\n\tvmaddw.xyz %0,%3,$vf0w":"+j"(r):"j"(m->r[1].q),"j"(m->r[2].q),"j"(m->r[3].q),"j"(p));return r;}
static inline qword CrossRetain(qword r,qword a,qword b){__asm__("vopmula.xyz ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"+j"(r):"j"(a),"j"(b));return r;}
static inline qword Unit(qword a){qword d,one,r;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a));__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(d):"j"(d));__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(a),"j"(d));return r;}
static inline float Dot(qword a,qword b){qword d,one;float f;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a),"j"(b));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(d));return f;}
void func_001856C0(MESH*mesh,LIST*out,int count,qword*points,PARAMS*params,float radius){
 WORK w;int i;
 VTE*e=&mesh->vt[31];M4*m;
 float stopping,step;
 w.query.count=count;w.query.points=points;
 m=((M4*(*)(void*))e->fn)((char*)mesh+e->delta);
 w.matrix=*m;
 stopping=Product(params->duration,Product(params->a+params->b,0.5f));step=Product(D_002DDED4,0.5f);
 for(i=0;i<mesh->triangleCount;i=w.nextTriangle){
  int edge;I3*indices=&mesh->triangles[i];
  w.nextTriangle=i+1;
  if(mesh->neighbors[i].index[0]!=-1&&mesh->neighbors[i].index[1]!=-1&&mesh->neighbors[i].index[2]!=-1)continue;
  w.twiceTriangle=i*2;
  w.vertices[0].q=PointInput(&w.matrix,mesh->vertices[indices->index[0]]);
  w.vertices[1].q=PointInput(&w.matrix,mesh->vertices[indices->index[1]]);
  {
   qword originalThird=mesh->vertices[indices->index[2]];
   w.vertices[2].q=PointRow(&w.matrix,originalThird);
   w.triangleNormal.q=CrossRetain(originalThird,Sub(w.vertices[1].q,w.vertices[0].q),Sub(w.vertices[2].q,w.vertices[0].q));
  }
  for(edge=0;edge<3;edge++){
   qword bestPlane;float best;
   if(((int*)mesh->neighbors)[w.twiceTriangle+i+edge]!=-1)continue;
   w.edgeStart.q=((qword*)&w)[4+(edge+1)%3];w.edgeEnd.q=((qword*)&w)[4+(edge+2)%3];
   best=D_002A5688;
   w.edgePlane.q=CrossRetain(w.vertices[2].q,w.triangleNormal.q,Sub(w.edgeEnd.q,w.edgeStart.q));
   {int remaining=w.query.count;qword*cursor=w.query.points;
   for(;remaining>0;remaining--,cursor++){
    w.point.q=*cursor;
    func_0011EE08(w.point.q,w.edgeStart.q,w.edgeEnd.q,&w.closest.q,0,&w.query.distance);
    if(w.query.distance<radius+stopping){
     float distance;
     w.normal.q=Unit(w.edgePlane.q);
     distance=Dot(w.normal.q,Sub(w.point.q,w.closest.q));
     func_0011D018(params,radius,distance,step,&w.query.clamped);
     if(w.query.clamped<best){
      best=w.query.clamped;
      func_001193C0(&w.plane.q,w.normal.q,best);
      bestPlane=w.plane.q;
     }
    }
   }
   }
   if(best!=D_002A5688)out->planes[out->count++]=bestPlane;
  }
 }
}

typedef char qword_Size[(sizeof(qword)==16)?1:-1];
typedef char Pointer_Size[(sizeof(void*)==4)?1:-1];
typedef char U_Size[(sizeof(U)==16)?1:-1];
typedef char M4_Size[(sizeof(M4)==0x40)?1:-1];
typedef char VTE_Size[(sizeof(VTE)==8)?1:-1];
typedef char I3_Size[(sizeof(I3)==12)?1:-1];
typedef char PARAMS_Size[(sizeof(PARAMS)==12)?1:-1];
typedef char IO_Size[(sizeof(IO)==16)?1:-1];
typedef char WORK_Size[(sizeof(WORK)==0x110)?1:-1];
typedef char Triangle_Buffer_Size[(sizeof(U[3])==0x30)?1:-1];
typedef char VTE_delta_Offset[((unsigned)&((VTE*)0)->delta==0)?1:-1];
typedef char VTE_fn_Offset[((unsigned)&((VTE*)0)->fn==4)?1:-1];
typedef char MESH_vt_Offset[((unsigned)&((MESH*)0)->vt==12)?1:-1];
typedef char MESH_vertices_Offset[((unsigned)&((MESH*)0)->vertices==228)?1:-1];
typedef char MESH_triangleCount_Offset[((unsigned)&((MESH*)0)->triangleCount==232)?1:-1];
typedef char MESH_triangles_Offset[((unsigned)&((MESH*)0)->triangles==236)?1:-1];
typedef char MESH_neighbors_Offset[((unsigned)&((MESH*)0)->neighbors==240)?1:-1];
typedef char LIST_count_Offset[((unsigned)&((LIST*)0)->count==0)?1:-1];
typedef char LIST_planes_Offset[((unsigned)&((LIST*)0)->planes==16)?1:-1];
typedef char PARAMS_a_Offset[((unsigned)&((PARAMS*)0)->a==0)?1:-1];
typedef char PARAMS_b_Offset[((unsigned)&((PARAMS*)0)->b==4)?1:-1];
typedef char PARAMS_duration_Offset[((unsigned)&((PARAMS*)0)->duration==8)?1:-1];
typedef char IO_distance_Offset[((unsigned)&((IO*)0)->distance==0)?1:-1];
typedef char IO_clamped_Offset[((unsigned)&((IO*)0)->clamped==4)?1:-1];
typedef char IO_count_Offset[((unsigned)&((IO*)0)->count==8)?1:-1];
typedef char IO_points_Offset[((unsigned)&((IO*)0)->points==12)?1:-1];
typedef char WORK_matrix_Offset[((unsigned)&((WORK*)0)->matrix==0)?1:-1];
typedef char WORK_vertices_Offset[((unsigned)&((WORK*)0)->vertices==64)?1:-1];
typedef char WORK_closest_Offset[((unsigned)&((WORK*)0)->closest==112)?1:-1];
typedef char WORK_plane_Offset[((unsigned)&((WORK*)0)->plane==128)?1:-1];
typedef char WORK_query_Offset[((unsigned)&((WORK*)0)->query==144)?1:-1];
typedef char WORK_triangleNormal_Offset[((unsigned)&((WORK*)0)->triangleNormal==160)?1:-1];
typedef char WORK_edgeStart_Offset[((unsigned)&((WORK*)0)->edgeStart==176)?1:-1];
typedef char WORK_edgeEnd_Offset[((unsigned)&((WORK*)0)->edgeEnd==192)?1:-1];
typedef char WORK_nextTriangle_Offset[((unsigned)&((WORK*)0)->nextTriangle==208)?1:-1];
typedef char WORK_twiceTriangle_Offset[((unsigned)&((WORK*)0)->twiceTriangle==212)?1:-1];
typedef char WORK_normal_Offset[((unsigned)&((WORK*)0)->normal==224)?1:-1];
typedef char WORK_edgePlane_Offset[((unsigned)&((WORK*)0)->edgePlane==240)?1:-1];
typedef char WORK_point_Offset[((unsigned)&((WORK*)0)->point==256)?1:-1];
