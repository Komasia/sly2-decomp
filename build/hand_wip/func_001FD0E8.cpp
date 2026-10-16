typedef unsigned int uint;
typedef unsigned long ulong;
struct HEADER {uint words[16];};
struct EVENT {HEADER header;int id;EVENT *next;int kind,selector;float gain;int pairCount;ulong *pairs;};
struct OTHER {HEADER header;int id;OTHER *next;};
struct P {char pad0[0x18];int mapCount;char pad1C[0x8C];HEADER previous;int handle;EVENT *events;OTHER *others;HEADER *extra;int flagCount;int *flags,*map;char pad104[0xCC];int propertyCount,properties[6];char pad1EC[0x3C];void *reference;};
struct MSG {int bytes,alignment;};
struct ARRAY {int count;EVENT *entries;};
extern int D_002E1E54;
extern "C" {
void func_00118458(void *,void *);
void func_002321B8(int);
int func_00231C48(void);
int func_00117D50(void *);
int func_00117D00(void *);
int func_00117BD0(void *);
int func_00117DB8(void *);
float func_00117E38(void *);
void func_00117968(void *,int,void *);
void *func_001AE2A0(MSG *);
void *func_001AE1D0(MSG *);
void *func_002333B4(void *,int,unsigned int);
void *func_001FC138(HEADER *,int);
void func_00259B48(void *,void *);
}
static inline bool Same(const HEADER *a,const HEADER *b){if(a==b)return true;if(!b)return false;return (a->words[2]^a->words[14])==(b->words[2]^b->words[14]);}
static inline void StoreCount(ARRAY *array,int value){__asm__("sw %1,%0":"=m"(array->count):"r"(value));}
static inline int Count(const ARRAY *array){int value;__asm__("lw %0,%1":"=r"(value):"m"(array->count));return value;}
extern "C" void func_001FD0E8(P *p,void *stream)
{
    HEADER header;
    MSG request;
    HEADER locale;
    ARRAY array;
    func_00118458(stream,&header);
    if(!Same(&header,&p->previous)){
        p->previous=header;
        if(p->handle){func_002321B8(p->handle);while(func_00231C48()){}p->handle=0;}
    }
    MSG *allocation=&request;
    int *properties=p->properties;
    int flagsIndex=0;
    p->flagCount=func_00117D50(stream);
    request.bytes=p->flagCount*4;allocation->alignment=16;
    p->flags=(int *)func_001AE2A0(allocation);
    for(;flagsIndex<p->flagCount;flagsIndex++){int *slot=&p->flags[flagsIndex];*slot=func_00117D00(stream);}
    int j=0;
    p->mapCount=func_00117D50(stream);
    request.bytes=p->mapCount*4;allocation->alignment=16;
    p->map=(int *)func_001AE1D0(allocation);
    func_002333B4(p->map,-1,p->mapCount*4);
    for(;j<p->flagCount;j++)p->map[func_00117D50(stream)]=j;
    p->propertyCount=func_00117D50(stream);
    if(p->propertyCount>0){
        request.bytes=sizeof(HEADER);allocation->alignment=16;
        p->extra=(HEADER *)func_001AE2A0(allocation);
        func_00118458(stream,p->extra);
        void *object=func_001FC138(p->extra,4);
        func_00259B48(&p->reference,object);
    }
    func_002333B4(properties,-1,24);
    for(int propertyIndex=0;propertyIndex<p->propertyCount;propertyIndex++)properties[propertyIndex]=func_00117D50(stream);
    int languages=func_00117BD0(stream);
    int selected=0;
    for(int languageIndex=0;languageIndex<languages;languageIndex++)if(func_00117BD0(stream)==D_002E1E54)selected=languageIndex;
    StoreCount(&array,func_00117DB8(stream));
    request.bytes=Count(&array)*sizeof(EVENT);allocation->alignment=16;
    array.entries=(EVENT *)func_001AE2A0(allocation);
    for(int i=0;i<Count(&array);i++){
        EVENT *e=&array.entries[i];
        e->id=func_00117D50(stream);
        e->kind=func_00117D50(stream);
        for(int localeIndex=0;localeIndex<languages;localeIndex++){
            func_00118458(stream,&locale);
            int selector=func_00117D00(stream);
            float gain=func_00117E38(stream);
            if(localeIndex==selected){e->header=locale;e->selector=selector;e->gain=gain;}
        }
        e->pairCount=func_00117DB8(stream);
        request.bytes=e->pairCount*8;request.alignment=16;
        e->pairs=(ulong *)func_001AE1D0(&request);
        func_00117968(stream,e->pairCount*8,e->pairs);
        e->next=p->events;p->events=e;
    }
    int count=func_00117DB8(stream);
    request.bytes=count*sizeof(OTHER);allocation->alignment=16;
    OTHER *other=(OTHER *)func_001AE2A0(allocation);
    if(count>0)do{
        other->id=func_00117D50(stream);
        func_00118458(stream,&other->header);
        other->next=p->others;p->others=other;
        ++other;
    }while(--count);
}
