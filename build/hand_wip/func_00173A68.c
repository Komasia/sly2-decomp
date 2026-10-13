// 25/172 instructions differ.
typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];} U;
struct VT{short delta,pad;void*fn;};
struct LO{char pad[0xC];struct VT*vt;char pad10[0xF54];void*xF64;};
struct SELECTOR{int kind;char pad4[0x10];int used;};
struct ENTRY{struct LO*object;float time,wait;struct SELECTOR*selector;};
struct EVENT{float time;char pad4[8];int tag;char pad10[0x18];int kind,previous;};
struct P{char pad[0xC];struct VT*vt;char pad10[0x48];int count,capacity;char pad60[0x10];qword last;char pad80[0x28];float next;int mode;};
struct M3{qword r[3];};
struct LINK{struct LO**pp;};
extern char D_003DD490[];
extern float D_002DDED0,D_002BE5CC,D_002BE5D0,D_002BE5D4,D_002BE5D8;
void func_001A5E28(struct P*);
qword func_00173A18(struct P*);
void func_00173D18(struct P*,qword);
int func_001C4840(void*);
struct EVENT*func_001F8240(int,int);
struct ENTRY*func_00173E78(struct P*,int);
struct SELECTOR*func_00173F18(struct P*,qword,qword*,struct M3*,int*);
void func_00173928(struct P*,struct ENTRY*,int,int);
struct LO*func_00174490(struct P*,struct SELECTOR*,qword*,struct M3*,int);
void func_001F7D10(struct LO*,float);
void func_001F7C68(struct LO*,float);
void func_00154038(void*,int,int);
static inline float DistanceXY(qword a,qword b){qword d;float f;__asm__("vsub.xyzw %0,%1,%2":"=j"(d):"j"(a),"j"(b));__asm__("vmul.xy %0,%0,%0\n\tvaddy.x %0,%0,%0y":"+j"(d));__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(d):"0"(d));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(d));return f;}
void func_00173A68(struct P*p){
 U point;
 struct M3 rotation;
 int flag;
 struct LO*object;
 struct LINK link;
 qword pos;
 struct EVENT*event;
 struct ENTRY*entry;
 struct SELECTOR*selector;
 int context;
 func_001A5E28(p);
 pos=func_00173A18(p);
 func_00173D18(p,pos);
 if(D_002DDED0<p->next)return;
 p->next=D_002DDED0+D_002BE5D0;
 if(p->count==p->capacity){int close=DistanceXY(pos,p->last)<D_002BE5D4;if(close)return;}
 event=0;context=func_001C4840(D_003DD490);
 {register int zero __asm__("$5")=0;
 if(context){
  event=func_001F8240(context,zero);
  if(event){
   if(!event->kind)event=0;
   else switch(p->mode){
   case 0:return;
   case 1:if(D_002DDED0-event->time>D_002BE5CC)return;break;
   case 2:break;
   }
  }
 }
 }
 entry=func_00173E78(p,event&&event->kind==1?event->previous:0);
 if(!entry)return;
 selector=func_00173F18(p,pos,&point.q,&rotation,&flag);
 if(!selector)return;
 p->last=pos;
 if(entry->object)func_00173928(p,entry,0,1);
 object=func_00174490(p,selector,&point.q,&rotation,flag);
 if(!object)return;
 func_001F7D10(object,0.01f);
 func_001F7C68(object,0.5f);
 if(event)func_00154038(object->xF64,event->tag,2);
 entry->object=object;
 entry->time=D_002DDED0;
 entry->selector=selector;
 p->count++;
 selector->used=1;
 link.pp=&object;
 p->next=D_002DDED0+D_002BE5D8;
 ((void(*)(void*,int,int,int,struct LINK*,int,int))p->vt[3].fn)((char*)p+p->vt[3].delta,0x19,0,1,&link,0,1);
}
