// Advance animation keys and update changed reusable sprite entries.
typedef unsigned char uchar;
typedef unsigned short ushort;
struct RGBA_RAW {uchar r,g,b,a;};
struct RGBA {uchar r,g,b,a;RGBA(){}RGBA(const RGBA &c){*(RGBA_RAW *)this=*(const RGBA_RAW *)&c;}RGBA(const RGBA_RAW &c){*(RGBA_RAW *)this=c;}RGBA &operator=(const RGBA &c){*(RGBA_RAW *)this=*(const RGBA_RAW *)&c;return *this;}} __attribute__((aligned(16)));
struct M23 {float a[6];} __attribute__((aligned(16)));
struct SPRITE;
struct ITEM {RGBA_RAW additive,multiply;char pad8[8];M23 matrix;SPRITE *sprite;int kind;float previousTime;RGBA_RAW previousAdditive,previousMultiply;M23 *previousMatrix;float nextTime;RGBA_RAW nextAdditive,nextMultiply;M23 *nextMatrix;int index;float cachedTime;uchar interpolate,mode;char pad62[2];int field64;int flags,pad6C;};
struct REUSE {int count;ITEM *items;ushort index,phase;float time;int field10,field14;};
struct ANIM;
struct GROUP {ushort animCount,reuseCount;ANIM *animations;REUSE *reuse;char padC[0x14];int index;void *owner;int first,pad2C;};
struct KEYPOSE {ushort id,index,offset;short color;char pad8[8];M23 matrix;uchar interpolate,mode;char pad32[2];int selected;char pad38[8];};
struct COLORS {RGBA_RAW multiply,additive;};
struct TAG {int kind,value;};
struct KEY {float time;uchar itemCount,colorCount,shortCount,byteCount;uchar *bytes;KEYPOSE *items;COLORS *colors;ushort *shorts;uchar tagCount;char pad19[3];TAG *tags;};
struct ANIM {ushort count,pad2;KEY *keys;float duration;void *owner;GROUP *group;int id;};
extern "C" {
void func_0011A058(int *);
void func_00219190(ANIM *,int,int);
void func_002190F8(ANIM *,int,int);
void func_00219348(ANIM *,int,int);
void func_00219400(float,float,ANIM *,int,int,M23 *,const RGBA *,const RGBA *);
void func_002158C0(SPRITE *,ITEM *);
void func_00218790(RGBA *,RGBA *,RGBA *,RGBA *,RGBA *,RGBA *);
void func_00215850(float,SPRITE *,ITEM *,M23 *,RGBA,RGBA);
}
static inline int NLerp(float t,int previous,int next){
 if(previous==next)return next;
 if(previous<next)return previous+(int)(t*((float)next+0.999f-(float)previous));
 return next+(int)((1.0f-t)*((float)previous+0.999f-(float)next));
}
static inline RGBA BlendColors(float t,RGBA previous,RGBA next){
 RGBA result;
 result.r=NLerp(t,previous.r,next.r);result.g=NLerp(t,previous.g,next.g);result.b=NLerp(t,previous.b,next.b);result.a=NLerp(t,previous.a,next.a);
 return result;
}
static inline M23 BlendMatrix(float t,const M23 &previous,const M23 &next){
 M23 result;float from=1.0f;from-=t;const float *a=previous.a,*b=next.a;float *out=result.a;
 for(int n=5;n>=0;n--){*out++=from * *a++ + t * *b++;}
 return result;
}
static inline M23 Mul(const M23 &q,const M23 &n){
 float m0=q.a[0],m1=q.a[1],m2=q.a[2],m3=q.a[3],m4=q.a[4],m5=q.a[5];M23 r;
 r.a[0]=m0*n.a[0]+m1*n.a[2];r.a[1]=m0*n.a[1]+m1*n.a[3];r.a[2]=m2*n.a[0]+m3*n.a[2];r.a[3]=m2*n.a[1]+m3*n.a[3];r.a[4]=m4*n.a[0]+m5*n.a[2]+n.a[4];r.a[5]=m4*n.a[1]+m5*n.a[3]+n.a[5];return r;
}
extern "C" void func_00219FE0(float duration,ANIM *animation,int index,M23 *parent,RGBA additive,RGBA multiply){
 int reuseOffset=index*sizeof(REUSE);
 REUSE *reuse=(REUSE *)(reuseOffset+(int)animation->group->reuse);
 int count;ITEM *items;items=reuse->items;count=reuse->count;float time=reuse->time,processed=time;
 int phase=reuse->phase;int first=(unsigned)phase<1;
 M23 matrix;RGBA outputAdditive,outputMultiply,currentAdditive,keyMultiply,currentMultiply;
 do{
  if(phase<animation->count&&animation->keys[phase].time<=time){
   processed=animation->keys[phase].time;
   func_00219190(animation,phase,index);
   func_002190F8(animation,phase,index);
   func_00219348(animation,phase,index);
   currentAdditive=additive;keyMultiply=multiply;
   func_00219400(processed,duration,animation,phase,index,parent,&currentAdditive,&keyMultiply);
   phase++;
   animation->group->reuse[index].phase++;
   if(animation->count<animation->group->reuse[index].phase)animation->group->reuse[index].phase=animation->count;
  }
  for(int i=0;i<count;i++){
   ITEM *item=(ITEM *)(i*sizeof(ITEM)+(int)items);
   if(item->sprite&&item->cachedTime!=processed){
    if(first)func_002158C0(item->sprite,item);
    else{
     if(item->interpolate&&item->nextMatrix){
      float fraction=(processed-item->previousTime)/(item->nextTime-item->previousTime);
      matrix=BlendMatrix(fraction,*item->previousMatrix,*item->nextMatrix);
      currentAdditive=BlendColors(fraction,RGBA(item->previousAdditive),RGBA(item->nextAdditive));
      currentMultiply=BlendColors(fraction,RGBA(item->previousMultiply),RGBA(item->nextMultiply));
     }
     else{matrix=*item->previousMatrix;*(RGBA_RAW *)&currentAdditive=item->previousAdditive;*(RGBA_RAW *)&currentMultiply=item->previousMultiply;}
     matrix=Mul(matrix,*parent);
     {
      RGBA inputMultiply(multiply),inputAdditive(additive),localMultiply(currentMultiply),localAdditive(currentAdditive);
      func_00218790(&inputMultiply,&inputAdditive,&localMultiply,&localAdditive,&outputMultiply,&outputAdditive);
     }
     func_00215850(duration,item->sprite,item,&matrix,outputAdditive,outputMultiply);
     item->cachedTime=processed;item->matrix=matrix;
     item->additive=*(RGBA_RAW *)&outputAdditive;item->multiply=*(RGBA_RAW *)&outputMultiply;
     func_0011A058(&item->flags);
    }
   }
  }
  first=0;
 }while(phase<animation->count&&animation->keys[phase].time<=time);
}
