typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
struct Node;
struct Origin {char pad[0x70];qword pos;};
struct Stats {struct Node *owner;qword *origin;int count,unusedC;float low;int unused14,unused18;float high,scale;char unknown24[0xC];};
struct Node {
 char pad[0x10];struct Node *parent;
 char pad14[0x60-0x14];struct Origin *reference;
 char pad64[0xA0-0x64];float radius;
 char padA4[0xD0-0xA4];ulong flags;
 char padD8[0x134-0xD8];struct Stats *stats;
 int unused138;float scale;
 char pad140[8];ulong state;
};
extern char D_003E12D4[];
struct Stats *func_0011CCC0(void *);
qword func_001A62E8(struct Node *);
static inline float Distance(qword a,qword b) {
 qword d,one;
 float result;
 __asm__("vsub.xyzw %0,%1,%2":"=j"(d):"j"(a),"j"(b));
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"0"(d));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(d));
 __asm__("mtc1 %1,%0":"=f"(result):"r"(d));
 return result;
}
static inline ulong LoadState(struct Node *p)
{
    register ulong value __asm__("$2");
    __asm__("ld %0,%1":"=r"(value):"m"(p->state));
    return value;
}
void func_001F2500(struct Node *p) {
 struct Node *top;
 struct Stats *attached;
 if (!(p->flags & (3UL<<32))) return;
 top=p;
 attached=p->stats;
 if(attached)goto count;
scan:
 {
   register struct Node *next __asm__("$4")=top->parent;
   if(!next || ((int)((unsigned int)(int)LoadState(top)<<8)>>28)==1) {
     struct Stats *s=func_0011CCC0(D_003E12D4);
     top->stats=s;
     p->stats=s;
     s->origin=&top->reference->pos;
     ++p->stats->count;
     p->stats->scale=p->scale;
     p->stats->owner=p;
     if(top==p)goto position;
     attached=p->stats;
     goto count;
   }
   top=next;
   attached=top->stats;
   if(!attached)goto scan;
   p->stats=attached;
 }
count:
 ++attached->count;
position:

 {
   qword position=func_001A62E8(p);
   float radius=p->radius+Distance(position,*p->stats->origin);
   if(p->flags&(1UL<<32)) {
     if(p->stats->low<radius) p->stats->low=radius;
   }
   if(p->flags&(1UL<<33)) {
     if(p->stats->high<radius) p->stats->high=radius;
   }
 }
}
