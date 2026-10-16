// 30/167 instructions differ; blend and final scale scheduling remain.
typedef int qword __attribute__((mode(TI)));
typedef union{qword q;float f[4];int i[4];}U;
struct M3{qword r[3];};
struct VT{short delta,pad;void*fn;};
struct O{char pad[0x494];struct O*anchor;};
struct ANIM{char pad[0x40];int ratebits;};
struct P{char pad[0xC];struct VT*vt;char pad10[0x180];U acceleration;char pad1A0[8];float heading;char pad1AC[0xE84];struct ANIM*anim;int pad1034;int side;char pad103C[0xA0];struct O*target;int pad10E0;int targetMode;};
struct AXES{char pad[0x10];qword a;char pad20[0x10];qword b;char pad40[0x10];qword c;char pad60[0x10];qword d;char pad80[0x10];qword e;char padA0[0x10];qword f;};
extern float D_002BF9F0;
void func_002046F0(struct P*,struct O*);
float func_0011CF60(float);
qword func_0011E1A0(float,float,float);
struct M3*func_001A6318(struct P*);
static inline qword GetVel(struct P*p){return ((qword(*)(void*))p->vt[33].fn)((char*)p+p->vt[33].delta);}
static inline void SetVel(struct P*p,qword v){((void(*)(void*,qword))p->vt[35].fn)((char*)p+p->vt[35].delta,v);}
static inline void Store(qword*out,qword q){__asm__("sqc2 %1,%0":"=m"(*out):"j"(q));}
static inline qword Dot(qword a,qword b){qword r,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a),"j"(b));return r;}
static inline qword Scale(qword v,qword k){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"j"(k));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"0"(a),"j"(b));return r;}
static inline qword ToVu(qword bits){register qword r __asm__("vf3");__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(bits));return r;}
static inline qword ScaleDot(qword v,qword k){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(v),"0"(k));return r;}
static inline qword ProjectOut(qword ni,qword vi){
 register qword n __asm__("vf1")=ni,v __asm__("vf3")=vi;
 register qword dot __asm__("vf2"),one __asm__("vf4");
 __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(dot),"=&j"(one):"j"(v),"j"(n));
 __asm__("vmulx.xyzw %0,%1,%0x":"+j"(dot):"j"(n));
 __asm__("vsub.xyzw %0,%0,%1":"+j"(v):"j"(dot));
 return v;
}
static inline void RemoveSide(struct P*p,U*result,U*old){
 struct M3*basis;
 qword value;
 old->q=ToVu(GetVel(p));
 basis=func_001A6318(p);
 value=ProjectOut(basis->r[1],old->q);
 result->q=value;
 SetVel(p,value);
}
static inline qword Bcast(float f,U*out){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));out->q=q;return q;}
static inline qword PureBits(int bits){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(bits));return q;}
static inline qword BcastBits(int bits,U*out){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(bits));out->q=q;return q;}
static inline float Min(float a,float b){float f;__asm__("min.s %0,%1,%2":"=f"(f):"f"(a),"f"(b));return f;}
static inline float Max(float a,float b){float f;__asm__("max.s %0,%1,%2":"=f"(f):"f"(a),"f"(b));return f;}
static inline qword Blend(qword a,qword b,qword c,qword ka,qword kb,qword kc){qword r;__asm__("vmulax.xyzw ACC,%1,%4x\n\tvmaddax.xyzw ACC,%2,%5x\n\tvmaddx.xyzw %0,%3,%6x":"=j"(r):"j"(a),"j"(b),"j"(c),"0"(ka),"j"(kb),"j"(kc));return r;}
static inline qword Bits(float f){qword bits;__asm__("mfc1 %0,%1":"=r"(bits):"f"(f));return bits;}
static inline qword Load4(const qword*p){register qword r __asm__("vf4");__asm__("lqc2 %0,%1":"=j"(r):"m"(*p));return r;}
static inline void BlendPositive(struct P*p,struct AXES*axes,float xin,float yin,U*out){
 register float x __asm__("$f1")=xin,y __asm__("$f3")=yin,zero __asm__("$f0")=0.0f;
 register float left __asm__("$f2"),right __asm__("$f0");
 register qword a __asm__("vf2") ,b __asm__("vf1"),c __asm__("vf4");
 register qword ka __asm__("vf3"),kb __asm__("vf5"),kc __asm__("vf6");
 qword ybits=Bits(y);
 c=axes->f;
 __asm__("min.s %0,%1,%2":"=f"(left):"f"(zero),"f"(x));
 left=-left;
 __asm__("max.s %0,%1,%2":"=f"(right):"f"(zero),"f"(x));
 __asm__("qmtc2.ni %1,%0":"=j"(ka):"r"(ybits));out->q=ka;
 __asm__("qmtc2.ni %1,%0":"=j"(kb):"r"(right));a=axes->b;b=axes->d;out->q=kb;
 __asm__("qmtc2.ni %1,%0":"=j"(kc):"r"(left));
 __asm__("vmulax.xyzw ACC,%1,%4x\n\tvmaddax.xyzw ACC,%2,%5x\n\tvmaddx.xyzw %0,%3,%6x":"=j"(ka):"j"(a),"j"(b),"j"(c),"0"(ka),"j"(kb),"j"(kc));
 p->acceleration.q=ka;out->q=kc;
}
static inline void BlendNegative(struct P*p,struct AXES*axes,float xin,float yin,U*out){
 register float x __asm__("$f1")=xin,y __asm__("$f2")=-yin,zero __asm__("$f0")=0.0f;
 register float left __asm__("$f3"),right __asm__("$f0");
 register qword a __asm__("vf3") ,b __asm__("vf1"),c __asm__("vf4");
 register qword ka __asm__("vf2"),kb __asm__("vf6"),kc __asm__("vf5");
 c=axes->e;
 __asm__("min.s %0,%1,%2":"=f"(left):"f"(zero),"f"(x));
 left=-left;
 __asm__("max.s %0,%1,%2":"=f"(right):"f"(zero),"f"(x));
 __asm__("qmtc2.ni %1,%0":"=j"(ka):"r"(y));out->q=ka;
 __asm__("qmtc2.ni %1,%0":"=j"(kb):"r"(right));a=axes->a;b=axes->c;out->q=kb;
 __asm__("qmtc2.ni %1,%0":"=j"(kc):"r"(left));
 __asm__("vmulax.xyzw ACC,%1,%4x\n\tvmaddax.xyzw ACC,%2,%5x\n\tvmaddx.xyzw %0,%3,%6x":"=j"(ka):"j"(a),"j"(b),"j"(c),"0"(ka),"j"(kb),"j"(kc));
 p->acceleration.q=ka;out->q=kc;
}
void func_001A0720(struct P*p,struct AXES*axes,int enabled,float heading,float magnitude){
 U input,scalar,old;
 register int side __asm__("$3");
 float zero;
 struct O*target;
 if(!enabled)return;
 target=p->target;
 if(target){if(p->targetMode==3)target=target->anchor;
 func_002046F0(p,target);}
 zero=0.0f;
 input.q=func_0011E1A0(func_0011CF60(heading-p->heading),magnitude,zero);
 if(D_002BF9F0<input.f[1]){
  if(p->side==0){input.f[1]=zero;RemoveSide(p,&scalar,&old);}
  side=1;
 }else if(input.f[1]<-D_002BF9F0){
  if(p->side==1){input.f[1]=zero;RemoveSide(p,&scalar,&old);}
  side=0;
 }else{side=p->side;if(side==-1)side=0;}
 {register float x __asm__("$f1")=input.f[0];
 if(side==1){
  BlendPositive(p,axes,x,input.f[1],&scalar);
 }else{
  BlendNegative(p,axes,x,input.f[1],&scalar);
 }
 }
 p->acceleration.i[2]=0;
 {qword rate=PureBits(p->anim->ratebits);qword scaled=Scale(p->acceleration.q,rate);
  p->side=side;
  p->acceleration.q=scaled;
  scalar.q=rate;
 }
}
