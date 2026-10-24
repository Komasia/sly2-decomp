typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
struct P;
struct VTE {short delta,pad;void *fn;};
struct M4 {qword rows[4];};
struct BIND {int kind,type;void *resource;int length;void *data;P *object;};
struct TABLE {int count;P **objects;int capacity,used,id;char pad14[0xC];char pad20[0x40];int instantiate;void *states,*nodes;};
struct TREE {int id;TREE *parent;char pad8[8];P *owner;};
struct P {void *resource;char pad4[8];VTE *vt;char pad10[0x18];ulong flags;char pad30[8];float scale;char pad3C[0x14];int channel;char pad54[0xC];M4 matrix;char padA0[0x40];TABLE *table;char padE4[8];int bindCount;BIND *binds;};
struct SW {char pad[0x3F08];TABLE *tables;TREE *root;};
struct IF {VTE *vt;};
struct DA {VTE *vt;int capacity,count;P **items;};
struct REQUEST {int size,alignment;};
union SCRATCH {REQUEST request;DA array;};
extern "C" {
int func_00117DB8(void *);
signed char func_00117D00(void *);
short func_00117D50(void *);
unsigned char func_00117BD0(void *);
unsigned short func_00117C20(void *);
unsigned int func_00117C80(void *);
void func_00117F18(void *,M4 *);
void func_001179B8(void *,int);
void func_00117968(void *,int,void *);
int func_0022D6B0(int,P *,P *);
void func_0022D670(int);
void func_0022D698(int);
int func_001CB770(SW *,int);
int func_001C9940(int,int);
P *func_0013E3C8(int,P *,int,int);
void func_002313F0(P *);
void func_001A6D28(P *,unsigned int);
void *func_001AE2A0(const REQUEST *);
void *func_001AE1D0(const REQUEST *);
void *func_001FFA40(SW *,int,P *);
void func_00256EE0(void **,void *);
int func_00132B10(P *,int);
void func_0013F810(P *,void *);
void func_001AE3D8();
void func_001AE428();
DA *func_0013F888(DA *);
void func_001CA370(SW *,int,P *,int,int,const M4 *,IF *);
TREE *func_001C99D8(TREE *,int,int *);
int func_0015E678(SW *,int,int,P *,TREE *,int,P **);
void func_00127B40(void *,void *);
void func_0013FB40(P *,void *,IF *);
}
static inline void Append(IF *p,int count,P **items){VTE &e=p->vt[1];((void(*)(IF *,int,P **))e.fn)((IF *)((char *)p+e.delta),count,items);}
static inline void SetKey(P *p,int key,int mode){VTE &e=p->vt[25];((void(*)(P *,int,int))e.fn)((P *)((char *)p+e.delta),key,mode);}
static inline void SetMatrix(P *p,const M4 *matrix){VTE &e=p->vt[37];((void(*)(P *,const M4 *))e.fn)((P *)((char *)p+e.delta),matrix);}
extern "C" void func_001C9B08(SW *world,P *parent,int classId,int id,int unused,void *stream,IF *output){
 M4 matrix;
 SCRATCH first;
 DA second;
 P *actor;
 int key;
 P *found;
 TREE *tree;
 DA *secondOut;
 int tableId=func_00117DB8(stream);
 int mode=func_00117D00(stream);
 int channel=func_0022D6B0(func_00117D50(stream),parent,0);
 func_00117F18(stream,&matrix);
 unsigned int flags=func_00117C80(stream);
 int index=func_001CB770(world,tableId);
 key=func_001C9940(index,world->tables[index].used);
 int instantiate=0;
 if(mode==1 || (mode==-1 && world->tables[index].instantiate))instantiate=1;
 if(instantiate){
  P *created=func_0013E3C8(classId,parent,id,-1);actor=created;
  created->channel=channel;
  created->matrix=matrix;
  func_002313F0(created);
  func_001A6D28(actor,flags);
  TABLE *table=&world->tables[index];
  P *tableActor=actor;
  tableActor->table=table;
  int previous=table->count;
  if(previous>0)tableActor->scale=table->objects[previous*table->capacity-1]->scale;
  int i=0;
  int bindCount=func_00117BD0(stream);
  actor->bindCount=bindCount;
  REQUEST *request=&first.request;
  request->size=bindCount*sizeof(BIND);request->alignment=16;
  actor->binds=(BIND *)func_001AE2A0(request);
  for(;i<actor->bindCount;i++){
   BIND *bind=&actor->binds[i];
   bind->kind=func_00117DB8(stream);
   bind->type=func_00117D50(stream);
   int resourceId=func_00117D50(stream);
   if(resourceId!=-1)bind->resource=func_001FFA40(world,resourceId,0);
   if(bind->kind==5){
    func_00256EE0(&actor->resource,bind->resource);
    int length=func_00117C20(stream);
    if(!func_00132B10(actor,bind->type))func_001179B8(stream,length);
    else func_0013F810(actor,stream);
   }else{
    bind->length=func_00117C20(stream);
    {REQUEST *lr=&first.request;lr->size=bind->length;lr->alignment=16;
    bind->data=func_001AE1D0(lr);}
    func_00117968(stream,bind->length,bind->data);
   }
  }
  int length=func_00117DB8(stream);
  func_00117D50(stream);
  func_001179B8(stream,length-2);
  if(output)Append(output,1,&actor);
  return;
 }
 if(!output)func_001AE3D8();
 int i=0;
 func_0013F888(&first.array);
 func_001CA370(world,index,parent,channel,id,&matrix,(IF *)&first.array);
 secondOut=&second;
 register int *pkey __asm__("$19")=&key;
 for(;i<first.array.count;i++){
  P *object=first.array.items[i];
  if(!(object->flags&(0x8000UL<<43)))func_001A6D28(object,flags);
 }
 tree=func_001C99D8(world->root,1,pkey);
 int count=func_00117BD0(stream);
 for(int k=0;k<count;k++){
  found=0;
  int kind=func_00117DB8(stream);
  int type=func_00117D50(stream);
  if(kind==5||kind==6){
   if(first.array.count>0)found=first.array.items[0];
  }else func_0015E678(world,0xA05,kind,0,tree,1,&found);
  if(found && !func_00132B10(found,type))found=0;
  int resourceId=func_00117D50(stream);
  if(found && resourceId!=-1){
   void *resource=func_001FFA40(world,resourceId,found);
   if(found->resource)func_00127B40(resource,found->resource);
   func_00256EE0(&found->resource,resource);
  }
  int length=func_00117C20(stream);
  if(found)func_0013F810(found,stream);
  else func_001179B8(stream,length);
 }
 i=0;
 func_0013F888(secondOut);
 func_00117DB8(stream);
 func_0022D670(channel);
 func_0013FB40(parent,stream,(IF *)secondOut);
 func_0022D698(channel);
 for(;i<second.count;i++){
  P *object=second.items[i];
  SetKey(object,key,1);SetMatrix(object,&matrix);
  if(!(object->flags&(0x8000UL<<43)))func_001A6D28(object,flags);
 }
 if(!output)func_001AE428();
 else{Append(output,first.array.count,first.array.items);Append(output,second.count,second.items);}
}
