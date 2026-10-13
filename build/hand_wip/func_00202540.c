typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];int i[4];} V;
struct O;
struct VT {short delta,pad;void(*fn)(void*,qword*);};
struct O {char pad[0xC];struct VT *vt;char pad10[0x28];float height;char pad3C[0xA4];float radius;char padE4[0x24];int state;};
struct REF {struct O*o;};
struct P {char pad[0x20];V position;int count;struct O *items[20];char pad84[8];struct O*best;char pad90[0x18];struct REF *ref;};
struct CAMERA {char pad[0x90];qword position;};
extern struct CAMERA D_002DDF40;
extern const float D_002A8550;
int func_00203790(struct O*);
qword func_001A62E8(struct O*);
int func_0014F850(struct CAMERA*,qword,qword);
int func_0014F898(struct CAMERA*,qword,float,float*);
void func_00202378(struct P*,struct O*);
void func_00202768(struct P*,int);
static inline qword Sub(qword a,qword b){__asm__("vsub.xyzw %0,%1,%2":"=j"(a):"0"(a),"j"(b));return a;}
static inline qword SubSecond(qword a,qword b){__asm__("vsub.xyzw %0,%1,%2":"=j"(b):"j"(a),"0"(b));return b;}
static inline float LengthXY(qword a){float g;
__asm__("vmul.xy %0,%0,%0\n\tvaddy.x %0,%0,%0y":"=j"(a):"0"(a));
__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(a):"0"(a));
__asm__("qmfc2.ni %0,%1":"=r"(g):"j"(a));return g;}
static inline void Store(qword*p,qword q){__asm__("sq %1,%0":"=m"(*p):"r"(q));}
static inline qword ScalarBits(const float*p){qword q;__asm__("lw %0,%1":"=r"(q):"m"(*p));return q;}
void func_00202540(struct P*p)
{
 V radius,screen,position;
 struct O *best=0;
 int i=0;
 struct O *owner=p->ref->o;
 float minimum;
 struct O **slot;
 owner->vt[97].fn((char*)owner+owner->vt[97].delta,&p->position.q);
 p->position.f[2]+=20.0f;
 minimum=D_002A8550;
 if(p->count>0){slot=p->items;do{
   struct O *o=*slot;
   struct CAMERA *camera;
   float distance;
   if(!func_00203790(o))continue;
   Store(&position.q,func_001A62E8(o));
   camera=&D_002DDF40;
   radius.q=ScalarBits(&o->radius);
   if(!func_0014F850(camera,Sub(position.q,camera->position),radius.q))continue;
   if(!func_0014F898(camera,func_001A62E8(o),o->height,&screen.f[0]))continue;
   distance=LengthXY(SubSecond(position.q,camera->position));
   if(distance<minimum){
     func_00202378(p,o);
     if(o->state!=2){best=o;minimum=distance;}
   }
 }while(++slot,++i<p->count);}
 if(best!=p->best){p->best=best;func_00202768(p,2);}
}
