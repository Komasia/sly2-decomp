/* laneH2v1 (Claude agent): from the old clean .cpp (155): spill-slot WORK members as plain locals, M3 product written directly into w.matrix, loop1 indexed, loop-2 counter set early. No pins. aligned 128. */
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];int i[4];};
struct M3{U r[3];M3(){}M3(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];}M3&operator=(const M3&m){r[0]=m.r[0];r[1]=m.r[1];r[2]=m.r[2];return*this;}};
inline void*operator new(unsigned,void*p){return p;}
struct M4{U r[4];};
struct VTE{short delta,pad;void*fn;};
struct PARAMS{float a,b,duration;};
struct CONTROL{char pad0[0x10];float y,z;int pad18;float speed;};
struct REQUEST{char pad0[0x78];float multiplier;};
struct AXIS{float weight;int active;char pad8[8];U direction;};
struct TRIREF{int index;float u,v;};
struct LIST{int count;qword planes[8];};
struct P{char pad0[0xC];VTE*vt;char pad10[0x140];CONTROL*control;char pad154[0x3C];U acceleration;char pad1A0[0x10];M3 basis;char pad1E0[0x1C30];AXIS axes[8];REQUEST*request;int pad1F14;void*mesh;TRIREF triangle;U points[3];};
struct CLOCK{float time,dt;};
struct ROWS{U r[3];};
union PHASE{ROWS facing;struct{U angular,linear,movement,scalar;}u;};
struct WORK{U closest,normal;M4 frame;U closestSamples[3];PHASE phase;LIST planes;U samples[3];M3 matrix,inverse,product;};
extern "C"{
extern U D_002A2DC0;extern M3 D_002DDFA0;extern CLOCK D_002DDED0;extern PARAMS D_002BE920,D_002BE930,D_002BE940;
qword func_001A62E8(P*);M4*func_001A6318(P*);
void func_00185310(void*,qword,TRIREF*,TRIREF*,qword*,qword*);
M3 func_0011B830(qword,qword);M3 func_0011B340(M3*);qword*func_00256D18(qword*,qword);
void func_0011C950(M4*,M3*,PARAMS*,M3*,qword*,float);
qword func_0011F088(qword,qword,PARAMS*,qword*,float);
void func_001856B8(void*,LIST*);void func_001856C0(void*,LIST*,int,qword*,PARAMS*,float);
qword func_00185A80(void*,LIST*,qword);
void func_0018C250(P*,int,int);void func_001A0450(P*,AXIS*,REQUEST*);
}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scalar(float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline qword ScalarBits(int f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline void StoreQ(qword*p,qword v){__asm__("sqc2 %1,%0":"=m"(*p):"j"(v));}
static inline qword Scale(qword a,qword k){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(k));return r;}
static inline qword AddScaled(qword a,qword b,qword k){qword r;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(k));return r;}
static inline qword Squared(qword a){qword r,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a));return r;}
static inline qword Root(qword a){qword r;__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(r):"j"(a));return r;}
static inline float FloatX(qword a){float r;__asm__("qmfc2.ni %0,%1":"=r"(r):"j"(a));return r;}
static inline qword Divide(qword a,qword length){qword r;__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(a),"j"(length));return r;}
static inline qword Unit(qword a){return Divide(a,Root(Squared(a)));}
static inline qword Cross(qword a,qword b){__asm__("vopmula.xyz ACC,%0,%1\n\tvopmsub.xyz %0,%1,%0":"+j"(a):"j"(b));return a;}
static inline qword Vector(const M3&m,qword p){__asm__("vmulax.xyz ACC,%1,%0x\n\tvmadday.xyz ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(p):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q));return p;}
static inline qword VectorFresh(const M3&m,qword p){qword r;__asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"=j"(r):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(p));return r;}
static inline qword Point(const M4&m,qword p){qword r;__asm__("vmulax.xyz ACC,%1,%5x\n\tvmadday.xyz ACC,%2,%5y\n\tvmaddaz.xyz ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(r):"j"(m.r[0].q),"j"(m.r[1].q),"j"(m.r[2].q),"j"(m.r[3].q),"j"(p));return r;}
static inline void Build(M4&d,const M3&m,qword p){func_00256D18(&d.r[3].q,p);d.r[0]=m.r[0];d.r[1]=m.r[1];d.r[2]=m.r[2];d.r[0].i[3]=d.r[1].i[3]=d.r[2].i[3]=0;d.r[3].f[3]=1.0f;}
static inline M3 Multiply(const M3&a,const M3&b) return r{
 r.r[2].q=Vector(a,b.r[2].q);r.r[0].q=Vector(a,b.r[0].q);r.r[1].q=Vector(a,b.r[1].q);
}
static inline qword Weighted(qword a,qword b,qword ka,qword kb){qword r;__asm__("vmulax.xyzw ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x":"=j"(r):"j"(a),"j"(b),"j"(ka),"j"(kb));return r;}
static inline void Set(P*p,int slot,qword q){VTE*e=&p->vt[slot];((void(*)(void*,qword))e->fn)((char*)p+e->delta,q);}
extern "C" void func_00185E40(P*p){
 WORK w;int remaining;qword position,target,negative,*samplePointer,projected;
 position=func_001A62E8(p);
 func_00185310(p->mesh,position,&p->triangle,&p->triangle,&w.closest.q,&w.normal.q);
 qword difference=Sub(w.closest.q,position),length=Root(Squared(difference)),direction;
 w.phase.u.angular.q=Scalar(-1.0f);
 qword fallback=Scale(w.normal.q,w.phase.u.angular.q);
 if(FloatX(length)<0.0001f)direction=fallback;else direction=Divide(difference,length);
 w.phase.u.angular.q=Scalar(-p->points[0].f[0]);
 target=AddScaled(w.closest.q,direction,w.phase.u.angular.q);
 new((M3*)&w.phase.u.linear) M3(func_0011B830(direction,D_002A2DC0.q));
 Build(w.frame,*(M3*)&w.phase.u.linear,target);
 samplePointer=&w.samples[0].q;
 {int i;for(i=0;i<3;i++)func_00185310(p->mesh,Point(w.frame,p->points[i].q),&p->triangle,0,&w.closestSamples[i].q,0);}
 qword surface=Unit(Cross(Sub(w.closestSamples[2].q,w.closestSamples[0].q),Sub(w.closestSamples[1].q,w.closestSamples[0].q)));
 new((M3*)&w.phase.facing) M3(func_0011B830(surface,D_002A2DC0.q));remaining=2;
 p->basis=*(M3*)&w.phase.facing;
 func_0011C950(func_001A6318(p),&p->basis,&D_002BE920,0,&w.phase.u.angular.q,D_002DDED0.dt*0.5f);
 Set(p,36,w.phase.u.angular.q);
 (void)func_0011F088(position,target,&D_002BE930,&w.phase.u.linear.q,D_002DDED0.dt*0.5f);
 {U*points=p->points,*out=w.samples;
 do{out->q=Add(target,Vector(p->basis,points->q));out++;points++;}while(--remaining>=0);}
 func_001856B8(p->mesh,&w.planes);
 func_001856C0(p->mesh,&w.planes,3,samplePointer,&D_002BE940,10.0f);
 if(p->control->speed>0.0f){
  w.phase.u.movement.f[0]=0.0f;w.phase.u.movement.f[1]=-p->control->y;w.phase.u.movement.f[2]=p->control->z;
  new(&w.inverse) M3(func_0011B340(&p->basis));
  w.matrix.r[2].q=Vector(w.inverse,D_002DDFA0.r[2].q);w.matrix.r[0].q=Vector(w.inverse,D_002DDFA0.r[0].q);w.matrix.r[1].q=Vector(w.inverse,D_002DDFA0.r[1].q);w.product=w.matrix;
  w.phase.u.movement.q=Vector(w.matrix,w.phase.u.movement.q);w.phase.u.movement.f[0]=0.0f;
  qword len=Root(Squared(w.phase.u.movement.q)),unit;
  w.phase.u.scalar.q=ScalarBits(*(int*)&p->control->speed);
  if(FloatX(len)<0.0001f)unit=D_002A2DC0.q;else unit=Divide(w.phase.u.movement.q,len);
  w.phase.u.movement.q=Scale(unit,w.phase.u.scalar.q);
  qword y=ScalarBits(w.phase.u.movement.i[1]),z=ScalarBits(w.phase.u.movement.i[2]);
  p->acceleration.q=Weighted(p->axes[1].direction.q,p->axes[2].direction.q,y,z);
  StoreQ(&w.phase.u.scalar.q,y);StoreQ(&w.phase.u.scalar.q,z);
  w.phase.u.scalar.q=ScalarBits(*(int*)&p->request->multiplier);
  p->acceleration.q=Scale(p->acceleration.q,w.phase.u.scalar.q);
 }else{p->acceleration.f[0]=p->acceleration.f[1]=p->acceleration.f[2]=0.0f;}
 if(w.planes.count>0){
  negative=Scalar(-1.0f);
  w.phase.u.movement.q=negative;
  projected=func_00185A80(p->mesh,&w.planes,VectorFresh(p->basis,Scale(p->acceleration.q,negative)));
  new(&w.matrix) M3(func_0011B340(&p->basis));
  p->acceleration.q=Vector(w.matrix,Scale(projected,negative));
  w.phase.u.movement.q=negative;
 }
 int active=0;
 if(FloatX(Squared(p->acceleration.q))>1.0f)active=1;
 else if(p->control->speed!=0.0f)active=1;
 if(active){
  func_0018C250(p,21,11);func_001A0450(p,p->axes,p->request);
  w.phase.u.movement.q=Scalar(-1.0f);
  Set(p,35,Add(w.phase.u.linear.q,Vector(p->basis,Scale(p->acceleration.q,w.phase.u.movement.q))));
 }else{func_0018C250(p,21,10);Set(p,35,w.phase.u.linear.q);}
}


typedef char qword_Size[(sizeof(qword)==16)?1:-1];
typedef char Pointer_Size[(sizeof(void*)==4)?1:-1];
typedef char U_Size[(sizeof(U)==16)?1:-1];
typedef char M3_Size[(sizeof(M3)==0x30)?1:-1];
typedef char M4_Size[(sizeof(M4)==0x40)?1:-1];
typedef char VTE_Size[(sizeof(VTE)==8)?1:-1];
typedef char PARAMS_Size[(sizeof(PARAMS)==12)?1:-1];
typedef char CONTROL_Size[(sizeof(CONTROL)==0x20)?1:-1];
typedef char REQUEST_Size[(sizeof(REQUEST)==0x7C)?1:-1];
typedef char AXIS_Size[(sizeof(AXIS)==0x20)?1:-1];
typedef char TRIREF_Size[(sizeof(TRIREF)==12)?1:-1];
typedef char LIST_Size[(sizeof(LIST)==0x90)?1:-1];
typedef char ROWS_Size[(sizeof(ROWS)==0x30)?1:-1];
typedef char PHASE_Size[(sizeof(PHASE)==0x40)?1:-1];
typedef char CLOCK_Size[(sizeof(CLOCK)==8)?1:-1];
typedef char Sample_Buffer_Size[(sizeof(U[3])==0x30)?1:-1];
typedef char Plane_Buffer_Size[(sizeof(qword[8])==0x80)?1:-1];
typedef char VTE_delta_Offset[((unsigned)&((VTE*)0)->delta==0)?1:-1];
typedef char VTE_fn_Offset[((unsigned)&((VTE*)0)->fn==4)?1:-1];
typedef char PARAMS_a_Offset[((unsigned)&((PARAMS*)0)->a==0)?1:-1];
typedef char PARAMS_b_Offset[((unsigned)&((PARAMS*)0)->b==4)?1:-1];
typedef char PARAMS_duration_Offset[((unsigned)&((PARAMS*)0)->duration==8)?1:-1];
typedef char CONTROL_y_Offset[((unsigned)&((CONTROL*)0)->y==16)?1:-1];
typedef char CONTROL_z_Offset[((unsigned)&((CONTROL*)0)->z==20)?1:-1];
typedef char CONTROL_speed_Offset[((unsigned)&((CONTROL*)0)->speed==28)?1:-1];
typedef char REQUEST_multiplier_Offset[((unsigned)&((REQUEST*)0)->multiplier==120)?1:-1];
typedef char AXIS_weight_Offset[((unsigned)&((AXIS*)0)->weight==0)?1:-1];
typedef char AXIS_active_Offset[((unsigned)&((AXIS*)0)->active==4)?1:-1];
typedef char AXIS_direction_Offset[((unsigned)&((AXIS*)0)->direction==16)?1:-1];
typedef char TRIREF_index_Offset[((unsigned)&((TRIREF*)0)->index==0)?1:-1];
typedef char TRIREF_u_Offset[((unsigned)&((TRIREF*)0)->u==4)?1:-1];
typedef char TRIREF_v_Offset[((unsigned)&((TRIREF*)0)->v==8)?1:-1];
typedef char LIST_count_Offset[((unsigned)&((LIST*)0)->count==0)?1:-1];
typedef char LIST_planes_Offset[((unsigned)&((LIST*)0)->planes==16)?1:-1];
typedef char CLOCK_time_Offset[((unsigned)&((CLOCK*)0)->time==0)?1:-1];
typedef char CLOCK_dt_Offset[((unsigned)&((CLOCK*)0)->dt==4)?1:-1];
typedef char P_vt_Offset[((unsigned)&((P*)0)->vt==12)?1:-1];
typedef char P_control_Offset[((unsigned)&((P*)0)->control==336)?1:-1];
typedef char P_acceleration_Offset[((unsigned)&((P*)0)->acceleration==400)?1:-1];
typedef char P_basis_Offset[((unsigned)&((P*)0)->basis==432)?1:-1];
typedef char P_axes_Offset[((unsigned)&((P*)0)->axes==7696)?1:-1];
typedef char P_request_Offset[((unsigned)&((P*)0)->request==7952)?1:-1];
typedef char P_mesh_Offset[((unsigned)&((P*)0)->mesh==7960)?1:-1];
typedef char P_triangle_Offset[((unsigned)&((P*)0)->triangle==7964)?1:-1];
typedef char P_points_Offset[((unsigned)&((P*)0)->points==7984)?1:-1];
typedef char PHASE_facing_Offset[((unsigned)&((PHASE*)0)->facing==0)?1:-1];
typedef char PHASE_u_angular_Offset[((unsigned)&((PHASE*)0)->u.angular==0)?1:-1];
typedef char PHASE_u_linear_Offset[((unsigned)&((PHASE*)0)->u.linear==16)?1:-1];
typedef char PHASE_u_movement_Offset[((unsigned)&((PHASE*)0)->u.movement==32)?1:-1];
typedef char PHASE_u_scalar_Offset[((unsigned)&((PHASE*)0)->u.scalar==48)?1:-1];
typedef char WORK_closest_Offset[((unsigned)&((WORK*)0)->closest==0)?1:-1];
typedef char WORK_normal_Offset[((unsigned)&((WORK*)0)->normal==16)?1:-1];
typedef char WORK_frame_Offset[((unsigned)&((WORK*)0)->frame==32)?1:-1];
typedef char WORK_closestSamples_Offset[((unsigned)&((WORK*)0)->closestSamples==96)?1:-1];
typedef char WORK_phase_Offset[((unsigned)&((WORK*)0)->phase==144)?1:-1];
typedef char WORK_planes_Offset[((unsigned)&((WORK*)0)->planes==208)?1:-1];
typedef char WORK_samples_Offset[((unsigned)&((WORK*)0)->samples==352)?1:-1];
typedef char WORK_matrix_Offset[((unsigned)&((WORK*)0)->matrix==400)?1:-1];
typedef char WORK_inverse_Offset[((unsigned)&((WORK*)0)->inverse==448)?1:-1];
typedef char WORK_product_Offset[((unsigned)&((WORK*)0)->product==496)?1:-1];
