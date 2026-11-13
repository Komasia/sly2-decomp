// PosSurroundPlace__FP5GUARDP9NAVREGIONG9VU_VECTORf MATCH (Claude agent lane H14), no pins: laneH13v2 with the inner loop as `int k=0;int i=hits;do{SEGMENT*base=segments;Closest(target,&base[k],...);...;k++;}while(--i);`. base is its own pseudo inside the do-body (cse block after the loop label, so not shared with the 1C0A40 call arg, which stays `addiu t0,sp,0x50`); loop.c hoists it to the inner preheader, the &base[k] giv is then initialised as a copy of it, and pass 1 hoists base once more into the index-loop preheader (s4), like the target.
// PosSurroundPlace__FP5GUARDP9NAVREGIONG9VU_VECTORf laneH13v2 (Claude agent lane H13): inner loop `SEGMENT*segment=base;int i=hits;do{...segment++;}while(--i);` with a function-scope `SEGMENT*base=segments;` so cse cannot share &segments with the 1C0A40 call arg (rematerialized like the target), 22 -> 17. Left: base is set before the mode loop (s6) instead of the index-loop preheader (target s4), which shifts s-reg roles.
// PosSurroundPlace__FP5GUARDP9NAVREGIONG9VU_VECTORf laneH12v1 (Claude agent lane H12): laneH11v2 + `U point` at function scope between selected and segments, and the two VU scales passed as a qword (QwFromMemWord) into QwOffset(base,v,const qword&g,U*scratch) that stores g into point (target sqc2 0x40): frame and the whole VU block exact (82 -> 72 differing, aligned 26).
// PosSurroundPlace__FP5GUARDP9NAVREGIONG9VU_VECTORf laneH11v2 (Claude agent lane H11): laneH6v1 + 11EE08 call via inline Closest(qword,const SEGMENT*,U&,float&) (55->33) + plain QwAddScaled with `U point` declared mid-block before `if(hits>0)` (frame 0x460 exact, 33->26).
// PosSurroundPlace__FP5GUARDP9NAVREGIONG9VU_VECTORf laneH6v1 (Claude agent lane H6): fresh Lilly-style rewrite, no pins, VU helper asms only. aligned 55 (old .c 81, which used lw/lqc2 instruction asms).
// Left: frame 0x480 vs 0x460 (VU_FLOAT temps get their own slot 0x370; target stores them into point at 0x40), region spilled instead of fp, &point/&distance hoisted by loop.c into s-regs (target rematerializes them).
typedef int qword __attribute__((mode(TI)));
union U{qword q;float f[4];int i[4];};
struct LM{float low,high;};
struct TUNING{char pad[0x10];int override;float narrow,wide;};
struct SCALE{char pad[0x20];float value;};
struct ACTOR{char pad31C[0x31C];LM first,second;char pad32C[0x3CC-0x32C];TUNING*tuning;char pad3D0[0xFBC-0x3D0];int mode;char padFC0[4];SCALE*scale;};
struct P{char pad[0x10];ACTOR*actor;};
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
extern "C" qword PosSurroundPlace__FP5GUARDP9NAVREGIONG9VU_VECTORf(P*p,void*region,qword origin,float heading){
 U closest;LM first,second,selected;U point;SEGMENT segments[8];FLOW flow;
 TUNING*tuning;
 first=p->actor->first;second=p->actor->second;
 if(p->actor->mode==8||p->actor->mode==13){
  SCALE*scale=p->actor->scale;
  if(scale){float factor=scale->value;first.low*=factor;first.high*=factor;second.low*=factor;second.high*=factor;}
 }
 tuning=p->actor->tuning;
 ConvertVectorToCylind(QwSub(PosOfLo(p->actor),origin),&flow.polarAngle,&flow.polarLength,0);
 float angle=heading+GLimitAbs(RadNormalize(flow.polarAngle-heading),tuning->narrow);
 float length=GLimitLm(&first,flow.polarLength);
 if(FKeepOnNav(region,QwAdd(origin,SetVectorCylind(angle,length,0.0f)),&closest.q)){
  ConvertVectorToCylind(QwSub(closest.q,origin),&flow.candidateAngle,&flow.candidateLength,0);
  if(__builtin_fabsf(RadNormalize(flow.candidateAngle-heading))<tuning->wide&&FCheckLm(&second,flow.candidateLength))return closest.q;
 }
 qword target,best;
 int mode;
 for(mode=0;mode<3;mode++){
  int count;float limit;
  switch(mode){
  case 0:selected=first;count=10;limit=tuning->narrow;break;
  case 1:selected=second;count=10;limit=tuning->wide;break;
  case 2:selected.low=0.0f;selected.high=second.high;count=15;limit=3.14159265f;break;
  }
  if(tuning->override==-1)limit=3.14159265f;
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
