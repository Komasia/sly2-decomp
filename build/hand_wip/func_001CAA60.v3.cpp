// v3 (Claude agent): v2 + function-scope int i,j (fixes spill order). aligned 25 (positional 28). natural locals, no outer if, node->next=0 only on found paths, owner/row scalars (cursor=&owner). Left: p s4/s5 swap with bind offset, spill slot order.
// Detach an object node and restore its child transforms and references.
typedef int qword __attribute__((mode(TI)));
struct P;
struct VTE {short delta,pad;void *fn;};
struct M3 {qword rows[3];};
struct M4 {float values[16];} __attribute__((aligned(16)));
struct POSE {qword position;M3 basis;};
struct NODE {P *owner;NODE *next;char pad8[8];M4 matrix;};
struct RESOURCE {int refs,pad4,count;void *items[1];};
struct BIND {int kind,pad4;RESOURCE *resource;int padC,pad10;void **slot;};
struct TABLE {int count;P **objects;char pad8[4];int rowBase;char pad10[0x54];POSE *states;NODE *nodes;};
struct P {char pad[0xC];VTE *vt;char pad10[0x48];int enabledPosition,enabledBasis;char pad60[0x80];TABLE *table;int disabled;NODE *head;int bindCount;BIND *binds;};
struct CONTEXT {P *owner;int row;};
struct WORK {M4 returned;P *object;void *cursor;CONTEXT context;int next;P **objectAddress;CONTEXT *contextAddress;};
extern "C" {
extern qword D_002A2DD0;
M4 func_0011C318(const M4 *);
void *func_002333B4(void *,int,unsigned);
int func_001CA930(const P *,const NODE *);
void func_00256EE0(void **,void *);
void func_00127B70(RESOURCE *,void *);
void func_001A58D0(P *,int,int);
int func_00132B10(P *,int);
}
static inline P *Adjusted(P *p,const VTE &entry){return (P *)((char *)p+entry.delta);}
static inline void Parent(P *p,P *parent){VTE &v=p->vt[27];((void(*)(P *,P *))v.fn)(Adjusted(p,v),parent);}
static inline void Query(P *p,void **cursor){VTE &v=p->vt[3];((void(*)(P *,int,int,int,void **,int))v.fn)(Adjusted(p,v),15,0,1,cursor,0);}
static inline void Reset(P *p){VTE &v=p->vt[9];((void(*)(P *))v.fn)(Adjusted(p,v));}
static inline void Matrix(P *p,const M4 &m){VTE &v=p->vt[37];((void(*)(P *,const M4 *))v.fn)(Adjusted(p,v),&m);}
static inline void Position(P *p,qword q){VTE &v=p->vt[29];((void(*)(P *,qword))v.fn)(Adjusted(p,v),q);}
static inline void Basis(P *p,const M3 &m){VTE &v=p->vt[30];((void(*)(P *,const M3 *))v.fn)(Adjusted(p,v),&m);}
static inline void Velocity(P *p,qword q){VTE &v=p->vt[35];((void(*)(P *,qword))v.fn)(Adjusted(p,v),q);}
static inline void Angular(P *p,qword q){VTE &v=p->vt[36];((void(*)(P *,qword))v.fn)(Adjusted(p,v),q);}
static inline void*operator new(unsigned size,void*destination){return destination;}
extern "C" void func_001CAA60(P *p,NODE *node){
 M4 inverse;
 P *object;
 void *cursor;
 P *owner;
 int row;
 int i,j;
 NODE *current=p->head;
 if(current){
  if(current==node){p->head=node->next;node->next=0;}
  else{
   NODE **link=&current->next;
   while((current=*link)!=0){
    if(current==node){*link=node->next;node->next=0;break;}
    link=&current->next;
   }
  }
 }
 node->owner=0;
 M4 *matrix=&node->matrix;
 owner=p;
 inverse=func_0011C318(matrix);
 func_002333B4(matrix,0,0x40);
 matrix->values[15]=1.0f;matrix->values[10]=1.0f;matrix->values[5]=1.0f;node->matrix.values[0]=1.0f;
 row=func_001CA930(p,node);
 for(i=0;i<p->table->count;i++){
  object=p->table->objects[row*p->table->count+i];
  for(j=0;j<p->bindCount;j++){
   BIND *bind=&p->binds[j];
   if(bind->kind==5)continue;
   RESOURCE *resource=bind->resource;
   if(resource && !p->disabled){
    void **slot=bind->slot;
    if(resource->count){func_00256EE0(slot,resource->items[0]);func_00127B70(resource,*slot);}
    else func_00256EE0(slot,0);
   }
   bind->slot=0;
  }
  Parent(object,p);
  cursor=&object;Query(p,&cursor);
  cursor=&owner;Query(object,&cursor);
  Reset(object);Matrix(object,inverse);
  func_001A58D0(object,0,0);
  if(func_00132B10(object,0x30)){
   P *o=object;
   POSE *pose=&p->table->states[i];
   if(o->enabledPosition){Position(o,pose->position);Velocity(o,D_002A2DD0);}
   if(o->enabledBasis){Basis(o,pose->basis);Angular(o,D_002A2DD0);}
  }
 }
}

#define OFF(t,m) ((int)&((t*)0)->m)
typedef char detach_layout[(sizeof(void*)==4 && sizeof(qword)==16 && sizeof(VTE)==8 && sizeof(M3)==0x30 && sizeof(M4)==0x40 && sizeof(POSE)==0x40 && sizeof(NODE)==0x50 && sizeof(BIND)==0x18 && sizeof(TABLE)==0x6C && sizeof(CONTEXT)==8 && sizeof(WORK)==0x60 && OFF(WORK,returned)==0 && OFF(VTE,delta)==0 && OFF(VTE,fn)==4 && OFF(NODE,owner)==0 && OFF(NODE,next)==4 && OFF(NODE,matrix)==0x10 && OFF(RESOURCE,count)==8 && OFF(RESOURCE,items)==0xC && OFF(BIND,kind)==0 && OFF(BIND,resource)==8 && OFF(BIND,slot)==0x14 && OFF(TABLE,count)==0 && OFF(TABLE,objects)==4 && OFF(TABLE,states)==0x64 && OFF(TABLE,nodes)==0x68 && OFF(P,vt)==0xC && OFF(P,enabledPosition)==0x58 && OFF(P,enabledBasis)==0x5C && OFF(P,table)==0xE0 && OFF(P,disabled)==0xE4 && OFF(P,head)==0xE8 && OFF(P,bindCount)==0xEC && OFF(P,binds)==0xF0 && OFF(CONTEXT,owner)==0 && OFF(CONTEXT,row)==4 && OFF(WORK,object)==0x40 && OFF(WORK,cursor)==0x44 && OFF(WORK,context)==0x48 && OFF(WORK,next)==0x50 && OFF(WORK,objectAddress)==0x54 && OFF(WORK,contextAddress)==0x58)?1:-1];

typedef char detach_copy_layout[(__alignof__(M4)==0x10 && __alignof__(WORK)==0x10 && OFF(POSE,position)==0 && OFF(POSE,basis)==0x10 && OFF(RESOURCE,refs)==0 && OFF(TABLE,rowBase)==0xC)?1:-1];
