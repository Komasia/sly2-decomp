// Apply animation key poses and their interpolation/color state.
typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
struct RGBA_RAW {uchar r,g,b,a;};
struct RGBA {uchar r,g,b,a;RGBA(){}RGBA(const RGBA &c){*(RGBA_RAW *)this=*(const RGBA_RAW *)&c;}RGBA(const RGBA_RAW &c){*(RGBA_RAW *)this=c;}RGBA &operator=(const RGBA &c){*(RGBA_RAW *)this=*(const RGBA_RAW *)&c;return *this;}} __attribute__((aligned(16)));
struct M23 {float a[6];} __attribute__((aligned(16)));
struct SPRITE {int id,kind;void *group;int fieldC,index;void *extra;char pad18[0x28];};
struct ITEM {RGBA_RAW additive,multiply;char pad8[8];M23 matrix;SPRITE *sprite;int kind;float previousTime;RGBA_RAW previousAdditive,previousMultiply;M23 *previousMatrix;float nextTime;RGBA_RAW nextAdditive,nextMultiply;M23 *nextMatrix;int index;float cachedTime;uchar interpolate,mode;char pad62[2];int field64;int flags,pad6C;};
struct REUSE {int count;ITEM *items;ushort index,phase;float time;int field10,field14;};
struct ANIM;
struct GROUP {ushort animCount,reuseCount;ANIM *animations;REUSE *reuse;char padC[0x14];int index;void *owner;int first,pad2C;};
struct KEYPOSE {ushort id,index,offset;short color;char pad8[8];M23 matrix;uchar interpolate,mode;char pad32[2];int selected;char pad38[8];};
struct COLORS {RGBA_RAW multiply,additive;};
struct TAG {int kind,value;};
struct KEY {float time;uchar itemCount,colorCount,shortCount,byteCount;uchar *bytes;KEYPOSE *items;COLORS *colors;ushort *shorts;uchar tagCount;char pad19[3];TAG *tags;};
struct ROOT {char pad[0x54];SPRITE *sprites;};
struct ANIM {ushort count,pad2;KEY *keys;float duration;ROOT *owner;GROUP *group;int id;};
extern "C" {
void func_0011A058(int *);
void *func_002333B4(void *,int,int);
void func_00215730(SPRITE *,ITEM *,M23 *,RGBA,RGBA);
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
struct LM {float lo,hi;LM(){func_002333B4(this,0,8);}};
float GLimitLm(LM *,float);
extern "C" void func_00219400(float time,float duration,ANIM *animation,int phase,int index,M23 *parent,const RGBA *additive,const RGBA *multiply){
 int j=0;ITEM *items=animation->group->reuse[index].items;
 KEY *key=&animation->keys[phase];
 M23 matrix;RGBA outputAdditive,outputMultiply,currentAdditive,currentMultiply;
 if(key->itemCount==0)return;
 uint defaultAdditive=0x7F7F7F7F,defaultMultiply=0xFFFFFFFF;
 for(;j<key->itemCount;j++){
  KEYPOSE *pose=&key->items[j];int entryIndex=pose->index,linkOffset=pose->offset,id=pose->id;
  ITEM *item=(ITEM *)(entryIndex*sizeof(ITEM)+(int)items);
  COLORS *colors=0;
  if(pose->color>=0)colors=&key->colors[pose->color];
  uint additiveWord=defaultAdditive;*(uint *)&item->previousAdditive=additiveWord;*(uint *)&currentAdditive=additiveWord;
  uint multiplyWord=defaultMultiply;*(uint *)&item->previousMultiply=multiplyWord;*(uint *)&currentMultiply=multiplyWord;
  if(colors){
   item->previousAdditive=colors->additive;*(RGBA_RAW *)&currentAdditive=item->previousAdditive;
   item->previousMultiply=colors->multiply;*(RGBA_RAW *)&currentMultiply=item->previousMultiply;
  }
  item->previousMatrix=&pose->matrix;item->previousTime=key->time;item->nextMatrix=0;item->nextTime=0.0f;
  int *flags=&item->flags;RGBA *additiveOutput=&outputAdditive;
  if(pose->interpolate){
   for(int next=phase+1;next<animation->count;next++){
    KEY *future=&animation->keys[next];
    for(int k=0;k<future->itemCount;k++){
     KEYPOSE *futurePose=&future->items[k];
     if(futurePose->index==entryIndex){
      item->nextMatrix=&futurePose->matrix;item->nextTime=future->time;
      if(futurePose->color>=0){
       item->nextAdditive=future->colors[futurePose->color].additive;
       item->nextMultiply=future->colors[futurePose->color].multiply;
      }
      else{item->nextAdditive=item->previousAdditive;item->nextMultiply=item->previousMultiply;}
      break;
     }
    }
    if(item->nextMatrix)break;
   }
  }
  if(pose->interpolate&&item->nextMatrix&&item->previousTime<item->nextTime){
   LM bounds;bounds.lo=item->previousTime;bounds.hi=item->nextTime;LM copy=bounds;
   float fraction=(GLimitLm(&copy,duration)-item->previousTime)/(item->nextTime-item->previousTime);
   matrix=BlendMatrix(fraction,*item->previousMatrix,*item->nextMatrix);
   currentAdditive=BlendColors(fraction,RGBA(item->previousAdditive),RGBA(item->nextAdditive));
   currentMultiply=BlendColors(fraction,RGBA(item->previousMultiply),RGBA(item->nextMultiply));
  }
  else{matrix=*item->previousMatrix;*(RGBA_RAW *)&currentAdditive=item->previousAdditive;*(RGBA_RAW *)&currentMultiply=item->previousMultiply;}
  matrix=Mul(matrix,*parent);
  {
   RGBA inputMultiply(*multiply),inputAdditive(*additive),localMultiply(currentMultiply),localAdditive(currentAdditive);
   func_00218790(&inputMultiply,&inputAdditive,&localMultiply,&localAdditive,&outputMultiply,additiveOutput);
  }
  if(id>0){
   if(item->sprite&&item->sprite->id==id){func_00215850(duration,item->sprite,item,&matrix,outputAdditive,outputMultiply);item->cachedTime=time;}
   else{
    if(item->sprite)func_002158C0(item->sprite,item);
    func_00215730(&animation->owner->sprites[id],item,&matrix,outputAdditive,outputMultiply);item->cachedTime=time;
   }
  }
  else{func_00215850(duration,item->sprite,item,&matrix,outputAdditive,outputMultiply);item->cachedTime=time;}
  item->matrix=matrix;item->additive=*(RGBA_RAW *)&outputAdditive;item->multiply=*(RGBA_RAW *)&outputMultiply;
  item->interpolate=pose->interpolate;item->mode=pose->mode;item->field64=pose->selected;func_0011A058(flags);
  if(linkOffset){item->kind=1;items[entryIndex+linkOffset].kind=4;}
  else if(item->kind!=4)item->kind=0;
 }
}
