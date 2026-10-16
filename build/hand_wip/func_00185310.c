typedef int qword __attribute__((mode(TI)));
typedef union U{qword q;float f[4];int i[4];}U;
typedef struct M4{U r[4];}M4;
typedef struct VTE{short delta,pad;void*fn;}VTE;
typedef struct I3{int index[3];}I3;
typedef struct MESH{char pad0[0xC];VTE*vt;char pad10[0xD4];qword*vertices;int count;I3*triangles;}MESH;
typedef struct TRIREF{int index;float u,v;}TRIREF;
typedef struct WORK{M4 matrix;TRIREF candidate;TRIREF best __attribute__((aligned(16)));U closest,scalar;float parameter;U bestNormal,input,normal;}WORK;
extern float D_002A5684;
extern void func_0011EE08(qword,qword,qword,qword*,float*,float*);
static inline qword ReadQ(qword*p){qword r;__asm__("lqc2 %0,%1":"=j"(r):"m"(*p));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Point(const M4*m,qword p){qword r;__asm__("vmulax.xyz ACC,%1,%5x\n\tvmadday.xyz ACC,%2,%5y\n\tvmaddaz.xyz ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(r):"j"(m->r[0].q),"j"(m->r[1].q),"j"(m->r[2].q),"j"(m->r[3].q),"j"(p));return r;}
static inline qword Copy(qword a){qword r;__asm__("vmove.xyzw %0,%1":"=j"(r):"j"(a));return r;}
static inline qword CrossRetain(qword r,qword a,qword b){__asm__("vopmula.xyz ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"+j"(r):"j"(a),"j"(b));return r;}
static inline float Dot(qword a,qword b){qword r,one;float f;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a),"j"(b));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(r));return f;}
static inline qword Scalar(float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline void StoreQ(qword*p,qword a){__asm__("sqc2 %1,%0":"=m"(*p):"j"(a));}
static inline qword Weighted(qword a,qword b,qword c,qword ka,qword kb,qword kc){qword r;__asm__("vmulax.xyzw ACC,%1,%4x\n\tvmaddax.xyzw ACC,%2,%5x\n\tvmaddx.xyzw %0,%3,%6x":"=j"(r):"j"(a),"j"(b),"j"(c),"j"(ka),"j"(kb),"j"(kc));return r;}
static inline qword Unit(qword input){register qword a __asm__("vf3")=input,d __asm__("vf1"),one __asm__("vf2"),r __asm__("vf1");__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a));__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(d):"j"(d));__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(a),"j"(d));return r;}
static inline float SquaredDistance(qword input){
 register qword value __asm__("vf1")=input,one __asm__("vf2");register int bits __asm__("$2");float r;
 __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(value),"=&j"(one));
 __asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(value));__asm__("mtc1 %1,%0":"=f"(r):"r"(bits));return r;
}
void func_00185310(MESH*mesh,qword point,void*inputReference,TRIREF*outReference,qword*outPoint,qword*outNormal){
 WORK w;int i=0;qword bestPoint;register float bestDistance __asm__("$f22");
 VTE*entry=&mesh->vt[31];M4*matrix;
 w.input.q=point;
 matrix=((M4*(*)(void*))entry->fn)((char*)mesh+entry->delta);
 w.matrix=*matrix;
 bestDistance=D_002A5684;
 for(;i<mesh->count;i++){
  I3*indices=&mesh->triangles[i];
  qword rawB=mesh->vertices[indices->index[1]];
  qword a=Point(&w.matrix,mesh->vertices[indices->index[0]]),b=Point(&w.matrix,rawB),c=Point(&w.matrix,mesh->vertices[indices->index[2]]);
  qword ac=Copy(a),cc=Copy(c),bc=Copy(b);
  qword edgeA=Sub(ac,cc),edgeB=Sub(bc,cc),delta,firstCross,secondCross;
  float denominator,u,v;
  StoreQ(&w.normal.q,CrossRetain(rawB,edgeA,edgeB));
  delta=Sub(w.input.q,cc);
  firstCross=CrossRetain(edgeB,ReadQ(&w.normal.q),edgeB);
  secondCross=CrossRetain(ReadQ(&w.normal.q),delta,edgeA);
  denominator=1.0f/Dot(edgeA,firstCross);
  u=denominator*Dot(delta,firstCross);
  v=denominator*Dot(ReadQ(&w.normal.q),secondCross);
  if(u<0.0f){
   func_0011EE08(w.input.q,bc,cc,&w.closest.q,&w.parameter,0);
   w.candidate.u=0.0f;w.candidate.v=1.0f-w.parameter;
  }else if(v<0.0f){
   func_0011EE08(w.input.q,ac,cc,&w.closest.q,&w.parameter,0);
   w.candidate.u=1.0f-w.parameter;w.candidate.v=0.0f;
  }else if(u+v>1.0f){
   func_0011EE08(w.input.q,ac,bc,&w.closest.q,&w.parameter,0);
   w.candidate.u=1.0f-w.parameter;w.candidate.v=w.parameter;
  }else{
   qword ka,kb,kc;
   w.candidate.u=u;w.candidate.v=v;
   ka=Scalar(u);StoreQ(&w.scalar.q,ka);
   kb=Scalar(v);StoreQ(&w.scalar.q,kb);
   kc=Scalar((1.0f-u)-v);StoreQ(&w.scalar.q,kc);
   w.closest.q=Weighted(a,b,c,ka,kb,kc);
  }
  {qword closest=w.closest.q; qword delta=Sub(closest,w.input.q);float distance=SquaredDistance(delta);
   if(distance<bestDistance){
    w.candidate.index=i;bestDistance=distance;w.best=w.candidate;bestPoint=closest;w.bestNormal=w.normal;
   }
  }
 }
 if(outReference)*outReference=w.best;
 if(outPoint)*outPoint=bestPoint;
 if(outNormal)*outNormal=Unit(w.bestNormal.q);
}

typedef char qword_Size[(sizeof(qword)==16)?1:-1];
typedef char Pointer_Size[(sizeof(void*)==4)?1:-1];
typedef char U_Size[(sizeof(U)==16)?1:-1];
typedef char M4_Size[(sizeof(M4)==0x40)?1:-1];
typedef char VTE_Size[(sizeof(VTE)==8)?1:-1];
typedef char I3_Size[(sizeof(I3)==12)?1:-1];
typedef char TRIREF_Size[(sizeof(TRIREF)==12)?1:-1];
typedef char WORK_Size[(sizeof(WORK)==0xC0)?1:-1];
typedef char VTE_delta_Offset[((unsigned)&((VTE*)0)->delta==0)?1:-1];
typedef char VTE_fn_Offset[((unsigned)&((VTE*)0)->fn==4)?1:-1];
typedef char MESH_vt_Offset[((unsigned)&((MESH*)0)->vt==12)?1:-1];
typedef char MESH_vertices_Offset[((unsigned)&((MESH*)0)->vertices==228)?1:-1];
typedef char MESH_count_Offset[((unsigned)&((MESH*)0)->count==232)?1:-1];
typedef char MESH_triangles_Offset[((unsigned)&((MESH*)0)->triangles==236)?1:-1];
typedef char TRIREF_index_Offset[((unsigned)&((TRIREF*)0)->index==0)?1:-1];
typedef char TRIREF_u_Offset[((unsigned)&((TRIREF*)0)->u==4)?1:-1];
typedef char TRIREF_v_Offset[((unsigned)&((TRIREF*)0)->v==8)?1:-1];
typedef char WORK_matrix_Offset[((unsigned)&((WORK*)0)->matrix==0)?1:-1];
typedef char WORK_candidate_Offset[((unsigned)&((WORK*)0)->candidate==64)?1:-1];
typedef char WORK_best_Offset[((unsigned)&((WORK*)0)->best==80)?1:-1];
typedef char WORK_closest_Offset[((unsigned)&((WORK*)0)->closest==96)?1:-1];
typedef char WORK_scalar_Offset[((unsigned)&((WORK*)0)->scalar==112)?1:-1];
typedef char WORK_parameter_Offset[((unsigned)&((WORK*)0)->parameter==128)?1:-1];
typedef char WORK_bestNormal_Offset[((unsigned)&((WORK*)0)->bestNormal==144)?1:-1];
typedef char WORK_input_Offset[((unsigned)&((WORK*)0)->input==160)?1:-1];
typedef char WORK_normal_Offset[((unsigned)&((WORK*)0)->normal==176)?1:-1];
