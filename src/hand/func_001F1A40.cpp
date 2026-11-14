// Choose a weighted reward and distribute the remaining pickup count.
extern "C" {
struct ITEM {int kind,flags,key,count;};
struct PICK {int weight,key;};
struct TABLE {int minimum,maximum;float chance;struct PICK picks[6];};
struct OBJECT {char pad[0x230];void *state;};
struct OWNER;
struct P {char pad404[0x404];struct ITEM items[8];int count;char pad488[8];int busy;struct OWNER *owner;};
extern char g_sw[];
extern struct TABLE D_002C3968[],D_002C3748[];
void ClearReward(struct OWNER *) asm("ClearReward__FP2LO");
int func_00210AE0(void);
int FIsBasicDerivedFrom(void *,int) asm("FIsBasicDerivedFrom__FP5BASIC3CID");
void *s1_memset(void *,int,int) asm("memset");
struct OBJECT *PloFindSwNearest(void *,int,int,void *) asm("PloFindSwNearest__FP2LO3OIDii");
int FTaskDone(void *) asm("FTaskDone__FP4TASK");
float GRandInRange(float,float) asm("GRandInRange__Fff");
int NRandInRange(int,int) asm("NRandInRange__Fii");
// name: SafeHouse port (FillPocket)
void FillPocket__FP2LO(struct P *p)
{
    struct TABLE *table;
    struct ITEM reward;
    int id,total,remaining,slots;unsigned int i;
    ClearReward(p->owner);
    if(p->busy)return;
    id=func_00210AE0();if(id==-1)id=1;
    if(FIsBasicDerivedFrom(p,0x3A))table=&D_002C3968[id];else table=&D_002C3748[id];
    s1_memset(&reward,0,sizeof(reward));
    if(p->count>0){
        struct OBJECT *object=PloFindSwNearest(g_sw,4,p->items[0].kind,p->owner);
        if(object && FIsBasicDerivedFrom(object,0x5C) && object->state && FTaskDone(object->state))p->count=0;
        if(p->count>0){reward=p->items[0];}
        else goto choose_reward;
    }else{
choose_reward:
        if(GRandInRange(0.0f,1.0f)>table->chance){reward.key=-1;reward.kind=-1;}
        else{
            total=0;for(i=0;i<6;i++)total+=table->picks[i].weight;
            int choice=NRandInRange(0,total-1);
            const PICK *pick=&table->picks[0];
            register int weight asm("$3")=pick->weight; /* pin: weight must be v1 (global-alloc gives it v0 and swaps pick/weight otherwise) */
            asm("" : "+r"(weight)); /* empty asm: gives the first weight load a dependent so sched2 issues it before the choice copy, as in the target */
            i=0;goto test_pick;
next_pick:
            choice-=pick->weight;i++;
            if(i>=6)goto selected_pick;
            pick=&table->picks[i];
            weight=pick->weight;
test_pick:
            if(choice>=weight)goto next_pick;
            reward.key=pick->key;
selected_pick:;
            reward.count=1;reward.kind=0x2B5;
        }
    }
    p->count=0;
    remaining=NRandInRange(table->minimum,table->maximum);
    slots=NRandInRange(2,3);
    int j=0;
    if(slots>0){do{
        struct ITEM *item=&p->items[p->count++];
        item->kind=0x2B3;item->flags=0;
        int amount=remaining/(slots-j);
        if(amount<1)amount=1;
        remaining-=amount;item->count=amount;
        if(!remaining)break;j++;
    }while(j<slots);}
    if(reward.count>0)p->items[p->count++]=reward;
}

}
