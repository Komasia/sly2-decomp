/* SteerRootBlend (0x1A0450): sets a root blend's eight weights from the actor's velocity (ACTOR +0x190, named
 * "acceleration" in the local fragment): each entry gets its share of the velocity along its own root velocity, the
 * rest goes to the standing entry; the side (+0x1038: -1 both, 0 / 1) picks entries 6 or 7; the velocity becomes the
 * blend's velocity at the ASEGA's speed (+0x1030 ->svt), then the blend (pbl) is recalculated. SafeHouse gang.cpp. */
typedef int qword __attribute__((mode(TI)));
typedef union{qword q;float f[4];int i[4];}U;
struct ASEGA{char pad[0x40];float svt;};  /* +0x40: the effective speed (asega.h) */
struct P{char pad[0x190];U acceleration;char pad1A0[0xE90];struct ASEGA*anim;int pad1034;int side;};
struct ROOTBLENDE{union{float value;int bits;}weight;int paseg;/* ASEG *, tested only */char pad8[8];U vel;};
void RecalcBlend__FP6ASEGBL(void*);
static inline qword Dot(qword a,qword b){qword d,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a),"j"(b));return d;}
static inline float FloatX(qword q){int bits;float f;__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(q));__asm__("mtc1 %1,%0":"=f"(f):"r"(bits));return f;}
static inline float Max(float a,float b){float f;__asm__("max.s %0,%1,%2":"=f"(f):"f"(a),"f"(b));return f;}
static inline qword AddScaled(qword v,qword x,qword k){qword q;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(q):"j"(v),"j"(x),"j"(k));return q;}

static inline float Float3(qword q){register int bits __asm__("$7");float f;__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(q));__asm__("mtc1 %1,%0":"=f"(f):"r"(bits));return f;}
static inline qword ScalarBits(int bits){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(bits));return q;}

static inline float Float1(qword q){register int bits __asm__("$7");register float f __asm__("$f1");__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(q));__asm__("mtc1 %1,%0":"=f"(f):"r"(bits));return f;}
// name: SafeHouse port (SteerRootBlend)
void SteerRootBlend__FP5ACTORP9ROOTBLENDPv(struct P*p,struct ROOTBLENDE*ae,void*pbl){
 int indices[5];
 U total,scalar;
 int i,count,clear,accum;
 register float rate __asm__("$f4");float sum;
 register qword rk __asm__("vf6");
 if(!pbl)return;
 rate=p->anim->svt;
 if(!ae[6].paseg||!ae[7].paseg)p->side=-1;
 else if(p->side==-1){
  if(FloatX(Dot(p->acceleration.q,ae[0].vel.q))<0.0f)p->side=1;
  else p->side=0;
 }
 {register int ratebits __asm__("$7");__asm__("mfc1 %0,%1":"=r"(ratebits):"f"(rate));__asm__("qmtc2.ni %1,%0":"=j"(rk):"r"(ratebits));}
 for(clear=7;clear>=0;clear--)ae[clear].weight.value=0.0f;
 switch(p->side){
 case -1:
  if(!ae[7].paseg){indices[0]=6;indices[1]=2;indices[2]=4;}
  else{indices[0]=7;indices[1]=3;indices[2]=5;}
  indices[3]=0;indices[4]=1;count=5;
  break;
 case 0:indices[0]=6;indices[1]=2;indices[2]=4;indices[3]=0;count=4;break;
 case 1:indices[0]=7;indices[1]=3;indices[2]=5;indices[3]=1;count=4;break;
 }
 sum=0.0f;
 if(rate>0.0f){
  for(i=1;i<count;i++){
   struct ROOTBLENDE*pe=&ae[indices[i]];
   float denominator=rate*Float1(Dot(pe->vel.q,pe->vel.q));
   float along=Float3(Dot(p->acceleration.q,pe->vel.q));
   float w=Max(along/denominator,0.0f);
   pe->weight.value=w;
   sum+=w;
  }
 }
 {struct ROOTBLENDE*head=&ae[indices[0]];
 if(sum<1.0f)head->weight.value=1.0f-sum;
 else{
  head->weight.value=0.0f;
  for(i=1;i<count;i++)ae[indices[i]].weight.value/=sum;
 }
 }
 total.i[0]=total.i[1]=total.i[2]=0;
 for(accum=7;accum>=0;accum--){
  qword k=ScalarBits(ae->weight.bits);
  total.q=AddScaled(total.q,ae->vel.q,k);
  scalar.q=k;
  ae++;
 }
 {qword q;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(q):"j"(total.q),"j"(rk));{register void*argument __asm__("$4")=pbl;scalar.q=rk;p->acceleration.q=q;RecalcBlend__FP6ASEGBL(argument);}}
}
