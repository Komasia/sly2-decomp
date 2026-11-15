extern "C" {void*func_001291A8(void*,const void*);void Decref(void*) asm("Decref__4CRef");}
struct CRefData{int tag;union{int n;float g;};};
struct CRef:CRefData{
 CRef(float x){tag=0x16;g=x;}
 CRef(const CRef&r){func_001291A8(this,&r);}
 ~CRef(){Decref(this);}
};
struct OPT;
/* JOB (include/h2_task.h): the suck times and the play time */
struct JOB{char pad[0x9C];float tSuckStart,tSuckEnd,tElapsed;};
/* SW: the current job, the progress keys of the game's play time and of each episode's (SafeHouse savedata.cpp) */
struct SW{char pad[0x3B0C];JOB*pjobCur;char pad10[0xC];OPT*poptTimePlayed;char pad20[0x38];OPT*apoptEpisodeDt[9];};
#include "clock.h"
extern SW g_sw;
extern int D_002E0C20;   /* the first pad's idle seconds (JOY +0x1020) */
extern char D_003D4A60[],D_002DE578[];   /* the game slot, the suck meter */
extern "C" CRef NProgress(OPT*,void*);
extern "C" CRef func_00258200(OPT*,const CRefData&,void*);
extern "C" int func_00210AE0();   /* the current episode */
extern "C" void func_00154D88(void*,float);
static inline float GetFloat(OPT*p,void*context){const CRef&r=NProgress(p,context);return r.g;}
static inline void SetPv(OPT*p,const CRef&r,void*context){CRef arg(r);const CRef&ret=func_00258200(p,arg,context);}
static inline void SetFloat(OPT*p,float x,void*context){CRef r(x);SetPv(p,r,context);}
struct CRefCopy:CRefData{
 CRefCopy(const CRefData&r){func_001291A8(this,&r);}
 ~CRefCopy(){Decref(this);}
};
static inline void SetPrimaryFloat(OPT*p,float value,void*context){
 CRef r(value);CRefCopy arg(r);const CRef&ret=func_00258200(p,arg,context);
}
/* UpdateGameTimers: add the frame's time to the game's play time and the current episode's; while the pad was used
 * in the last 10 s, to the current job's too, which past its suck start grows the suck meter. */
// name: SafeHouse port (UpdateGameTimers)
extern "C" void UpdateGameTimers__Fv(){
 if(!g_sw.poptTimePlayed)return;
 float t=GetFloat(g_sw.poptTimePlayed,D_003D4A60);
 SetPrimaryFloat(g_sw.poptTimePlayed,t+g_clock.dt,D_003D4A60);
 unsigned int iep=func_00210AE0();
 if(iep<9){
  OPT*popt=g_sw.apoptEpisodeDt[iep];
  if(popt){float dt=GetFloat(popt,D_003D4A60);SetFloat(popt,dt+g_clock.dt,D_003D4A60);}
 }
 JOB*pjob=g_sw.pjobCur;
 if(pjob&&(float)D_002E0C20<10.0f){
  pjob->tElapsed+=g_clock.dt;
  if(pjob->tSuckStart<pjob->tElapsed)func_00154D88(D_002DE578,g_clock.dt/(pjob->tSuckEnd-pjob->tSuckStart));
 }
}

#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef char Pointer_Size[sizeof(void*)==4?1:-1];
typedef char Integer_Size[sizeof(int)==4?1:-1];
typedef char Float_Size[sizeof(float)==4?1:-1];
typedef char CRefData_Size[sizeof(CRefData)==8?1:-1];
typedef char CRef_Size[sizeof(CRef)==8?1:-1];
typedef char CRefCopy_Size[sizeof(CRefCopy)==8?1:-1];
typedef char CRefData_Alignment[__alignof__(CRefData)==4?1:-1];
typedef char CRef_Alignment[__alignof__(CRef)==4?1:-1];
typedef char CRefCopy_Alignment[__alignof__(CRefCopy)==4?1:-1];
typedef char CRefData_Tag[FIELD_OFFSET(CRefData,tag)==0?1:-1];
typedef char CRefData_Float[FIELD_OFFSET(CRefData,g)==4?1:-1];
typedef char CRef_Tag[FIELD_OFFSET(CRef,tag)==0?1:-1];
typedef char CRef_Float[FIELD_OFFSET(CRef,g)==4?1:-1];
typedef char CRefCopy_Tag[FIELD_OFFSET(CRefCopy,tag)==0?1:-1];
typedef char CRefCopy_Float[FIELD_OFFSET(CRefCopy,g)==4?1:-1];
typedef char JOB_Size[sizeof(JOB)==0xA8?1:-1];
typedef char JOB_Start[FIELD_OFFSET(JOB,tSuckStart)==0x9C?1:-1];
typedef char JOB_End[FIELD_OFFSET(JOB,tSuckEnd)==0xA0?1:-1];
typedef char JOB_Elapsed[FIELD_OFFSET(JOB,tElapsed)==0xA4?1:-1];
typedef char SW_Size[sizeof(SW)==0x3B7C?1:-1];
typedef char SW_Job[FIELD_OFFSET(SW,pjobCur)==0x3B0C?1:-1];
typedef char SW_TimePlayed[FIELD_OFFSET(SW,poptTimePlayed)==0x3B1C?1:-1];
typedef char SW_EpisodeDt[FIELD_OFFSET(SW,apoptEpisodeDt)==0x3B58?1:-1];
typedef char SW_EpisodeCount[sizeof(((SW*)0)->apoptEpisodeDt)/sizeof(OPT*)==9?1:-1];
