typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
union U {qword q;float f[4];int words[4];};
union FLOATWORD {float value;int bits;};
struct ENTITY {char pad70[0x70];qword position;};
struct CANDIDATE {ENTITY *entity;void *owner;float radius;int wordC;ulong flags;char pad18[0x5C];int shape;};
struct CONTACT {qword position;U plane;char info20[16];};
struct P {char pad150[0x150];int state;char pad154[0x1C];qword position,velocity;char pad190[0x34];int raised;char pad1C8[8];float threshold;FLOATWORD boost,radius;int word1DC;float normalResponse;FLOATWORD tangentResponse;};
struct FRAME;
extern "C" FRAME *func_001AE478(FRAME *);
extern "C" void func_001AE4A0(FRAME *,int);
struct FRAME {FRAME(){func_001AE478(this);}~FRAME(){func_001AE4A0(this,2);}};
struct WORK {FRAME frame;U scalar,normal;CONTACT contacts[8];qword response;U primary,secondary,last;int count;CANDIDATE **candidates;qword minimum,center;};
extern "C" {
extern char D_003DD490[];
extern qword D_002A2DA0,D_002A2DC0,D_002A2DD0,D_002A2DE0;
extern float D_002C0D74,D_002C0D78;
qword func_001A62E8(P *);
int func_001C5570(void *,CANDIDATE *);
void func_0020FAA0(void *,qword,qword,int(*)(void *,CANDIDATE *),void *,int *,CANDIDATE ***);
int func_001A93C8(qword,CANDIDATE *,int mask,int triangleCount,void *triangles,int capacity,float,CONTACT *);
float func_0011E290(qword,qword,qword *,qword *);
}
static inline void CopyVU(qword *out,const qword &input){qword value;__asm__("lqc2 %0,%1":"=j"(value):"m"(input));*out=value;}
static inline qword Position3(P *p){qword raw=func_001A62E8(p);register qword v __asm__("vf3");__asm__("qmtc2.ni %1,%0":"=j"(v):"r"(raw));return v;}
static inline qword ToVU(qword value){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(value));return r;}
static inline qword Scalar(U &home,float value){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(value));home.q=r;return home.q;}
static inline qword ScalarBits(U &home,int bits){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(bits));home.q=r;return home.q;}
static inline qword AddScaled(qword value,qword direction,qword scale){__asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(value):"j"(direction),"j"(scale));return value;}
static inline qword Difference(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Square(qword value){qword r,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=j"(one):"j"(value));return r;}
static inline qword Root(qword square){__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(square));return square;}
static inline float X(qword value){float r;__asm__("mtc1 %1,%0":"=f"(r):"r"(value));return r;}
static inline float X0(qword value){register qword word __asm__("$2")=value;float result;__asm__("mtc1 %1,%0":"=f"(result):"r"(word));return result;}
static inline float X1(qword value){register qword word __asm__("$3")=value;float result;__asm__("mtc1 %1,%0":"=f"(result):"r"(word));return result;}
static inline float X4(qword value){register qword word __asm__("$4")=value;float result;__asm__("mtc1 %1,%0":"=f"(result):"r"(word));return result;}
static inline float Length(qword value){return X0(Root(Square(value)));}
static inline float Dot(qword a,qword b){qword r,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=j"(one):"j"(a),"j"(b));return X(r);}
static inline qword Divide(qword value,qword length){__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%0,$Q":"+j"(value):"j"(length));return value;}
static inline qword ReadPacked(const qword &value){qword r;__asm__("lq %0,%1":"=r"(r):"m"(value));return r;}
static inline qword NormalizeInto(U &value,const qword &fallback){
 register qword input __asm__("vf3");__asm__("qmtc2.ni %1,%0":"=j"(input):"r"(value.q));
 register qword square __asm__("vf1"),one __asm__("vf2");
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(square),"=&j"(one):"j"(input));
 register qword length __asm__("vf2");
 __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(length):"j"(square));
 float g=X1(length);
 if(g<0.0001f)value.q=ReadPacked(fallback);
 else{
  register qword result __asm__("vf1");
  __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(result):"j"(input),"j"(length));
  value.q=result;
 }
 return length;
}
static inline float Min(float a,float b){float r;__asm__("min.s %0,%1,%2":"=f"(r):"f"(a),"f"(b));return r;}
static inline qword Combine(qword a,qword b,qword sa,qword sb){qword r;__asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x":"=j"(r):"j"(a),"j"(b),"j"(sa),"j"(sb));return r;}
static inline qword Read1(const qword &q){register qword v __asm__("vf1");__asm__("lqc2 %0,%1":"=j"(v):"m"(q));return v;}
static inline qword Read2(const qword &q){register qword v __asm__("vf2");__asm__("lqc2 %0,%1":"=j"(v):"m"(q));return v;}
static inline qword SphereDirection(P *p,CANDIDATE *candidate){
 register qword position __asm__("vf2")=Read2(p->position);
 register qword center __asm__("vf1")=Read1(candidate->entity->position);
 register qword direction __asm__("vf3");
 __asm__("vsub.xyzw %0,%1,%2":"=j"(direction):"j"(position),"j"(center));
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(position),"=&j"(center):"j"(direction));
 qword alternative=ReadPacked(D_002A2DA0);
 __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(center):"j"(position));
 float length=X1(center);
 if(length<0.0001f)direction=alternative;
 else direction=Divide(direction,center);
 return direction;
}
static inline CONTACT* FirstContact(CONTACT*records){register CONTACT*cursor __asm__("$3");__asm__("la %0,%a1":"=r"(cursor):"p"(records));return cursor;}
static inline int NextCandidate(int index){register int next __asm__("$19");__asm__("addiu %0,%1,1":"=r"(next):"r"(index));return next;}
static inline qword PenetrationCenter(const CANDIDATE*candidate,const qword&home,float&radius){register float r __asm__("$f2");register qword center __asm__("vf1");__asm__("lwc1 %0,%2\n\tlqc2 %1,%3":"=f"(r),"=j"(center):"m"(candidate->radius),"m"(home));radius=r;return center;}
static inline void ResponseRates(P*p,qword length,float&normalRate,float&tangentRate,float&speed){
 register float n __asm__("$f1"),t __asm__("$f0"),v __asm__("$f3");
 register qword bits __asm__("$4");
 __asm__("lwc1 %0,%4\n\tqmfc2.ni %1,%6\n\tlwc1 %2,%5\n\tmtc1 %1,%3"
 :"=&f"(n),"=&r"(bits),"=&f"(t),"=f"(v)
 :"m"(p->normalResponse),"m"(p->tangentResponse.value),"j"(length));
 normalRate=n;tangentRate=t;speed=v;
}
extern "C" void func_001C55E0(P *p){
 WORK work;
 int i=0;
 float deepest=0.0f;
 qword start=Position3(p);
 work.minimum=AddScaled(start,D_002A2DE0,Scalar(work.scalar,-p->radius.value));
 qword end=AddScaled(Position3(p),D_002A2DE0,ScalarBits(work.scalar,p->radius.bits));
 func_0020FAA0(D_003DD490,work.minimum,end,func_001C5570,0,&work.count,&work.candidates);
 while(i<work.count){int next;
  CANDIDATE *candidate=work.candidates[i];
  if(candidate->flags&(0x8000UL<<34)){next=i+1;
   CopyVU(&work.center,candidate->entity->position);
   qword current=ToVU(func_001A62E8(p));
   float candidateRadius;
   qword center=PenetrationCenter(candidate,work.center,candidateRadius);
   qword displacement=Difference(center,current);
   float ownRadius=p->radius.value;
   float penetration=Length(displacement)-candidateRadius-ownRadius;
   if(penetration<deepest){
    qword direction=SphereDirection(p,candidate);next=NextCandidate(i);
    work.scalar.q=direction;
    if(Dot(p->velocity,direction)<0.0f){deepest=penetration;work.normal.q=direction;}
   }
  }else{next=i+1;if(candidate->shape){
   int count=func_001A93C8(func_001A62E8(p),candidate,0x7FFFFFFF,0,0,8,p->radius.value,work.contacts);
   if(count>0){CONTACT *contact=FirstContact(work.contacts);do{
    float penetration=Dot(contact->position,contact->plane.q)-contact->plane.f[3];
    if(penetration<deepest && Dot(p->velocity,contact->plane.q)<0.0f){work.normal.q=contact->plane.q;deepest=penetration;}
    ++contact;
   }while(--count);}
  }
  }
  i=next;
 }
 if(deepest<0.0f){float correction;
  if(work.normal.f[2]>0.7f && p->state==4){
   float vertical=func_0011E290(p->velocity,D_002A2DC0,0,&work.primary.q);
   qword length=NormalizeInto(work.primary,D_002A2DD0);
   float normalRate,tangentRate,speed;
   ResponseRates(p,length,normalRate,tangentRate,speed);
   float tangent=Min(tangentRate*speed,D_002C0D74);
   float normal=Min((-normalRate)*vertical,D_002C0D78);
   qword ts=Scalar(work.secondary,tangent),ns=Scalar(work.secondary,normal);
   work.response=Combine(work.primary.q,D_002A2DC0,ts,ns);
   if(p->raised)goto correctionReady;
   {
    int trigger=Dot(work.response,work.normal.q)<p->threshold;
    if(!trigger)goto correctionReady;
    work.response=Combine(work.primary.q,D_002A2DC0,Scalar(work.secondary,tangent),ScalarBits(work.secondary,p->boost.bits));
    {int raised=1;__asm__("sw %1,%0":"=m"(p->raised):"r"(raised):"memory");}
   }
  }else{
   func_0011E290(p->velocity,work.normal.q,&work.primary.q,&work.secondary.q);
   work.response=Combine(work.primary.q,work.secondary.q,Scalar(work.last,-p->normalResponse),ScalarBits(work.last,p->tangentResponse.bits));
  }
  correctionReady:correction=-deepest;
  p->position=AddScaled(p->position,work.normal.q,Scalar(work.primary,correction));
  p->velocity=work.response;
 }
}

#define OFF(t,m) ((unsigned int)&((t*)0)->m)
typedef char collision_layout[(sizeof(void*)==4 && sizeof(qword)==16 && sizeof(ulong)==8 && sizeof(U)==16 && sizeof(FLOATWORD)==4 && sizeof(FRAME)==1 && __alignof__(FRAME)==1 && sizeof(CONTACT)==0x30 && sizeof(WORK)==0x220 && OFF(ENTITY,position)==0x70 && OFF(CANDIDATE,entity)==0 && OFF(CANDIDATE,owner)==4 && OFF(CANDIDATE,radius)==8 && OFF(CANDIDATE,flags)==0x10 && OFF(CANDIDATE,shape)==0x74 && OFF(CONTACT,position)==0 && OFF(CONTACT,plane)==0x10 && OFF(CONTACT,plane.f[3])==0x1C && OFF(P,state)==0x150 && OFF(P,position)==0x170 && OFF(P,velocity)==0x180 && OFF(P,raised)==0x1C4 && OFF(P,threshold)==0x1D0 && OFF(P,boost)==0x1D4 && OFF(P,radius)==0x1D8 && OFF(P,normalResponse)==0x1E0 && OFF(P,tangentResponse)==0x1E4 && OFF(WORK,frame)==0 && OFF(WORK,scalar)==0x10 && OFF(WORK,normal)==0x20 && OFF(WORK,contacts)==0x30 && OFF(WORK,response)==0x1B0 && OFF(WORK,primary)==0x1C0 && OFF(WORK,secondary)==0x1D0 && OFF(WORK,last)==0x1E0 && OFF(WORK,count)==0x1F0 && OFF(WORK,candidates)==0x1F4 && OFF(WORK,minimum)==0x200 && OFF(WORK,center)==0x210)?1:-1];
