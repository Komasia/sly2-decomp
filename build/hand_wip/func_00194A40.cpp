typedef int qword __attribute__((mode(TI)));typedef unsigned int uint;
union U{qword q;float f[4];};struct P;struct VTE;
struct SAMPLE{char pad0[0x10];int priority,cue,group,mask;VTE*vt;};
struct BASE190{char pad[0x190];};struct N190:BASE190,SAMPLE{N190*next;};
struct BASEE0{char pad[0xE0];};struct NE0:BASEE0,SAMPLE{NE0*next;};
struct BASE130{char pad[0x130];};struct N130:BASE130,SAMPLE{N130*next;};
struct N100;struct BASE100{char pad0[0xE0];N100*next;char padE4[4];uint flags;char padEC[0x14];};struct N100:BASE100,SAMPLE{};
struct CANDIDATE{void*object;SAMPLE*sample;float distance;int priority;P*link;float time,parameter,speed;U position;};
struct GAME{char pad0[0x4678];int count;char pad467C[4];CANDIDATE entries[4];int lastCue;};struct CONTEXT;struct CUE;struct INFO{char pad0[0x18];int kind;};
struct WORK{CANDIDATE entries[4];U position;uint scan1,scan2,scan20;};
extern "C"{extern float D_002BF664,D_002BF660,D_002BF70C;extern N190*D_003E13F0,*D_003E13CC,*D_003E13C0;extern NE0*D_003E13FC,*D_003E1414,*D_003E13D8,*D_003E1408;extern N130*D_003E1438;extern N100*D_003E13B4;extern GAME D_003DD490;extern CUE D_003DA0C0;
int func_001C40C0(P*);void*func_002333B4(void*,int,uint);qword func_001A62E8(P*);void func_00194688(CONTEXT*,P*,qword,void*,SAMPLE*,int,CANDIDATE*);int func_00132B10(void*,int);void func_00195368(GAME*,P*,int,CANDIDATE*);void func_00194F70(GAME*,P*,int,CANDIDATE*);int func_001DA5B0(CUE*);INFO*func_001CB658(P*);void func_001DA578(CUE*,int);void func_001DA4B8(CUE*,int,float);}
template<class NODE> static inline void Insert(CONTEXT*context,P*p,qword position,NODE*n,CANDIDATE*out){void*object=n;SAMPLE*sample=n;func_00194688(context,p,position,object,sample,4,out);}
static inline int TooFar(U*a,U*b,float limit){qword v=b->q,one;float length;__asm__("vsub.xyzw %0,%1,%0":"+j"(v):"j"(a->q));__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(v),"=&j"(one));__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(v));register int bits __asm__("$3");__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(v));__asm__("mtc1 %1,%0":"=f"(length):"r"(bits));int result=1;if(limit<length){}else result=0;return result;}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char SAMPLE_Size[sizeof(SAMPLE)==36?1:-1];
typedef char BASE190_Size[sizeof(BASE190)==400?1:-1];
typedef char BASEE0_Size[sizeof(BASEE0)==224?1:-1];
typedef char BASE130_Size[sizeof(BASE130)==304?1:-1];
typedef char BASE100_Size[sizeof(BASE100)==256?1:-1];
typedef char N190_Size[sizeof(N190)==440?1:-1];
typedef char NE0_Size[sizeof(NE0)==264?1:-1];
typedef char N130_Size[sizeof(N130)==344?1:-1];
typedef char N100_Size[sizeof(N100)==292?1:-1];
typedef char CANDIDATE_Size[sizeof(CANDIDATE)==48?1:-1];
typedef char GAME_Size[sizeof(GAME)==18256?1:-1];
typedef char INFO_Size[sizeof(INFO)==28?1:-1];
typedef char WORK_Size[sizeof(WORK)==224?1:-1];
typedef char SAMPLE_priority_Offset[FIELD_OFFSET(SAMPLE,priority)==16?1:-1];
typedef char SAMPLE_cue_Offset[FIELD_OFFSET(SAMPLE,cue)==20?1:-1];
typedef char SAMPLE_group_Offset[FIELD_OFFSET(SAMPLE,group)==24?1:-1];
typedef char SAMPLE_mask_Offset[FIELD_OFFSET(SAMPLE,mask)==28?1:-1];
typedef char SAMPLE_vt_Offset[FIELD_OFFSET(SAMPLE,vt)==32?1:-1];
typedef char N190_priority_Offset[(sizeof(BASE190)+FIELD_OFFSET(SAMPLE,priority))==416?1:-1];
typedef char N190_next_Offset[FIELD_OFFSET(N190,next)==436?1:-1];
typedef char NE0_priority_Offset[(sizeof(BASEE0)+FIELD_OFFSET(SAMPLE,priority))==240?1:-1];
typedef char NE0_next_Offset[FIELD_OFFSET(NE0,next)==260?1:-1];
typedef char N130_priority_Offset[(sizeof(BASE130)+FIELD_OFFSET(SAMPLE,priority))==320?1:-1];
typedef char N130_next_Offset[FIELD_OFFSET(N130,next)==340?1:-1];
typedef char N100_flags_Offset[FIELD_OFFSET(N100,flags)==232?1:-1];
typedef char N100_next_Offset[FIELD_OFFSET(N100,next)==224?1:-1];
typedef char N100_priority_Offset[(sizeof(BASE100)+FIELD_OFFSET(SAMPLE,priority))==272?1:-1];
typedef char CANDIDATE_object_Offset[FIELD_OFFSET(CANDIDATE,object)==0?1:-1];
typedef char CANDIDATE_sample_Offset[FIELD_OFFSET(CANDIDATE,sample)==4?1:-1];
typedef char CANDIDATE_distance_Offset[FIELD_OFFSET(CANDIDATE,distance)==8?1:-1];
typedef char CANDIDATE_priority_Offset[FIELD_OFFSET(CANDIDATE,priority)==12?1:-1];
typedef char CANDIDATE_link_Offset[FIELD_OFFSET(CANDIDATE,link)==16?1:-1];
typedef char CANDIDATE_time_Offset[FIELD_OFFSET(CANDIDATE,time)==20?1:-1];
typedef char CANDIDATE_parameter_Offset[FIELD_OFFSET(CANDIDATE,parameter)==24?1:-1];
typedef char CANDIDATE_speed_Offset[FIELD_OFFSET(CANDIDATE,speed)==28?1:-1];
typedef char CANDIDATE_position_Offset[FIELD_OFFSET(CANDIDATE,position)==32?1:-1];
typedef char GAME_count_Offset[FIELD_OFFSET(GAME,count)==18040?1:-1];
typedef char GAME_entries_Offset[FIELD_OFFSET(GAME,entries)==18048?1:-1];
typedef char GAME_lastCue_Offset[FIELD_OFFSET(GAME,lastCue)==18240?1:-1];
typedef char INFO_kind_Offset[FIELD_OFFSET(INFO,kind)==24?1:-1];
typedef char WORK_entries_Offset[FIELD_OFFSET(WORK,entries)==0?1:-1];
typedef char WORK_position_Offset[FIELD_OFFSET(WORK,position)==192?1:-1];
typedef char WORK_scan1_Offset[FIELD_OFFSET(WORK,scan1)==208?1:-1];
typedef char WORK_scan2_Offset[FIELD_OFFSET(WORK,scan2)==212?1:-1];
typedef char WORK_scan20_Offset[FIELD_OFFSET(WORK,scan20)==216?1:-1];
extern "C" void func_00194A40(CONTEXT*context,P*p,uint mask){
 if(!func_001C40C0(p))return;
 WORK w;w.scan20=mask&0x20;uint scan8=mask&8;
 (void)func_002333B4(w.entries,0,sizeof(w.entries));
 uint scan10=mask&0x10,scan2=mask&2,scan80=mask&0x80,scan4=mask&4,scan400=mask&0x400,scan200=mask&0x200;mask&=1;w.scan2=scan2;w.scan1=mask;
 {CANDIDATE*e=w.entries;do{e->priority=-1;e->distance=D_002BF664;}while(++e<w.entries+4);}
 w.position.q=func_001A62E8(p);
 if(scan8)for(N190*n=D_003E13F0;n;n=n->next)Insert(context,p,w.position.q,n,w.entries);
 if(scan10)for(NE0*n=D_003E13FC;n;n=n->next)Insert(context,p,w.position.q,n,w.entries);
 if(scan80)for(NE0*n=D_003E1414;n;n=n->next)Insert(context,p,w.position.q,n,w.entries);
 if(scan4)for(N130*n=D_003E1438;n;n=n->next)Insert(context,p,w.position.q,n,w.entries);
 if(scan400)for(NE0*n=D_003E13D8;n;n=n->next)Insert(context,p,w.position.q,n,w.entries);
 if(scan200)for(N190*n=D_003E13CC;n;n=n->next)Insert(context,p,w.position.q,n,w.entries);
 if(w.scan2)for(N190*n=D_003E13C0;n;n=n->next)Insert(context,p,w.position.q,n,w.entries);
 if(w.scan1)for(N100*n=D_003E13B4;n;n=n->next)if((n->flags&1)&&func_00132B10(n,0x13))Insert(context,p,w.position.q,n,w.entries);
 if(w.scan20)for(NE0*n=D_003E1408;n;n=n->next)Insert(context,p,w.position.q,n,w.entries);
 int count=4;if(!w.entries[3].object){CANDIDATE*e=w.entries+3;while(--count>0){--e;if(e->object)break;}}
 GAME*game=&D_003DD490;func_00195368(game,p,count,w.entries);func_00194F70(game,p,count,w.entries);
 int current=func_001DA5B0(&D_003DA0C0);if(current!=-1&&current!=game->lastCue)return;
 int next;
 if(!game->count)next=-1;else{
  int far=TooFar(&w.position,&game->entries[0].position,D_002BF660);
  if(far)next=-1;else{INFO*info=game->entries[0].link?func_001CB658(game->entries[0].link):0;
   if(info&&info->kind==0x624&&D_002BF70C<game->entries[0].time)next=0x125;
   else next=D_003DD490.entries[0].sample->cue;
  }
 }
 if(next!=current){if(next==-1)func_001DA578(&D_003DA0C0,D_003DD490.lastCue);else func_001DA4B8(&D_003DA0C0,next,-1.0f);D_003DD490.lastCue=next;}
}