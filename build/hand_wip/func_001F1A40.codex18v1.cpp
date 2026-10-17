// Choose a weighted reward and distribute the remaining pickup count.
extern "C" {
struct ITEM {int kind,flags,key,count;};
struct PICK {int weight,key;};
struct TABLE {int minimum,maximum;float chance;struct PICK picks[6];};
struct OBJECT {char pad[0x230];void *state;};
struct OWNER;
struct P {char pad404[0x404];struct ITEM items[8];int count;char pad488[8];int busy;struct OWNER *owner;};
extern char D_003DD490[];
extern struct TABLE D_002C3968[],D_002C3748[];
void func_001C2DB8(struct OWNER *);
int func_00210AE0(void);
int func_00132B10(void *,int);
void *func_002333B4(void *,int,unsigned int);
struct OBJECT *func_0015E938(void *,int,int,void *);
int func_00164030(void *);
float func_0011D448(float,float);
int func_0011D3F8(int,int);
static inline int Weight(const PICK *p){register int r __asm__("$3");__asm__("lw %0,%1":"=r"(r):"m"(p->weight));return r;}
static inline int Key(const PICK *p){register int r __asm__("$2");__asm__("lw %0,%1":"=r"(r):"m"(p->key));return r;}
void func_001F1A40(struct P *p)
{
    struct TABLE *table;
    struct ITEM reward;
    int id,total,remaining,slots;unsigned int i;
    func_001C2DB8(p->owner);
    if(p->busy)return;
    id=func_00210AE0();if(id==-1)id=1;
    if(func_00132B10(p,0x3A))table=&D_002C3968[id];else table=&D_002C3748[id];
    func_002333B4(&reward,0,sizeof(reward));
    if(p->count>0){
        struct OBJECT *object=func_0015E938(D_003DD490,4,p->items[0].kind,p->owner);
        if(object && func_00132B10(object,0x5C) && object->state && func_00164030(object->state))p->count=0;
        if(p->count>0){reward=p->items[0];}
        else goto choose_reward;
    }else{
choose_reward:
        if(func_0011D448(0.0f,1.0f)>table->chance){reward.key=-1;reward.kind=-1;}
        else{
            total=0;for(i=0;i<6;i++)total+=table->picks[i].weight;
            int draw=func_0011D3F8(0,total-1);
            register const PICK *pick __asm__("$2")=&table->picks[0];
            int weight=Weight(pick);
            register int choice __asm__("$4")=draw;
            i=0;goto test_pick;
next_pick:
            choice-=pick->weight;i++;
            if(i>=6)goto selected_pick;
            pick=&table->picks[i];
            weight=Weight(pick);
test_pick:
            if(choice>=weight)goto next_pick;
            reward.key=Key(pick);
selected_pick:;
            reward.count=1;reward.kind=0x2B5;
        }
    }
    p->count=0;
    remaining=func_0011D3F8(table->minimum,table->maximum);
    slots=func_0011D3F8(2,3);
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

typedef char layout_pointer[(sizeof(void*)==4)?1:-1];
typedef char layout_int[(sizeof(int)==4)?1:-1];
typedef char layout_float[(sizeof(float)==4)?1:-1];
typedef char layout_ITEM[(sizeof(ITEM)==0x10)?1:-1];
typedef char layout_PICK[(sizeof(PICK)==8)?1:-1];
typedef char layout_TABLE[(sizeof(TABLE)==0x3C)?1:-1];
typedef char layout_P[(sizeof(P)==0x498)?1:-1];
typedef char layout_OBJECT[(sizeof(OBJECT)==0x234)?1:-1];
typedef char layout_ITEM_kind[((unsigned)&((ITEM*)0)->kind==0)?1:-1];
typedef char layout_ITEM_flags[((unsigned)&((ITEM*)0)->flags==4)?1:-1];
typedef char layout_ITEM_key[((unsigned)&((ITEM*)0)->key==8)?1:-1];
typedef char layout_ITEM_count[((unsigned)&((ITEM*)0)->count==12)?1:-1];
typedef char layout_PICK_weight[((unsigned)&((PICK*)0)->weight==0)?1:-1];
typedef char layout_PICK_key[((unsigned)&((PICK*)0)->key==4)?1:-1];
typedef char layout_TABLE_minimum[((unsigned)&((TABLE*)0)->minimum==0)?1:-1];
typedef char layout_TABLE_maximum[((unsigned)&((TABLE*)0)->maximum==4)?1:-1];
typedef char layout_TABLE_chance[((unsigned)&((TABLE*)0)->chance==8)?1:-1];
typedef char layout_TABLE_picks[((unsigned)&((TABLE*)0)->picks==0xC)?1:-1];
typedef char layout_TABLE_pick_span[(sizeof(((TABLE*)0)->picks)==0x30)?1:-1];
typedef char layout_P_items[((unsigned)&((P*)0)->items==0x404)?1:-1];
typedef char layout_P_count[((unsigned)&((P*)0)->count==0x484)?1:-1];
typedef char layout_P_busy[((unsigned)&((P*)0)->busy==0x490)?1:-1];
typedef char layout_P_owner[((unsigned)&((P*)0)->owner==0x494)?1:-1];
typedef char layout_OBJECT_state[((unsigned)&((OBJECT*)0)->state==0x230)?1:-1];
