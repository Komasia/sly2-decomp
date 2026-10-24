// func_0018F958 (Claude agent, lane J4, 2026-10-24): aligned 63 but store giv now sp+(t+0x50) with stores at -0x10/0 like the target (stores through Addr(&effects[side][axisIndex].first/.second)). Inner s-reg roles still differ.
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
static inline qword Scalar(float value){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(value));return q;}
static inline qword Scale(const qword&value,const qword&amount){qword q;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(q):"j"(value),"j"(amount));return q;}
static inline qword Sub(const qword&first,const qword&second){qword q;__asm__("vsub.xyzw %0,%1,%2":"=j"(q):"j"(first),"j"(second));return q;}
static inline void StoreDot(float*out,qword a,const qword&b){qword one;int bits;__asm__("vmul.xyz %1,%1,%3\n\tvaddw.x %2,$vf0,$vf0w\n\tvadday.x $ACC,%1,%1y\n\tvmaddz.x %1,%2,%1z\n\tqmfc2.ni %0,%1":"=&r"(bits),"+j"(a),"=j"(one):"j"(b));*(int*)out=bits;}
static inline qword VuFloatFromMemWord(int n){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"rV"(n));return q;}
static inline qword Sum3(const U*a,const U*b,const U*c,const qword&x,const qword&y,const qword&z,U*scalar){scalar->q=x;qword va=a->q;scalar->q=y;qword vb=b->q;scalar->q=z;qword vc=c->q;qword out;__asm__("vmulax.xyzw $ACC,%1,%4x\n\tvmaddax.xyzw $ACC,%2,%5x\n\tvmaddx.xyzw %0,%3,%6x":"=j"(out):"j"(va),"j"(vb),"j"(vc),"j"(x),"j"(y),"j"(z));return out;}
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
  DELTA(*table)[3]=effects;DELTA*response=&effects[0][axisIndex];
  for(side=0;side<2;side++){
   P*object=objects[side];axis.q=D_002A2D00[axisIndex].q;
   if(side==1){qword minus=Scalar(-1.0f);axis.q=Scale(axis.q,minus);scalar.q=minus;}
   Addr(&effects[side][axisIndex].first)->q=func_001FAA00(object,axis.q);
   Addr(&effects[side][axisIndex].second)->q=func_001FAA48(object,Addr(&points[side])->q,axis.q);
   VE*method=&p->vt[69];method->fn((P*)((char*)p+method->delta),response,*point,&velocity[side]);response+=3;
  }
  relative[axisIndex].q=Sub(velocity[0].q,velocity[1].q);
 }
 for(axisIndex=0;axisIndex<3;axisIndex++){
  float*row=matrix[axisIndex];
  const U*basis=D_002A2D00;
  int column=3;
  while(--column>=0){qword value=basis->q;StoreDot(row,value,relative[axisIndex].q);row++;basis++;}
  rhs[axisIndex]=input[axisIndex];
 }
 CroutDecomp(3,&matrix[0][0],&decomposed[0][0]);
 CroutSolve(3,&decomposed[0][0],rhs,weights);
 qword x=VuFloatFromMemWord(*(int*)&weights[0]),y=VuFloatFromMemWord(*(int*)&weights[1]),z=VuFloatFromMemWord(*(int*)&weights[2]);
 for(side=0;side<2;side++){
  out[side].first.q=Sum3(&effects[side][0].first,&effects[side][1].first,&effects[side][2].first,x,y,z,&scalar);
  out[side].second.q=Sum3(&effects[side][0].second,&effects[side][1].second,&effects[side][2].second,x,y,z,&scalar);
 }
}
