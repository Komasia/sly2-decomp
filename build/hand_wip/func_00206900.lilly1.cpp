extern "C" {
typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
struct P;
struct ENTRY {struct P *object;int mode;float stamp;int unusedC;};
struct MANAGER {char pad0[0xFC];int count;struct ENTRY entries[8];};
struct ANCHOR {int unused0;float stamp;int mode;struct P *object;};
struct P {char pad0[0x2C0];ulong flags;char pad2C8[0xCC];int kindCount;int kinds[3];int generated;char pad3A8[0x24];struct ANCHOR *anchor;char pad3D0[0xB94];struct MANAGER *manager;};
struct CANDIDATE {float distance;int *source;struct P *object;int mode;float stamp;int unused14;};
struct GAME;
extern struct GAME D_003DD490;
extern int D_003DD488;
extern ulong D_003DD480;
extern float D_002A8614;
extern float D_002C3D04,D_002C3D08,D_002C3D0C;
ulong func_00207A20(int);
int func_0015E9C8(struct GAME *,int,int,int,int,struct P **);
qword func_001A62E8(struct P *);
void func_002338C0(void *,unsigned int,unsigned int,int (*)(const void *,const void *));
int func_002068D8(const void *,const void *);
int func_002085D0(struct P *,struct P *,int);
void func_00153DE0(struct MANAGER *);
struct ENTRY *func_00154180(struct MANAGER *,struct P *);
void func_0020A9A8(struct ANCHOR *,int);
static __inline__ qword Subtract(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static __inline__ float LengthXY(qword a){qword r;float f;__asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(r):"j"(a));__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(r));__asm__("mtc1 %1,%0":"=f"(f):"r"(r));return f;}
static __inline__ float Z(qword q){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(q));return f;}
static __inline__ float Abs(float f){float r;__asm__("abs.s %0,%1":"=f"(r):"f"(f));return r;}
static __inline__ int Near(qword difference){return LengthXY(difference)<D_002C3D08 && Abs(Z(difference))<D_002C3D0C;}
static inline int CandidateOffset(int index){
    register int stride __asm__("$2")=0x18;
    register int offset __asm__("$4");
    __asm__("mult %0,%1,%2":"=r"(offset):"r"(index),"r"(stride):"hi","lo");
    return offset;
}
void func_00206900(struct P *p)
{
    struct CANDIDATE candidates[64];
    struct P *objects[256];
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
    if(p->flags&D_003DD480)return;
    if(p->kindCount){
        int candidateCount=0;
        int kind;
        for(kind=0;kind<p->kindCount;kind++){
            int *source=&p->kinds[kind];
            int objectCount=func_0015E9C8(&D_003DD490,0x505,*source,0,256,objects);
            int i=0;
            if(objectCount>0){
                float initialStamp=D_002A8614;
                do{
                    struct P *object=objects[i];
                    if(object!=p){
                        qword otherPosition;
                        float distance;
                        ownerPosition=func_001A62E8(p);
                        otherPosition=func_001A62E8(object);
                        distance=LengthXY(Subtract(ownerPosition,otherPosition));
                        if(distance<D_002C3D04 && (unsigned int)candidateCount<64){
                            struct CANDIDATE *record=&candidates[candidateCount];
                            int old;
                            record->distance=distance;
                            record->mode=-1;
                            record->source=source;
                            record->object=object;
                            record->stamp=initialStamp;
                            ++candidateCount;
                            for(old=p->manager->count-p->generated;old<p->manager->count;old++){
                                struct ENTRY *entry=&p->manager->entries[old];
                                if(entry->object==record->object){
                                    record->mode=entry->mode;
                                    record->stamp=entry->stamp;
                                    break;
                                }
                            }

                        }
                    }
                }while(++i<objectCount);
            }
        }
        func_002338C0(candidates,candidateCount,sizeof(struct CANDIDATE),func_002068D8);
        p->manager->count-=p->generated;
        p->generated=0;
        if(candidateCount>0){
            int absentMode=-1;
            struct CANDIDATE *record=candidates;
            do{
                if(func_002085D0(p,record->object,(int)record->source)){
                    p->generated++;
                    if(record->mode!=absentMode){
                        struct ENTRY *entry=&p->manager->entries[p->manager->count-1];
                        entry->mode=record->mode;
                        entry->stamp=record->stamp;
                    }
                }
                record++;
            }while(--candidateCount);
        }
    }
    func_00153DE0(p->manager);
    if(p->anchor){
        struct ENTRY *entry=func_00154180(p->manager,p->anchor->object);
        if(entry){
            switch(entry->mode){case 1:func_0020A9A8(p->anchor,1);break;
            case 2:{
                qword ownPosition,difference;
                anchorPosition=func_001A62E8(p->anchor->object);
                ownPosition=func_001A62E8(p);
                difference=Subtract(anchorPosition,ownPosition);
                if(Near(difference))func_0020A9A8(p->anchor,2);
            }break;
            }
        }
    }
}
}
