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
struct WORK {M4 matrix;SCRATCH first;DA second;P *actor;int key;P *found;int classId,id;TREE *tree;DA *secondOut;};
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
static inline int PreviousInstanceCount(const TABLE*table){register int value __asm__("$6");__asm__("lw %0,%1":"=r"(value):"m"(table->count));return value;}
static inline TABLE* TableBase(const SW*w){register TABLE*value __asm__("$3");__asm__("lw %0,%1":"=r"(value):"m"(w->tables));return value;}
static inline TABLE* SelectedTable(TABLE*base,int index){register TABLE*value __asm__("$3");__asm__("addu %0,%1,%2":"=r"(value):"r"(base),"r"(index*(int)sizeof(TABLE)));return value;}
static inline P* TableActor(const WORK&w){register P*value __asm__("$5");__asm__("lw %0,%1":"=r"(value):"m"(w.actor));return value;}
static inline P* BindingActor(const WORK&w){register P*value __asm__("$3");__asm__("lw %0,%1":"=r"(value):"m"(w.actor));return value;}
static inline int PublishBinds(P*p,BIND*b){register int count __asm__("$2");__asm__("sw %2,%1\n\tlw %0,%3":"=r"(count),"=m"(p->binds):"r"(b),"m"(p->bindCount));return count;}
static inline int SpawnClassAndParent(const WORK&work,P*parent,P*&argument){
 register P*p __asm__("$5");register int classId __asm__("$4");
 __asm__("daddu %0,%2,$zero\n\tlw %1,%3":"=&r"(p),"=r"(classId):"r"(parent),"m"(work.classId));argument=p;return classId;
}
extern "C" void func_001C9B08(SW *worldInput,P *parentInput,int classId,int id,int unused,void *streamInput,IF *outputInput){
 register SW*world __asm__("$20");register P*parent __asm__("$23");register void*stream __asm__("$18");register IF*output __asm__("$22");
 __asm__("daddu %0,%1,$zero":"=r"(stream):"r"(streamInput));
 __asm__("daddu %0,%1,$zero":"=r"(world):"r"(worldInput));
 __asm__("daddu %0,%1,$zero":"=r"(output):"r"(outputInput));
 __asm__("daddu %0,%1,$zero":"=r"(parent):"r"(parentInput));
 WORK work;
 work.classId=classId;work.id=id;
 int tableId=func_00117DB8(stream);
 int mode=func_00117D00(stream);
 int channel=func_0022D6B0(func_00117D50(stream),parent,0);
 func_00117F18(stream,&work.matrix);
 unsigned int flags=func_00117C80(stream);
 int index=func_001CB770(world,tableId);
 TABLE*initialTables;
 __asm__("lw %0,0x3F08(%1)":"=r"(initialTables):"r"(world),"m"(world->tables));
 work.key=func_001C9940(index,initialTables[index].used);
 int instantiate=0;
 if(mode==1 || (mode==-1 && world->tables[index].instantiate))instantiate=1;
 register int spawnId __asm__("$6")=work.id;
 if(instantiate){
  P*spawnParent;int spawnClass=SpawnClassAndParent(work,parent,spawnParent);
  P *actor=work.actor=func_0013E3C8(spawnClass,spawnParent,spawnId,-1);
  actor->channel=channel;
  actor->matrix=work.matrix;
  func_002313F0(actor);
  func_001A6D28(work.actor,flags);
  TABLE *table=SelectedTable(TableBase(world),index);
  P*tableActor=TableActor(work);tableActor->table=table;
  int previous=PreviousInstanceCount(table);
  if(previous>0)tableActor->scale=table->objects[previous*table->capacity-1]->scale;
  int i=0;
  int bindCount=func_00117BD0(stream);
  work.actor->bindCount=bindCount;
  register REQUEST *request __asm__("$16")=&work.first.request;
  request->size=bindCount*sizeof(BIND);request->alignment=16;
  BIND*allocated=(BIND*)func_001AE2A0(request);
  P*bindingActor=BindingActor(work);
  int firstCount=PublishBinds(bindingActor,allocated);
  register REQUEST*bindingRequest __asm__("$23")=request;
  for(;i<firstCount;i++){
   BIND *bind=&bindingActor->binds[i];
   bind->kind=func_00117DB8(stream);
   bind->type=func_00117D50(stream);
   int resourceId=func_00117D50(stream);
   if(resourceId!=-1)bind->resource=func_001FFA40(world,resourceId,0);
   if(bind->kind==5){
    func_00256EE0(&work.actor->resource,bind->resource);
    int length=func_00117C20(stream);
    if(!func_00132B10(work.actor,bind->type))func_001179B8(stream,length);
    else func_0013F810(work.actor,stream);
   }else{
    bind->length=func_00117C20(stream);
    work.first.request.size=bind->length;bindingRequest->alignment=16;
    bind->data=func_001AE1D0(bindingRequest);
    func_00117968(stream,bind->length,bind->data);
   }
   bindingActor=work.actor;firstCount=bindingActor->bindCount;
  }
  int length=func_00117DB8(stream);
  func_00117D50(stream);
  func_001179B8(stream,length-2);
  if(output)Append(output,1,&work.actor);
  return;
 }
 if(!output)func_001AE3D8();
 int i=0;
 func_0013F888(&work.first.array);
 func_001CA370(world,index,parent,channel,work.id,&work.matrix,(IF *)&work.first.array);
 work.secondOut=&work.second;
 for(;i<work.first.array.count;i++){
  P *object=work.first.array.items[i];
  if(!(object->flags&(0x8000UL<<43)))func_001A6D28(object,flags);
 }
 work.tree=func_001C99D8(world->root,1,&work.key);
 int count=func_00117BD0(stream);
 for(int k=0;k<count;k++){
  work.found=0;
  int kind=func_00117DB8(stream);
  int type=func_00117D50(stream);
  if(kind==5||kind==6){
   if(work.first.array.count>0)work.found=work.first.array.items[0];
  }else func_0015E678(world,0xA05,kind,0,work.tree,1,&work.found);
  if(work.found && !func_00132B10(work.found,type))work.found=0;
  int resourceId=func_00117D50(stream);
  if(work.found && resourceId!=-1){
   void *resource=func_001FFA40(world,resourceId,work.found);
   if(work.found->resource)func_00127B40(resource,work.found->resource);
   func_00256EE0(&work.found->resource,resource);
  }
  int length=func_00117C20(stream);
  if(work.found)func_0013F810(work.found,stream);
  else func_001179B8(stream,length);
 }
 i=0;
 func_0013F888(work.secondOut);
 func_00117DB8(stream);
 func_0022D670(channel);
 func_0013FB40(parent,stream,(IF *)work.secondOut);
 func_0022D698(channel);
 for(;i<work.second.count;i++){
  P *object=work.second.items[i];
  SetKey(object,work.key,1);SetMatrix(object,&work.matrix);
  if(!(object->flags&(0x8000UL<<43)))func_001A6D28(object,flags);
 }
 if(!output)func_001AE428();
 else{Append(output,work.first.array.count,work.first.array.items);Append(output,work.second.count,work.second.items);}
}

#define OFF(t,m) ((unsigned int)&((t*)0)->m)
typedef char loader_layout[(sizeof(void*)==4 && sizeof(qword)==16 && sizeof(ulong)==8 && sizeof(VTE)==8 && sizeof(M4)==0x40 && sizeof(BIND)==0x18 && sizeof(TABLE)==0x6C && sizeof(REQUEST)==8 && sizeof(DA)==0x10 && sizeof(IF)==4 && sizeof(SCRATCH)==0x10 && sizeof(WORK)==0x80 && OFF(VTE,delta)==0 && OFF(VTE,fn)==4 && OFF(BIND,kind)==0 && OFF(BIND,type)==4 && OFF(BIND,resource)==8 && OFF(BIND,length)==0xC && OFF(BIND,data)==0x10 && OFF(BIND,object)==0x14 && OFF(TABLE,count)==0 && OFF(TABLE,objects)==4 && OFF(TABLE,capacity)==8 && OFF(TABLE,used)==0xC && OFF(TABLE,id)==0x10 && OFF(TABLE,instantiate)==0x60 && OFF(TABLE,states)==0x64 && OFF(TABLE,nodes)==0x68 && OFF(P,resource)==0 && OFF(P,vt)==0xC && OFF(P,flags)==0x28 && OFF(P,scale)==0x38 && OFF(P,channel)==0x50 && OFF(P,matrix)==0x60 && OFF(P,table)==0xE0 && OFF(P,bindCount)==0xEC && OFF(P,binds)==0xF0 && OFF(SW,tables)==0x3F08 && OFF(SW,root)==0x3F0C && OFF(DA,vt)==0 && OFF(DA,capacity)==4 && OFF(DA,count)==8 && OFF(DA,items)==0xC && OFF(REQUEST,size)==0 && OFF(REQUEST,alignment)==4 && OFF(WORK,matrix)==0 && OFF(WORK,first)==0x40 && OFF(WORK,second)==0x50 && OFF(WORK,actor)==0x60 && OFF(WORK,key)==0x64 && OFF(WORK,found)==0x68 && OFF(WORK,classId)==0x6C && OFF(WORK,id)==0x70 && OFF(WORK,tree)==0x74 && OFF(WORK,secondOut)==0x78)?1:-1];
