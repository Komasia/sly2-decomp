// Attach an object node, bind its resources, and update its children.
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct P;
struct M4 {qword rows[4];};
struct NODE {P *owner;NODE *next;char pad8[8];M4 matrix;};
struct TREE {int id;TREE *parent;char pad8[8];P *owner;};
struct BIND {int kind,pad4;void *resource;void *begin,*end;P *object;};
struct TABLE {int count;P **objects;int capacity,used;char pad10[0x54];void *states;NODE *nodes;};
struct P {void *resource;char pad4[8];VTENT *vt;void *context;char pad14[0x24];float scale;char pad3C[0x14];void *channel;char pad54[0xC];M4 matrix;char padA0[0x40];TABLE *table;int disabled;NODE *head;int bindCount;BIND *binds;};
struct SW {char pad[0x3F08];TABLE *tables;TREE *root;};
struct DESC {int kind,flags;char pad8[0x20];};
struct STREAM {int flags;unsigned char *cursor;int remaining,consumed;unsigned char *raw;int rawCount,compression,pending,word20;unsigned char *decompressed;int word28,word2C;VTENT *vt;void *begin,*end;};
struct WORK {int id;P *found,*child;void *cursor;P *owner;};
extern "C" {
extern SW g_sw;
extern DESC D_002AC880[];
NODE *IrowProxyChoose(P *,int) asm("IrowProxyChoose__FP2SWi");
void DetachProxy(P *,NODE *) asm("DetachProxy__FP5PROXYP10PROXYSPARE");
int func_001CA930(P *,NODE *);
int func_001C9940(int,int);
TREE *func_001C99D8(TREE *,int,int *);
int CFindObjects(SW *,int,int,P *,void *,int,P **) asm("CFindObjects__FP2SWi3OIDP2LOPviPP2LO");
STREAM *func_00118480(STREAM *);
void func_00118500(STREAM *,void *,void *,int);
short S16Read(STREAM *) asm("S16Read__18CBinaryInputStream");
void LoadOptionFromBrx(P *,DESC *,int,STREAM *) asm("LoadOptionFromBrx__FPvP5EOPIDiP18CBinaryInputStream");
void AddParent(void *,void *) asm("AddParent__6CFrameP6CFrame");
void func_00256EE0(void **,void *);
void func_001184B8(STREAM *,int);
}
static inline P *Adjusted(P *p,const VTENT &entry){return (P *)VT_THIS(p, &entry);}
static inline void Channel(P *p,void *context,void *channel){VTENT &v=p->vt[10];((void(*)(P *,void *,void *,int))v.pfn)(Adjusted(p,v),context,channel,0);}
static inline void Matrix(P *p,const M4 *m){VTENT &v=p->vt[37];((void(*)(P *,const M4 *))v.pfn)(Adjusted(p,v),m);}
static inline void Reset(P *p){VTENT &v=p->vt[8];((void(*)(P *))v.pfn)(Adjusted(p,v));}
static inline void Parent(P *p,P *parent){VTENT &v=p->vt[26];((void(*)(P *,P *))v.pfn)(Adjusted(p,v),parent);}
static inline void Query(P *p,void **cursor){VTENT &v=p->vt[3];((void(*)(P *,int,int,int,void **,int))v.pfn)(Adjusted(p,v),14,0,1,cursor,0);}
extern "C" NODE *func_001CAEC8(P *p,int minimum){
 STREAM stream;
 WORK work;
 NODE *node=IrowProxyChoose(p,minimum);
 if(!node)return 0;
 if(node->owner)DetachProxy(node->owner,node);
 node->owner=p;node->next=p->head;p->head=node;
 work.owner=p;
 node->matrix=p->matrix;
 int row=func_001CA930(p,node);
 work.id=func_001C9940(p->table-g_sw.tables,row);
 TREE *tree=func_001C99D8(g_sw.root,1,&work.id);
 for(int i=0;i<p->bindCount;i++){
  BIND *bind=&p->binds[i];
  if(bind->kind==5)continue;
  if(bind->kind==6){work.found=tree->owner;if(!work.found)continue;}
  else if(CFindObjects(&g_sw,0xA05,bind->kind,0,tree,1,&work.found)!=1)continue;
  bind->object=work.found;
  func_00118480(&stream);
  func_00118500(&stream,bind->begin,bind->end,0);
  int index;
  while((index=S16Read(&stream))>=0){DESC *desc=&D_002AC880[index];LoadOptionFromBrx(work.found,desc,desc->flags&0x2031,&stream);}
  if(bind->resource && !p->disabled){
   if(work.found->resource)AddParent(bind->resource,work.found->resource);
   func_00256EE0(&work.found->resource,bind->resource);
  }
  func_001184B8(&stream,2);
 }
 for(int i=0;i<p->table->count;i++){
 void **cursor=&work.cursor;
  P *child=p->table->objects[row*p->table->count+i];
  VTENT &entry=child->vt[42];
  work.child=child;
  ((void(*)(P *,float))entry.pfn)(Adjusted(child,entry),p->scale);Channel(work.child,p->context,p->channel);Matrix(work.child,&p->matrix);Reset(work.child);Parent(work.child,p);
  work.cursor=&work.child;Query(p,cursor);
  work.cursor=&work.owner;Query(work.child,cursor);
 }
 return node;
}

#define OFF(t,m) ((int)&((t*)0)->m)
