#include "stepguard.h"
extern "C" {
struct GUARD;
struct DETENTRY {struct GUARD *object;int mode;float stamp;int unusedC;};
struct DETECTOR {char pad0[0xFC];int cdetentry;struct DETENTRY adetentry[8];};
struct TARGETREC {int unused0;float stamp;int mode;struct GUARD *object;};
struct CANDIDATE {float distance;int *source;struct GUARD *object;int mode;float stamp;int unused14;};
struct SW;
extern struct SW g_sw;
extern int D_003DD488;
extern ulong D_003DD480;   /* the busy states' mask (made once, D_003DD488) */
extern float D_002A8614;
extern float D_002C3D04,D_002C3D08,D_002C3D0C;
ulong func_00207A20(int);
int CFindObjectsByClass(struct SW *,int,int,int,int,struct GUARD **) asm("CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO");
qword PosOfLo(struct GUARD *) asm("PosOfLo__FP2LO");
void qsort(void *,unsigned int,unsigned int,int (*)(const void *,const void *)) asm("qsort");
int func_002068D8(const void *,const void *);
int func_002085D0(struct GUARD *,struct GUARD *,int);
void UpdateDetector(struct DETECTOR *) asm("UpdateDetector__FP8DETECTOR");
struct DETENTRY *PdetentryFind(struct DETECTOR *,struct GUARD *) asm("PdetentryFind__FP8DETECTORi");
void SetTargetrecTimer(struct TARGETREC *,int) asm("SetTargetrecTimer__FP9TARGETRECi");
static __inline__ qword Subtract(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static __inline__ float LengthXY(qword a){qword r;float f;__asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(r):"j"(a));__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(r));__asm__("mtc1 %1,%0":"=f"(f):"r"(r));return f;}
static __inline__ float Z(qword q){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(q));return f;}
static __inline__ float Abs(float f){return __builtin_fabsf(f);}
static __inline__ int Near(qword difference){return LengthXY(difference)<D_002C3D08 && Abs(Z(difference))<D_002C3D0C;}
/* Two empty-asm tricks for the nearby-object collection loop (T1592); neither emits an instruction:
   OPAQUE_COUNT: an empty asm that "sets" the candidate count. loop.c then sees no basic induction variable, so
     &candidates[n] stays a real `mult` by 24 instead of a strength-reduced pointer, and the increment is not PRE-copied.
   LOOP_SIZE_PAD: 24 empty volatile asms at the end of the loop body. They emit nothing, but loop.c's move_movables only
     hoists a constant out of a loop when threshold(95)*savings*lifetime >= insn count; the original loop body has ~96 RTL
     insns, so only the D_002C3D04 high part is hoisted (to $fp) and the `li 24` / `li -1` stay inside the loop. */
#define OPAQUE_COUNT(n) __asm__("":"+r"(n))
#define PAD1 __asm__ volatile("");
#define PAD4 PAD1 PAD1 PAD1 PAD1
#define LOOP_SIZE_PAD PAD4 PAD4 PAD4 PAD4 PAD4 PAD4
/* RefreshGuardTargets (0x206900): unless the guard's state is one of the busy ones (states 5 6 23 7 16 1 22 42), the
 * objects of its nearby classes within D_002C3D04 become its generated detector entries, nearest first, keeping the
 * mode/stamp of entries it already had; then the detector updates and the pursued target's record gets its timer (1
 * seen, 2 lost but near). */
// name: SafeHouse port (RefreshGuardTargets)
void RefreshGuardTargets__FP5GUARD(struct GUARD *pguard)
{
    struct CANDIDATE candidates[64];
    struct GUARD *objects[256];
    qword anchorPosition,ownerPosition;
    if(!D_003DD488){
        ulong a=func_00207A20(5);
        ulong b=func_00207A20(6);
        ulong c=func_00207A20(23);
        ulong d=func_00207A20(7);
        ulong e=func_00207A20(16);
        ulong f=func_00207A20(1);
        ulong g=func_00207A20(22);
        ulong h=func_00207A20(42);
        D_003DD488=1;
        D_003DD480=a|b|c|d|e|f|g|h;
    }
    if(pguard->grfState&D_003DD480)return;
    if(pguard->ccidTarget){
        int candidateCount=0;
        int kind;
        for(kind=0;kind<pguard->ccidTarget;kind++){
            int *source=&pguard->acidTarget[kind];
            int objectCount=CFindObjectsByClass(&g_sw,0x505,*source,0,256,objects);
            int i=0;
            if(objectCount>0){
                float initialStamp=D_002A8614;
                do{
                    struct GUARD *object=objects[i];
                    if(object!=pguard){
                        qword otherPosition;
                        float distance;
                        ownerPosition=PosOfLo(pguard);
                        otherPosition=PosOfLo(object);
                        distance=LengthXY(Subtract(ownerPosition,otherPosition));
                        if(distance<D_002C3D04 && (unsigned int)candidateCount<64){
                            struct CANDIDATE *record;
                            int old;
                            record=&candidates[candidateCount];
                            record->distance=distance;
                            record->mode=-1;
                            record->source=source;
                            record->object=object;
                            record->stamp=initialStamp;
                            candidateCount++;
                            for(old=pguard->pdet->cdetentry-pguard->cdetentryGenerated;old<pguard->pdet->cdetentry;old++){
                                struct DETENTRY *pdetentry=&pguard->pdet->adetentry[old];
                                if(pdetentry->object==record->object){
                                    record->mode=pdetentry->mode;
                                    record->stamp=pdetentry->stamp;
                                    break;
                                }
                            }
                        }
                        OPAQUE_COUNT(candidateCount);
                        LOOP_SIZE_PAD
                    }
                }while(++i<objectCount);
            }
        }
        qsort(candidates,candidateCount,sizeof(struct CANDIDATE),func_002068D8);
        pguard->pdet->cdetentry-=pguard->cdetentryGenerated;
        pguard->cdetentryGenerated=0;
        if(candidateCount>0){
            int absentMode=-1;
            struct CANDIDATE *record=candidates;
            do{
                if(func_002085D0(pguard,record->object,(int)record->source)){
                    pguard->cdetentryGenerated++;
                    if(record->mode!=absentMode){
                        struct DETENTRY *pdetentry=&pguard->pdet->adetentry[pguard->pdet->cdetentry-1];
                        pdetentry->mode=record->mode;
                        pdetentry->stamp=record->stamp;
                    }
                }
                record++;
            }while(--candidateCount);
        }
    }
    UpdateDetector(pguard->pdet);
    if(pguard->ptarget3CC){
        struct DETENTRY *pdetentry=PdetentryFind(pguard->pdet,pguard->ptarget3CC->object);
        if(pdetentry){
            switch(pdetentry->mode){case 1:SetTargetrecTimer(pguard->ptarget3CC,1);break;
            case 2:{
                qword ownPosition,difference;
                anchorPosition=PosOfLo(pguard->ptarget3CC->object);
                ownPosition=PosOfLo(pguard);
                difference=Subtract(anchorPosition,ownPosition);
                if(Near(difference))SetTargetrecTimer(pguard->ptarget3CC,2);
            }break;
            }
        }
    }
}
}
