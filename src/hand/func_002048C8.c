// FStepFloorNear (0x2048C8): whether a floor face (normal z > 0.7) is reachable from psurfStart over edges within 1.45
// times the climb height (sFloorTarget - zBase) of pos and not above pos by more than it: breadth-first over at most
// 32 faces. (Claude agent, 2026-10-17) MATCH.
typedef int qword __attribute__((mode(TI)));
typedef unsigned short ushort;
union V {qword q;float f[4];};
struct EDGE {ushort aipos[2],aisurf[2];struct EDGE *next0,*next1;};
struct POLY {float normal[3];int unknown;struct EDGE *head0,*head1;int flags,pad;};
/* SOE: the entry's world geometry (points and faces) */
struct SOE {char pad94[0x94];qword *aposWorld;int csurfWorld;struct POLY *asurfWorld;};
struct STEP {char pad210[0x210];float sFloorTarget;char pad214[0x34];float zBase;};
void PosNearestSegment__FG9VU_VECTORN20P6VECTORN23(qword,qword,qword,qword *,float *,float *);
static __inline__ float Z(qword q){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(q));return f;}
// name: SafeHouse port (FStepFloorNear)
int FStepFloorNear__FP3ALOG9VU_VECTORP3SOEP4POLY(struct STEP *pstep,qword pos,struct SOE *psoe,struct POLY *psurfStart)
{
    struct POLY *queue[32];
    union V closest;
    float distance;
    int count=1,current=0;
    float delta=pstep->sFloorTarget-pstep->zBase;
    float limit=delta*1.45f;
    float maximumNormal=0.7f;
    queue[0]=psurfStart;
    do {
        struct POLY *poly=queue[current];
        int side;
        for(side=0;side<2;side++){
            struct EDGE *edge;
            if(!side)edge=poly->head0;else edge=poly->head1;
            while(edge){
                float z=Z(pos);
                PosNearestSegment__FG9VU_VECTORN20P6VECTORN23(pos,psoe->aposWorld[edge->aipos[0]],psoe->aposWorld[edge->aipos[1]],&closest.q,0,&distance);
                if(limit<distance)goto next;
                if(z+delta<closest.f[2])goto next;
                {
                    struct POLY *neighbor=&psoe->asurfWorld[edge->aisurf[1-side]];
                    int j;struct POLY **pp;
                    if(maximumNormal<neighbor->normal[2])return 1;
                    for(j=0,pp=queue;;pp++,j++){
                        if(j>=count){
                            if((unsigned)count<32)queue[count++]=neighbor;
                            break;
                        }
                        if(neighbor==*pp)break;
                    }
                }
            next:
                if(!side)edge=edge->next0;else edge=edge->next1;
            }
        }
    }while(++current<count);
    return 0;
}
