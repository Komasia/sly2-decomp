// func_0018F958 (Claude agent, lane J7, 2026-10-24): aligned 7, 29 diff lines, frame 0x2B0, 194 insns, no pins. laneJ6v3 + `U*second=Addr(&...second)` computed before the empty asm and reused by the .second store: the store giv representative is now earlier than the arg giv, so loop.c emits the arg increment first (target addiu s2 before s1).
#define FIELD_OFFSET(t,m) ((uint)&(((t*)0)->m))
typedef unsigned int uint;
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];};
struct DELTA{U first,second;};
struct P;
struct VE{short delta,pad;void(*fn)(P*,DELTA*,qword,U*);};
struct P{char pad[12];VE*vt;};
extern "C"{
qword func_001A62E8(P*);
qword func_001FAA00(P*,qword);
qword func_001FAA48(P*,qword,qword);
extern U D_002A2D00[3];
}
void CroutDecomp(int,float*,float*);
void CroutSolve(int,float*,float*,float*);
struct VU_FLOAT{qword q;VU_FLOAT(){}VU_FLOAT(qword a){q=a;}};
struct VU_VECTOR{qword q;VU_VECTOR(){}VU_VECTOR(qword a){q=a;}};
static inline VU_FLOAT Scalar(float value){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(value));return VU_FLOAT(q);}
static inline qword Scale(VU_VECTOR value,VU_FLOAT amount){qword q;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(q):"j"(value.q),"j"(amount.q));return q;}
static inline qword Sub(VU_VECTOR first,VU_VECTOR second){qword q;__asm__("vsub.xyzw %0,%1,%2":"=j"(q):"j"(first.q),"j"(second.q));return q;}
static inline void StoreDot(float*out,const qword&a0,const qword&b){qword a=a0;qword one;float bits;__asm__("vmul.xyz %1,%1,%3\n\tvaddw.x %2,$vf0,$vf0w\n\tvadday.x $ACC,%1,%1y\n\tvmaddz.x %1,%2,%1z\n\tqmfc2.ni %0,%1":"=&rV"(*out),"+j"(a),"=j"(one):"j"(b),"j"(a));}
static inline VU_FLOAT VuFloatFromMemWord(int n){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"rV"(n));return VU_FLOAT(q);}
static inline VU_VECTOR MulAdd3(VU_VECTOR a,VU_VECTOR b,VU_VECTOR c,VU_FLOAT x,VU_FLOAT y,VU_FLOAT z){qword out;__asm__("vmulax.xyzw $ACC,%1,%4x\n\tvmaddax.xyzw $ACC,%2,%5x\n\tvmaddx.xyzw %0,%3,%6x":"=j"(out):"j"(a.q),"j"(b.q),"j"(c.q),"j"(x.q),"j"(y.q),"j"(z.q));return VU_VECTOR(out);}
static inline VU_VECTOR Sum3(const U*a,const U*b,const U*c,VU_FLOAT x,VU_FLOAT y,VU_FLOAT z,U*scalar){scalar->q=x.q;VU_VECTOR va=a->q;scalar->q=y.q;VU_VECTOR vb=b->q;scalar->q=z.q;VU_VECTOR vc=c->q;return MulAdd3(va,vb,vc,x,y,z);}
static inline U*Addr(U*p){return p;}
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char DELTA_Size[sizeof(DELTA)==32?1:-1];
typedef char P_Size[sizeof(P)==16?1:-1];
typedef char VE_Size[sizeof(VE)==8?1:-1];
typedef char P_vt_Offset[FIELD_OFFSET(P,vt)==12?1:-1];
typedef char VE_delta_Offset[FIELD_OFFSET(VE,delta)==0?1:-1];
typedef char VE_fn_Offset[FIELD_OFFSET(VE,fn)==4?1:-1];
typedef char DELTA_first_Offset[FIELD_OFFSET(DELTA,first)==0?1:-1];
typedef char DELTA_second_Offset[FIELD_OFFSET(DELTA,second)==16?1:-1];
extern "C" void func_0018F958(P*p,P*other,qword*point,float*input,DELTA*out){
 int axisIndex=0,side;
 P*objects[2];U points[2];U axis;
 DELTA effects[2][3];U velocity[2];U relative[3];
 float matrix[3][3],decomposed[3][3],rhs[3],weights[3];U scalar;
 objects[0]=p;objects[1]=other;
 points[0].q=func_001A62E8(p);points[1].q=*point;
 
 for(;axisIndex<3;axisIndex++){
  for(side=0;side<2;side++){
   P*object=objects[side];axis.q=D_002A2D00[axisIndex].q;
   if(side==1){VU_FLOAT minus=Scalar(-1.0f);axis.q=Scale(axis.q,minus);scalar.q=minus.q;}
   Addr(&effects[side][axisIndex].first)->q=func_001FAA00(object,axis.q);
   /* empty asm, allocation-only: two extra refs make the arg and .second store givs outrank objects/points in global-alloc (target s1 store, s2 arg, s3 objects, s4 points); "=m"(scalar) keeps it a non-barrier */U*second=Addr(&effects[side][axisIndex].second);__asm__("" : "=m"(scalar) : "r"(&effects[side][axisIndex]),"r"(second));
   second->q=func_001FAA48(object,Addr(&points[side])->q,axis.q);
   VE*method=&p->vt[69];method->fn((P*)((char*)p+method->delta),&effects[side][axisIndex],*point,&velocity[side]);
  }
  relative[axisIndex].q=Sub(velocity[0].q,velocity[1].q);
 }
 const U*rows=D_002A2D00;
 for(axisIndex=0;axisIndex<3;axisIndex++){
  float*row=matrix[axisIndex];
  const U*basis=rows;
  int column=3;
  while(--column>=0){qword value=basis->q;StoreDot(row,value,relative[axisIndex].q);row++;basis++;}
  {float*in=input+axisIndex;rhs[axisIndex]=*in;}
 }
 CroutDecomp(3,&matrix[0][0],&decomposed[0][0]);
 CroutSolve(3,&decomposed[0][0],rhs,weights);
 VU_FLOAT x=VuFloatFromMemWord(*(int*)&weights[0]),y=VuFloatFromMemWord(*(int*)&weights[1]),z=VuFloatFromMemWord(*(int*)&weights[2]);
 for(side=0;side<2;side++){
  out[side].first.q=Sum3(&effects[side][0].first,&effects[side][1].first,&effects[side][2].first,x,y,z,&scalar).q;
  out[side].second.q=Sum3(&effects[side][0].second,&effects[side][1].second,&effects[side][2].second,x,y,z,&scalar).q;
 }
 
}
