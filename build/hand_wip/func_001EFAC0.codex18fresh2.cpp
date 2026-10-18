typedef unsigned int uint;
struct VTE {short delta,pad;void(*fn)();};
struct CHILD {char padC[0xC];VTE *vt;char pad10[8];int id;};
struct PAIR {int id,next;};
struct EDGE {CHILD *child;int from,to;uint flags;int value;float weight;};
struct GROUP {uint mask;signed char *distance;};
struct DL {void *first,*last;int offset;};
struct GRAPH {char pad10[0x10];void *root;char pad14[0x3C];int count;PAIR *nodes;int edgeCount;EDGE *edges;int groupCount;GROUP *groups;DL active;};
struct IF {VTE *vt;};
struct DA {VTE *vt;int capacity,count;CHILD **items;};
struct REQUEST {int size,alignment;void *Allocate(int);void *Zero(int);void *Copy(int,void *);};
struct FRAME;
extern "C" {
void func_0011A1F8(DL*,int);
FRAME *func_001AE478(FRAME*);
void func_001AE4A0(FRAME*,int);
DA *func_0013F888(DA*);
void func_0013FB40(void*,void*,IF*);
unsigned char func_00117BD0(void*);
int func_00117DB8(void*);
float func_00117E38(void*);
void *func_001AE1D0(REQUEST*);
void *func_001AE378(REQUEST*);
void *func_001AE238(REQUEST*,void*);
int func_001F0438(GRAPH*,int);
void func_0013F810(GRAPH*,void*);
}
struct FRAME {FRAME(){func_001AE478(this);}~FRAME(){func_001AE4A0(this,2);}};
inline void *REQUEST::Allocate(int bytes){size=bytes;alignment=16;return func_001AE1D0(this);}
inline void *REQUEST::Zero(int bytes){size=bytes;alignment=16;return func_001AE378(this);}
inline void *REQUEST::Copy(int bytes,void *source){size=bytes;alignment=16;return func_001AE238(this,source);}

static inline void Initialize(CHILD *p){VTE &v=p->vt[9];((void(*)(void*))v.fn)((char*)p+v.delta);}
static inline int ChildId(int value){
 register int result __asm__("$4");
 __asm__("daddu %0,%1,$zero":"=r"(result):"r"(value));
 return result;
}
struct EDGE_FLAGS {
 uint address;
 EDGE_FLAGS(const EDGE *edges):address((uint)edges+12){}
 uint Read()const{return *(const uint *)address;}
 void Next(){address+=sizeof(EDGE);}
};
extern "C" void func_001EFAC0(GRAPH *p,void *stream){
 int i=0;
 func_0011A1F8(&p->active,0x14);
 FRAME frame;
 DA children;func_0013F888(&children);
 REQUEST request;
 uint masks[32];
 func_0013FB40(p->root,stream,(IF*)&children);
 for(;i<children.count;i++)Initialize(children.items[i]);
 i=0;
 p->count=func_00117BD0(stream);
  p->nodes=(PAIR*)request.Allocate(p->count*8);
 for(;i<p->count;i++){
  PAIR *entry=&p->nodes[i];
  entry->id=func_00117DB8(stream);
  entry->next=func_00117DB8(stream);
 }
 i=0;
 if(p->count>0){
  register int noNode __asm__("$18")=-2;
  do{
   PAIR *entry=&p->nodes[i];int id=entry->next;
   if(id==-1)entry->next=id;else if(id==0x20)entry->next=noNode;else entry->next=func_001F0438(p,entry->next);
   ++i;
  }while(i<p->count);
 }
 uint all=0;
 p->edgeCount=func_00117BD0(stream);
  p->edges=(EDGE*)request.Zero(p->edgeCount*(int)sizeof(EDGE));
 int offset=0,edgeIndex=0;
 for(;edgeIndex<p->edgeCount;edgeIndex++,offset+=(int)sizeof(EDGE)){
  EDGE *edge=(EDGE*)((char*)p->edges+offset);
  edge->from=func_001F0438(p,func_00117DB8(stream));
  edge->to=func_001F0438(p,func_00117DB8(stream));
  edge->flags=func_00117DB8(stream);
  edge->value=func_00117DB8(stream);
  edge->weight=func_00117E38(stream);
  int id=ChildId(func_00117DB8(stream));
  if(id!=-1){
   if(children.count>0){
    i=0;CHILD *child;
    for(;;){child=children.items[i];if(child->id==id)break;if(++i>=children.count)break;}
    edge->child=child;
   }
   if(!edge->child){--p->edgeCount;--edgeIndex;offset-=(int)sizeof(EDGE);continue;}
  }
  all|=edge->flags&0xFFFC;
 }
 p->edges=(EDGE*)request.Copy(p->edgeCount*(int)sizeof(EDGE),p->edges);
 func_0013F810(p,stream);
 int maskCount=0;
 for(int bit=4;bit<=0x1000;bit<<=1){
  if(!(all&bit))continue;
  int j=0;
  for(;j<maskCount;j++)if(masks[j]&bit)break;
  if(j!=maskCount)continue;
  uint mask=all;
  {edgeIndex=p->edgeCount;
   if(edgeIndex>0){EDGE_FLAGS flags(p->edges);do{uint f=flags.Read();--edgeIndex;flags.Next();if(f&bit)mask&=f;}while(edgeIndex!=0);}
  }
  {edgeIndex=p->edgeCount;
   if(edgeIndex>0){EDGE_FLAGS flags(p->edges);do{uint f=flags.Read();if((f&mask)&&!(f&bit))mask&=~f;--edgeIndex;flags.Next();}while(edgeIndex!=0);}
  }
  masks[maskCount++]=mask;
 }
 p->groupCount=maskCount;
 p->groups=(GROUP*)request.Allocate(maskCount*(int)sizeof(GROUP));
 for(int groupIndex=0;groupIndex<p->groupCount;){
  GROUP *group=&p->groups[groupIndex];
  group->mask=masks[groupIndex];
    group->distance=(signed char*)request.Allocate(p->count*p->count);
  int nextGroup=groupIndex+1;
  for(int row=0;row<p->count;row++){
   for(int column=0;column<p->count;column++)group->distance[row*p->count+column]=row==column?0:-1;
  }
  int depth=1,changed;
  do{
   changed=0;
   for(groupIndex=0;groupIndex<p->edgeCount;groupIndex++){
    EDGE *edge=&p->edges[groupIndex];
    if(edge->flags&group->mask){
     for(i=0;i<p->count;i++){
      signed char *matrix=group->distance;int from=edge->from;
      if(matrix[i*p->count+from]==depth-1&&matrix[i*p->count+edge->to]<0){matrix[i*p->count+edge->to]=depth;goto row_changed;}
      else if(edge->flags&1){
       if(matrix[i*p->count+edge->to]==depth-1&&matrix[i*p->count+from]<0){matrix[i*p->count+from]=depth;goto row_changed;}
      }
      continue;
row_changed:
      changed=1;
     }
    }
   }
   ++depth;
  }while(changed);
  groupIndex=nextGroup;
 }
}

#define OFF(t,m) ((unsigned int)&((t*)0)->m)
typedef char graph_layout[(sizeof(void*)==4 && sizeof(uint)==4 && sizeof(VTE)==8 && sizeof(PAIR)==8 && sizeof(EDGE)==24 && sizeof(GROUP)==8 && sizeof(DL)==12 && sizeof(DA)==16 && sizeof(REQUEST)==8 && sizeof(FRAME)==1 && __alignof__(FRAME)==1 && OFF(VTE,delta)==0 && OFF(VTE,fn)==4 && OFF(CHILD,vt)==0xC && OFF(CHILD,id)==0x18 && OFF(PAIR,id)==0 && OFF(PAIR,next)==4 && OFF(EDGE,child)==0 && OFF(EDGE,from)==4 && OFF(EDGE,to)==8 && OFF(EDGE,flags)==0xC && OFF(EDGE,value)==0x10 && OFF(EDGE,weight)==0x14 && OFF(GROUP,mask)==0 && OFF(GROUP,distance)==4 && OFF(GRAPH,root)==0x10 && OFF(GRAPH,count)==0x50 && OFF(GRAPH,nodes)==0x54 && OFF(GRAPH,edgeCount)==0x58 && OFF(GRAPH,edges)==0x5C && OFF(GRAPH,groupCount)==0x60 && OFF(GRAPH,groups)==0x64 && OFF(GRAPH,active)==0x68 && OFF(DL,offset)==8 && OFF(DA,vt)==0 && OFF(DA,capacity)==4 && OFF(DA,count)==8 && OFF(DA,items)==0xC && OFF(REQUEST,size)==0 && OFF(REQUEST,alignment)==4)?1:-1];
