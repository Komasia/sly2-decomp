typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];} V;
struct ASEG;struct ALO;
struct ASEGA {char pad[0x14];struct ASEG *owner;};
struct TAG {float value;int kind,id,pad;};
struct E {struct ASEG *animation;int pad[3];qword velocity;float speed;int pad20[3];};
struct P {char pad[0x10];qword direction;struct ALO *root;struct ASEGA *active;struct E *entries,*best;int flags,forward,backward;};
extern const float D_002A8904;
extern float D_002C3DE4;
extern "C" struct TAG *func_0012F938(struct ASEG*,int);
void ApplyAsegCur(struct ASEG*,struct ALO*,float,float,int,struct ASEGA**);
extern "C" void func_001333C0(struct ASEGA*,int);
static inline qword Dot(qword a,qword b){qword r,one;
__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(r),"=&j"(one):"j"(a),"j"(b));return r;}
static inline qword DotReuse(qword a,qword b){qword one;
__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(b),"=&j"(one):"j"(a),"0"(b));return b;}
static inline qword Sqrt(qword q){__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(q):"0"(q));return q;}
static inline qword Normalize(qword v){qword length=Sqrt(Dot(v,v)),result;
__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(result):"j"(length),"j"(v));return result;}
static inline qword NormalizeEntry(qword v){qword length=Sqrt(Dot(v,v));
__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(length):"0"(length),"j"(v));return length;}
static inline float Float(qword v){float f;__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(v));return f;}
static inline qword Scalar(const float*p){qword v;__asm__("qmtc2.ni %1,%0":"=j"(v):"r"(*(const int*)p));return v;}
static inline qword Scale(qword v,qword s){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(s));return r;}
static inline float StartTime(struct ASEG*a,int id){float f=0.0f;struct TAG*t=func_0012F938(a,id);if(t)f=t->value;return f;}
extern "C" void func_0020CB28(struct P*p,qword v)
{
 V scalar,direction;
 struct E *best=0;
 direction.q=Normalize(v);
 float maximum=D_002A8904;
 if(p->forward||p->backward){
   struct E *entry=p->entries;
   unsigned int i=0;
   float bias=D_002C3DE4;
   do{
     struct ASEG *animation=entry->animation;
     if(animation){
       float score=Float(DotReuse(direction.q,NormalizeEntry(entry->velocity)));
       if(animation==p->active->owner)score*=bias;
       if(maximum<score){maximum=score;best=entry;}
     }
   }while(++entry,++i<4);
 }
 if(best!=p->best){
   float time;
   if(p->forward)time=StartTime(best->animation,0x17D);
   else time=StartTime(best->animation,0x17F);
   ApplyAsegCur(best->animation,p->root,time,1.0f,p->flags,&p->active);
   func_001333C0(p->active,(int)p);
   p->best=best;
 }
 scalar.q=Scalar(&p->best->speed);
 p->direction=Scale(direction.q,scalar.q);
}
