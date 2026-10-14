typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct VE{short delta,pad;void*fn;};
struct ASEG{char pad0[0x74];float duration;};
struct ASEGA{char pad0[0x1C];float localTime;char pad20[0x40-0x20];float elapsed;char pad44[4];float rate;};
struct EFFECT;struct ACTION;struct SM;struct COMPONENT;
struct NODE{char pad0[12];VE*vt;};
struct TARGET{char pad0[0x130];int exitEffect;};
struct POINT{char pad0[0x70];U position;};
struct BLEND{float incoming,unknown4,unknown8,outgoing,unknown10,unknown14;ASEG*clip;};
struct CLOCK{float t,dt;};
struct P{
 char pad0[0x1028];
 SM * sm;
 char pad102c[0x8];
 COMPONENT * component;
 char pad1038[0x49c];
 ASEG * alternate10;
 ASEG * alternate11;
 char pad14dc[0x2f4];
 char track[0x30];
 ASEG * idle;
 char pad1804[0x7c];
 int reset;
 char pad1884[0x3c];
 int surface;
 TARGET * target;
 int mode;
 char pad18cc[0xc];
 int state;
 float stateTime;
 ASEGA * current;
 int finished;
 char pad18e8[0x4];
 int attack;
 char pad18f0[0xb0];
 NODE * normalNode;
 void * pointObject;
 NODE * alternateNode;
 char pad19ac[0x4];
 float deadline;
 char pad19b4[0xc];
 POINT * point;
 char pad19c4[0x40];
 BLEND blend4;
 BLEND blend5;
 BLEND blend6;
 BLEND blend7;
 ASEG * clip8;
 ASEG * clip9;
 char pad1a7c[0xc];
 ACTION * action;
 char pad1a8c[0x254];
 ASEG * clip12;
 ASEG * clip13;
 ASEG * clip14;
 ASEG * clip15;
 ASEG * clip16;
 ASEG * clip17;
 ASEG * clip18;
 ASEG * clip19;
 ASEG * clip20;
 ASEG * clip21;
 char pad1d08[0xc];
 ASEG * clip22;
 ASEG * clip23;
};
extern "C"{
extern CLOCK D_002DDED0;extern int D_002BF448[];extern float D_002BF430,D_002BF434,D_002BF438,D_002BF43C,D_002BF440;
extern void*D_002E1E44;extern void*D_002E1E48;
void func_001F2AD0(P*,ACTION*);void func_001F4BF8(P*);void func_001CCAC0(void*,int);
EFFECT*func_001FBB90(int);void func_001FB2F8(EFFECT*,void*);void func_001FB3F0(EFFECT*,qword);
qword func_001A62E8(void*);qword func_001A6F00(void*,void*,qword);
void func_0018F560(P*,BLEND*,ASEG*);int func_001F0400(SM*,int);void func_001F09D8(COMPONENT*,int);
void func_001305B8(ASEG*,P*,float,float,int,ASEGA**);void func_00131A90(ASEGA*,float);
}
static __inline__ void Emit(P*p,int id){if(id!=-1){EFFECT*effect=func_001FBB90(id);func_001FB2F8(effect,0);func_001FB3F0(effect,func_001A62E8(p));}}
static __inline__ qword Scalar(float f){qword value;int bits;__asm__("mfc1 %0,%1":"=r"(bits):"f"(f));__asm__("qmtc2.ni %1,%0":"=j"(value):"r"(bits));return value;}
static __inline__ qword Average(const U&first,qword second,const U&half){qword value;__asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%3x":"=j"(value):"j"(first.q),"j"(second),"j"(half.q));return value;}
static __inline__ float Min(float a,float b){float result;__asm__("min.s %0,%1,%2":"=f"(result):"f"(a),"f"(b));return result;}
static __inline__ void Active(NODE*p){VE&v=p->vt[8];((void(*)(void*))v.fn)((char*)p+v.delta);}
static __inline__ void Link(NODE*p,NODE*other){VE&v=p->vt[38];((void(*)(void*,NODE*))v.fn)((char*)p+v.delta,other);}
static __inline__ void Inactive(NODE*p){VE&v=p->vt[9];((void(*)(void*))v.fn)((char*)p+v.delta);}
extern "C" void func_0018E540(P*p,int state){
 if(p->state==state)return;
 int compatible=0;
 if(state!=-1&&p->state!=-1)compatible=D_002BF448[p->state]==state;
 if(!compatible)func_001F2AD0(p,p->action);
 int exitEffect=-1;
 if(p->state==0)func_001CCAC0(p->track,-1);else switch(p->state){case 1:exitEffect=p->target->exitEffect;func_001F4BF8(p);break;case 2:func_001F4BF8(p);break;}
 Emit(p,exitEffect);
 float start=0.0f,rate=1.0f,stopDelay=0.0f;
 ASEG*clip=0;
 int enterEffect=-1;
 switch(state){
 case -1:p->surface=0;break;
 case 1:case 2:func_001F4BF8(p);break;
 case 10:func_001F4BF8(p);clip=p->alternate10;break;
 case 11:func_001F4BF8(p);clip=p->alternate11;break;
 case 0:func_001CCAC0(p->track,0);clip=p->idle;rate=0.0f;start=clip->duration*0.5f;enterEffect=15;func_001F4BF8(p);p->deadline=D_002DDED0.t+0.1f;break;
 case 3:{
  U first;first.q=func_001A6F00(0,p,func_001A62E8(p->pointObject));
  qword second=func_001A6F00(0,p,p->point->position.q);
  U half;half.q=Scalar(0.5f);
  U average;average.q=Average(first,second,half);
  if(!p->mode){
   if(D_002E1E44){state=6;goto enter6;}
   if(D_002E1E48){state=7;goto enter7;}
   if(average.f[1]<0.0f){state=6;goto enter6;}
   state=7;goto enter7;
  }
  if(D_002E1E44){state=4;goto enter4;}
  if(D_002E1E48){state=5;goto enter5;}
  if(average.f[1]<0.0f){state=4;goto enter4;}
  state=5;goto enter5;
 }
 case 4:enter4:func_0018F560(p,&p->blend4,p->blend4.clip);enterEffect=11;stopDelay=D_002BF430;p->deadline=D_002DDED0.t+D_002BF434;clip=p->blend4.clip;break;
 case 5:enter5:func_0018F560(p,&p->blend5,p->blend5.clip);enterEffect=11;stopDelay=D_002BF430;p->deadline=D_002DDED0.t+D_002BF438;clip=p->blend5.clip;break;
 case 6:enter6:func_0018F560(p,&p->blend6,p->blend6.clip);enterEffect=11;stopDelay=D_002BF430;clip=p->blend6.clip;if(func_001F0400(p->sm,0x17B)>=0)func_001F09D8(p->component,0x17B);p->deadline=D_002DDED0.t+D_002BF434;break;
 case 7:enter7:func_0018F560(p,&p->blend7,p->blend7.clip);enterEffect=11;stopDelay=D_002BF430;clip=p->blend7.clip;if(func_001F0400(p->sm,0x17B)>=0)func_001F09D8(p->component,0x17B);p->deadline=D_002DDED0.t+D_002BF438;break;
 case 8:clip=p->clip8;break;
 case 9:clip=p->clip9;break;
 case 12:stopDelay=D_002BF43C;p->deadline=D_002DDED0.t+D_002BF440;p->attack=1;clip=p->clip12;if(!p->mode&&func_001F0400(p->sm,0x17B)>=0)func_001F09D8(p->component,0x17B);break;
 case 13:stopDelay=D_002BF43C;p->deadline=D_002DDED0.t+D_002BF440;p->attack=1;clip=p->clip13;if(!p->mode&&func_001F0400(p->sm,0x17B)>=0)func_001F09D8(p->component,0x17B);break;
 case 14:stopDelay=D_002BF43C;p->deadline=D_002DDED0.t+D_002BF440;p->attack=1;clip=p->clip14;break;
 case 15:stopDelay=D_002BF43C;p->deadline=D_002DDED0.t+D_002BF440;p->attack=1;clip=p->clip15;break;
 case 16:stopDelay=D_002BF43C;p->deadline=D_002DDED0.t+D_002BF440;p->attack=1;clip=p->clip16;break;
 case 17:stopDelay=D_002BF43C;p->deadline=D_002DDED0.t+D_002BF440;p->attack=1;clip=p->clip17;break;
 case 18:stopDelay=D_002BF43C;p->deadline=D_002DDED0.t+D_002BF440;p->attack=1;clip=p->clip18;break;
 case 19:stopDelay=D_002BF43C;p->deadline=D_002DDED0.t+D_002BF440;p->attack=1;clip=p->clip19;break;
 case 20:stopDelay=D_002BF43C;p->deadline=D_002DDED0.t+D_002BF440;p->attack=1;clip=p->clip20;break;
 case 21:stopDelay=D_002BF43C;p->deadline=D_002DDED0.t+D_002BF440;p->attack=1;clip=p->clip21;break;
 case 22:case 23:clip=state==22?p->clip22:p->clip23;stopDelay=D_002BF43C;p->deadline=D_002DDED0.t+D_002BF440;p->attack=0;if(!p->mode&&func_001F0400(p->sm,0x17B)>=0)func_001F09D8(p->component,0x17B);break;
 }
 if(compatible){enterEffect=-1;rate=p->current->elapsed/p->current->rate;start=Min(p->current->localTime,clip->duration);}
 else p->finished=0;
 int wasAlternate=p->state==11||p->state==2;
 int nowAlternate=state==11||state==2;
 if(wasAlternate!=nowAlternate){
  if(nowAlternate){Active(p->alternateNode);Link(p->alternateNode,p->normalNode);Inactive(p->normalNode);}
  else{Active(p->normalNode);Link(p->normalNode,p->alternateNode);Inactive(p->alternateNode);}
 }
 p->state=state;p->reset=0;p->stateTime=D_002DDED0.t;
 func_001305B8(clip,p,start,rate,1,&p->current);
 if(stopDelay!=0.0f)func_00131A90(p->current,D_002DDED0.t+stopDelay);
 Emit(p,enterEffect);
}

typedef char layout_qword[(sizeof(qword)==16)?1:-1];
typedef char layout_pointer[(sizeof(void*)==4)?1:-1];
typedef char layout_U[(sizeof(U)==16)?1:-1];
typedef char layout_VE[(sizeof(VE)==8)?1:-1];
typedef char layout_BLEND[(sizeof(BLEND)==0x1C)?1:-1];
typedef char layout_VE_delta[((unsigned long)&((VE*)0)->delta==0x0)?1:-1];
typedef char layout_VE_fn[((unsigned long)&((VE*)0)->fn==0x4)?1:-1];
typedef char layout_ASEG_duration[((unsigned long)&((ASEG*)0)->duration==0x74)?1:-1];
typedef char layout_ASEGA_localTime[((unsigned long)&((ASEGA*)0)->localTime==0x1c)?1:-1];
typedef char layout_ASEGA_elapsed[((unsigned long)&((ASEGA*)0)->elapsed==0x40)?1:-1];
typedef char layout_ASEGA_rate[((unsigned long)&((ASEGA*)0)->rate==0x48)?1:-1];
typedef char layout_NODE_vt[((unsigned long)&((NODE*)0)->vt==0xc)?1:-1];
typedef char layout_TARGET_exitEffect[((unsigned long)&((TARGET*)0)->exitEffect==0x130)?1:-1];
typedef char layout_POINT_position[((unsigned long)&((POINT*)0)->position==0x70)?1:-1];
typedef char layout_BLEND_incoming[((unsigned long)&((BLEND*)0)->incoming==0x0)?1:-1];
typedef char layout_BLEND_outgoing[((unsigned long)&((BLEND*)0)->outgoing==0xc)?1:-1];
typedef char layout_BLEND_clip[((unsigned long)&((BLEND*)0)->clip==0x18)?1:-1];
typedef char layout_P_sm[((unsigned long)&((P*)0)->sm==0x1028)?1:-1];
typedef char layout_P_component[((unsigned long)&((P*)0)->component==0x1034)?1:-1];
typedef char layout_P_alternate10[((unsigned long)&((P*)0)->alternate10==0x14d4)?1:-1];
typedef char layout_P_alternate11[((unsigned long)&((P*)0)->alternate11==0x14d8)?1:-1];
typedef char layout_P_track[((unsigned long)&((P*)0)->track==0x17d0)?1:-1];
typedef char layout_P_idle[((unsigned long)&((P*)0)->idle==0x1800)?1:-1];
typedef char layout_P_reset[((unsigned long)&((P*)0)->reset==0x1880)?1:-1];
typedef char layout_P_surface[((unsigned long)&((P*)0)->surface==0x18c0)?1:-1];
typedef char layout_P_target[((unsigned long)&((P*)0)->target==0x18c4)?1:-1];
typedef char layout_P_mode[((unsigned long)&((P*)0)->mode==0x18c8)?1:-1];
typedef char layout_P_state[((unsigned long)&((P*)0)->state==0x18d8)?1:-1];
typedef char layout_P_stateTime[((unsigned long)&((P*)0)->stateTime==0x18dc)?1:-1];
typedef char layout_P_current[((unsigned long)&((P*)0)->current==0x18e0)?1:-1];
typedef char layout_P_finished[((unsigned long)&((P*)0)->finished==0x18e4)?1:-1];
typedef char layout_P_attack[((unsigned long)&((P*)0)->attack==0x18ec)?1:-1];
typedef char layout_P_normalNode[((unsigned long)&((P*)0)->normalNode==0x19a0)?1:-1];
typedef char layout_P_pointObject[((unsigned long)&((P*)0)->pointObject==0x19a4)?1:-1];
typedef char layout_P_alternateNode[((unsigned long)&((P*)0)->alternateNode==0x19a8)?1:-1];
typedef char layout_P_deadline[((unsigned long)&((P*)0)->deadline==0x19b0)?1:-1];
typedef char layout_P_point[((unsigned long)&((P*)0)->point==0x19c0)?1:-1];
typedef char layout_P_blend4[((unsigned long)&((P*)0)->blend4==0x1a04)?1:-1];
typedef char layout_P_blend5[((unsigned long)&((P*)0)->blend5==0x1a20)?1:-1];
typedef char layout_P_blend6[((unsigned long)&((P*)0)->blend6==0x1a3c)?1:-1];
typedef char layout_P_blend7[((unsigned long)&((P*)0)->blend7==0x1a58)?1:-1];
typedef char layout_P_clip8[((unsigned long)&((P*)0)->clip8==0x1a74)?1:-1];
typedef char layout_P_clip9[((unsigned long)&((P*)0)->clip9==0x1a78)?1:-1];
typedef char layout_P_action[((unsigned long)&((P*)0)->action==0x1a88)?1:-1];
typedef char layout_P_clip22[((unsigned long)&((P*)0)->clip22==0x1d14)?1:-1];
typedef char layout_P_clip23[((unsigned long)&((P*)0)->clip23==0x1d18)?1:-1];
typedef char layout_P_clip12[((unsigned long)&((P*)0)->clip12==0x1ce0)?1:-1];
typedef char layout_P_clip13[((unsigned long)&((P*)0)->clip13==0x1ce4)?1:-1];
typedef char layout_P_clip14[((unsigned long)&((P*)0)->clip14==0x1ce8)?1:-1];
typedef char layout_P_clip15[((unsigned long)&((P*)0)->clip15==0x1cec)?1:-1];
typedef char layout_P_clip16[((unsigned long)&((P*)0)->clip16==0x1cf0)?1:-1];
typedef char layout_P_clip17[((unsigned long)&((P*)0)->clip17==0x1cf4)?1:-1];
typedef char layout_P_clip18[((unsigned long)&((P*)0)->clip18==0x1cf8)?1:-1];
typedef char layout_P_clip19[((unsigned long)&((P*)0)->clip19==0x1cfc)?1:-1];
typedef char layout_P_clip20[((unsigned long)&((P*)0)->clip20==0x1d00)?1:-1];
typedef char layout_P_clip21[((unsigned long)&((P*)0)->clip21==0x1d04)?1:-1];
