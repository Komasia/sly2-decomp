extern "C" {void *func_001291A8(void*,const void*);void Decref(void*) asm("Decref__4CRef");}
struct CRef {
 int tag;
 union {int n;float g;};
 CRef(int x){tag=0x15;n=x;}
 CRef(bool x){tag=0x17;n=x;}
 CRef(const CRef&r){func_001291A8(this,&r);}
 ~CRef(){Decref(this);}
};
struct OPT{int kind,value;};
struct TASK{char pad[0x54];int nState;char pad58[0xC];int cPlayed,cDone;char pad6C[0x10];void*pjob;char pad80[0x48];OPT prPlayed,prCDone,prDone,prState,prRestart;int fF0,nMode;};
extern char D_003D4A60[];
extern "C" CRef func_00258200(OPT*,const CRef&,void*);
extern "C" int FTaskDone(TASK*) asm("FTaskDone__FP4TASK");
extern "C" void func_00163460(void*);
static inline void SetPv(OPT*p,const CRef&r,void*context=0){CRef arg(r);const CRef&ret=func_00258200(p,arg,D_003D4A60);}
static inline void SetInt(OPT*p,int n){CRef r(n);SetPv(p,r);}
// func_001643B0: save cPlayed task's progress (not in mode 1, nor cPlayed task of another world): its play and done counts,
// whether it is done, its nState, and the restart flag cleared; then its job's (func_00163460).
extern "C" void func_001643B0(TASK*p){
 if(p->nMode==1||p->nState==-1)return;
 {OPT*opt=&p->prPlayed;if(opt->kind){SetInt(opt,p->cPlayed);}}
 {OPT*opt=&p->prCDone;if(opt->kind){SetInt(opt,p->cDone);}}
 {OPT*opt=&p->prDone;if(opt->kind){void*key=D_003D4A60;int prState=FTaskDone(p);{CRef r(prState!=0);SetPv(opt,r,key);}}}
 {OPT*opt=&p->prState;if(opt->kind){SetInt(opt,p->nState);}}
 {OPT*opt=&p->prRestart;if(opt->kind){CRef r(false);SetPv(opt,r,D_003D4A60);}}
 if(p->pjob)func_00163460(p->pjob);
}
