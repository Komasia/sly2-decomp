// func_001728B0 lanef7v1 (Claude agent, 2026-10-24): codex18v2 statement order converted to clean C; aligned 43, one pin (Radial scalar vf4), no instruction asm.

typedef int qword __attribute__((mode(TI)));
typedef union U{qword q;float f[4];int i[4];}U;
typedef struct NODE{char pad0[0xE0];struct NODE*nextE0;char padE4[4];unsigned flags;char padEC[0x18];struct NODE*next104;char pad108[4];float reach;char pad110[0x64];struct NODE*next174;char pad178[0x3C];struct NODE*next1B4;}NODE;
typedef struct PAIR{U candidate,original;}PAIR;
typedef struct P{char pad0[0x10];NODE*actor;char pad14[0x28];float time;char pad40[0x10];PAIR pair[4];int index;}P;
typedef struct ROW{U point;float angle;}ROW;
typedef struct QUERY{U point;float heading;unsigned count;ROW row[64];U candidate,delta,scalar;}QUERY;
typedef struct WORK{QUERY query;NODE*result256[256];NODE*result32[32];NODE*result128[128];U origin,anchor;}WORK;
typedef struct LM{float low,high;}LM;
extern NODE*D_003E13FC,*D_003E13F0,*D_003E1408,*D_003E13E4,*D_003E13C0,*D_003E13D8,*D_003E13CC,*D_003E13B4,*D_003E1450;
extern char D_003DD490;
extern qword D_002A2DA0,D_002A2DC0;
extern float D_002A53D0;
extern LM D_002BE5A8,D_002BE5B0;
extern qword func_001A62E8(NODE*);extern float func_00204740(NODE*);
extern int func_00172798(QUERY*);
extern void func_001E6F60(NODE*,qword,void*,qword*,qword*,float*,float*);
extern int func_00132B10(NODE*,int);
extern int func_0015E9C8(void*,int,int,NODE*,int,NODE**);
extern int func_00172888(ROW*,ROW*);
extern void func_002338C0(void*,unsigned,unsigned,int(*)(ROW*,ROW*));
extern qword func_0011E1A0(float,float,float);extern float func_0011D448(float,float);
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Broadcast(float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline float X(qword a){float f;__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(a));return f;}
static inline float XY(qword a){qword d;__asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(d):"j"(a));__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(d):"j"(d));return X(d);}
static inline qword Length(qword v){qword d,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=j"(one):"j"(v));__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(d):"j"(d));return d;}
static inline qword VFI(int g){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(g));return r;}
static inline float GetX(qword q){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(q));return f;}
static inline qword DivQ(qword v,qword l){qword r;__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(v),"j"(l));return r;}
static inline qword AddScaled(qword a,qword v,qword s){qword r;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(v),"j"(s));return r;}
static inline qword Radial(QUERY*q,NODE*object,qword position){
 qword len,value,fallback=D_002A2DA0;
 register qword scalar __asm__("vf4"); /* register tie */
 q->delta.q=Sub(q->point.q,position);q->delta.i[2]=0;
 len=Length(q->delta.q);
 scalar=VFI(*(int*)&object->reach);
 if(GetX(len)<0.0001f){q->scalar.q=scalar;value=fallback;}
 else{q->scalar.q=scalar;value=DivQ(q->delta.q,len);}
 return AddScaled(position,value,scalar);
}
static inline qword Dot(qword a,qword b){qword d,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=j"(one):"j"(a),"j"(b));return d;}
static inline qword Scale(qword v,qword s){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(s));return r;}
/* volatile: the target re-broadcasts the constant inside the loop (loop.c must not hoist it) */
static inline qword VFV(float g){qword r;__asm__ __volatile__("qmtc2.ni %1,%0":"=j"(r):"r"(g));return r;}
static inline qword OffsetTarget(qword root,qword item,U*scalar){
 qword up=D_002A2DC0,delta,planar,value,fallback,s,target;
 delta=Sub(item,root);
 planar=Dot(delta,up);
 fallback=D_002A2DA0;
 planar=Scale(up,planar);
 planar=Sub(delta,planar);
 value=Length(planar);
 if(GetX(value)<0.0001f)planar=fallback;
 else planar=DivQ(planar,value);
 s=VFV(200.0f);
 target=AddScaled(root,planar,s);
 scalar->q=s;return target;
}
void func_001728B0(P*p){
 WORK w;NODE*object;NODE**cursor;int remaining,i;unsigned accepted;float lastAngle;
 w.query.point.q=func_001A62E8(p->actor);
 w.query.heading=func_00204740(p->actor);w.query.count=0;
 for(object=D_003E13FC;object;object=object->next104){
  qword origin=func_001A62E8(object);
  w.query.candidate.q=Radial(&w.query,object,origin);
  func_00172798(&w.query);
 }
 for(object=D_003E13F0;object;object=object->next1B4){func_001E6F60(object,w.query.point.q,0,&w.query.candidate.q,0,0,0);func_00172798(&w.query);}
 for(object=D_003E1408;object;object=object->next104){w.query.candidate.q=func_001A62E8(object);func_00172798(&w.query);}
 for(object=D_003E13E4;object;object=object->next174){w.query.candidate.q=func_001A62E8(object);func_00172798(&w.query);}
 for(object=D_003E13C0;object;object=object->next1B4){func_001E6F60(object,w.query.point.q,0,&w.query.candidate.q,0,0,0);func_00172798(&w.query);}
 for(object=D_003E13D8;object;object=object->next104){w.query.candidate.q=func_001A62E8(object);func_00172798(&w.query);}
 for(object=D_003E13CC;object;object=object->next1B4){func_001E6F60(object,w.query.point.q,0,&w.query.candidate.q,0,0,0);func_00172798(&w.query);}
 for(object=D_003E13B4;object;object=object->nextE0){
  if((object->flags&1)&&func_00132B10(object,0x13)){w.query.candidate.q=func_001A62E8(object);func_00172798(&w.query);}
 }
 {int count=func_0015E9C8(&D_003DD490,0x505,0x23,0,0x100,w.result256);
 if(count>0){cursor=w.result256;remaining=count;do{NODE*item=*cursor++;--remaining;w.query.candidate.q=func_001A62E8(item);func_00172798(&w.query);}while(remaining);}}
 {int count=func_0015E9C8(&D_003DD490,0x505,0x67,0,0x20,w.result32);
 if(count>0){cursor=w.result32;remaining=count;do{NODE*item=*cursor++;--remaining;w.query.candidate.q=func_001A62E8(item);func_00172798(&w.query);}while(remaining);}}
 {int count=func_0015E9C8(&D_003DD490,0x505,0x1B,0,0x80,w.result128);
 if(count>0){cursor=w.result128;remaining=count;do{NODE*item=*cursor++;--remaining;w.query.candidate.q=func_001A62E8(item);func_00172798(&w.query);}while(remaining);}}
 for(object=D_003E1450;object;object=object->next174){w.query.candidate.q=func_001A62E8(object);func_00172798(&w.query);}
 lastAngle=0.0f;
 func_002338C0(w.query.row,w.query.count,sizeof(ROW),func_00172888);
 accepted=0;
 {
  PAIR*previous=0;qword root=w.query.point.q;
  for(i=0;i<(int)w.query.count&&accepted<4;i++){
   ROW*row=&w.query.row[i];qword original=row->point.q;
   {qword target=OffsetTarget(root,original,&w.query.delta);
    if(previous&&XY(Sub(target,previous->candidate.q))<150.0f)continue;
    previous=&p->pair[accepted++];lastAngle=row->angle;previous->original.q=original;previous->candidate.q=target;
   }
  }
 }
 w.origin.q=w.query.point.q;
 w.anchor.q=Add(w.origin.q,func_0011E1A0(w.query.heading+3.1415927f,-350.0f,0.0f));

 while(accepted<4){
  float angle,length;qword point;
  lastAngle+=func_0011D448(D_002BE5A8.low,D_002BE5A8.high);
  angle=lastAngle+w.query.heading;
  length=func_0011D448(D_002BE5B0.low,D_002BE5B0.high);
  point=Add(w.anchor.q,func_0011E1A0(angle,length,0.0f));
  p->pair[accepted].original.q=point;p->pair[accepted].candidate.q=point;accepted++;
 }
 p->index=0;p->time=D_002A53D0;
}

typedef char qword_Size[(sizeof(qword)==16)?1:-1];
typedef char Pointer_Size[(sizeof(void*)==4)?1:-1];
typedef char U_Size[(sizeof(U)==16)?1:-1];
typedef char NODE_Size[(sizeof(NODE)==0x1B8)?1:-1];
typedef char PAIR_Size[(sizeof(PAIR)==0x20)?1:-1];
typedef char P_Size[(sizeof(P)==0xE0)?1:-1];
typedef char ROW_Size[(sizeof(ROW)==0x20)?1:-1];
typedef char QUERY_Size[(sizeof(QUERY)==0x850)?1:-1];
typedef char WORK_Size[(sizeof(WORK)==0xEF0)?1:-1];
typedef char LM_Size[(sizeof(LM)==8)?1:-1];
typedef char Result256_Size[(sizeof(NODE*[256])==0x400)?1:-1];
typedef char Result32_Size[(sizeof(NODE*[32])==0x80)?1:-1];
typedef char Result128_Size[(sizeof(NODE*[128])==0x200)?1:-1];
typedef char Rows_Size[(sizeof(ROW[64])==0x800)?1:-1];
typedef char Pairs_Size[(sizeof(PAIR[4])==0x80)?1:-1];
typedef char NODE_nextE0_Offset[((unsigned)&((NODE*)0)->nextE0==224)?1:-1];
typedef char NODE_flags_Offset[((unsigned)&((NODE*)0)->flags==232)?1:-1];
typedef char NODE_next104_Offset[((unsigned)&((NODE*)0)->next104==260)?1:-1];
typedef char NODE_reach_Offset[((unsigned)&((NODE*)0)->reach==268)?1:-1];
typedef char NODE_next174_Offset[((unsigned)&((NODE*)0)->next174==372)?1:-1];
typedef char NODE_next1B4_Offset[((unsigned)&((NODE*)0)->next1B4==436)?1:-1];
typedef char PAIR_candidate_Offset[((unsigned)&((PAIR*)0)->candidate==0)?1:-1];
typedef char PAIR_original_Offset[((unsigned)&((PAIR*)0)->original==16)?1:-1];
typedef char P_actor_Offset[((unsigned)&((P*)0)->actor==16)?1:-1];
typedef char P_time_Offset[((unsigned)&((P*)0)->time==60)?1:-1];
typedef char P_pair_Offset[((unsigned)&((P*)0)->pair==80)?1:-1];
typedef char P_index_Offset[((unsigned)&((P*)0)->index==208)?1:-1];
typedef char ROW_point_Offset[((unsigned)&((ROW*)0)->point==0)?1:-1];
typedef char ROW_angle_Offset[((unsigned)&((ROW*)0)->angle==16)?1:-1];
typedef char QUERY_point_Offset[((unsigned)&((QUERY*)0)->point==0)?1:-1];
typedef char QUERY_heading_Offset[((unsigned)&((QUERY*)0)->heading==16)?1:-1];
typedef char QUERY_count_Offset[((unsigned)&((QUERY*)0)->count==20)?1:-1];
typedef char QUERY_row_Offset[((unsigned)&((QUERY*)0)->row==32)?1:-1];
typedef char QUERY_candidate_Offset[((unsigned)&((QUERY*)0)->candidate==2080)?1:-1];
typedef char QUERY_delta_Offset[((unsigned)&((QUERY*)0)->delta==2096)?1:-1];
typedef char QUERY_scalar_Offset[((unsigned)&((QUERY*)0)->scalar==2112)?1:-1];
typedef char WORK_query_Offset[((unsigned)&((WORK*)0)->query==0)?1:-1];
typedef char WORK_result256_Offset[((unsigned)&((WORK*)0)->result256==2128)?1:-1];
typedef char WORK_result32_Offset[((unsigned)&((WORK*)0)->result32==3152)?1:-1];
typedef char WORK_result128_Offset[((unsigned)&((WORK*)0)->result128==3280)?1:-1];
typedef char WORK_origin_Offset[((unsigned)&((WORK*)0)->origin==3792)?1:-1];
typedef char WORK_anchor_Offset[((unsigned)&((WORK*)0)->anchor==3808)?1:-1];
typedef char LM_low_Offset[((unsigned)&((LM*)0)->low==0)?1:-1];
typedef char LM_high_Offset[((unsigned)&((LM*)0)->high==4)?1:-1];
