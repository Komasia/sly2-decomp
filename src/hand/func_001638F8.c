/* StartTask: a task's start (vt slot 15): after PostLoLoad it joins its job's task list, its prerequisite and next
 * task oids become task pointers (the ones found), a task not yet current shows its "end" objects and goals, its
 * play / done counts come from the progress, and a task with a time limit or a child list becomes updated (flag 2;
 * activated always when its activation kind was 2). */
typedef struct CRef { int m_tagk; int m_tag; } CRef;
struct E16 {int oid,oidOwner,grfState,iwrec;};                     /* TASKOBJE */
struct E24 {int nState,oid,oidSm,oidGoal,fNotInstant,iwrec;};     /* TASKSME */
struct SL {void*first;void*last;int nextOffset;};                /* a DL */
struct BF { unsigned long pad:52; long st:4; unsigned long pad2:8; };   /* LO +0x28: bits 52..55 the activation kind */
struct TASK {
    char pad[0x28]; struct BF bf;
    char pad0[0x40 - 0x30]; int grfUpd;
    char pad1[0x64 - 0x44]; int cPlayed; int cDone;
    char pad2[0x78 - 0x6C]; float dtLimit; struct TASK *pjob; struct SL children;
    char pad3[0x90 - 0x8C]; int *aoidPrereq; int cptaskPrereq; void **aptaskPrereq; int *aoidNext; int cptaskNext; void **aptaskNext; int cobje;struct E16*aobje;int csme;struct E24*asme;
    char pad4[0xC8 - 0xB8]; int prPlayed; int pad5; int prCDone;
};
extern char D_003D4A60[];
extern char g_sw[];
void PostLoLoad__FP2LO(struct TASK *p);
void func_0011A070(struct SL *pdl, struct TASK *p);   /* append to a DL */
void *PloFindSwNearest__FP2LO3OIDii(void *pg, int kind, int oid, void *owner);
int FTaskCur__FP4TASK(struct TASK *p);
int func_001637E8(struct TASK *p);
void ApplyTaskObjects__FPviiT0(struct TASK *p, int nState, int cobje, struct E16 *aobje);
void ApplyTaskSms__FPvT0iT0i(struct TASK *p, int nState, int csme, struct E24 *asme, int nMode);
CRef *NProgress(CRef *pref, void *a, void *b);
void Decref(CRef *pref) asm("Decref__4CRef");
void func_001A6CA8(struct TASK *p, int n);
// name: SafeHouse port (StartTask)
void StartTask__FP2SW(struct TASK *p)
{
    CRef ref;
    int i;
    register int j asm("$16"); /* allocation: i/j tie in global alloc */
    int *pnPlayed;
    int *pnCDone;
    PostLoLoad__FP2LO(p);
    if (p->pjob)
        func_0011A070(&p->pjob->children, p);
    i = 0;
    j = 0;
    pnPlayed = &p->prPlayed;
    pnCDone = &p->prCDone;
    if (p->cptaskPrereq > 0) {
        do {
            void *pv = PloFindSwNearest__FP2LO3OIDii(g_sw, 0x105, p->aoidPrereq[i], 0);
            if (pv)
                p->aptaskPrereq[j++] = pv;
        } while (++i < p->cptaskPrereq);
    }
    p->cptaskPrereq = j;
    j = 0;
    for (i = 0; i < p->cptaskNext; i++) {
        void *pv = PloFindSwNearest__FP2LO3OIDii(g_sw, 0x105, p->aoidNext[i], 0);
        if (pv)
            p->aptaskNext[j++] = pv;
    }
    p->cptaskNext = j;
    if (!FTaskCur__FP4TASK(p) && func_001637E8(p)) {
        ApplyTaskObjects__FPviiT0(p, 5, p->cobje, p->aobje);
        ApplyTaskSms__FPvT0iT0i(p, 5, p->csme, p->asme, 1);
    }
    if (p->prPlayed) {
        int n;
        NProgress(&ref, pnPlayed, D_003D4A60);
        n = ref.m_tag;
        Decref(&ref);
        p->cPlayed = n;
    }
    if (p->prCDone) {
        int n;
        NProgress(&ref, pnCDone, D_003D4A60);
        n = ref.m_tag;
        Decref(&ref);
        p->cDone = n;
    }
    if (p->dtLimit != 0.0f || p->children.first) {
        int v;
        if (p->bf.st == 2)
            func_001A6CA8(p, 0);
        v = p->grfUpd;
        if ((v ^ 1) & 1)
            *(int *)v |= 2;
        else
            p->grfUpd = v | 2;
    }
}

typedef char layout_pointer[(sizeof(void*)==4)?1:-1];
typedef char layout_int[(sizeof(int)==4)?1:-1];
typedef char layout_ulong[(sizeof(unsigned long)==8)?1:-1];
typedef char layout_CRef[(sizeof(CRef)==8)?1:-1];
typedef char layout_BF[(sizeof(struct BF)==8)?1:-1];
typedef char layout_SL[(sizeof(struct SL)==12)?1:-1];
typedef char layout_E16[(sizeof(struct E16)==16)?1:-1];
typedef char layout_E24[(sizeof(struct E24)==24)?1:-1];
typedef char layout_TASK_prefix[(sizeof(struct TASK)==0xD8)?1:-1];
typedef char layout_TASK_bf[(((unsigned)&((struct TASK*)0)->bf==0x28))?1:-1];
typedef char layout_TASK_fl[(((unsigned)&((struct TASK*)0)->grfUpd==0x40))?1:-1];
typedef char layout_TASK_f64[(((unsigned)&((struct TASK*)0)->cPlayed==0x64))?1:-1];
typedef char layout_TASK_f68[(((unsigned)&((struct TASK*)0)->cDone==0x68))?1:-1];
typedef char layout_TASK_f78[(((unsigned)&((struct TASK*)0)->dtLimit==0x78))?1:-1];
typedef char layout_TASK_f7c[(((unsigned)&((struct TASK*)0)->pjob==0x7c))?1:-1];
typedef char layout_TASK_children[(((unsigned)&((struct TASK*)0)->children==0x80))?1:-1];
typedef char layout_TASK_a90[(((unsigned)&((struct TASK*)0)->aoidPrereq==0x90))?1:-1];
typedef char layout_TASK_c94[(((unsigned)&((struct TASK*)0)->cptaskPrereq==0x94))?1:-1];
typedef char layout_TASK_a98[(((unsigned)&((struct TASK*)0)->aptaskPrereq==0x98))?1:-1];
typedef char layout_TASK_a9C[(((unsigned)&((struct TASK*)0)->aoidNext==0x9c))?1:-1];
typedef char layout_TASK_cA0[(((unsigned)&((struct TASK*)0)->cptaskNext==0xa0))?1:-1];
typedef char layout_TASK_aA4[(((unsigned)&((struct TASK*)0)->aptaskNext==0xa4))?1:-1];
typedef char layout_TASK_fa8[(((unsigned)&((struct TASK*)0)->cobje==0xa8))?1:-1];
typedef char layout_TASK_fac[(((unsigned)&((struct TASK*)0)->aobje==0xac))?1:-1];
typedef char layout_TASK_fb0[(((unsigned)&((struct TASK*)0)->csme==0xb0))?1:-1];
typedef char layout_TASK_fb4[(((unsigned)&((struct TASK*)0)->asme==0xb4))?1:-1];
typedef char layout_TASK_fc8[(((unsigned)&((struct TASK*)0)->prPlayed==0xc8))?1:-1];
typedef char layout_TASK_fd0[(((unsigned)&((struct TASK*)0)->prCDone==0xd0))?1:-1];
typedef char layout_SL_first[(((unsigned)&((struct SL*)0)->first==0))?1:-1];
typedef char layout_SL_last[(((unsigned)&((struct SL*)0)->last==4))?1:-1];
typedef char layout_SL_nextOffset[(((unsigned)&((struct SL*)0)->nextOffset==8))?1:-1];
