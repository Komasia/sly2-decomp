// Build paired sampled paths from the two animation motions.
typedef int qword __attribute__((mode(TI)));
struct M4 {qword rows[4];};
struct VTE {short delta,pad;void *fn;};
struct SPACE {M4 matrix;char pad40[0x54];int kind;char pad98[8];SPACE *parent;};
struct LO {char padC[0xC];VTE *vt;char pad10[0x50];SPACE *space;};
struct SOURCE {char padC[0xC];VTE *vt;};
struct MOTION {char pad74[0x74];float duration;};
struct PATH {char padC[0xC];VTE *vt;char pad10[0xD0];int mode,cyclic,count;float *times,*distances;qword *points;};
struct BLEND {float weight;MOTION *motion;int flags;PATH *first,*second;};
struct P {LO *owner;void *animation;BLEND blends[2];MOTION *controller;SOURCE *source;SPACE *space;int word3C;M4 matrix;};
struct REQUEST {int size,alignment;};
union SCRATCH {M4 matrix;REQUEST request;};
struct WORK {M4 original;SCRATCH scratch;M4 sample;SPACE *originalSpace;int present;PATH **first,**second;MOTION **records;int nextI,nextJ;};
extern "C" {
extern int D_002C1ED0;
M4 *func_0011C168(M4 *,const M4 *,const M4 *);
PATH *func_0013E3C8(int,LO *,int,int);
void *func_001AE1D0(const REQUEST *);
void *func_002333B4(void *,int,int);
void func_001300B8(MOTION *,LO *,SPACE *,SPACE *,M4 *,M4 *,float,float);
void func_001E6180(PATH *);
void func_00137A30(LO *,int,int,BLEND *,int,void *,void *,MOTION **);
}
static inline PATH*PathReceiver(PATH*value){register PATH*path __asm__("$17");__asm__("daddu %0,%1,$zero":"=r"(path):"r"(value));return path;}
static inline void CopyOriginal(M4*destination,const M4*source){register qword row2 __asm__("$2"),row0 __asm__("$4"),row1 __asm__("$5"),row3 __asm__("$3");__asm__("lq %0,%7\n\tlq %1,%5\n\tlq %2,%6\n\tlq %3,%8\n\tsq %1,%4\n\tsq %2,16+%4\n\tsq %0,32+%4\n\tsq %3,48+%4":"=&r"(row2),"=&r"(row0),"=&r"(row1),"=&r"(row3),"=m"(*destination):"m"(source->rows[0]),"m"(source->rows[1]),"m"(source->rows[2]),"m"(source->rows[3]));}
static inline SPACE* CopyProduct(P*p,const M4*source){register SPACE*space __asm__("$2");register qword row1 __asm__("$3"),row2 __asm__("$4"),row3 __asm__("$5");__asm__("lq %0,%5\n\tlq %1,%6\n\tlq %2,%7\n\tlq %3,%8\n\tsq %0,%4\n\tlw %0,%9\n\tsq %1,16+%4\n\tsq %2,32+%4\n\tsq %3,48+%4":"=&r"(space),"=&r"(row1),"=&r"(row2),"=&r"(row3),"=m"(p->matrix):"m"(source->rows[0]),"m"(source->rows[1]),"m"(source->rows[2]),"m"(source->rows[3]),"m"(p->space));return space;}
static inline void* OriginalEntry(const VTE*table,int*adjustment){register void*function __asm__("$2");register int delta __asm__("$4");__asm__("lw %0,0x104(%2)\n\tlh %1,0x100(%2)":"=&r"(function),"=r"(delta):"r"(table),"m"(table[32].fn),"m"(table[32].delta));*adjustment=delta;return function;}
static inline SPACE* ParentSpace(const SPACE*oldSpace){register SPACE*parent __asm__("$3");__asm__("lw %0,%1":"=r"(parent):"m"(oldSpace->parent));return parent;}
static inline const VTE* SourceTable(const SOURCE*source){register const VTE*table __asm__("$3");__asm__("lw %0,%1":"=r"(table):"m"(source->vt));return table;}
static inline void Reset(PATH *p){VTE &v=p->vt[9];((void(*)(PATH *))v.fn)((PATH *)((char *)p+v.delta));}
static inline qword ReadPoint(const qword*p){register qword v __asm__("vf5");__asm__("lqc2 %0,%1":"=j"(v):"m"(*p));return v;}
static inline qword ReadRow0(const qword*p){register qword v __asm__("vf2");__asm__("lqc2 %0,%1":"=j"(v):"m"(*p));return v;}
static inline qword ReadRow1(const qword*p){register qword v __asm__("vf4");__asm__("lqc2 %0,%1":"=j"(v):"m"(*p));return v;}
static inline qword ReadRow2(const qword*p){register qword v __asm__("vf3");__asm__("lqc2 %0,%1":"=j"(v):"m"(*p));return v;}
static inline qword ReadRow3(const qword*p){register qword v __asm__("vf1");__asm__("lqc2 %0,%1":"=j"(v):"m"(*p));return v;}
static inline qword Point(const M4&m,const qword*position){
 qword v=ReadPoint(position),r=ReadRow0(&m.rows[0]),b=ReadRow1(&m.rows[1]),c=ReadRow2(&m.rows[2]),d=ReadRow3(&m.rows[3]);
 __asm__("vmulax.xyz $ACC,%0,%4x\n\tvmadday.xyz $ACC,%1,%4y\n\tvmaddaz.xyz $ACC,%2,%4z\n\tvmaddw.xyz %0,%3,$vf0w":"+j"(r):"j"(b),"j"(c),"j"(d),"j"(v));return r;
}
static inline void StorePath(PATH **slot,PATH *path){__asm__("sw %1,%0":"=m"(*slot):"r"(path));}
static inline void StoreSpace(SPACE **slot,SPACE *space){__asm__("sw %1,%0":"=m"(*slot):"r"(space));}
static inline SPACE *LoadSpace(SPACE **slot){register SPACE *space __asm__("$3");__asm__("lw %0,%1":"=r"(space):"m"(*slot));return space;}
extern "C" void func_001CC5E8(P *p,LO *owner,void *animation){
 WORK work;
 p->owner=owner;p->animation=animation;
 if(!p->source)return;
 SOURCE *source=p->source;const VTE*table=SourceTable(source);
 work.records=&p->blends[0].motion;
 int delta;void*function=OriginalEntry(table,&delta);
 StoreSpace(&work.originalSpace,((SPACE*(*)(SOURCE *,M4 *))function)((SOURCE *)((char *)source+delta),&work.original));
 CopyOriginal(&p->matrix,&work.original);p->space=LoadSpace(&work.originalSpace);
 while(p->space->kind!=6){func_0011C168(&work.scratch.matrix,&p->space->matrix,&p->matrix);p->space=ParentSpace(CopyProduct(p,&work.scratch.matrix));}
 work.present=0;
 for(int i=0;i<2;i=work.nextI){
  int offset=i*sizeof(BLEND);work.nextI=i+1;
  MOTION *motion=*(MOTION **)((char *)work.records+offset);
  if(!motion)continue;
  work.first=(PATH **)((char *)&p->blends[0].first+offset);work.second=(PATH **)((char *)&p->blends[0].second+offset);++work.present;
  register M4 *working __asm__("$19")=&work.scratch.matrix;
  register REQUEST *request __asm__("$22")=&work.scratch.request;
  for(int j=0;j<2;j=work.nextJ){
   PATH *path=PathReceiver(func_0013E3C8(10,p->owner,0xB2,-1));
   path->mode=0;path->count=D_002C1ED0;
   request->size=D_002C1ED0*4;request->alignment=16;path->times=(float *)func_001AE1D0(request);
   request->size=D_002C1ED0*4;request->alignment=16;path->distances=(float *)func_001AE1D0(request);
   request->size=D_002C1ED0*16;request->alignment=16;path->points=(qword *)func_001AE1D0(request);
   SPACE *space;
   if(j==0){work.scratch.matrix=work.original;space=work.originalSpace;}
   else{space=p->space;func_002333B4(working,0,0x40);((float *)working)[15]=1.0f;((float *)working)[10]=1.0f;((float *)working)[5]=1.0f;((float *)working)[0]=1.0f;}
   work.nextJ=j+1;
   int k=0;
   if(D_002C1ED0>0)for(;;){
    float t=(float)k/(float)(D_002C1ED0-1);
    func_001300B8(motion,p->owner,space,p->owner->space,&work.sample,0,t*motion->duration,0.0f);
    path->times[k]=t;qword *destination=&path->points[k];++k;int limit=D_002C1ED0;*destination=Point(work.sample,&work.scratch.matrix.rows[3]);
    if(k>=limit)break;
   }
   Reset(path);func_001E6180(path);
   if(j==0)*work.first=path;else StorePath(work.second,path);
  }
 }
 if(work.present==2){p->blends[0].weight=1.0f;func_00137A30(p->owner,20,2,p->blends,0,0,0,&p->controller);}
}

#define OFF(t,m) ((int)&((t*)0)->m)
typedef char sampling_layout[(sizeof(qword)==16 && sizeof(void*)==4 && sizeof(VTE)==8 && sizeof(M4)==0x40 && sizeof(BLEND)==0x14 && sizeof(REQUEST)==8 && sizeof(SCRATCH)==0x40 && sizeof(WORK)==0xE0 && OFF(VTE,delta)==0 && OFF(VTE,fn)==4 && OFF(SPACE,matrix)==0 && OFF(SPACE,kind)==0x94 && OFF(SPACE,parent)==0xA0 && OFF(LO,space)==0x60 && OFF(SOURCE,vt)==0xC && OFF(MOTION,duration)==0x74 && OFF(PATH,vt)==0xC && OFF(PATH,mode)==0xE0 && OFF(PATH,count)==0xE8 && OFF(PATH,times)==0xEC && OFF(PATH,distances)==0xF0 && OFF(PATH,points)==0xF4 && OFF(BLEND,weight)==0 && OFF(BLEND,motion)==4 && OFF(BLEND,first)==0xC && OFF(BLEND,second)==0x10 && OFF(P,owner)==0 && OFF(P,animation)==4 && OFF(P,blends)==8 && OFF(P,controller)==0x30 && OFF(P,source)==0x34 && OFF(P,space)==0x38 && OFF(P,matrix)==0x40 && OFF(REQUEST,size)==0 && OFF(REQUEST,alignment)==4 && OFF(WORK,original)==0 && OFF(WORK,scratch)==0x40 && OFF(WORK,sample)==0x80 && OFF(WORK,originalSpace)==0xC0 && OFF(WORK,present)==0xC4 && OFF(WORK,first)==0xC8 && OFF(WORK,second)==0xCC && OFF(WORK,records)==0xD0 && OFF(WORK,nextI)==0xD4 && OFF(WORK,nextJ)==0xD8 && sizeof(int)==4 && __alignof__(qword)==16 && OFF(M4,rows[0])==0 && OFF(M4,rows[1])==0x10 && OFF(M4,rows[2])==0x20 && OFF(M4,rows[3])==0x30 && sizeof(((VTE*)0)->delta)==2 && sizeof(((VTE*)0)->fn)==4 && sizeof(((SPACE*)0)->parent)==4)?1:-1];
