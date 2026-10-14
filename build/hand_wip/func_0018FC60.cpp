typedef int qword __attribute__((mode(TI)));
typedef union U{qword q;float f[4];int i[4];}U;
struct M3{U r[3];M3(){}M3(const M3&m){r[0].q=m.r[0].q;r[1].q=m.r[1].q;r[2].q=m.r[2].q;}M3&operator=(const M3&m){r[0].q=m.r[0].q;r[1].q=m.r[1].q;r[2].q=m.r[2].q;return *this;}};
typedef struct M4{U r[4];}M4;
typedef struct VTE{short delta,pad;void*fn;}VTE;
typedef struct NODE{char pad0[12];VTE*vt;char pad10[0x124];float property;}NODE;
typedef struct ACCEL{char pad0[0x80];U value;}ACCEL;
typedef struct LINK{int header;NODE*object;}LINK;
typedef struct DELTA{U first,second;}DELTA;
typedef struct P{char pad0[12];VTE*vt;char pad10[0xD8];ACCEL*accel;char padEC[0x17D8];NODE*target;char pad18C8[8];int state;float stamp;char pad18D8[0x24];int reverse;LINK*other;char pad1904[12];DELTA response[2];}P;
typedef struct POLY{float a,b,c;}POLY;
typedef struct CLAMP{float low,high;}CLAMP;
typedef struct SMPA{float a,b,duration,limit;}SMPA;
typedef struct CLOCK{float time,dt;}CLOCK;
typedef struct STATE{U direction,position,velocity;M3 rotation;}STATE;
typedef struct WORK{U anchor,displacement,anchorVelocity,axis;M3 anchorBasis;U relative,perpendicular,parallel,firstAxis,angularFirst,temporary,secondAxis,angularSecond,angular,parallelAngular,perpendicularAngular,velocity;STATE state;M3 rotation;U halfScalar;float speedOut;U savedVelocity,dtScalar,savedPoint,savedAngular,finalVelocity;}WORK;
inline void*operator new(unsigned int,void*p){return p;}
extern "C"{
qword func_001A62E8(void*);
M4*func_001A6318(void*);
qword func_0022D348(void*,void*,qword);
float func_0011E290(qword,qword,qword*,qword*);
float func_0011D1C0(float,float,float,float,SMPA*,float*);
M3 func_0011B570(qword);
void func_0018F958(P*,NODE*,qword*,float*,DELTA*);
extern U D_002A2DC0,D_002A2DA0,D_002A2DB0,D_002A2DD0;
extern POLY D_002BF4F0,D_002BF520;
extern CLAMP D_002BF500,D_002BBB60;
extern float D_002BF508,D_002BF50C,D_002BF510,D_002BF514,D_002BF540,D_002BF544;
extern SMPA D_002BF530;
extern CLOCK D_002DDED0;
}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Scalar(float value){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(value));return r;}
static inline qword ScalarWord(const float*p){qword r;__asm__("lw %0,%1":"=r"(r):"m"(*p));return r;}
static inline qword Transfer(qword a){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(a));return r;}
static inline qword Scale(qword a,qword b){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Divide(qword a,qword s){qword r;__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(a),"j"(s));return r;}
static inline qword Squared(qword a){qword d,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a));return d;}
static inline qword Root(qword a){qword r;__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(r):"j"(a));return r;}
static inline float FloatX(qword a){int bits;float f;__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(a));__asm__("mtc1 %1,%0":"=f"(f):"r"(bits));return f;}
static inline float Length(qword a){return FloatX(Root(Squared(a)));}
static inline qword UnitOr(qword a,qword fallback){qword length=Root(Squared(a));if(FloatX(length)<0.0001f)return fallback;return Divide(a,length);}
static inline qword CrossRetain(qword r,qword a,qword b){__asm__("vopmula.xyz ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"+j"(r):"j"(a),"j"(b));return r;}
static inline qword RemoveParallel(qword a,qword b){qword d,one,parallel,r;__asm__("vmul.xyz %0,%4,%5\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z\n\tvmulx.xyzw %2,%5,%0x\n\tvsub.xyzw %3,%4,%2":"=&j"(d),"=&j"(one),"=&j"(parallel),"=j"(r):"j"(a),"j"(b));return r;}
static inline qword AddScale(qword a,qword b,qword s){qword r;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(s));return r;}
static inline qword Weighted(qword a,qword b,qword x,qword y){qword r;__asm__("vmulax.xyzw ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x":"=j"(r):"j"(a),"j"(b),"j"(x),"j"(y));return r;}
static inline qword RequestVelocity(qword velocity,qword angular,qword difference,qword dt){
 qword cross=CrossRetain(difference,angular,difference),r;
 __asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddax.xyzw ACC,%2,%4x\n\tvmaddx.xyzw %0,%3,%4x":"=j"(r):"j"(velocity),"j"(angular),"j"(cross),"j"(dt));return r;
}
static inline qword Rotate(M3*m,qword a){qword r=a;__asm__("vmulax.xyz ACC,%1,%4x\n\tvmadday.xyz ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z":"+j"(r):"j"(m->r[0].q),"j"(m->r[1].q),"j"(m->r[2].q),"j"(a));return r;}
static inline float Clamp(float value,float low,float high){if(value<low)return low;else if(high<value)return high;return value;}
static inline float Min(float a,float b){float r;__asm__("min.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline float Max(float a,float b){float r;__asm__("max.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline float Evaluate(POLY*p,float t){return p->a+t*(p->b+t*p->c);}
static inline qword Velocity(void*p){VTE*vt=((NODE*)p)->vt;VTE*e=&vt[33];return((qword(*)(void*))e->fn)((char*)p+e->delta);}
static inline void*Space(NODE*p){VTE*e=&p->vt[32];return((void*(*)(void*,void*))e->fn)((char*)p+e->delta,0);}
extern "C" void func_0018FC60(P*p){
 WORK w;float distance,radial,drag,bias,nextDistance;
 w.anchor.q=func_001A62E8(p->target);
 w.anchorBasis=*(M3*)func_001A6318(p->target);
 w.anchorVelocity.q=func_0022D348(Space(p->target),0,w.anchor.q);
 w.axis.q=Sub(func_001A62E8(p),w.anchor.q);
 w.displacement.q=w.axis.q;
 {qword length=Root(Squared(w.axis.q));
  if(FloatX(length)<0.0001f)w.axis=D_002A2DC0;else w.axis.q=Divide(w.axis.q,length);
  distance=FloatX(length);
 }
 w.relative.q=Sub(Velocity(p),w.anchorVelocity.q);
 radial=func_0011E290(w.relative.q,w.axis.q,&w.parallel.q,&w.perpendicular.q);
 w.firstAxis.q=UnitOr(CrossRetain(w.relative.q,w.axis.q,w.perpendicular.q),D_002A2DA0.q);
 {float ratio=Length(w.perpendicular.q)/distance;
  w.temporary.q=Scalar(ratio);
  w.angularFirst.q=Scale(w.firstAxis.q,w.temporary.q);
  w.temporary.q=RemoveParallel(p->accel->value.q,w.axis.q);
  w.secondAxis.q=UnitOr(CrossRetain(w.firstAxis.q,w.axis.q,w.temporary.q),D_002A2DB0.q);
  {float acceleration=Length(w.temporary.q)/distance;
   w.angular.q=Scalar(acceleration);
   w.angularSecond.q=Scale(w.secondAxis.q,w.angular.q);
  }
  drag=Clamp(Evaluate(&D_002BF4F0,ratio),D_002BF500.low,D_002BF500.high);
 }
 if(p->state==0||p->state==2)bias=D_002BF508;else bias=D_002BF50C;
 w.velocity.q=Transfer(ScalarWord(&D_002DDED0.dt));
 w.angular.q=AddScale(w.angularFirst.q,w.angularSecond.q,w.velocity.q);
 func_0011E290(w.angular.q,w.anchorBasis.r[1].q,&w.parallelAngular.q,&w.perpendicularAngular.q);
 {float dt=D_002DDED0.dt;
  w.velocity.q=Scalar(drag*dt+1.0f);
  qword first=w.velocity.q;
  w.velocity.q=Scalar(bias*dt+1.0f);
  w.angular.q=Weighted(w.parallelAngular.q,w.perpendicularAngular.q,first,w.velocity.q);
 }
 if((p->state==0||p->state==2)&&D_002DDED0.time-p->stamp<D_002BF510){
  float amount=D_002DDED0.dt*D_002BF514;
  if(p->state==0)amount=-amount;
  if(p->reverse)amount=-amount;
  float down=-p->accel->value.f[2],speed=Length(w.perpendicular.q);
  float t=(down*w.displacement.f[2]+speed*(speed*0.5f))/down;
  amount*=Clamp(Evaluate(&D_002BF520,t),D_002BBB60.low,D_002BBB60.high);
  w.velocity.q=Scalar(amount);
  w.angular.q=AddScale(w.angular.q,w.anchorBasis.r[1].q,w.velocity.q);
 }
 nextDistance=func_0011D1C0(distance,radial,D_002BF544-p->target->property,D_002DDED0.dt,&D_002BF530,&w.speedOut);
 {float scale=Min(D_002BF544,distance)/Max(D_002BF540,nextDistance);
  w.velocity.q=Scalar(scale);w.angular.q=Scale(w.angular.q,w.velocity.q);
 }
 if(p->other){
  NODE*other=p->other->object;
  w.dtScalar.q=ScalarWord(&D_002DDED0.dt);
  w.savedPoint=w.anchor;w.savedAngular=D_002A2DD0;
  w.savedVelocity=w.anchorVelocity;
  w.state.direction=D_002A2DD0;w.state.position=D_002A2DD0;w.state.velocity=w.dtScalar;
  qword delta=Sub(w.savedPoint.q,func_001A62E8(other));
  w.velocity.q=RequestVelocity(w.savedVelocity.q,w.savedAngular.q,delta,Transfer(w.dtScalar.q));
 }else w.velocity=w.anchorVelocity;
 {float halfTime=D_002DDED0.dt*0.5f;
  w.halfScalar.q=Scalar(halfTime);
  qword turn=Scale(Add(w.angular.q,w.angularFirst.q),w.halfScalar.q);
  new(&w.rotation)M3(func_0011B570(turn));
 }
 w.state.direction.q=Rotate(&w.rotation,w.axis.q);
 {qword nextScalar=Scalar(nextDistance);
  qword radius=Scale(w.state.direction.q,nextScalar);
  qword speedScalar=Transfer(ScalarWord(&w.speedOut));
  qword cross=CrossRetain(w.angular.q,w.angular.q,radius);
  w.state.position.q=Add(w.anchor.q,radius);
  w.state.velocity.q=Add(Add(w.velocity.q,cross),Scale(w.state.direction.q,speedScalar));
  w.state.rotation=w.rotation;
  ((U*)&w.rotation)->q=nextScalar;
  w.finalVelocity=w.state.velocity;
  ((U*)&w.rotation)->q=speedScalar;
 }
 {qword current=Velocity(p);
  qword duration=Transfer(ScalarWord(&D_002DDED0.dt));
  ((U*)&w.rotation)->q=duration;
  w.temporary.q=Sub(Divide(Sub(w.finalVelocity.q,current),duration),p->accel->value.q);
 }
 if(p->other)func_0018F958(p,p->other->object,&w.anchor.q,&w.temporary.f[0],p->response);
 else p->response[0].first=w.temporary;
}

typedef char layout_size_qword[(sizeof(qword)==16)?1:-1];
typedef char layout_size_voidpointer[(sizeof(void*)==4)?1:-1];
typedef char layout_size_U[(sizeof(U)==16)?1:-1];
typedef char layout_size_M3[(sizeof(M3)==48)?1:-1];
typedef char layout_size_M4[(sizeof(M4)==64)?1:-1];
typedef char layout_size_VTE[(sizeof(VTE)==8)?1:-1];
typedef char layout_size_NODE[(sizeof(NODE)==0x138)?1:-1];
typedef char layout_size_ACCEL[(sizeof(ACCEL)==0x90)?1:-1];
typedef char layout_size_LINK[(sizeof(LINK)==8)?1:-1];
typedef char layout_size_DELTA[(sizeof(DELTA)==32)?1:-1];
typedef char layout_size_P[(sizeof(P)==0x1950)?1:-1];
typedef char layout_size_POLY[(sizeof(POLY)==12)?1:-1];
typedef char layout_size_CLAMP[(sizeof(CLAMP)==8)?1:-1];
typedef char layout_size_SMPA[(sizeof(SMPA)==16)?1:-1];
typedef char layout_size_CLOCK[(sizeof(CLOCK)==8)?1:-1];
typedef char layout_size_STATE[(sizeof(STATE)==0x60)?1:-1];
typedef char layout_size_WORK[(sizeof(WORK)==0x230)?1:-1];
typedef char layout_VTE_delta[((unsigned long)&((VTE*)0)->delta==0x0)?1:-1];
typedef char layout_VTE_fn[((unsigned long)&((VTE*)0)->fn==0x4)?1:-1];
typedef char layout_NODE_vt[((unsigned long)&((NODE*)0)->vt==0xc)?1:-1];
typedef char layout_NODE_property[((unsigned long)&((NODE*)0)->property==0x134)?1:-1];
typedef char layout_ACCEL_value[((unsigned long)&((ACCEL*)0)->value==0x80)?1:-1];
typedef char layout_LINK_object[((unsigned long)&((LINK*)0)->object==0x4)?1:-1];
typedef char layout_DELTA_first[((unsigned long)&((DELTA*)0)->first==0x0)?1:-1];
typedef char layout_DELTA_second[((unsigned long)&((DELTA*)0)->second==0x10)?1:-1];
typedef char layout_P_vt[((unsigned long)&((P*)0)->vt==0xc)?1:-1];
typedef char layout_P_accel[((unsigned long)&((P*)0)->accel==0xe8)?1:-1];
typedef char layout_P_target[((unsigned long)&((P*)0)->target==0x18c4)?1:-1];
typedef char layout_P_state[((unsigned long)&((P*)0)->state==0x18d0)?1:-1];
typedef char layout_P_stamp[((unsigned long)&((P*)0)->stamp==0x18d4)?1:-1];
typedef char layout_P_reverse[((unsigned long)&((P*)0)->reverse==0x18fc)?1:-1];
typedef char layout_P_other[((unsigned long)&((P*)0)->other==0x1900)?1:-1];
typedef char layout_P_response[((unsigned long)&((P*)0)->response==0x1910)?1:-1];
typedef char layout_POLY_a[((unsigned long)&((POLY*)0)->a==0x0)?1:-1];
typedef char layout_POLY_b[((unsigned long)&((POLY*)0)->b==0x4)?1:-1];
typedef char layout_POLY_c[((unsigned long)&((POLY*)0)->c==0x8)?1:-1];
typedef char layout_CLAMP_low[((unsigned long)&((CLAMP*)0)->low==0x0)?1:-1];
typedef char layout_CLAMP_high[((unsigned long)&((CLAMP*)0)->high==0x4)?1:-1];
typedef char layout_SMPA_a[((unsigned long)&((SMPA*)0)->a==0x0)?1:-1];
typedef char layout_SMPA_b[((unsigned long)&((SMPA*)0)->b==0x4)?1:-1];
typedef char layout_SMPA_duration[((unsigned long)&((SMPA*)0)->duration==0x8)?1:-1];
typedef char layout_SMPA_limit[((unsigned long)&((SMPA*)0)->limit==0xc)?1:-1];
typedef char layout_CLOCK_time[((unsigned long)&((CLOCK*)0)->time==0x0)?1:-1];
typedef char layout_CLOCK_dt[((unsigned long)&((CLOCK*)0)->dt==0x4)?1:-1];
typedef char layout_STATE_direction[((unsigned long)&((STATE*)0)->direction==0x0)?1:-1];
typedef char layout_STATE_position[((unsigned long)&((STATE*)0)->position==0x10)?1:-1];
typedef char layout_STATE_velocity[((unsigned long)&((STATE*)0)->velocity==0x20)?1:-1];
typedef char layout_STATE_rotation[((unsigned long)&((STATE*)0)->rotation==0x30)?1:-1];
typedef char layout_WORK_anchor[((unsigned long)&((WORK*)0)->anchor==0x0)?1:-1];
typedef char layout_WORK_displacement[((unsigned long)&((WORK*)0)->displacement==0x10)?1:-1];
typedef char layout_WORK_anchorVelocity[((unsigned long)&((WORK*)0)->anchorVelocity==0x20)?1:-1];
typedef char layout_WORK_axis[((unsigned long)&((WORK*)0)->axis==0x30)?1:-1];
typedef char layout_WORK_anchorBasis[((unsigned long)&((WORK*)0)->anchorBasis==0x40)?1:-1];
typedef char layout_WORK_relative[((unsigned long)&((WORK*)0)->relative==0x70)?1:-1];
typedef char layout_WORK_perpendicular[((unsigned long)&((WORK*)0)->perpendicular==0x80)?1:-1];
typedef char layout_WORK_parallel[((unsigned long)&((WORK*)0)->parallel==0x90)?1:-1];
typedef char layout_WORK_firstAxis[((unsigned long)&((WORK*)0)->firstAxis==0xa0)?1:-1];
typedef char layout_WORK_angularFirst[((unsigned long)&((WORK*)0)->angularFirst==0xb0)?1:-1];
typedef char layout_WORK_temporary[((unsigned long)&((WORK*)0)->temporary==0xc0)?1:-1];
typedef char layout_WORK_secondAxis[((unsigned long)&((WORK*)0)->secondAxis==0xd0)?1:-1];
typedef char layout_WORK_angularSecond[((unsigned long)&((WORK*)0)->angularSecond==0xe0)?1:-1];
typedef char layout_WORK_angular[((unsigned long)&((WORK*)0)->angular==0xf0)?1:-1];
typedef char layout_WORK_parallelAngular[((unsigned long)&((WORK*)0)->parallelAngular==0x100)?1:-1];
typedef char layout_WORK_perpendicularAngular[((unsigned long)&((WORK*)0)->perpendicularAngular==0x110)?1:-1];
typedef char layout_WORK_velocity[((unsigned long)&((WORK*)0)->velocity==0x120)?1:-1];
typedef char layout_WORK_state[((unsigned long)&((WORK*)0)->state==0x130)?1:-1];
typedef char layout_WORK_rotation[((unsigned long)&((WORK*)0)->rotation==0x190)?1:-1];
typedef char layout_WORK_halfScalar[((unsigned long)&((WORK*)0)->halfScalar==0x1c0)?1:-1];
typedef char layout_WORK_speedOut[((unsigned long)&((WORK*)0)->speedOut==0x1d0)?1:-1];
typedef char layout_WORK_savedVelocity[((unsigned long)&((WORK*)0)->savedVelocity==0x1e0)?1:-1];
typedef char layout_WORK_dtScalar[((unsigned long)&((WORK*)0)->dtScalar==0x1f0)?1:-1];
typedef char layout_WORK_savedPoint[((unsigned long)&((WORK*)0)->savedPoint==0x200)?1:-1];
typedef char layout_WORK_savedAngular[((unsigned long)&((WORK*)0)->savedAngular==0x210)?1:-1];
typedef char layout_WORK_finalVelocity[((unsigned long)&((WORK*)0)->finalVelocity==0x220)?1:-1];
