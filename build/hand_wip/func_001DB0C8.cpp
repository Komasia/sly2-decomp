// Rank selectable items along the input direction.
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct ITEM {int id;char pad4[0x10];float x,y;int flags;};
struct PROX {float along,distance;};
struct INPUT {char pad[0x103C];float x,y;};
struct P {char pad10[0x10];INPUT*input;char pad14[0x14];int mode;float changed;char pad30[0x18];int selected,count;ITEM*items;};
struct HIT {qword position,other,normal;char pad30[0x10];float fraction;char pad44[0x1C];};
extern float D_002DDF0C,D_002C3280,D_002C3274,D_002C3278,D_002C327C,D_002A79C8;
extern "C" {
ITEM *func_001DAE20(P*,int);
int func_0014C748(qword,qword,qword,int,HIT*,float);
void func_0011EE08(qword,qword,qword,qword*,float*,float*);
void func_001DB390(P*,int);
void func_001DA9E8(P*);
void *func_001FBB90(int);
void func_001FB2F8(void*,int);
void func_001DB0C8(P*,int);
}
static inline qword XYZ(float x,float y,float z,U&home){qword r,t;
 __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0":"=&r"(r),"=&r"(t):"f"(x),"f"(y),"f"(z));
 home.q=r;return home.q;
}
static inline qword ToVF(qword v){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(v));return r;}
static inline qword Zero(){qword r;__asm__("vsub.xyzw %0,$vf0,$vf0":"=j"(r));return r;}
static inline qword Unit(qword v){qword len,one,r;
 __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(len),"=&j"(one):"j"(v));
 __asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(len));
 __asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(v),"0"(len));return r;
}
static inline qword Scalar(const float&f,U&home){int bits;qword r;__asm__("lw %0,%1":"=r"(bits):"m"(f));__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(bits));home.q=r;return home.q;}
static inline qword Scale(qword a,qword s){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(s));return r;}
static inline qword Add(qword a,qword b){qword r;__asm__("vadd.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
void func_001DB0C8(P*p,int mode){
 U home;HIT hit;PROX proximity;U ray;
 if(mode==p->mode)return;
 p->mode=mode;p->changed=D_002DDF0C;
 if(mode==-1||p->selected==-1)return;
 ITEM*current=func_001DAE20(p,p->selected);
 qword origin=XYZ(current->x,current->y*D_002C3280,0.0f,home);
 qword direction;
 if(p->input)direction=ToVF(XYZ(p->input->x,-p->input->y,0.0f,home));
 else direction=Zero();
 ray.q=Scale(Unit(direction),Scalar(D_002C3274,home));
 int bestId=-1;
 float best=D_002A79C8;
 origin=ToVF(origin);
 for(int i=0;i<p->count;i++){
  ITEM*item=&p->items[i];
  if(item==current)continue;
  if(!(item->flags&4))continue;
  float zero=0.0f;
  qword point=XYZ(item->x,item->y*D_002C3280,zero,home);
  float score;
  if(func_0014C748(point,origin,Add(origin,ray.q),1,&hit,D_002C3278)>0){
   score=hit.fraction*D_002C3274;
  }else{
   func_0011EE08(point,origin,Add(origin,ray.q),0,&proximity.along,&proximity.distance);
   if(proximity.distance<D_002C327C){if(zero<proximity.along){score=D_002C3274+proximity.distance;}else continue;}else continue;
  }
  if(score<best){bestId=item->id;best=score;}
 }
 if(bestId!=-1){func_001DB390(p,bestId);func_001DA9E8(p);func_001FB2F8(func_001FBB90(0x35),0);}
}
