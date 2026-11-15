/* PosSurroundPlace: where the guard should stand around the target at origin facing heading: its own direction from
 * the target, limited to the target record's narrow angle (+0x14) and the guard's near range (+0x31C, both ranges
 * scaled by its scale controller in modes 8 / 13), kept on the navigation region - taken when that lands within the
 * wide angle (+0x18) and the surround range (+0x324). Otherwise rays are cast (10 within the near range and the
 * narrow angle, 10 within the surround range and the wide angle, then 15 all around; all around when +0x10 is -1) and
 * the free-navigation segment point nearest the target wins; failing all, the origin kept on the navigation region,
 * or the origin. SafeHouse port (aipursuit.cpp PosSurroundPlace).
 * Matching notes (Claude agent lanes H6..H14): no register pins, only VU helper asms; the inner loop is
 * `int k=0;int i=hits;do{SEGMENT*base=segments;Closest(target,&base[k],...);...;k++;}while(--i);` so base stays its
 * own pseudo in the do-body (not shared with the AtFreeNav call's &segments) and loop.c hoists it like the target;
 * `U point` sits between selected and segments and the two VU scales go through QwOffset(), which stores g into point
 * (the target's sqc2 0x40), giving the 0x460 frame. */
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];int i[4];};
struct LM{float low,high;};
struct TARGETREC{char pad[0x10];int n10;float radNarrow,radWide;};
struct SCALE{char pad[0x20];float value;};
struct ACTOR{char pad31C[0x31C];LM lmNear,lmSurround;char pad32C[0x3CC-0x32C];TARGETREC*ptarget;char pad3D0[0xFBC-0x3D0];int nMode;char padFC0[4];SCALE*pscale;};
struct JOBSURROUND{char pad[0x10];ACTOR*pguard;};
struct FLOW{float polarAngle,polarLength,candidateAngle,candidateLength,distance;};
struct SEGMENT{qword a,b;char data[0x40];};
extern "C"{
extern float D_002A5600;
qword PosOfLo(ACTOR*) asm("PosOfLo__FP2LO");
void ConvertVectorToCylind(qword,float*,float*,float*) asm("ConvertVectorToCylind__FG9VU_VECTORPfN21");
float RadNormalize(float) asm("RadNormalize__Ff");float GLimitAbs(float,float) asm("GLimitAbs__Fff");float GLimitLm(LM*,float) asm("GLimitLm__FP2LMf");
qword SetVectorCylind(float,float,float) asm("SetVectorCylind__Ffff");int FCheckLm(LM*,float) asm("FCheckLm__FP2LMf");
int FKeepOnNav(void*,qword,qword*) asm("FKeepOnNav__FP9NAVREGIONG9VU_VECTORP6VECTOR");
int AtFreeNav(void*,qword,qword,int,SEGMENT*) asm("AtFreeNav__FP9NAVREGIONG9VU_VECTORT1ii");
void PosNearestSegment(qword,qword,qword,qword*,float*,float*) asm("PosNearestSegment__FG9VU_VECTORN20P6VECTORN23");
}
struct VU_FLOAT{qword qw;};
static inline VU_FLOAT VuFloatFromMemWord(int n){VU_FLOAT v;__asm__("qmtc2.ni %1,%0":"=j"(v.qw):"rV"(n));return v;}
static inline qword QwAdd(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword QwSub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword QwOffset(qword base,qword v,const qword&g,U*scratch){scratch->q=g;qword r;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(base),"j"(v),"j"(g));return r;}
static inline qword QwFromMemWord(int n){qword v;__asm__("qmtc2.ni %1,%0":"=j"(v):"rV"(n));return v;}
static inline qword QwAddScaled(qword base,qword v,VU_FLOAT g){qword r;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(base),"j"(v),"j"(g.qw));return r;}

static inline void Closest(qword t,const SEGMENT*s,U&pt,float&d){PosNearestSegment(t,s->a,s->b,&pt.q,0,&d);}
// name: SafeHouse port (PosSurroundPlace)
extern "C" qword PosSurroundPlace__FP5GUARDP9NAVREGIONG9VU_VECTORf(JOBSURROUND*p,void*region,qword origin,float heading){
 U closest;LM lmNear,lmSurround,selected;U point;SEGMENT segments[8];FLOW flow;
 TARGETREC*ptarget;
 lmNear=p->pguard->lmNear;lmSurround=p->pguard->lmSurround;
 if(p->pguard->nMode==8||p->pguard->nMode==13){
  SCALE*scale=p->pguard->pscale;
  if(scale){float factor=scale->value;lmNear.low*=factor;lmNear.high*=factor;lmSurround.low*=factor;lmSurround.high*=factor;}
 }
 ptarget=p->pguard->ptarget;
 ConvertVectorToCylind(QwSub(PosOfLo(p->pguard),origin),&flow.polarAngle,&flow.polarLength,0);
 float angle=heading+GLimitAbs(RadNormalize(flow.polarAngle-heading),ptarget->radNarrow);
 float length=GLimitLm(&lmNear,flow.polarLength);
 if(FKeepOnNav(region,QwAdd(origin,SetVectorCylind(angle,length,0.0f)),&closest.q)){
  ConvertVectorToCylind(QwSub(closest.q,origin),&flow.candidateAngle,&flow.candidateLength,0);
  if(__builtin_fabsf(RadNormalize(flow.candidateAngle-heading))<ptarget->radWide&&FCheckLm(&lmSurround,flow.candidateLength))return closest.q;
 }
 qword target,best;
 int mode;
 for(mode=0;mode<3;mode++){
  int count;float limit;
  switch(mode){
  case 0:selected=lmNear;count=10;limit=ptarget->radNarrow;break;
  case 1:selected=lmSurround;count=10;limit=ptarget->radWide;break;
  case 2:selected.low=0.0f;selected.high=lmSurround.high;count=15;limit=3.14159265f;break;
  }
  if(ptarget->n10==-1)limit=3.14159265f;
  float bestDistance=D_002A5600;
  int index;
  for(index=0;index<count;index++){
   qword direction=SetVectorCylind(heading+(-1.0f+index/((count-1)*0.5f))*limit,1.0f,0.0f);
   int hits=AtFreeNav(region,QwOffset(origin,direction,QwFromMemWord(*(int*)&selected.low),&point),QwOffset(origin,direction,QwFromMemWord(*(int*)&selected.high),&point),8,segments);
   if(hits>0){
    int k=0;int i=hits;
    do{
     SEGMENT*base=segments;
     Closest(target,&base[k],point,flow.distance);
     if(flow.distance<bestDistance){best=point.q;bestDistance=flow.distance;}
     k++;
    }while(--i);
   }
  }
  if(bestDistance!=D_002A5600)return best;
 }
 if(FKeepOnNav(region,origin,&closest.q))return closest.q;
 return origin;
}
