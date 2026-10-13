
typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];} U;
struct X {qword header,v;};
struct P {char pad10[0x10];void*p10;int pad14;void*p18;char pad1C[0x30-0x1C];void*p30;char pad34[0x40-0x34];qword v40;int state;float time;int pad58[2];qword v60;};
void func_001EEF98(struct P*);
int func_001EF0A8(struct P*);
qword func_001A62E8(void*);
qword func_001A6F00(void*,int,qword);
int func_00209098(void*);
void func_0017C928(struct P*,int);
void func_002562A8(struct X*);
void func_0017DD38(void*,struct X*);
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=&j"(r):"j"(a),"j"(b));return r;}
static inline qword SubIn(qword a,qword b){__asm__("vsub.xyzw %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline float LenXY(qword v){float r;__asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(v):"0"(v));__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(v):"0"(v));__asm__("qmfc2.ni %0,%1":"=r"(r):"j"(v));return r;}
void func_0017C6D0(struct P*p){
 struct X x;U pos;float dist;int state;
 func_001EEF98(p);
 pos.q=func_001A62E8(p->p30);
 dist=LenXY(Sub(pos.q,func_001A62E8(p->p10)));
 while(!func_001EF0A8(p)){
  state=p->state;
  switch(state){
  case 0:
   if(func_00209098(p->p10))func_0017C928(p,2);
   else if(1000.0f<dist)func_0017C928(p,1);
   else if(250.0f<LenXY(SubIn(p->v60,pos.q))){
    qword v;p->v60=pos.q;v=func_001A6F00(p->p30,0,p->v40);
    func_002562A8(&x);x.v=v;func_0017DD38(p->p18,&x);
   }
   break;
  case 1:
   if(func_00209098(p->p10))func_0017C928(p,2);
   else if(dist<700.0f)func_0017C928(p,0);
   else if(250.0f<LenXY(SubIn(p->v60,pos.q))){
    p->v60=pos.q;func_002562A8(&x);x.v=pos.q;func_0017DD38(p->p18,&x);
   }
   break;
  case 2:if(!func_00209098(p->p10))func_0017C928(p,0);break;
  }
  if(state==p->state)return;
 }
}
