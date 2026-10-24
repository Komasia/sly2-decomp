// func_0018F958 (Claude agent, lane H5, 2026-10-24): fresh rewrite in Lilly's style (VU_FLOAT by-value temps at 0x1D0).
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];};
struct DELTA{U first,second;};
struct P;
struct VTE{short delta,pad;void(*fn)(P*,DELTA*,qword,U*);};
struct P{char pad[12];VTE*vt;};
struct VU_FLOAT{qword qw;};
extern "C"{
qword func_001A62E8(P*);
qword func_001FAA00(P*,qword);
qword func_001FAA48(P*,qword,qword);
extern U D_002A2D00[3];
}
void CroutDecomp(int,float*,float*);
void CroutSolve(int,float*,float*,float*);
static inline VU_FLOAT VuFloat(float g){VU_FLOAT v;__asm__("qmtc2.ni %1,%0":"=j"(v.qw):"r"(g));return v;}
static inline VU_FLOAT VuFloatFromMemWord(int n){VU_FLOAT v;__asm__("qmtc2.ni %1,%0":"=j"(v.qw):"rV"(n));return v;}
static inline qword QwScaleX(qword a,VU_FLOAT g){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(g.qw));return r;}
static inline qword QwSub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword QwDot(qword a,qword b){qword r,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=j"(one):"j"(a),"j"(b));return r;}
static inline qword QwCombo3(VU_FLOAT x,qword a,VU_FLOAT y,qword b,VU_FLOAT z,qword c){qword r;__asm__("vmulax.xyzw $ACC,%2,%1x\n\tvmaddax.xyzw $ACC,%4,%3x\n\tvmaddx.xyzw %0,%6,%5x":"=j"(r):"j"(x.qw),"j"(a),"j"(y.qw),"j"(b),"j"(z.qw),"j"(c));return r;}
extern "C" void func_0018F958(P*p,P*other,qword*point,float*input,DELTA*out){
 P*objects[2];U points[2];U axis;
 DELTA effects[2][3];U velocity[2];U relative[3];
 float matrix[3][3],decomposed[3][3],rhs[3],weights[3];
 int axisIndex,side,column;
 objects[0]=p;objects[1]=other;
 points[0].q=func_001A62E8(p);points[1].q=*point;
 for(axisIndex=0;axisIndex<3;axisIndex++){
  for(side=0;side<2;side++){
   P*object=objects[side];
   axis.q=D_002A2D00[axisIndex].q;
   if(side==1)axis.q=QwScaleX(axis.q,VuFloat(-1.0f));
   effects[side][axisIndex].first.q=func_001FAA00(object,axis.q);
   effects[side][axisIndex].second.q=func_001FAA48(object,points[side].q,axis.q);
   VTE*e=&p->vt[69];
   e->fn((P*)((char*)p+e->delta),&effects[side][axisIndex],*point,&velocity[side]);
  }
  relative[axisIndex].q=QwSub(velocity[0].q,velocity[1].q);
 }
 for(axisIndex=0;axisIndex<3;axisIndex++){
  for(column=0;column<3;column++)
   *(int*)&matrix[axisIndex][column]=(int)QwDot(D_002A2D00[column].q,relative[axisIndex].q);
  rhs[axisIndex]=input[axisIndex];
 }
 CroutDecomp(3,&matrix[0][0],&decomposed[0][0]);
 CroutSolve(3,&decomposed[0][0],rhs,weights);
 DELTA(*current)[3]=effects;
 for(side=0;side<2;side++){
  out->first.q=QwCombo3(VuFloatFromMemWord(*(int*)&weights[0]),(*current)[0].first.q,VuFloatFromMemWord(*(int*)&weights[1]),(*current)[1].first.q,VuFloatFromMemWord(*(int*)&weights[2]),(*current)[2].first.q);
  out->second.q=QwCombo3(VuFloatFromMemWord(*(int*)&weights[0]),(*current)[0].second.q,VuFloatFromMemWord(*(int*)&weights[1]),(*current)[1].second.q,VuFloatFromMemWord(*(int*)&weights[2]),(*current)[2].second.q);
  current++;out++;
 }
}
