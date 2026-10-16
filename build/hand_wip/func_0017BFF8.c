
typedef int qword __attribute__((mode(TI)));
typedef union{qword q;float f[4];}U;
struct LM{float low,high;};
struct TUNING{char pad[0x10];int override;float narrow,wide;};
struct SCALE{char pad[0x20];float value;};
struct ACTOR{char pad31C[0x31C];struct LM first,second;char pad32C[0x3CC-0x32C];struct TUNING*tuning;char pad3D0[0xFBC-0x3D0];int mode;char padFC0[4];struct SCALE*scale;};
struct P{char pad[0x10];struct ACTOR*actor;};
struct FLOW{float polarAngle,polarLength,candidateAngle,candidateLength,distance;};
struct SEGMENT{qword a,b;char data[0x40];};
extern float D_002A5600;
qword func_001A62E8(struct ACTOR*);
void func_0011EF08(qword,float*,float*,float*);
float func_0011CF60(float);float func_0011CFE0(float,float);float func_0011D948(struct LM*,float);
qword func_0011E1A0(float,float,float);int func_0011D910(struct LM*,float);
int func_001C0B50(void*,qword,qword*);
int func_001C0A40(void*,qword,qword,int,struct SEGMENT*);
void func_0011EE08(qword,qword,qword,qword*,float*,float*);
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline int Word(const float*address){int word;__asm__("lw %0,%1":"=r"(word):"m"(*address));return word;}
static inline qword Broadcast(U*out,int bits){qword scalar;__asm__("qmtc2.ni %1,%0":"=j"(scalar):"r"(bits));out->q=scalar;return out->q;}
static inline qword Offset(const qword*point,qword direction,qword scalar){
 qword p;__asm__("lqc2 %0,%1":"=j"(p):"m"(*point));
 __asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(p):"j"(direction),"j"(scalar));return p;
}
qword func_0017BFF8(struct P*p,void*region,qword origin,float heading){
 U closest;struct LM first,second,selected;U scratch;struct SEGMENT segments[8];
 struct FLOW flow;float chosenAngle,chosenLength;
 struct TUNING*tuning;
 int mode,count,index;float angleLimit,bestDistance,midpoint;
 qword bestPoint,target;
 first=p->actor->first;second=p->actor->second;
 if(p->actor->mode==8||p->actor->mode==13){if(p->actor->scale){float factor=p->actor->scale->value;first.low*=factor;first.high*=factor;second.low*=factor;second.high*=factor;}}
 tuning=p->actor->tuning;
 func_0011EF08(Sub(func_001A62E8(p->actor),origin),&flow.polarAngle,&flow.polarLength,0);
 chosenAngle=heading+func_0011CFE0(func_0011CF60(flow.polarAngle-heading),tuning->narrow);
 chosenLength=func_0011D948(&first,flow.polarLength);
 if(func_001C0B50(region,Add(origin,func_0011E1A0(chosenAngle,chosenLength,0.0f)),&closest.q)){
  func_0011EF08(Sub(closest.q,origin),&flow.candidateAngle,&flow.candidateLength,0);
  if(__builtin_fabsf(func_0011CF60(flow.candidateAngle-heading))<tuning->wide&&func_0011D910(&second,flow.candidateLength))return closest.q;
 }
 for(mode=0;mode<3;mode++){
  switch(mode){
  case 0:selected=first;count=10;angleLimit=tuning->narrow;break;
  case 1:selected=second;count=10;angleLimit=tuning->wide;break;
  case 2:selected.low=0.0f;selected.high=second.high;count=15;angleLimit=3.14159265f;break;
  }
  if(tuning->override==-1)angleLimit=3.14159265f;
  bestDistance=D_002A5600;
  midpoint=(count-1)*0.5f;
  for(index=0;index<count;index++){
   qword direction=func_0011E1A0(heading+(index/midpoint-1.0f)*angleLimit,1.0f,0.0f);
   qword endHigh=Offset(&origin,direction,Broadcast(&scratch,Word(&selected.high)));
   qword endLow=Offset(&origin,direction,Broadcast(&scratch,Word(&selected.low)));
   int hits=func_001C0A40(region,endLow,endHigh,8,segments);
   struct SEGMENT*segment=segments;
   while(hits>0){
    func_0011EE08(target,segment->a,segment->b,&scratch.q,0,&flow.distance);
    if(flow.distance<bestDistance){bestDistance=flow.distance;bestPoint=scratch.q;}
    hits--;segment++;
   }
  }
  if(bestDistance!=D_002A5600)return bestPoint;
 }
 if(func_001C0B50(region,origin,&closest.q))return closest.q;
 return origin;
}

typedef char qword_Size[(sizeof(qword)==16)?1:-1];
typedef char U_Size[(sizeof(U)==16)?1:-1];
typedef char LM_Size[(sizeof(struct LM)==8)?1:-1];
typedef char SEGMENT_Size[(sizeof(struct SEGMENT)==0x60)?1:-1];
typedef char FLOW_Size[(sizeof(struct FLOW)==20)?1:-1];
typedef char Segment_Buffer_Size[(sizeof(struct SEGMENT[8])==0x300)?1:-1];
typedef char LM_low_Offset[((unsigned)&((struct LM*)0)->low==0)?1:-1];
typedef char LM_high_Offset[((unsigned)&((struct LM*)0)->high==4)?1:-1];
typedef char TUNING_override_Offset[((unsigned)&((struct TUNING*)0)->override==16)?1:-1];
typedef char TUNING_narrow_Offset[((unsigned)&((struct TUNING*)0)->narrow==20)?1:-1];
typedef char TUNING_wide_Offset[((unsigned)&((struct TUNING*)0)->wide==24)?1:-1];
typedef char SCALE_value_Offset[((unsigned)&((struct SCALE*)0)->value==32)?1:-1];
typedef char ACTOR_first_Offset[((unsigned)&((struct ACTOR*)0)->first==796)?1:-1];
typedef char ACTOR_second_Offset[((unsigned)&((struct ACTOR*)0)->second==804)?1:-1];
typedef char ACTOR_tuning_Offset[((unsigned)&((struct ACTOR*)0)->tuning==972)?1:-1];
typedef char ACTOR_mode_Offset[((unsigned)&((struct ACTOR*)0)->mode==4028)?1:-1];
typedef char ACTOR_scale_Offset[((unsigned)&((struct ACTOR*)0)->scale==4036)?1:-1];
typedef char P_actor_Offset[((unsigned)&((struct P*)0)->actor==16)?1:-1];
typedef char SEGMENT_a_Offset[((unsigned)&((struct SEGMENT*)0)->a==0)?1:-1];
typedef char SEGMENT_b_Offset[((unsigned)&((struct SEGMENT*)0)->b==16)?1:-1];
typedef char FLOW_polarAngle_Offset[((unsigned)&((struct FLOW*)0)->polarAngle==0)?1:-1];
typedef char FLOW_polarLength_Offset[((unsigned)&((struct FLOW*)0)->polarLength==4)?1:-1];
typedef char FLOW_candidateAngle_Offset[((unsigned)&((struct FLOW*)0)->candidateAngle==8)?1:-1];
typedef char FLOW_candidateLength_Offset[((unsigned)&((struct FLOW*)0)->candidateLength==12)?1:-1];
typedef char FLOW_distance_Offset[((unsigned)&((struct FLOW*)0)->distance==16)?1:-1];
