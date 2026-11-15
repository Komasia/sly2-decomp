// ChangeTaskState: change a task's nState (not re-entrant): the prerequisites the change carries along
// (CollectTasks) change first, each in this task's iep and context, then the task (func_00165A60); the episode's
// percentage is saved, and a task that becomes done reaches its job (JobTaskReached), else - once all its next
// tasks are in jobs - the game auto-saves.
struct TASK{char pad[0x54];int nState;char pad58[0x24];void*pjob;char pad80[0x14];int fCheckNext;char pad98[8];int cptaskNext;TASK**aptaskNext;char padA8[0x48];int nPending;int nMode,ploContext;};
struct CONTEXT{char pad[0xF0];int nMode,ploContext;};
struct REQUEST{int bytes,alignment;REQUEST(int cb,int a):bytes(cb),alignment(a){}};
struct G{char pad[0x3B7C];void*apoptPercent[9];};
struct CRef;
struct HEAP_SCOPE;
extern "C"{
extern int D_002DEB28,D_003E0F8C;   /* a change in progress, the task count */
extern char g_game[],D_002E65E0[],D_003D4A60[];
extern G g_sw;
HEAP_SCOPE*__10STACKSCOPE(HEAP_SCOPE*);
void*PvAllocStackClearImpl(const REQUEST&) asm("PvAllocStackClearImpl__Fi");
void _$_10STACKSCOPE(HEAP_SCOPE*,int);
void CollectTasks(TASK*,int,int*,TASK**) asm("CollectTasks__FP4TASKiPiPv");
void func_00165A60(TASK*,int);
int func_00210AE0(void);
int NTasksPercentDone(void*) asm("NTasksPercentDone__Fv");
int func_001637E8(TASK*);
void JobTaskReached(void*,TASK*) asm("JobTaskReached__FP3JOBP4TASK");
void HudAutoSave(void*,int) asm("HudAutoSave__FP4SAVEi");
CRef*func_001291A8(CRef*,const CRef*);
void Decref(CRef*) asm("Decref__4CRef");
}
static inline void*Allocate(int n){return PvAllocStackClearImpl(REQUEST(n,16));}
struct HEAP_SCOPE{HEAP_SCOPE(){__10STACKSCOPE(this);}~HEAP_SCOPE(){_$_10STACKSCOPE(this,2);}};
struct OVERRIDE{CONTEXT*context;TASK*object;int nModeOld,ploContextOld;
    OVERRIDE(TASK*p,int nMode,int ploContext):context(0),object(p){if(object){nModeOld=object->nMode;object->nMode=nMode;ploContextOld=object->ploContext;object->ploContext=ploContext;}}
    ~OVERRIDE(){if(context){context->nMode=nModeOld;context->ploContext=ploContextOld;}if(object){object->nMode=nModeOld;object->ploContext=ploContextOld;}}
};
struct CRef{int kind,value;CRef(int v){kind=0x15;value=v;}CRef(const CRef&r){func_001291A8(this,&r);}~CRef(){Decref(this);}};
extern "C" CRef func_00258200(void*,const CRef&,void*);
static inline void SetPv(void*object,const CRef&ref,void*){CRef arg(ref);const CRef&result=func_00258200(object,arg,D_003D4A60);}
static inline void SetValue(void*object,int n){CRef r(n);SetPv(object,r,D_003D4A60);}
// name: SafeHouse port (ChangeTaskState)
extern "C" void ChangeTaskState__FP4TASKi(TASK*p,int nState){
    int nStateOld=p->nState;
    if(nState==nStateOld)return;
    if(D_002DEB28)return;
    D_002DEB28=1;
    int nStateCollect=-1;
    switch(nState){case 0:break;case 1:case 2:nStateCollect=2;break;case 3:nStateCollect=3;break;}
    if(nStateCollect!=-1){
        int i=0;
        HEAP_SCOPE scope;
        TASK**list;
        int cptaskNext=0;
        list=(TASK**)Allocate(D_003E0F8C*4);
        p->nPending=nState;
        CollectTasks(p,nStateCollect,&cptaskNext,list);
        for(;i<cptaskNext;i++){
            TASK*object=list[i];
            OVERRIDE temporary(object,p->nMode,p->ploContext);
            func_00165A60(object,object->nPending);
        }
        for(int j=0;j<cptaskNext;j++)list[j]->nPending=-1;
        p->nPending=-1;
    }
    func_00165A60(p,nState);
    D_002DEB28=0;
    int iep=func_00210AE0();
    if((unsigned)iep<9){
        void*object=g_sw.apoptPercent[iep];
        if(object){SetValue(object,NTasksPercentDone(g_game));}
    }
    if(func_001637E8(p)&&nStateOld!=-1&&nStateOld<2&&p->nState>=2){
        if(p->pjob){JobTaskReached(p->pjob,p);if(p->pjob)return;}
        if(p->fCheckNext){
            int all=1;
            for(int i=0;i<p->cptaskNext;i++){if(!p->aptaskNext[i]->pjob){all=0;break;}}
            if(!all)return;
        }
        HudAutoSave(D_002E65E0,0);
    }
}
