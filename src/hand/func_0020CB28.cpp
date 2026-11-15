// SelectK3 (0x20CB28): the directional player picks, while a change window is open, the direction whose clip's mean
// velocity best matches the requested one (the playing clip's score biased by D_002C3DE4) and plays it from its window
// marker (0x17D forward, else 0x17F); its velocity is the requested direction times the chosen clip's speed.
typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];} V;
union FLOATWORD {float value;int word;};
struct ASEG;struct ALO;
struct ASEGA {char pad[0x14];struct ASEG *paseg;};
struct ASEGEVENT {float t;};
/* one direction of a KIND3: its clip, mean velocity and speed */
struct KIND3E {struct ASEG *paseg;int pad[3];qword vel;FLOATWORD s20;int pad20[3];};
/* the directional player (SafeHouse guard.h K3PLAY) */
struct K3PLAY {char pad[0x10];qword vel;struct ALO *palo;struct ASEGA *pasega;struct KIND3E *pk3,*pcur;int grf,fForward,fBackward;};
extern const float D_002A8904;
extern float D_002C3DE4;
extern "C" struct ASEGEVENT *PeventLaunch(struct ASEG*,int) asm("PeventLaunch__FP5KINDEi");
void ApplyAsegCur(struct ASEG*,struct ALO*,float,float,int,struct ASEGA**);
extern "C" void AddLoListener__FP2LOi(struct ASEGA*,int);
static inline qword Dot(qword a,qword b){qword r,one;
__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(r),"=&j"(one):"j"(a),"j"(b));return r;}
static inline qword DotReuse(qword a,qword b){qword one;
__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(b),"=&j"(one):"j"(a),"0"(b));return b;}
static inline qword Sqrt(qword q){__asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"=j"(q):"0"(q));return q;}
static inline void Normalize(V*dst,qword v){qword length=Sqrt(Dot(v,v));register qword result __asm__("vf3");
__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=&j"(result):"j"(length),"j"(v));dst->q=result;}
static inline qword NormalizeEntry(qword v){qword length=Sqrt(Dot(v,v));
__asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(length):"0"(length),"j"(v));return length;}
static inline float Float(qword v){float f;__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(v));return f;}
static inline qword Scalar(const FLOATWORD*p){register qword v __asm__("vf1");register int w __asm__("$2")=p->word;__asm__("qmtc2.ni %1,%0":"=j"(v):"r"(w));return v;}
static inline qword Scale(qword v,qword s){register qword r __asm__("vf2");__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(s));return r;}
// name: SafeHouse port (SelectK3)
extern "C" void SelectK3__FP6K3PLAYG9VU_VECTOR(struct K3PLAY*pk3play,qword vecDir)
{
 V scalar,direction;
 register qword finalDirection __asm__("vf3");
 struct KIND3E *best=0;
 register struct KIND3E *current __asm__("v0");
 Normalize(&direction,vecDir);
 float maximum=D_002A8904;
 if(pk3play->fForward||pk3play->fBackward){
   struct KIND3E *entry;
   unsigned int i;float bias;
   register qword scoringDirection __asm__("vf4");
   __asm__("lqc2 %0,%4\n\tlw %1,%5\n\tdaddu %2,%z6,$zero\n\tlwc1 %3,%7":"=j"(scoringDirection),"=&r"(entry),"=&r"(i),"=f"(bias):"m"(direction.q),"m"(pk3play->pk3),"rJ"(0),"m"(D_002C3DE4));
   do{
     struct ASEG *animation=entry->paseg;
     if(animation){
       float score=Float(DotReuse(scoringDirection,NormalizeEntry(entry->vel)));
       if(animation==pk3play->pasega->paseg)score*=bias;
       if(maximum<score){maximum=score;best=entry;}
     }
   }while(++entry,++i<4);
 current=pk3play->pcur;
 finalDirection=direction.q;
 if(best!=current){
   float time=0.0f;
   struct ASEGEVENT*tag;
   struct ASEG*animation;
   int id;
   if(pk3play->fForward){id=0x17D;animation=best->paseg;}
   else {id=0x17F;animation=best->paseg;}
   tag=PeventLaunch(animation,id);
   if(tag)time=tag->t;
   ApplyAsegCur(best->paseg,pk3play->palo,time,1.0f,pk3play->grf,&pk3play->pasega);
   AddLoListener__FP2LOi(pk3play->pasega,(int)pk3play);
   pk3play->pcur=best;
 }
 }
 current=pk3play->pcur;finalDirection=direction.q;
 scalar.q=Scalar(&current->s20);
 pk3play->vel=Scale(finalDirection,scalar.q);
}
