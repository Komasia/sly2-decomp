
typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];} U;
typedef struct {int index;float a,b;} TRIREF;
typedef struct {TRIREF ref;U point,normal,scalar,acceleration,duration,velocity;} WORK;
extern void func_00185310(void*,qword,int,TRIREF*,qword*,qword*);
extern float D_002BE918;
static inline void Publish(U*home,qword q){__asm__("sqc2 %1,%0":"=m"(home->q):"j"(q));}
int func_00185D18(void*p,qword inputPoint,qword inputVelocity,qword inputAcceleration,float offset,float time,TRIREF*reference,qword*outPoint,qword*outVelocity){
 WORK w;qword prediction;register float half __asm__("$f0")=0.5f;
 {
  register qword velocity __asm__("vf6"),duration __asm__("vf5"),acceleration __asm__("vf3"),point __asm__("vf2"),square __asm__("vf1");
  register int timeBits __asm__("$2");
  __asm__("mfc1 %0,%7\n\tqmtc2.ni %6,%1\n\tmul.s %2,%7,%2\n\tqmtc2.ni %0,%3\n\tsq %8,%4\n\tqmtc2.ni %8,%5"
  :"=&r"(timeBits),"=j"(velocity),"+f"(half),"=j"(duration),"=m"(w.acceleration.q),"=j"(acceleration)
  :"r"(inputVelocity),"f"(time),"r"(inputAcceleration));
  __asm__("qmtc2.ni %1,%0":"=j"(point):"r"(inputPoint));
  time=time*half;
  Publish(&w.scalar,duration);
  __asm__("qmtc2.ni %1,%0":"=j"(square):"r"(time));
  __asm__("vadda.xyzw ACC,%0,$vf0\n\tvmaddax.xyzw ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x":"+j"(point):"j"(velocity),"j"(duration),"j"(acceleration),"j"(square));
  __asm__("qmfc2.ni %0,%1":"=r"(prediction):"j"(point));
  Publish(&w.scalar,square);
  w.duration.q=duration;w.velocity.q=velocity;
 }
 func_00185310(p,prediction,0,&w.ref,&w.point.q,&w.normal.q);
 {
  register qword normal __asm__("vf3"),point __asm__("vf1"),duration __asm__("vf5"),velocity __asm__("vf6"),gain __asm__("vf4");
  __asm__("lqc2 %0,%2\n\tlqc2 %1,%3":"=j"(normal),"=j"(point):"m"(w.normal.q),"m"(w.point.q));
  *reference=w.ref;
  {
   register qword scalar __asm__("vf2");
   {register int bits __asm__("$2");__asm__("mfc1 %0,%2\n\tqmtc2.ni %0,%1":"=&r"(bits),"=j"(scalar):"f"(offset));}
   duration=w.duration.q;
   Publish(&w.scalar,scalar);
   __asm__("vadda.xyzw ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(point):"j"(normal),"j"(scalar));
  }
  velocity=w.velocity.q;
  {
   register qword acceleration __asm__("vf2")=w.acceleration.q;
   __asm__("qmtc2.ni %1,%0":"=j"(gain):"r"(*(int*)&D_002BE918));
   *outPoint=point;
   __asm__("vadda.xyzw ACC,%0,$vf0\n\tvmaddax.xyzw ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x":"+j"(velocity):"j"(acceleration),"j"(duration),"j"(normal),"j"(gain));
  }
  Publish(&w.scalar,duration);
  *outVelocity=velocity;
  Publish(&w.scalar,gain);
 }
 return 1;
}
typedef char WORK_Size[sizeof(WORK)==0x70?1:-1];
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char TRIREF_Size[sizeof(TRIREF)==12?1:-1];

typedef char qword_Size[sizeof(qword)==16?1:-1];
typedef char Float_Size[sizeof(float)==4?1:-1];
typedef char Int_Size[sizeof(int)==4?1:-1];
typedef char Pointer_Size[sizeof(void*)==4?1:-1];
typedef char U_Align[__alignof__(U)==16?1:-1];
typedef char WORK_Align[__alignof__(WORK)==16?1:-1];
typedef char U_q_Offset[((unsigned)&((U*)0)->q==0)?1:-1];
typedef char U_float_Offset[((unsigned)&((U*)0)->f==0)?1:-1];
typedef char Ref_index_Offset[((unsigned)&((TRIREF*)0)->index==0)?1:-1];
typedef char Ref_a_Offset[((unsigned)&((TRIREF*)0)->a==4)?1:-1];
typedef char Ref_b_Offset[((unsigned)&((TRIREF*)0)->b==8)?1:-1];
typedef char WORK_ref_Offset[((unsigned)&((WORK*)0)->ref==0)?1:-1];
typedef char WORK_point_Offset[((unsigned)&((WORK*)0)->point==0x10)?1:-1];
typedef char WORK_normal_Offset[((unsigned)&((WORK*)0)->normal==0x20)?1:-1];
typedef char WORK_scalar_Offset[((unsigned)&((WORK*)0)->scalar==0x30)?1:-1];
typedef char WORK_acceleration_Offset[((unsigned)&((WORK*)0)->acceleration==0x40)?1:-1];
typedef char WORK_duration_Offset[((unsigned)&((WORK*)0)->duration==0x50)?1:-1];
typedef char WORK_velocity_Offset[((unsigned)&((WORK*)0)->velocity==0x60)?1:-1];
