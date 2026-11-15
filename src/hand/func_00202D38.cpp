// UpdatePhotoPrompt__FPv (0x202D38): per-frame update of the binocucom's photo prompt: projects the best photo
// target and its size marker to the screen (centering / size gain), runs the prompt's state machine (PHOTOSTATE) and
// takes the shutter button. MATCH (Lilly/Claude T1613), no register pins.
// The ready test of PHOTOSTATE_Taken is `!ptask || ptask->nState == 1` (the game's `beqz` jumps TO the `li a0,1`); the
// label before that set keeps jump.c from turning it into movn.
// field: SafeHouse port (photo.cpp PHOTOPROMPT / PHOTOTARGET)
typedef int qword __attribute__((mode(TI)));
struct M4 {qword r[4];};
struct CM {char pad0[0x60];M4 mat;};
struct TASK {char pad0[0x54];int nState;};
/* a photo target (cid 0x2E, an LO) */
struct PHOTOTARGET {
    char pad0[0xE4];
    float size;          /* +0xE4 height of the size marker above the target */
    float tolerance;     /* +0xE8 how far below full size still counts */
    TASK *ptask;         /* +0xEC task completed by the photo */
    char padF0[0x18];
    int visibility;      /* +0x108 PHOTOVIS_* */
    int fCustom;         /* +0x10C a custom message instead of taking the photo */
    int message;         /* +0x110 */
};
/* the prompt's screen objects: the messages shown when the shutter misses */
struct SCREENOBJ {char pad0[0x110];int messageHidden,messageRising,messageFalling,messageApproach,messageNone;};
struct BINOC {char pad0[0x20];int nView;};
/* the photo states (PHOTOPROMPT::state) */
enum PHOTOSTATE {
    PHOTOSTATE_Off = -1,
    PHOTOSTATE_Opening = 0,
    PHOTOSTATE_Inactive = 1,   /* not in a photo volume */
    PHOTOSTATE_Idle = 2,
    PHOTOSTATE_Hidden = 3,     /* best target not visible */
    PHOTOSTATE_Approach = 4,
    PHOTOSTATE_Rising = 5,     /* centred, size marker growing toward full */
    PHOTOSTATE_Falling = 6,    /* centred, past full size */
    PHOTOSTATE_Framed = 7,
    PHOTOSTATE_Shutter = 8,
    PHOTOSTATE_Taken = 9,
    PHOTOSTATE_Closing = 10
};
enum PHOTOVIS {PHOTOVIS_Visible = 1, PHOTOVIS_Idle = 2, PHOTOVIS_Hidden = 3};
struct PHOTOPROMPT {
    int state;                 /* +0x00 PHOTOSTATE_* */
    char pad4[0xC];
    qword posScreen;           /* +0x10 the reticle's screen point */
    qword posEye;              /* +0x20 */
    int cTarget;               /* +0x30 */
    PHOTOTARGET *apTarget[16]; /* +0x34 */
    int cListed;               /* +0x74 */
    PHOTOTARGET *apListed[5];  /* +0x78 */
    PHOTOTARGET *ptargetBest;  /* +0x8C */
    float uCentering;          /* +0x90 1 when the target is within 128 px of the reticle */
    float uSize;               /* +0x94 size marker's screen length / 120 (folded above 1) */
    int fRising;               /* +0x98 uSize was not above 1 */
    float tHint;               /* +0x9C when the hint part was selected */
    int grfSaved;              /* +0xA0 owner's update flags while the shutter pauses */
    void *ploOverlay;          /* +0xA4 */
    BINOC *pbinoc;             /* +0xA8 */
    SCREENOBJ *pscrPrimary;    /* +0xAC */
    SCREENOBJ *pscrSecondary;  /* +0xB0 */
    int fClosePending;         /* +0xB4 */
    int fVolume;               /* +0xB8 */
    int selected;              /* +0xBC */
    int message;               /* +0xC0 */
};
#include "clock.h"
struct PLAYER {char pad0[0x150];void *ppadctl;};
struct VU_FLOAT {qword qw;};
extern CM g_cm;
extern PLAYER *D_002E1E40;   /* the current player */
extern char D_002DE2E0[];   /* the default camera policy */
extern "C" {
void CloseBinoc(BINOC *) asm("CloseBinoc__FP5ACTOR");
void func_00213928(SCREENOBJ *,int);                /* resets a screen object part */
void func_00202540(PHOTOPROMPT *);                  /* picks the best target */
void DistanceModels(PHOTOPROMPT *) asm("DistanceModels__FP11PHOTOPROMPT");
int func_002022D8(PHOTOPROMPT *);                   /* whether the prompt is active (in a photo volume) */
void SetPhotoPromptState(PHOTOPROMPT *,int) asm("SetPhotoPromptState__FPvi");
qword PosOfLo(PHOTOTARGET *) asm("PosOfLo__FP2LO");
qword ConvertCmWorldToScreen(CM *,qword) asm("ConvertCmWorldToScreen__FP2CMG9VU_VECTOR");
void func_00212E40(SCREENOBJ *,int,float);          /* sets a screen object part's fraction */
int FSpriteAnimPlaying(SCREENOBJ *,int) asm("FSpriteAnimPlaying__FP2LOi");
void func_00213B00(SCREENOBJ *,int);                /* selects a screen object part */
int func_00203758(PHOTOTARGET *);                   /* whether the target's photo is done */
int func_0014FD50(void *);                          /* whether a camera policy is active */
int GrfPadctlTakePressed(void *,int,float) asm("GrfPadctlTakePressed__FP6PADCTL");
}
static inline VU_FLOAT VuFloatFromMemWord(int n){VU_FLOAT v;__asm__("qmtc2 %1,%0":"=j"(v.qw):"rV"(n));return v;}
static inline qword QwScaleX(qword a,qword s){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(s));return r;}
static inline qword QwAdd(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword QwSub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword QwLengthXY(qword v){qword r;__asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(r):"j"(v));__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(r):"0"(r));return r;}
// camera up row; the pointer parameter gives the game's &cm+0x60 base register (lqc2 0x10(s1), then s1-0x60 for the calls)
static inline qword QwUp(const M4 *m){return m->r[1];}
static inline float GXOfQw(qword qw){float x;__asm__("mtc1 %1,%0":"=f"(x):"r"(qw));return x;}
static inline float GYOfQw(qword qw){float y;__asm__("prot3w %0,%1":"=r"(y):"r"(qw));return y;}
static inline float GZOfQw(qword qw){float z;__asm__("pextuw %0,$0,%1":"=r"(z):"r"(qw));return z;}
// screen position of a projected point: x and y from [-1,1] to pixels, z kept
static inline VU_FLOAT ScreenFromProjected(qword q)
{
    VU_FLOAT v;
    int t;
    float x=GXOfQw(q)*320.0f+320.0f;
    float y=GYOfQw(q)*-246.40000915527344f+246.40000915527344f;
    float z=GZOfQw(q);
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0":"=&r"(v.qw),"=&r"(t):"f"(x),"f"(y),"f"(z));
    return v;
}
static inline float Min(float a,float b){return a<b?a:b;}
static inline float Max(float a,float b){return a<b?b:a;}
static inline float GClamp(float g,float gMin,float gMax){return Max(gMin,Min(g,gMax));}
// name: SafeHouse port (UpdatePhotoPrompt)
extern "C" void UpdatePhotoPrompt__FPv(PHOTOPROMPT *pprompt)
{
    if(!pprompt->pscrPrimary)return;
    if(!pprompt->pscrSecondary)return;
    if(pprompt->fClosePending){pprompt->fClosePending=0;CloseBinoc(pprompt->pbinoc);}
    if(pprompt->tHint+5.0f<g_clock.t)func_00213928(pprompt->pscrPrimary,0x35B);
    if(pprompt->state<PHOTOSTATE_Shutter)if(pprompt->state>=PHOTOSTATE_Idle){
        func_00202540(pprompt);
        DistanceModels(pprompt);
        if(!func_002022D8(pprompt))SetPhotoPromptState(pprompt,PHOTOSTATE_Inactive);
    }
    if(pprompt->ptargetBest){
        qword world=PosOfLo(pprompt->ptargetBest);
        VU_FLOAT offset=VuFloatFromMemWord(*(int *)&pprompt->ptargetBest->size);
        qword head=QwAdd(world,QwScaleX(QwUp(&g_cm.mat),offset.qw));
        qword base=ConvertCmWorldToScreen(&g_cm,world);
        qword top=ConvertCmWorldToScreen(&g_cm,head);
        VU_FLOAT screen=ScreenFromProjected(base);
        float distance=GXOfQw(QwLengthXY(QwSub(screen.qw,pprompt->posScreen)));
        VU_FLOAT screenTop=ScreenFromProjected(top);
        float size=GXOfQw(QwLengthXY(QwSub(screen.qw,screenTop.qw)));
        float centering=1.0f-(distance-128.0f)/128.0f;
        size=size/120.0f;
        pprompt->fRising=1;
        pprompt->uCentering=GClamp(centering,0.0f,1.0f);
        pprompt->uSize=size;
        if(size>1.0f){pprompt->fRising=0;pprompt->uSize=2.0f-size;}
        pprompt->uSize=Max(pprompt->uSize,0.0f);
    }
    switch(pprompt->state){
    case PHOTOSTATE_Off:
        break;
    case PHOTOSTATE_Idle:
        if(pprompt->ptargetBest&&pprompt->ptargetBest->visibility!=PHOTOVIS_Idle)SetPhotoPromptState(pprompt,PHOTOSTATE_Approach);
        break;
    case PHOTOSTATE_Approach:
        if(!pprompt->ptargetBest)SetPhotoPromptState(pprompt,PHOTOSTATE_Idle);
        else if(pprompt->ptargetBest->visibility==PHOTOVIS_Hidden)SetPhotoPromptState(pprompt,PHOTOSTATE_Hidden);
        else if(pprompt->uCentering>=1.0f){
            if(pprompt->fRising)SetPhotoPromptState(pprompt,PHOTOSTATE_Rising);
            else SetPhotoPromptState(pprompt,PHOTOSTATE_Falling);
        }
        break;
    case PHOTOSTATE_Hidden:
        if(!pprompt->ptargetBest)SetPhotoPromptState(pprompt,PHOTOSTATE_Idle);
        else if(pprompt->ptargetBest->visibility!=PHOTOVIS_Hidden)SetPhotoPromptState(pprompt,PHOTOSTATE_Approach);
        break;
    case PHOTOSTATE_Rising:
        if(!pprompt->ptargetBest)SetPhotoPromptState(pprompt,PHOTOSTATE_Idle);
        else if(pprompt->uCentering<1.0f)SetPhotoPromptState(pprompt,PHOTOSTATE_Approach);
        else if(pprompt->uSize>=1.0f-pprompt->ptargetBest->tolerance)SetPhotoPromptState(pprompt,PHOTOSTATE_Framed);
        else func_00212E40(pprompt->pscrSecondary,0x35A,pprompt->uSize);
        break;
    case PHOTOSTATE_Falling:
        if(!pprompt->ptargetBest)SetPhotoPromptState(pprompt,PHOTOSTATE_Idle);
        else if(pprompt->uCentering<1.0f)SetPhotoPromptState(pprompt,PHOTOSTATE_Approach);
        else if(pprompt->uSize>=1.0f-pprompt->ptargetBest->tolerance)SetPhotoPromptState(pprompt,PHOTOSTATE_Framed);
        else func_00212E40(pprompt->pscrSecondary,0x35A,pprompt->uSize);
        break;
    case PHOTOSTATE_Framed:
        if(pprompt->ptargetBest){
            if(pprompt->uCentering<1.0f||pprompt->uSize<1.0f-pprompt->ptargetBest->tolerance){
                if(pprompt->fRising)SetPhotoPromptState(pprompt,PHOTOSTATE_Rising);
                else SetPhotoPromptState(pprompt,PHOTOSTATE_Falling);
            }
        }
        else SetPhotoPromptState(pprompt,PHOTOSTATE_Idle);
        break;
    case PHOTOSTATE_Shutter:
        if(!FSpriteAnimPlaying(pprompt->pscrPrimary,0x358)){
            int changed=0;
            if(pprompt->ptargetBest&&pprompt->ptargetBest->visibility==PHOTOVIS_Visible&&pprompt->uCentering>=1.0f&&pprompt->uSize>=1.0f-pprompt->ptargetBest->tolerance){
                if(!pprompt->ptargetBest->fCustom)SetPhotoPromptState(pprompt,PHOTOSTATE_Taken);
                else{pprompt->message=pprompt->ptargetBest->message;SetPhotoPromptState(pprompt,PHOTOSTATE_Framed);changed=1;}
            }
            else{
                if(pprompt->ptargetBest&&pprompt->ptargetBest->visibility!=PHOTOVIS_Visible){pprompt->message=pprompt->pscrPrimary->messageHidden;SetPhotoPromptState(pprompt,PHOTOSTATE_Hidden);}
                else if(pprompt->uCentering>=1.0f&&pprompt->fRising){pprompt->message=pprompt->pscrPrimary->messageRising;SetPhotoPromptState(pprompt,PHOTOSTATE_Rising);}
                else if(pprompt->uCentering>=1.0f&&!pprompt->fRising){pprompt->message=pprompt->pscrPrimary->messageFalling;SetPhotoPromptState(pprompt,PHOTOSTATE_Falling);}
                else if(pprompt->ptargetBest){pprompt->message=pprompt->pscrPrimary->messageApproach;SetPhotoPromptState(pprompt,PHOTOSTATE_Approach);}
                else{pprompt->message=pprompt->pscrPrimary->messageNone;SetPhotoPromptState(pprompt,PHOTOSTATE_Idle);}
                changed=1;
            }
            if(changed){func_00213B00(pprompt->pscrPrimary,0x35B);pprompt->tHint=g_clock.t;}
        }
        break;
    case PHOTOSTATE_Taken:
        if(!FSpriteAnimPlaying(pprompt->pscrPrimary,0x35C)){
            int ready=1;
            SetPhotoPromptState(pprompt,PHOTOSTATE_Idle);
            for(int i=0;i<pprompt->cTarget;i++){
                PHOTOTARGET *ptarget=pprompt->apTarget[i];
                int fDone=func_00203758(ptarget);
                // every target without a task or with an open one (state 1) must be done before the binoc closes
                int fTaskOpen=!ptarget->ptask||ptarget->ptask->nState==1;
                if(!fDone&&fTaskOpen){ready=0;break;}
            }
            if(ready)pprompt->fClosePending=1;
        }
        break;
    case PHOTOSTATE_Closing:
        if(!FSpriteAnimPlaying(pprompt->pscrPrimary,0x314))SetPhotoPromptState(pprompt,PHOTOSTATE_Off);
        break;
    case PHOTOSTATE_Opening:
        if(FSpriteAnimPlaying(pprompt->pscrPrimary,0x314))SetPhotoPromptState(pprompt,PHOTOSTATE_Inactive);
        break;
    case PHOTOSTATE_Inactive:
        DistanceModels(pprompt);
        if(func_002022D8(pprompt))SetPhotoPromptState(pprompt,PHOTOSTATE_Idle);
        break;
    }
    if(pprompt->pbinoc->nView!=1){
        switch(pprompt->state){
        case PHOTOSTATE_Idle:case PHOTOSTATE_Hidden:case PHOTOSTATE_Approach:case PHOTOSTATE_Rising:case PHOTOSTATE_Falling:
            if(!func_0014FD50(D_002DE2E0)&&GrfPadctlTakePressed(D_002E1E40->ppadctl,10,0.0f))SetPhotoPromptState(pprompt,PHOTOSTATE_Shutter);
            break;
        case PHOTOSTATE_Framed:
            if(!func_0014FD50(D_002DE2E0)&&GrfPadctlTakePressed(D_002E1E40->ppadctl,250,0.0f))SetPhotoPromptState(pprompt,PHOTOSTATE_Shutter);
            break;
        }
    }
}
