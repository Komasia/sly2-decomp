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
struct TABLE {int count;P **objects;char pad8[0x5C];POSE *states;NODE *nodes;};
struct P {char pad[0xC];VTE *vt;char pad10[0x48];int enabledPosition,enabledBasis;char pad60[0x80];TABLE *table;int disabled;NODE *head;int bindCount;BIND *binds;};
struct CONTEXT {P *owner;int row;};
struct WORK {P *object;void *cursor;CONTEXT context;int next;P **objectAddress;CONTEXT *contextAddress;};
extern "C" {
extern qword D_002A2DD0;
M4 func_0011C318(const M4 *);
void *func_002333B4(void *,int,int);
int func_001CA930(P *,NODE *);
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
extern "C" void func_001CAA60(P *p,NODE *node){
 M4 inverse;
 WORK work;
 if(p->head){
  if(p->head==node)p->head=node->next;
  else{
   NODE *current=p->head;
   NODE **link=&current->next;
   current=current->next;
   while(current){if(current==node){*link=node->next;break;}link=&current->next;current=current->next;}
  }
 }
 node->next=0;node->owner=0;
 work.context.owner=p;
 inverse=func_0011C318(&node->matrix);
 func_002333B4(&node->matrix,0,0x40);
 node->matrix.values[5]=1.0f;node->matrix.values[15]=1.0f;node->matrix.values[10]=1.0f;node->matrix.values[0]=1.0f;
 work.context.row=func_001CA930(p,node);
 if(p->table->count>0){
  work.objectAddress=&work.object;work.contextAddress=&work.context;
  register void **cursor __asm__("$30")=&work.cursor;
  for(int i=0;i<p->table->count;i=work.next){
   work.next=i+1;
   work.object=p->table->objects[work.context.row*p->table->count+i];
   for(int j=0;j<p->bindCount;j++){
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
   Parent(work.object,p);
   work.cursor=work.objectAddress;Query(p,cursor);
   work.cursor=work.contextAddress;Query(work.object,cursor);
   Reset(work.object);Matrix(work.object,inverse);
   func_001A58D0(work.object,0,0);
   if(func_00132B10(work.object,0x30)){
    P *object=work.object;
    POSE *pose=&p->table->states[i];
    if(object->enabledPosition){Position(object,pose->position);Velocity(object,D_002A2DD0);}
    if(object->enabledBasis){Basis(object,pose->basis);Angular(object,D_002A2DD0);}
   }
  }
 }
}
