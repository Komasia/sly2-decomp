typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M4 {qword a,b,c,d;};
struct WORK {U segment;M4 matrix;U normInput;float elapsed,duration;float*outTime,*outValue;U position;};
struct VTE {short delta,pad;void(*fn)();};
struct P {char pad0[0xC];VTE*vt;char pad10[0xE4-0x10];int cyclic,count;float*times;int padF0;qword*points;};
struct SPACE {qword axis;int mode;};
extern "C" {
int func_001E7538(P*,float,float*,float*);
qword func_001FA970(SPACE*,qword);
float func_001E63C0(P*,float);
void func_001E6A30(P*,qword,SPACE*,qword*,qword*,float*,float*,float);
}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Bc(float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline qword Dir(M4*m,qword a){__asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(a):"j"(m->a),"j"(m->b),"j"(m->c));return a;}
static inline qword Point(M4*m,qword a){qword r;__asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"=j"(r):"j"(m->a),"j"(m->b),"j"(m->c),"j"(m->d),"j"(a));return r;}
static inline qword Length(qword a){qword d,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w":"=j"(d),"=j"(one):"j"(a));__asm__("vadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(d):"j"(one));__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(d));return d;}
static inline qword Norm(qword a,qword len){qword r;__asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(r):"j"(a),"j"(len));return r;}
static inline qword Dot(qword a,qword b){qword one;__asm__("vmul.xyz %0,%2,%0\n\tvaddw.x %1,$vf0,$vf0w":"+j"(b),"=&j"(one):"j"(a));__asm__("vadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(b):"j"(one));return b;}
static inline int Bits(qword a){int r;__asm__("qmfc2.ni %0,%1":"=r"(r):"j"(a));return r;}
static inline float FromBits(int a){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
static inline float Scalar(qword a){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
static inline qword Lerp(qword a,qword b,qword low,qword high){__asm__("vmulax.xyzw $ACC,%1,%0x\n\tvmaddx.xyzw %0,%2,%3x":"+j"(low):"j"(a),"j"(b),"j"(high));return low;}
void func_001E6A30(P*p,qword position,SPACE*space,qword*outPosition,qword*outDirection,float*outTime,float*outValue,float initial){
 WORK work;work.position.q=position;work.outTime=outTime;work.outValue=outValue;
 int forward=0,backward=0,previous;
 int index=func_001E7538(p,initial,&work.elapsed,&work.duration);
 work.matrix=*((M4*(*)(void*))p->vt[31].fn)((char*)p+p->vt[31].delta);
 M4*basis=&work.matrix;
 register float fraction __asm__("$f12");
 for(;;){
  qword start=p->points[index],end=p->points[index+1];
  work.segment.q=Dir(basis,Sub(end,start));
  qword delta=Sub(work.position.q,Point(&work.matrix,start));
  if(space){delta=func_001FA970(space,delta);work.segment.q=func_001FA970(space,work.segment.q);}
  qword length=Length(work.segment.q);int sizeBits=Bits(length);
  work.normInput.q=work.segment.q;
  qword direction=Norm(work.normInput.q,length);
  qword projection=Dot(direction,delta);
  float distance=Scalar(projection),size=FromBits(sizeBits);
  work.segment.q=direction;
  fraction=0;
  if(distance<fraction){
   if(forward){fraction=1;index=previous;break;}
   if(index>0)--index;
   else {if(!p->cyclic){fraction=0;break;}index=p->count-2;backward=1;}
   next:
   previous=index;continue;
  }else if(size<distance){
   if(backward){fraction=0;index=previous;break;}
   if(index<p->count-2)++index;
   else {if(!p->cyclic){fraction=1;break;}index=0;}
   forward=1;goto next;
  }else {fraction=distance/size;break;}
 }
 if(outPosition){
  qword high=Bc(fraction),low=Bc(1.0f-fraction);
  *outPosition=Point(&work.matrix,Lerp(p->points[index],p->points[index+1],low,high));
 }
 if(outDirection){qword tangent=Dir(basis,Sub(p->points[index+1],p->points[index]));*outDirection=Norm(tangent,Length(tangent));}
 float time=(1.0f-fraction)*p->times[index]+fraction*p->times[index+1];
 if(work.outTime)*work.outTime=time;
 if(work.outValue)*work.outValue=func_001E63C0(p,time);
}

#define OFF(t,m) ((int)&((t*)0)->m)
typedef char projection_layout[(sizeof(U)==16 && sizeof(M4)==0x40 && sizeof(VTE)==8 && sizeof(SPACE)==0x20 && sizeof(WORK)==0x80 && OFF(M4,a)==0 && OFF(M4,b)==0x10 && OFF(M4,c)==0x20 && OFF(M4,d)==0x30 && OFF(VTE,delta)==0 && OFF(VTE,fn)==4 && OFF(SPACE,axis)==0 && OFF(SPACE,mode)==0x10 && OFF(P,vt)==0xC && OFF(P,cyclic)==0xE4 && OFF(P,count)==0xE8 && OFF(P,times)==0xEC && OFF(P,points)==0xF4 && OFF(WORK,segment)==0 && OFF(WORK,matrix)==0x10 && OFF(WORK,normInput)==0x50 && OFF(WORK,elapsed)==0x60 && OFF(WORK,duration)==0x64 && OFF(WORK,outTime)==0x68 && OFF(WORK,outValue)==0x6C && OFF(WORK,position)==0x70)?1:-1];
