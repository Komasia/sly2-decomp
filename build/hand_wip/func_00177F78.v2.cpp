// (Claude agent, vu_hi6) v2: 552/672 aligned 287 (v1 556/368). DotPort as one asm (separate vaddw asm was CSE'd/spilled, separate vadday asm was implicitly volatile); avoidance/correction Normalize written out with X(length) taken twice (target never stores the length to the stack).
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];};
union WORD{int bits;float value;};
struct VE{short delta,pad;void*fn;};
struct CURVE{char pad0[0xE4];int wrapped;};
struct BODY;struct CONTEXT{char pad0[0x118];BODY*first;};
struct BODY{void*object;float z,radius,mass;CONTEXT*context;char pad14[0x4C];BODY*next;};
struct GROUP{char pad0[0xDC];BODY*body;};
struct OBJECT{
 char pad0[0xC];VE*vt;char pad10[0xD8];GROUP*group;
 char padEC[0xC4];qword axis;
 char pad1C0[0xD4];CURVE*primary;
};
struct S{
 char pad0[0x10];OBJECT*actor;char pad14[0x1C];
 CURVE*curve;float distance;int reverse,hold,noCollision;
 char pad44[8];int mode;char pad50[4];CURVE*extra;int extraMode;float extraDistance;
 char pad60[0x10];float separation;
 char pad74[0xC];qword position,velocity;int initialize;
};
struct POLY{float a,b,c;};struct RANGE{float lo,hi;};
struct CLOCK{float time,dt;};
struct PROJECTION{float length;union{U closest,prediction;}value;};
struct WORK{U point,direction,next,nextDirection;union{U phase,scalar;}shared;PROJECTION projection;U cross,force,origin;CONTEXT*context;};
extern "C"{
extern char D_003DD020[];extern CLOCK D_002DDED0;
extern qword D_002A2DA0,D_002A2DC0,D_002A2DD0;
extern float D_002BE630,D_002BE634,D_002BE660,D_002BE668,D_002BE66C,D_002BE670,D_002BE674,D_002BE690;
extern WORD D_002BE658,D_002BE65C,D_002BE664;
extern POLY D_002BE640,D_002BE680;
extern RANGE D_002BE650,D_002BBB60;
qword func_001A62E8(void*);
float func_001E66C8(CURVE*,float);float func_001E6648(CURVE*);
void func_001E7380(CURVE*,qword,void*,float,U*,U*,float*,float*);
void func_001E6F10(CURVE*,float,U*,U*);
int func_00178D00(S*);
void func_0011EE08(qword,qword,qword,U*,float*,float*);
int func_001C0B50(CONTEXT*,qword,U*);
}
static __inline__ qword Velocity(void*object){OBJECT*p=(OBJECT*)object;VE&v=p->vt[33];return((qword(*)(void*))v.fn)((char*)p+v.delta);}
static __inline__ qword Scalar(float f){int bits;qword value;__asm__("mfc1 %0,%1":"=r"(bits):"f"(f));__asm__("qmtc2.ni %1,%0":"=j"(value):"r"(bits));return value;}
static __inline__ qword WordScalar(const WORD&f){int bits;qword value;__asm__("lw %0,%1":"=r"(bits):"m"(f.bits));__asm__("qmtc2.ni %1,%0":"=j"(value):"r"(bits));return value;}
static __inline__ qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static __inline__ qword Scale(qword a,qword f){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(f));return r;}
static __inline__ qword Offset(qword a,qword b,qword f){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(f));return r;}
static __inline__ qword Integrate(qword a,qword b,qword c,qword f,qword g){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddax.xyzw $ACC,%2,%4x\n\tvmaddx.xyzw %0,%3,%5x":"=j"(r):"j"(a),"j"(b),"j"(c),"j"(f),"j"(g));return r;}
static __inline__ qword Blend(qword a,qword b,qword f,qword g){qword r;__asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x":"=j"(r):"j"(a),"j"(b),"j"(f),"j"(g));return r;}
static __inline__ qword DotPort(qword a,qword b){
 qword product,one;
 __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(product),"=&j"(one):"j"(a),"j"(b));
 return product;
}
static __inline__ float X(qword value){int bits;float r;__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(value));__asm__("mtc1 %1,%0":"=f"(r):"r"(bits));return r;}
static __inline__ float Dot(qword a,qword b){return X(DotPort(a,b));}
static __inline__ float Z(qword value){float r;__asm__("pextuw %0,$zero,%1":"=r"(r):"r"(value));return r;}
static __inline__ qword Flatten(qword value,qword up){return Sub(value,Scale(up,DotPort(value,up)));}
static __inline__ qword LengthPort(qword value){
 qword norm=DotPort(value,value);
 __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(norm));return norm;
}
static __inline__ float LengthXY(qword value){
 qword squared;
 __asm__("vmul.xy %0,%1,%1":"=j"(squared):"j"(value));
 __asm__("vaddy.x %0,%0,%0y":"+j"(squared));
 __asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(squared));return X(squared);
}
static __inline__ qword Unit(qword value,qword length){
 qword result;__asm__ __volatile__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(result):"j"(length),"j"(value));return result;
}
static __inline__ qword Normalize(qword value){
 qword length=LengthPort(value);float f=X(length);
 if(f<0.0001f)return D_002A2DA0;
 return Unit(value,length);
}
static __inline__ qword Normalize(qword value,float&f){
 qword length=LengthPort(value);f=X(length);
 if(f<0.0001f)return D_002A2DA0;
 return Unit(value,length);
}
static __inline__ qword Cross(qword a,qword b){__asm__("vopmula.xyz $ACC,%0,%1\n\tvopmsub.xyz %0,%1,%0":"+j"(a):"j"(b));return a;}
static __inline__ float Polynomial(const POLY&p,float x){return p.a+x*(p.b+x*p.c);}
static __inline__ float Clamp(float x,float lo,float hi){if(x<lo)x=lo;else if(hi<x)x=hi;return x;}
static __inline__ float Max(float a,float b){float r;__asm__("max.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
extern "C" void func_00177F78(S*p){
 WORK w;
 w.origin.q=func_001A62E8(p->actor);
 qword initial=w.origin.q;
 BODY*body=0;if(p->actor->group)body=p->actor->group->body;
 w.context=0;if(body)w.context=body->context;
 int reverse=p->reverse;
 float query;if(reverse)query=p->distance-D_002BE634;else query=p->distance+D_002BE634;
 query=func_001E66C8(p->curve,query);
 func_001E7380(p->curve,initial,D_003DD020,query,&w.point,&w.direction,0,&p->distance);
 if(p->mode==1||p->mode==4){
  reverse=p->extraMode!=2;
  if(reverse)query=p->extraDistance-D_002BE634;else query=p->extraDistance+D_002BE634;
  query=func_001E66C8(p->extra,query);
  func_001E7380(p->extra,initial,D_003DD020,query,&w.point,&w.direction,0,&p->extraDistance);
 }
 w.direction.q=Normalize(Flatten(w.direction.q,D_002A2DC0));
 p->separation=LengthXY(Sub(w.point.q,w.origin.q));
 float step=Clamp(Polynomial(D_002BE640,p->separation),D_002BE650.lo,D_002BE650.hi);
 if(reverse)step=-step;
 float gain;
 if(func_00178D00(p)){
  w.next.q=w.origin.q;w.nextDirection.q=D_002A2DA0;gain=0.0f;
 }else{
  gain=D_002BE630;
  switch(p->mode){
  case 0:case 2:case 3:
   if(p->curve==p->actor->primary){
    float lo=-p->distance;
    float length=func_001E6648(p->curve);
    float delta=Clamp(step,lo,length-p->distance);
    if(step!=delta)gain=0.0f;
    w.shared.scalar.q=Scalar(delta);
    w.next.q=Offset(w.point.q,w.direction.q,w.shared.scalar.q);w.nextDirection.q=w.direction.q;
   }else{
    float delta;
    if(p->curve->wrapped)delta=func_001E66C8(p->curve,p->distance+step);
    else{
     float lo=-p->distance;float length=func_001E6648(p->curve);
     delta=Clamp(step,lo,length-p->distance);
     if(step!=delta)gain=0.0f;
     delta=p->distance+delta;
    }
    func_001E6F10(p->curve,delta,&w.next,&w.nextDirection);
   }break;
  case 1:case 4:
   w.shared.scalar.q=Scalar(step);w.next.q=Offset(w.point.q,w.direction.q,w.shared.scalar.q);w.nextDirection.q=w.direction.q;
   break;
  default:break;
  }
 }
 if(reverse){w.shared.scalar.q=Scalar(-1.0f);w.nextDirection.q=Scale(w.nextDirection.q,w.shared.scalar.q);}
 w.shared.scalar.q=Scalar(gain);
 qword desired=Scale(w.nextDirection.q,w.shared.scalar.q);
 if(p->initialize){p->velocity=desired;p->position=w.next.q;p->initialize=0;}
 qword velocityError=Sub(desired,p->velocity);
 w.shared.scalar.q=WordScalar(D_002BE658);qword damping=w.shared.scalar.q;
 qword positionError=Sub(w.next.q,p->position);
 w.shared.scalar.q=WordScalar(D_002BE65C);
 qword acceleration=Blend(velocityError,positionError,damping,w.shared.scalar.q);
 if(!p->noCollision){
  BODY*entry=w.context->first;
  BODY*self=p->actor->group->body;
  for(;entry;entry=entry->next){
   if(entry->radius==0.0f||entry->mass==0.0f||entry->object==p->actor)continue;
   void*object=entry->object;
   w.shared.phase.q=func_001A62E8(object);w.shared.phase.f[2]+=entry->z;
   qword relative=Sub(w.origin.q,w.shared.phase.q);
   if(__builtin_fabsf(Z(relative))>D_002BE660)continue;
   qword velocity=Velocity(object);
   w.projection.value.prediction.q=WordScalar(D_002BE664);
   qword predicted=Offset(w.shared.phase.q,velocity,w.projection.value.prediction.q);
   qword now=Flatten(relative,D_002A2DC0);
   qword future=Flatten(Sub(p->position,predicted),D_002A2DC0);
   func_0011EE08(D_002A2DD0,now,future,&w.projection.value.closest,0,0);
   qword closestLength=LengthPort(w.projection.value.closest.q);
   if(X(closestLength)<0.0001f)w.projection.value.closest.q=D_002A2DA0;
   else w.projection.value.closest.q=Unit(w.projection.value.closest.q,closestLength);
   float distance=X(closestLength);
   float gap=Max(0.0f,(distance-entry->radius)-self->radius);
   float mass=entry->mass/(entry->mass+self->mass);
   if(gap<D_002BE668){
    float force=mass*(1.0f-gap/D_002BE668)*D_002BE66C;
    w.cross.q=Scalar(force);
    acceleration=Offset(acceleration,w.projection.value.closest.q,w.cross.q);
   }
   if(gap<D_002BE670){
    qword normal=Normalize(now);
    float factor=(1.0f-gap/D_002BE670)*Clamp(Polynomial(D_002BE680,Dot(normal,p->actor->axis)),D_002BBB60.lo,D_002BBB60.hi);
    if(factor==0.0f)continue;
    w.cross.q=Cross(D_002A2DC0,w.nextDirection.q);
    if(p->curve!=p->actor->primary&&Dot(w.projection.value.closest.q,w.cross.q)<0.0f)factor=-factor;
    w.force.q=Scalar(mass*factor*D_002BE674);
    acceleration=Offset(acceleration,Cross(w.projection.value.closest.q,D_002A2DC0),w.force.q);
   }
  }
 }
 float dt=D_002DDED0.dt;
 w.shared.scalar.q=Scalar(dt);
 float half=dt*0.5f;
 qword squared=Scalar(dt*half);
 acceleration=Flatten(acceleration,D_002A2DC0);
 qword nextVelocity=Offset(p->velocity,acceleration,w.shared.scalar.q);
 qword nextPoint=Integrate(p->position,p->velocity,acceleration,w.shared.scalar.q,squared);
 if(!p->noCollision&&func_001C0B50(w.context,nextPoint,&w.shared.phase)){
  qword correction=Flatten(Sub(w.shared.phase.q,nextPoint),D_002A2DC0);
  qword correctionLength=LengthPort(correction);
  if(X(correctionLength)<0.0001f)w.projection.value.closest.q=D_002A2DA0;
  else w.projection.value.closest.q=Unit(correction,correctionLength);
  float distance=X(correctionLength);
  if(D_002BE690<distance){
   float closing=Dot(nextVelocity,w.projection.value.closest.q);
   if(closing<0.0f){w.shared.scalar.q=Scalar(-closing);nextVelocity=Offset(nextVelocity,w.projection.value.closest.q,w.shared.scalar.q);}
   nextPoint=w.shared.phase.q;
  }
 }
 p->position=nextPoint;p->velocity=nextVelocity;
}

typedef char layout_pointer[(sizeof(void*)==4)?1:-1];
typedef char layout_qword[(sizeof(qword)==16)?1:-1];
typedef char layout_U[(sizeof(U)==16)?1:-1];
typedef char layout_WORD[(sizeof(WORD)==4)?1:-1];
typedef char layout_VE[(sizeof(VE)==8)?1:-1];
typedef char layout_CURVE[(sizeof(CURVE)==0xE8)?1:-1];
typedef char layout_BODY[(sizeof(BODY)==0x64)?1:-1];
typedef char layout_CONTEXT[(sizeof(CONTEXT)==0x11C)?1:-1];
typedef char layout_GROUP[(sizeof(GROUP)==0xE0)?1:-1];
typedef char layout_OBJECT[(sizeof(OBJECT)==0x2A0)?1:-1];
typedef char layout_S[(sizeof(S)==0xB0)?1:-1];
typedef char layout_POLY[(sizeof(POLY)==12)?1:-1];
typedef char layout_RANGE[(sizeof(RANGE)==8)?1:-1];
typedef char layout_CLOCK[(sizeof(CLOCK)==8)?1:-1];
typedef char layout_PROJECTION[(sizeof(PROJECTION)==0x20)?1:-1];
typedef char layout_WORK[(sizeof(WORK)==0xB0)?1:-1];
typedef char layout_U_q[((unsigned long)&((U*)0)->q==0x0)?1:-1];
typedef char layout_U_f[((unsigned long)&((U*)0)->f==0x0)?1:-1];
typedef char layout_WORD_bits[((unsigned long)&((WORD*)0)->bits==0x0)?1:-1];
typedef char layout_WORD_value[((unsigned long)&((WORD*)0)->value==0x0)?1:-1];
typedef char layout_VE_delta[((unsigned long)&((VE*)0)->delta==0x0)?1:-1];
typedef char layout_VE_fn[((unsigned long)&((VE*)0)->fn==0x4)?1:-1];
typedef char layout_CURVE_wrapped[((unsigned long)&((CURVE*)0)->wrapped==0xe4)?1:-1];
typedef char layout_BODY_object[((unsigned long)&((BODY*)0)->object==0x0)?1:-1];
typedef char layout_BODY_z[((unsigned long)&((BODY*)0)->z==0x4)?1:-1];
typedef char layout_BODY_radius[((unsigned long)&((BODY*)0)->radius==0x8)?1:-1];
typedef char layout_BODY_mass[((unsigned long)&((BODY*)0)->mass==0xc)?1:-1];
typedef char layout_BODY_context[((unsigned long)&((BODY*)0)->context==0x10)?1:-1];
typedef char layout_BODY_next[((unsigned long)&((BODY*)0)->next==0x60)?1:-1];
typedef char layout_CONTEXT_first[((unsigned long)&((CONTEXT*)0)->first==0x118)?1:-1];
typedef char layout_GROUP_body[((unsigned long)&((GROUP*)0)->body==0xdc)?1:-1];
typedef char layout_OBJECT_vt[((unsigned long)&((OBJECT*)0)->vt==0xc)?1:-1];
typedef char layout_OBJECT_group[((unsigned long)&((OBJECT*)0)->group==0xe8)?1:-1];
typedef char layout_OBJECT_axis[((unsigned long)&((OBJECT*)0)->axis==0x1b0)?1:-1];
typedef char layout_OBJECT_primary[((unsigned long)&((OBJECT*)0)->primary==0x294)?1:-1];
typedef char layout_S_actor[((unsigned long)&((S*)0)->actor==0x10)?1:-1];
typedef char layout_S_curve[((unsigned long)&((S*)0)->curve==0x30)?1:-1];
typedef char layout_S_distance[((unsigned long)&((S*)0)->distance==0x34)?1:-1];
typedef char layout_S_reverse[((unsigned long)&((S*)0)->reverse==0x38)?1:-1];
typedef char layout_S_hold[((unsigned long)&((S*)0)->hold==0x3c)?1:-1];
typedef char layout_S_noCollision[((unsigned long)&((S*)0)->noCollision==0x40)?1:-1];
typedef char layout_S_mode[((unsigned long)&((S*)0)->mode==0x4c)?1:-1];
typedef char layout_S_extra[((unsigned long)&((S*)0)->extra==0x54)?1:-1];
typedef char layout_S_extraMode[((unsigned long)&((S*)0)->extraMode==0x58)?1:-1];
typedef char layout_S_extraDistance[((unsigned long)&((S*)0)->extraDistance==0x5c)?1:-1];
typedef char layout_S_separation[((unsigned long)&((S*)0)->separation==0x70)?1:-1];
typedef char layout_S_position[((unsigned long)&((S*)0)->position==0x80)?1:-1];
typedef char layout_S_velocity[((unsigned long)&((S*)0)->velocity==0x90)?1:-1];
typedef char layout_S_initialize[((unsigned long)&((S*)0)->initialize==0xa0)?1:-1];
typedef char layout_POLY_a[((unsigned long)&((POLY*)0)->a==0x0)?1:-1];
typedef char layout_POLY_b[((unsigned long)&((POLY*)0)->b==0x4)?1:-1];
typedef char layout_POLY_c[((unsigned long)&((POLY*)0)->c==0x8)?1:-1];
typedef char layout_RANGE_lo[((unsigned long)&((RANGE*)0)->lo==0x0)?1:-1];
typedef char layout_RANGE_hi[((unsigned long)&((RANGE*)0)->hi==0x4)?1:-1];
typedef char layout_CLOCK_time[((unsigned long)&((CLOCK*)0)->time==0x0)?1:-1];
typedef char layout_CLOCK_dt[((unsigned long)&((CLOCK*)0)->dt==0x4)?1:-1];
typedef char layout_PROJECTION_length[((unsigned long)&((PROJECTION*)0)->length==0x0)?1:-1];
typedef char layout_PROJECTION_value[((unsigned long)&((PROJECTION*)0)->value==0x10)?1:-1];
typedef char layout_WORK_point[((unsigned long)&((WORK*)0)->point==0x0)?1:-1];
typedef char layout_WORK_direction[((unsigned long)&((WORK*)0)->direction==0x10)?1:-1];
typedef char layout_WORK_next[((unsigned long)&((WORK*)0)->next==0x20)?1:-1];
typedef char layout_WORK_nextDirection[((unsigned long)&((WORK*)0)->nextDirection==0x30)?1:-1];
typedef char layout_WORK_shared[((unsigned long)&((WORK*)0)->shared==0x40)?1:-1];
typedef char layout_WORK_projection[((unsigned long)&((WORK*)0)->projection==0x50)?1:-1];
typedef char layout_WORK_cross[((unsigned long)&((WORK*)0)->cross==0x70)?1:-1];
typedef char layout_WORK_force[((unsigned long)&((WORK*)0)->force==0x80)?1:-1];
typedef char layout_WORK_origin[((unsigned long)&((WORK*)0)->origin==0x90)?1:-1];
typedef char layout_WORK_context[((unsigned long)&((WORK*)0)->context==0xa0)?1:-1];
