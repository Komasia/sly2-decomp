typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];int i[4];};struct M3{U row[3];};
struct VTE{short delta,pad;void*fn;};struct BODY{char pad0[0xB0];U angularVelocity;char padC0[0x30];U angularAcceleration;};struct MOTION{char pad0[0x80];U acceleration;};struct ACTOR{char pad0[12];VTE*vt;char pad10[0x4C];BODY*body;char pad60[0x88];MOTION*motion;char padEC[0x190-0xEC];U velocity;};
struct CONTEXT{ACTOR*actor;int state;char pad8[0x10];float stamp;int mode;char pad20[0x14];float gain;char pad38[0x68];U desired;char padB0[0x110];float targetX,targetZ;};
struct CLOCK{float time,dt;};struct SMP{float maximum,minimum,duration;};struct RANGE{float low,high;};struct POLY{float c0,c1,c2;};struct PARAMS{float values[3];};
union BASE_PHASE{M3 returned;struct{U local,acceleration,corrected,scalar;}vectors;};
union WORK{struct{U local,scalar;M3 basis,rotation,returned;U original;}turn;struct{U direction;M3 basis;BASE_PHASE phase;}move;U scalar;};
extern "C"{extern CLOCK D_002DDED0;extern U D_002A2DA0,D_002A2DC0,D_002A2DD0;extern SMP D_002BF7A8,D_002BF7B8,D_002BF7C8;extern float D_002BF7D4,D_002BF7F0,D_002BF7F4,D_002BF7F8,D_002BF810,D_002BF814;extern PARAMS D_002BF7E0;extern POLY D_002BF800;extern RANGE D_002BBB60;
qword func_001A6FC0(ACTOR*,ACTOR*,qword);M3*func_0011B570(M3*,qword);M3*func_0011B7E0(M3*,qword);M3*func_001A6318(ACTOR*);float func_0011D018(float,float,float,SMP*,float*);qword func_0011E9F8(qword,float);void func_001FAC30(ACTOR*,qword);void func_001F5E10(ACTOR*,qword,ACTOR*,qword,PARAMS*);void func_00196AA8(CONTEXT*,U*);}
static inline qword Velocity(ACTOR*p){VTE&v=p->vt[33];return ((qword(*)(void*))v.fn)((char*)p+v.delta);}
static inline qword Scalar(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword AddScaled(qword a,qword b,qword k){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(k));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scale(qword a,qword k){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(k));return r;}
static inline qword Divide(qword a,qword k){qword r;__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(r):"j"(k),"j"(a));return r;}
static inline qword Rotate(qword r0,qword r1,qword r2,qword vector,qword seed){__asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"+j"(seed):"j"(r0),"j"(r1),"j"(r2),"j"(vector));return seed;}
static inline qword Rotate(M3*m,qword vector,qword seed){return Rotate(m->row[0].q,m->row[1].q,m->row[2].q,vector,seed);}
static inline void Multiply(M3*result,M3*a,M3*b){qword r0=a->row[0].q,r1=a->row[1].q,r2=a->row[2].q;result->row[0].q=Rotate(r0,r1,r2,b->row[0].q,b->row[0].q);result->row[1].q=Rotate(r0,r1,r2,b->row[1].q,b->row[1].q);result->row[2].q=Rotate(r0,r1,r2,b->row[2].q,r0);}
static inline qword Inverse(M3*m,qword vector){qword a,b,c,one;__asm__("vmul.xyzw %0,%4,%7\n\tvmaxw.xyzw %3,$vf0,$vf0w\n\tvmul.xyzw %1,%5,%7\n\tvmul.xyzw %2,%6,%7":"=&j"(a),"=&j"(b),"=&j"(c),"=&j"(one):"j"(m->row[0].q),"j"(m->row[1].q),"j"(m->row[2].q),"j"(vector));__asm__("vadday.x $ACC,%1,%1y\n\tvmaddz.x %0,%4,%1z\n\tvaddax.y $ACC,%2,%2x\n\tvmaddz.y %0,%4,%2z\n\tvaddax.z $ACC,%3,%3x\n\tvmaddy.z %0,%4,%3y":"+j"(vector):"j"(a),"j"(b),"j"(c),"j"(one));return vector;}
static inline float X(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline qword ReadVector(U*p){qword q;__asm__("lq %0,%1":"=r"(q):"m"(*p));return q;}
static inline qword Normalize(U*value){qword v=ReadVector(value),d,one;float length;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(d),"=&j"(one):"j"(v));__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(one):"j"(d));__asm__("qmfc2.ni %0,%1":"=r"(length):"j"(one));if(length<0.0001f)value->q=D_002A2DA0.q;else value->q=Divide(v,one);return one;}
static inline float Z(qword q){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(q));return f;}
static inline float Y(qword q){float f;__asm__("prot3w %0,%1":"=r"(f):"r"(q));return f;}
static inline qword XY(float x,float y,float z){int a,b,c;qword q;__asm__("mfc1 %0,%1":"=r"(a):"f"(x));__asm__("mfc1 %0,%1":"=r"(b):"f"(y));__asm__("pextlw %0,%2,%1":"=r"(q):"r"(a),"r"(b));__asm__("mfc1 %0,%1":"=r"(c):"f"(z));__asm__("pcpyld %0,%1,%0":"+r"(q):"r"(c));return q;}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char M3_Size[sizeof(M3)==48?1:-1];
typedef char VTE_Size[sizeof(VTE)==8?1:-1];
typedef char BODY_Size[sizeof(BODY)==256?1:-1];
typedef char MOTION_Size[sizeof(MOTION)==144?1:-1];
typedef char ACTOR_Size[sizeof(ACTOR)==416?1:-1];
typedef char CONTEXT_Size[sizeof(CONTEXT)==464?1:-1];
typedef char CLOCK_Size[sizeof(CLOCK)==8?1:-1];
typedef char SMP_Size[sizeof(SMP)==12?1:-1];
typedef char RANGE_Size[sizeof(RANGE)==8?1:-1];
typedef char POLY_Size[sizeof(POLY)==12?1:-1];
typedef char PARAMS_Size[sizeof(PARAMS)==12?1:-1];
typedef char BASE_PHASE_Size[sizeof(BASE_PHASE)==64?1:-1];
typedef char WORK_Size[sizeof(WORK)==192?1:-1];
typedef char BODY_angularVelocity_Offset[FIELD_OFFSET(BODY,angularVelocity)==176?1:-1];
typedef char BODY_angularAcceleration_Offset[FIELD_OFFSET(BODY,angularAcceleration)==240?1:-1];
typedef char MOTION_acceleration_Offset[FIELD_OFFSET(MOTION,acceleration)==128?1:-1];
typedef char ACTOR_vt_Offset[FIELD_OFFSET(ACTOR,vt)==12?1:-1];
typedef char ACTOR_body_Offset[FIELD_OFFSET(ACTOR,body)==92?1:-1];
typedef char ACTOR_motion_Offset[FIELD_OFFSET(ACTOR,motion)==232?1:-1];
typedef char ACTOR_velocity_Offset[FIELD_OFFSET(ACTOR,velocity)==400?1:-1];
typedef char CONTEXT_actor_Offset[FIELD_OFFSET(CONTEXT,actor)==0?1:-1];
typedef char CONTEXT_state_Offset[FIELD_OFFSET(CONTEXT,state)==4?1:-1];
typedef char CONTEXT_stamp_Offset[FIELD_OFFSET(CONTEXT,stamp)==24?1:-1];
typedef char CONTEXT_mode_Offset[FIELD_OFFSET(CONTEXT,mode)==28?1:-1];
typedef char CONTEXT_gain_Offset[FIELD_OFFSET(CONTEXT,gain)==52?1:-1];
typedef char CONTEXT_desired_Offset[FIELD_OFFSET(CONTEXT,desired)==160?1:-1];
typedef char CONTEXT_targetX_Offset[FIELD_OFFSET(CONTEXT,targetX)==448?1:-1];
typedef char CONTEXT_targetZ_Offset[FIELD_OFFSET(CONTEXT,targetZ)==452?1:-1];
typedef char CLOCK_time_Offset[FIELD_OFFSET(CLOCK,time)==0?1:-1];
typedef char CLOCK_dt_Offset[FIELD_OFFSET(CLOCK,dt)==4?1:-1];
typedef char SMP_maximum_Offset[FIELD_OFFSET(SMP,maximum)==0?1:-1];
typedef char SMP_minimum_Offset[FIELD_OFFSET(SMP,minimum)==4?1:-1];
typedef char SMP_duration_Offset[FIELD_OFFSET(SMP,duration)==8?1:-1];
typedef char RANGE_low_Offset[FIELD_OFFSET(RANGE,low)==0?1:-1];
typedef char RANGE_high_Offset[FIELD_OFFSET(RANGE,high)==4?1:-1];
typedef char POLY_c0_Offset[FIELD_OFFSET(POLY,c0)==0?1:-1];
typedef char POLY_c1_Offset[FIELD_OFFSET(POLY,c1)==4?1:-1];
typedef char POLY_c2_Offset[FIELD_OFFSET(POLY,c2)==8?1:-1];
typedef char PARAMS_values_Offset[FIELD_OFFSET(PARAMS,values)==0?1:-1];
typedef char BASE_PHASE_returned_Offset[FIELD_OFFSET(BASE_PHASE,returned)==0?1:-1];
typedef char BASE_PHASE_vectors_local_Offset[FIELD_OFFSET(BASE_PHASE,vectors.local)==0?1:-1];
typedef char BASE_PHASE_vectors_acceleration_Offset[FIELD_OFFSET(BASE_PHASE,vectors.acceleration)==16?1:-1];
typedef char BASE_PHASE_vectors_corrected_Offset[FIELD_OFFSET(BASE_PHASE,vectors.corrected)==32?1:-1];
typedef char BASE_PHASE_vectors_scalar_Offset[FIELD_OFFSET(BASE_PHASE,vectors.scalar)==48?1:-1];
typedef char WORK_turn_local_Offset[FIELD_OFFSET(WORK,turn.local)==0?1:-1];
typedef char WORK_turn_scalar_Offset[FIELD_OFFSET(WORK,turn.scalar)==16?1:-1];
typedef char WORK_turn_basis_Offset[FIELD_OFFSET(WORK,turn.basis)==32?1:-1];
typedef char WORK_turn_rotation_Offset[FIELD_OFFSET(WORK,turn.rotation)==80?1:-1];
typedef char WORK_turn_returned_Offset[FIELD_OFFSET(WORK,turn.returned)==128?1:-1];
typedef char WORK_turn_original_Offset[FIELD_OFFSET(WORK,turn.original)==176?1:-1];
typedef char WORK_move_direction_Offset[FIELD_OFFSET(WORK,move.direction)==0?1:-1];
typedef char WORK_move_basis_Offset[FIELD_OFFSET(WORK,move.basis)==16?1:-1];
typedef char WORK_move_phase_Offset[FIELD_OFFSET(WORK,move.phase)==64?1:-1];
typedef char WORK_scalar_Offset[FIELD_OFFSET(WORK,scalar)==0?1:-1];
extern "C" void func_00196DF8(CONTEXT*p){WORK w;
 switch(p->mode){
 case 20:{
  w.turn.original.q=Velocity(p->actor);w.turn.local.q=func_001A6FC0(0,p->actor,w.turn.original.q);
  BODY*body=p->actor->body;w.turn.scalar.q=Scalar(D_002DDED0.dt);qword full=w.turn.scalar.q;w.turn.scalar.q=Scalar(D_002DDED0.dt*0.5f);
  qword rotation=Scale(Add(body->angularVelocity.q,AddScaled(body->angularVelocity.q,body->angularAcceleration.q,full)),w.turn.scalar.q);
  (void)func_0011B570(&w.turn.rotation,rotation);Multiply(&w.turn.returned,&w.turn.rotation,func_001A6318(p->actor));w.turn.basis=w.turn.returned;
  w.turn.local.f[0]=func_0011D018(w.turn.local.f[0],p->targetX,D_002DDED0.dt,&D_002BF7A8,0);
  w.turn.local.f[1]=func_0011D018(w.turn.local.f[1],0.0f,D_002DDED0.dt,&D_002BF7B8,0);
  w.turn.local.f[2]=func_0011D018(w.turn.local.f[2],p->targetZ,D_002DDED0.dt,&D_002BF7C8,0);
  qword desired=Rotate(&w.turn.basis,w.turn.local.q,w.turn.local.q);w.turn.scalar.q=Scalar(D_002DDED0.dt);
  qword acceleration=func_0011E9F8(Divide(Sub(desired,w.turn.original.q),w.turn.scalar.q),D_002BF7D4);
  if(Z(acceleration)<0.0f){w.turn.scalar.q=XY(X(acceleration),Y(acceleration),0.0f);acceleration=w.turn.scalar.q;}
  func_001FAC30(p->actor,acceleration);break;
 }
 case 22:{
  w.scalar.q=Scalar(-1.0f);qword reverse=Scale(p->actor->velocity.q,w.scalar.q);w.scalar.q=Scalar(-1.0f/D_002BF7E0.values[1]);
  qword force=AddScaled(reverse,p->actor->motion->acceleration.q,w.scalar.q);func_001F5E10(p->actor,D_002A2DD0.q,0,force,&D_002BF7E0);break;
 }
 case 6:case 8:case 9:case 10:case 11:case 12:case 13:case 14:case 15:case 16:case 17:case 18:case 19:case 21:break;
 default:{
  w.move.direction.q=Velocity(p->actor);w.move.direction.i[2]=0;float speed=X(Normalize(&w.move.direction));
  (void)func_0011B7E0(&w.move.phase.returned,w.move.direction.q);w.move.basis=w.move.phase.returned;
  w.move.phase.vectors.local.q=Inverse(&w.move.basis,p->desired.q);
  float side,longitudinal;float inverseTime=1.0f/D_002DDED0.dt;
  if(p->mode==0||p->mode==2){side=inverseTime;longitudinal=inverseTime;}
  else{longitudinal=w.move.phase.vectors.local.f[0]<speed?D_002BF7F4:D_002BF7F0;side=D_002BF7F8;}
  w.move.phase.vectors.acceleration.f[0]=longitudinal*(w.move.phase.vectors.local.f[0]-speed);
  w.move.phase.vectors.acceleration.f[1]=side*w.move.phase.vectors.local.f[1];w.move.phase.vectors.acceleration.i[2]=0;
  float gain;
  if(p->state==12){float elapsed=D_002DDED0.time-p->stamp;gain=D_002BF800.c0+elapsed*(D_002BF800.c1+elapsed*D_002BF800.c2);if(gain<D_002BBB60.low)gain=D_002BBB60.low;else if(D_002BBB60.high<gain)gain=D_002BBB60.high;}else gain=p->gain;
  w.move.phase.vectors.scalar.q=Scalar(gain);w.move.phase.vectors.acceleration.q=Scale(w.move.phase.vectors.acceleration.q,w.move.phase.vectors.scalar.q);
  w.move.phase.vectors.corrected.q=Rotate(&w.move.basis,w.move.phase.vectors.acceleration.q,w.move.basis.row[0].q);
  func_00196AA8(p,&w.move.phase.vectors.corrected);
  if(p->mode!=5){w.move.direction.q=Velocity(p->actor);if(w.move.direction.f[2]<D_002BF810){w.move.phase.vectors.scalar.q=Scalar(D_002BF814*(w.move.direction.f[2]-D_002BF810));w.move.phase.vectors.corrected.q=AddScaled(w.move.phase.vectors.corrected.q,D_002A2DC0.q,w.move.phase.vectors.scalar.q);}}
  func_001FAC30(p->actor,w.move.phase.vectors.corrected.q);break;
 }
 }
}