typedef int qword __attribute__((mode(TI)));
typedef union U{qword q;float f[4];int i[4];}U;
typedef struct M3{U r[3];}M3;
typedef struct VTE{short delta,pad;void*fn;}VTE;
typedef struct NODE{char pad0[0xC];VTE*vt;char pad10[0xD4];int cyclic;char padE8[0xD4];int flags;}NODE;
typedef struct LINK{char pad0[0x4C];NODE*object;}LINK;
typedef struct LIMIT{char pad0[0x28];float value;}LIMIT;
typedef struct POLY{float a,b,c;}POLY;
typedef struct SMPA{float a,b,duration,limit;}SMPA;
typedef struct CLAMP{float low,high;}CLAMP;
typedef struct CLOCK{float time,dt;}CLOCK;
typedef union WORD{float f;int bits;}WORD;
typedef struct P{char pad0[0xC];VTE*vt;char pad10[0x1A0];M3 basis;char pad1E0[0x28];LINK*source;char pad20C[0x2BC];int pathMode,disabled,unknown4D0;NODE*path;int unknown4D8;float parameter,offset;int reverse;char pad4E8[0x2C8];float left;char pad7B4[8];float middle;char pad7C0[8];float right;char pad7CC[8];void*blend;float value,velocity;char pad7E0[0x10E8];int mode;char pad18CC[0xC];int state;char pad18DC[0x108];void*primary,*secondary,*tertiary;LIMIT*firstLimit,*secondLimit;}P;
typedef struct WORK{U correction,position,direction,previous,response,scalar,filtered;}WORK;
extern U D_002A2DD0,D_002A2DC0;extern float D_002BF2D0,D_002BF2D4,D_002BF2D8,D_002BF2DC,D_002BF300;extern WORD D_002BF2E0;extern POLY D_002BF310,D_002BF330;extern SMPA D_002BF320;extern CLAMP D_002BBB60;extern CLOCK D_002DDED0;
extern int func_0012D058(void*),func_001443D8(P*);
extern void func_0012DA30(void*,qword);
extern qword func_001A62E8(void*);
extern void func_001E67B8(NODE*,qword*,qword*,float);
extern float func_001E6648(NODE*),func_001E6620(NODE*),func_0011D898(float,float);
extern void func_001E6F10(NODE*,qword*,qword*,float);
extern float func_0011E290(qword,qword,qword*,qword*);
extern float func_0011D1C0(float,float,float,float,SMPA*,float*);
extern void func_001384C0(void*);
extern qword func_0022D348(void*,void*,qword);
static inline qword Root(qword a){qword r;__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(r):"j"(a));return r;}
static inline float Evaluate(POLY*p,float t){return p->a+t*(p->b+t*p->c);}
static inline void*Space(NODE*p){VTE*e=&p->vt[32];return((void*(*)(void*,void*))e->fn)((char*)p+e->delta,0);}
void func_00189618(P*p){
 WORK w;register NODE*selected __asm__("$19")=0;
 register unsigned transfer __asm__("$16"),zeroHigh __asm__("$21"),high __asm__("$3");
 __asm__("lui %0,%%hi(%1)":"=r"(high):"i"(&D_002A2DD0));
 __asm__("addiu %0,%1,%%lo(%2)":"=r"(transfer):"r"(high),"i"(&D_002A2DD0));
 __asm__("daddu %0,%1,$zero":"=r"(zeroHigh):"r"(high));
 {
  register qword zero __asm__("$2");register void*primary __asm__("$4");
  __asm__("lq %0,%2\n\tlw %1,%3":"=&r"(zero),"=r"(primary):"m"(((U*)transfer)->q),"m"(p->primary));
  w.correction.q=zero;
  if(!primary||!func_0012D058(primary))return;
 }
 if(func_001443D8(p)){
  func_0012DA30(p->primary,((U*)transfer)->q);func_0012DA30(p->secondary,((U*)transfer)->q);func_0012DA30(p->tertiary,((U*)transfer)->q);return;
 }
 if(p->mode==0)goto from_link;
 if(p->mode==7)goto curve_case;
 goto selected_end;
from_link:
 if(p->source)selected=p->source->object;
 goto selected_end;
curve_case:
 if(p->disabled)goto selected_end;
 if(p->pathMode==3)goto curve_sample;
 if(p->pathMode!=4)goto selected_end;
 selected=p->path;w.position.q=func_001A62E8(selected);
 goto selected_end;
curve_sample:{
    register NODE*path __asm__("$18")=p->path;
    selected=path;
    func_001E67B8(path,&w.position.q,&w.direction.q,p->parameter);
    if(selected->flags){
     float parameter,end;
     register qword input __asm__("vf1")=w.direction.q;
     register VTE*vtable __asm__("$3");
     register qword returned __asm__("$2");
     register NODE*durationReceiver __asm__("$4");
     register float product __asm__("$f0"),offset __asm__("$f1");
     register qword normalized __asm__("vf2"),velocity __asm__("vf4");
     __asm__("vmul.xyz $vf2,%2,%2\n\tvaddw.x $vf3,$vf0,$vf0w\n\tvadday.x $ACC,$vf2,$vf2y\n\tvmaddz.x $vf2,$vf3,$vf2z\n\tlw %0,%3\n\tvsqrt Q,$vf2x\n\tvwaitq\n\tvaddq.x $vf2,$vf0,Q\n\tvdiv Q,$vf0w,$vf2x\n\tvwaitq\n\tvmulq.xyzw $vf2,%2,Q\n\tsqc2 $vf2,%1"
      :"=r"(vtable),"=m"(w.direction.q):"j"(input),"m"(p->vt):"vf2","vf3");
     returned=((qword(*)(void*))vtable[33].fn)((char*)p+vtable[33].delta);
     __asm__("lqc2 %0,%3\n\tlui $3,%%hi(%5)\n\tqmtc2.ni %4,%1\n\tlwc1 %2,%%lo(%5)($3)":"=j"(normalized),"=j"(velocity),"=f"(product):"m"(w.direction.q),"r"(returned),"i"(&D_002BF2D0):"$3","memory");
     __asm__("vmul.xyz $vf1,%3,%2\n\tvaddw.x $vf3,$vf0,$vf0w\n\tvadday.x $ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf3,$vf1z\n\tlwc1 %1,%4\n\tqmfc2.ni %0,$vf1":"=r"(transfer),"=f"(offset):"j"(normalized),"j"(velocity),"m"(p->offset):"vf1","vf3");
     __asm__("daddu %1,%6,$zero\n\tmtc1 %5,$f2\n\tqmtc2.ni %5,$vf1\n\tvmulx.xyzw %4,%4,$vf1x\n\tsqc2 $vf1,%2\n\tmul.s %0,$f2,%0\n\tsqc2 %4,%3"
      :"+f"(product),"=r"(durationReceiver),"=m"(w.scalar.q),"=m"(w.previous.q),"+j"(normalized):"r"(transfer),"r"(selected):"$f2","vf1");
     parameter=offset+product;
     end=func_001E6648(durationReceiver);
     if(selected->cyclic)parameter=func_0011D898(parameter,end);
     else{float first=func_001E6620(selected);if(parameter<first)parameter=first;else if(end<parameter)parameter=end;}
     {
      register float argument __asm__("$f12");register NODE*receiver __asm__("$4");
      __asm__("daddu %0,%2,$zero\n\tmov.s %1,%3":"=r"(receiver),"=f"(argument):"r"(path),"f"(parameter));
      func_001E6F10(receiver,0,&w.direction.q,argument);
     }
     {
      register qword sampledDirection __asm__("vf5")=w.direction.q;
      register qword current __asm__("vf1");
      register void*blend __asm__("$2");
      __asm__("qmtc2.ni %5,$vf2\n\tvmul.xyz $vf1,%4,%4\n\tvaddw.x $vf4,$vf0,$vf0w\n\tvadday.x $ACC,$vf1,$vf1y\n\tvmaddz.x $vf1,$vf4,$vf1z\n\tlw %0,%6\n\tvsqrt Q,$vf1x\n\tvwaitq\n\tvaddq.x $vf1,$vf0,Q\n\tsqc2 $vf2,%1\n\tvdiv Q,$vf0w,$vf1x\n\tvwaitq\n\tvmulq.xyzw $vf1,%4,Q\n\tlqc2 $vf3,%7\n\tvmulx.xyzw $vf2,$vf1,$vf2x\n\tvsub.xyzw %3,$vf2,$vf3\n\tsqc2 $vf2,%2"
       :"=r"(blend),"=m"(w.scalar.q),"=m"(w.response.q),"=j"(current):"j"(sampledDirection),"r"(transfer),"m"(p->blend),"m"(w.previous.q):"vf2","vf3","vf4");
      w.correction.q=current;
      if(blend){
      float lateral,result;
      register float boundShape __asm__("$f14");
      register qword word __asm__("vf1")=current,sideVector __asm__("vf2");
      register qword differenceArgument __asm__("$4"),sideArgument __asm__("$5");
      register qword*nullOutput __asm__("$6"),*correctionOutput __asm__("$7");
      __asm__("lui $2,%%hi(%4)\n\tqmfc2.ni %0,%3\n\taddiu $2,$2,%%lo(%4)\n\tdaddu %1,$zero,$zero\n\tlqc2 %3,0($2)\n\tdaddu %2,%5,$zero"
       :"=r"(differenceArgument),"=r"(nullOutput),"=r"(correctionOutput),"+j"(word):"i"(&D_002A2DC0),"p"(&w.correction.q):"$2","memory");
      __asm__("vopmula.xyz $ACC,%2,%3\n\tvopmsub.xyz %2,%3,%2\n\tvmul.xyz $vf2,%2,%2\n\tvaddw.x $vf3,$vf0,$vf0w\n\tvadday.x $ACC,$vf2,$vf2y\n\tvmaddz.x $vf2,$vf3,$vf2z\n\tvsqrt Q,$vf2x\n\tvwaitq\n\tvaddq.x $vf2,$vf0,Q\n\tvdiv Q,$vf0w,$vf2x\n\tvwaitq\n\tvmulq.xyzw %1,%2,Q\n\tqmfc2.ni %0,%1"
       :"=r"(sideArgument),"=j"(sideVector),"+j"(word):"j"(sampledDirection):"vf3");
      w.scalar.q=sideVector;
      lateral=func_0011E290(differenceArgument,sideArgument,nullOutput,correctionOutput);
      {
       register float value __asm__("$f0")=lateral,upper __asm__("$f2"),clamped __asm__("$f1");
       __asm__("lui $2,%%hi(%3)\n\t.set noat\n\tlui $1,0xbf80\n\tmtc1 $1,%1\n\t.set at\n\tlwc1 $f1,%%lo(%3)($2)\n\t.set noat\n\tlui $1,0x3f80\n\tmtc1 $1,%2\n\t.set at\n\tdiv.s %0,%0,$f1":"+f"(value),"=f"(boundShape),"=f"(upper):"i"(&D_002BF2D4):"$1","$2","$f1","memory");
       if(value<boundShape)clamped=boundShape;else if(upper<value)clamped=upper;else clamped=value;
      if(p->reverse)clamped=-clamped;
      {
       register SMPA*params __asm__("$4");register float*output __asm__("$5");
       register float dt __asm__("$f15"),value __asm__("$f12"),velocity __asm__("$f13");
       __asm__("abs.s $f0,%6\n\t.set noat\n\tlui $1,0x4000\n\tmtc1 $1,%4\n\t.set at\n\tlui $2,%%hi(%9)\n\tlui %0,%%hi(%8)\n\tlwc1 %5,%%lo(%9)($2)\n\taddiu %0,%0,%%lo(%8)\n\tsub.s %4,%4,$f0\n\tlwc1 %2,0x7d8(%7)\n\tlwc1 %3,0x7dc(%7)\n\taddiu %1,%7,0x7dc"
        :"=r"(params),"=r"(output),"=f"(value),"=f"(velocity),"=f"(boundShape),"=f"(dt):"f"(clamped),"r"(p),"i"(&D_002BF320),"i"(&D_002DDED0.dt):"$1","$2","$f0","memory");
       result=func_0011D1C0(value,velocity,clamped*boundShape,dt,params,output);
      }
      {
       register float actualResult __asm__("$f0")=result,middleValue __asm__("$f3");
       register void*blendReceiver __asm__("$4");
       __asm__("mtc1 $zero,$f2\n\t.set noat\n\tlui $1,0x3f80\n\tmtc1 $1,%0\n\t.set at\n\tneg.s $f1,%5\n\tmax.s $f4,%5,$f2\n\tlw %1,%6\n\tsub.s %0,%0,$f4\n\tswc1 %5,%2\n\tmax.s $f1,$f1,$f2\n\tswc1 $f4,%3\n\tswc1 $f1,%4\n\tsub.s %0,%0,$f1"
        :"=f"(middleValue),"=r"(blendReceiver),"=m"(p->value),"=m"(p->left),"=m"(p->right):"f"(actualResult),"m"(p->blend):"$1","$f1","$f2","$f4");
       p->middle=middleValue;
       func_001384C0(blendReceiver);
      }
      }
     }
     goto response_dispatch;
     }
    }
   }
selected_end:

 if(!selected)return;
response_dispatch:
 {
 register qword returned __asm__("$2")=func_0022D348(Space(selected),0,w.position.q);
 register qword point __asm__("vf4"),row1 __asm__("vf1"),row2 __asm__("vf2"),coordinates __asm__("vf3");
 register unsigned basisAddress __asm__("$2"),distanceWord __asm__("$2");
 register float epsilon __asm__("$f0"),distance __asm__("$f7");
 register qword xy __asm__("vf1");
 __asm__("qmtc2.ni %7,%0\n\t.set noat\n\tlui $1,0x38d1\n\tori $1,$1,0xb717\n\tmtc1 $1,%1\n\t.set at\n\tsqc2 %0,%6\n\taddiu %5,%8,0x1b0\n\tlqc2 %2,0x10(%5)\n\tlqc2 %3,0x20(%5)\n\tlqc2 %4,0x1b0(%8)"
  :"=j"(point),"=f"(epsilon),"=j"(row1),"=j"(row2),"=j"(coordinates),"=r"(basisAddress),"=m"(w.direction.q):"r"(returned),"r"(p):"$1","memory");
 __asm__("vmul.xyzw $vf7,%0,%1\n\tvmaxw.xyzw $vf8,$vf0,$vf0w\n\tvmul.xyzw $vf6,%2,%1\n\tvmul.xyzw $vf5,%3,%1\n\tvadday.x $ACC,$vf7,$vf7y\n\tvmaddz.x %0,$vf8,$vf7z\n\tvaddax.y $ACC,$vf6,$vf6x\n\tvmaddz.y %0,$vf8,$vf6z\n\tvaddax.z $ACC,$vf5,$vf5x\n\tvmaddy.z %0,$vf8,$vf5y":"+j"(coordinates):"j"(point),"j"(row1),"j"(row2):"vf5","vf6","vf7","vf8");
 __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(xy):"j"(coordinates));
 w.response.q=coordinates;
 xy=Root(xy);
 __asm__("qmfc2.ni %0,%1":"=r"(distanceWord):"j"(xy));
 __asm__("mtc1 %1,%0":"=f"(distance):"r"(distanceWord));
 if(epsilon<distance){
  register float raw __asm__("$f4"),lower __asm__("$f5"),divisor __asm__("$f3"),upper __asm__("$f6");
  register CLAMP*limits __asm__("$2");register unsigned polynomialHigh __asm__("$5");
  __asm__("lui %0,%%hi(%3)\n\tlwc1 %1,%2":"=r"(polynomialHigh),"=f"(divisor):"m"(D_002BF300),"i"(&D_002BF310));
  __asm__("addiu $3,%5,%%lo(%6)\n\t.set noat\n\tlui $1,0x3f80\n\tmtc1 $1,$f0\n\t.set at\n\tlui $4,%%hi(%7)\n\tdiv.s %3,%4,%3\n\tlwc1 $f1,8($3)\n\tlwc1 $f2,4($3)\n\taddiu %2,$4,%%lo(%7)\n\tlwc1 %0,%%lo(%6)(%5)\n\tlwc1 %1,%%lo(%7)($4)\n\tmin.s $f0,$f0,%3\n\tmul.s $f1,$f0,$f1\n\tadd.s $f2,$f2,$f1\n\tmul.s $f0,$f0,$f2\n\tadd.s %0,%0,$f0"
   :"=f"(raw),"=f"(lower),"=r"(limits),"+f"(divisor):"f"(distance),"r"(polynomialHigh),"i"(&D_002BF310),"i"(&D_002BBB60):"$1","$3","$4","$f0","$f1","$f2","memory");
  upper=limits->high;
  if(raw<lower)goto radial_gain_ready;
  if(upper<raw){__asm__("mov.s %0,%1":"=f"(lower):"f"(upper));}else lower=raw;
radial_gain_ready:
  {
   register float x __asm__("$f2"),y __asm__("$f1"),z __asm__("$f0"),speedRoot __asm__("$f3");
   {
    register unsigned speedHigh __asm__("$2");
    __asm__("lui %0,%%hi(%4)\n\tlwc1 %1,%3\n\tlwc1 %2,%%lo(%4)(%0)":"=&r"(speedHigh),"=f"(x),"=f"(speedRoot):"m"(w.response.f[0]),"i"(&D_002BF2D8):"memory");
   }
   __asm__("mul.s $f4,%4,%4\n\tlwc1 %1,%6\n\tmul.s %0,%0,%3\n\t.set noat\n\tlui $1,0x3f80\n\tmtc1 $1,%2\n\t.set at\n\tmul.s %1,%1,%3\n\tsub.s %2,%2,$f4\n\tmul.s %0,%0,%4\n\tmul.s %1,%1,%4\n\tdiv.s %0,%0,%5\n\tdiv.s %1,%1,%5\n\tsqrt.s %3,%2\n\tlui $2,%%hi(%7)\n\tlwc1 %2,%%lo(%7)($2)\n\tmul.s %2,%2,%3"
    :"+f"(x),"=f"(y),"=f"(z),"+f"(speedRoot):"f"(lower),"f"(distance),"m"(w.response.f[1]),"i"(&D_002BF2DC):"$1","$2","$f4","memory");
   w.previous.f[0]=x;w.previous.f[1]=y;w.previous.f[2]=z;
  }
 }else{w.previous.i[0]=w.previous.i[1]=w.previous.i[2]=0;}
 }
 {float first=Evaluate(&D_002BF330,p->firstLimit->value),maximum=Evaluate(&D_002BF330,p->secondLimit->value),z=w.previous.f[2];
  if(z<first&&z<maximum)maximum=z;else if(first<maximum)maximum=first;
  {
   register float x __asm__("$f1")=w.previous.f[0],y __asm__("$f0")=w.previous.f[1];
   register qword packed __asm__("$2");register long scratch __asm__("$3");register void*receiver __asm__("$4");
   __asm__("mfc1 %0,%3\n\tmfc1 %1,%4\n\tpextlw %0,%1,%0\n\tmfc1 %1,%5\n\tpcpyld %0,%1,%0\n\tlw %2,%6":"=&r"(packed),"=&r"(scratch),"=r"(receiver):"f"(x),"f"(y),"f"(maximum),"m"(p->primary));
   w.scalar.q=packed;
   func_0012DA30(receiver,packed);
  }
 }
 {
  register int state __asm__("$3"),sentinel __asm__("$2");register qword filtered __asm__("vf3");
  __asm__("lui %3,%%hi(%5)\n\tlqc2 $vf2,%4\n\tlw %3,%%lo(%5)(%3)\n\tqmtc2.ni %3,$vf1\n\tlw %0,%6\n\tvmulx.xyzw %1,$vf2,$vf1x\n\tsqc2 $vf1,%2\n\tli %3,-1":"=r"(state),"=j"(filtered),"=m"(w.scalar.q),"=&r"(sentinel):"m"(w.previous.q),"i"(&D_002BF2E0),"m"(p->state):"vf1","vf2","memory");
  w.filtered.q=filtered;
 if(state==sentinel){
  func_0012DA30(p->tertiary,w.filtered.q);func_0012DA30(p->secondary,w.filtered.q);
 }else{
  __asm__("addiu %0,%1,%%lo(%2)":"=r"(transfer):"r"(zeroHigh),"i"(&D_002A2DD0));
  func_0012DA30(p->tertiary,((U*)transfer)->q);func_0012DA30(p->secondary,((U*)transfer)->q);
 }
 }
}

typedef char layout_size_qword[(sizeof(qword)==16)?1:-1];
typedef char layout_size_voidpointer[(sizeof(void*)==4)?1:-1];
typedef char layout_size_U[(sizeof(U)==16)?1:-1];
typedef char layout_size_M3[(sizeof(M3)==48)?1:-1];
typedef char layout_size_VTE[(sizeof(VTE)==8)?1:-1];
typedef char layout_size_NODE[(sizeof(NODE)==0x1C0)?1:-1];
typedef char layout_size_LINK[(sizeof(LINK)==0x50)?1:-1];
typedef char layout_size_LIMIT[(sizeof(LIMIT)==0x2C)?1:-1];
typedef char layout_size_POLY[(sizeof(POLY)==12)?1:-1];
typedef char layout_size_SMPA[(sizeof(SMPA)==16)?1:-1];
typedef char layout_size_CLAMP[(sizeof(CLAMP)==8)?1:-1];
typedef char layout_size_CLOCK[(sizeof(CLOCK)==8)?1:-1];
typedef char layout_size_WORD[(sizeof(WORD)==4)?1:-1];
typedef char layout_size_WORK[(sizeof(WORK)==0x70)?1:-1];
typedef char layout_VTE_delta[((unsigned long)&((VTE*)0)->delta==0x0)?1:-1];
typedef char layout_VTE_fn[((unsigned long)&((VTE*)0)->fn==0x4)?1:-1];
typedef char layout_NODE_vt[((unsigned long)&((NODE*)0)->vt==0xc)?1:-1];
typedef char layout_NODE_cyclic[((unsigned long)&((NODE*)0)->cyclic==0xe4)?1:-1];
typedef char layout_NODE_flags[((unsigned long)&((NODE*)0)->flags==0x1bc)?1:-1];
typedef char layout_LINK_object[((unsigned long)&((LINK*)0)->object==0x4c)?1:-1];
typedef char layout_LIMIT_value[((unsigned long)&((LIMIT*)0)->value==0x28)?1:-1];
typedef char layout_POLY_a[((unsigned long)&((POLY*)0)->a==0x0)?1:-1];
typedef char layout_POLY_b[((unsigned long)&((POLY*)0)->b==0x4)?1:-1];
typedef char layout_POLY_c[((unsigned long)&((POLY*)0)->c==0x8)?1:-1];
typedef char layout_SMPA_a[((unsigned long)&((SMPA*)0)->a==0x0)?1:-1];
typedef char layout_SMPA_b[((unsigned long)&((SMPA*)0)->b==0x4)?1:-1];
typedef char layout_SMPA_duration[((unsigned long)&((SMPA*)0)->duration==0x8)?1:-1];
typedef char layout_SMPA_limit[((unsigned long)&((SMPA*)0)->limit==0xc)?1:-1];
typedef char layout_CLAMP_low[((unsigned long)&((CLAMP*)0)->low==0x0)?1:-1];
typedef char layout_CLAMP_high[((unsigned long)&((CLAMP*)0)->high==0x4)?1:-1];
typedef char layout_CLOCK_time[((unsigned long)&((CLOCK*)0)->time==0x0)?1:-1];
typedef char layout_CLOCK_dt[((unsigned long)&((CLOCK*)0)->dt==0x4)?1:-1];
typedef char layout_P_vt[((unsigned long)&((P*)0)->vt==0xc)?1:-1];
typedef char layout_P_basis[((unsigned long)&((P*)0)->basis==0x1b0)?1:-1];
typedef char layout_P_source[((unsigned long)&((P*)0)->source==0x208)?1:-1];
typedef char layout_P_pathMode[((unsigned long)&((P*)0)->pathMode==0x4c8)?1:-1];
typedef char layout_P_disabled[((unsigned long)&((P*)0)->disabled==0x4cc)?1:-1];
typedef char layout_P_path[((unsigned long)&((P*)0)->path==0x4d4)?1:-1];
typedef char layout_P_parameter[((unsigned long)&((P*)0)->parameter==0x4dc)?1:-1];
typedef char layout_P_offset[((unsigned long)&((P*)0)->offset==0x4e0)?1:-1];
typedef char layout_P_reverse[((unsigned long)&((P*)0)->reverse==0x4e4)?1:-1];
typedef char layout_P_left[((unsigned long)&((P*)0)->left==0x7b0)?1:-1];
typedef char layout_P_middle[((unsigned long)&((P*)0)->middle==0x7bc)?1:-1];
typedef char layout_P_right[((unsigned long)&((P*)0)->right==0x7c8)?1:-1];
typedef char layout_P_blend[((unsigned long)&((P*)0)->blend==0x7d4)?1:-1];
typedef char layout_P_value[((unsigned long)&((P*)0)->value==0x7d8)?1:-1];
typedef char layout_P_velocity[((unsigned long)&((P*)0)->velocity==0x7dc)?1:-1];
typedef char layout_P_mode[((unsigned long)&((P*)0)->mode==0x18c8)?1:-1];
typedef char layout_P_state[((unsigned long)&((P*)0)->state==0x18d8)?1:-1];
typedef char layout_P_primary[((unsigned long)&((P*)0)->primary==0x19e4)?1:-1];
typedef char layout_P_secondary[((unsigned long)&((P*)0)->secondary==0x19e8)?1:-1];
typedef char layout_P_tertiary[((unsigned long)&((P*)0)->tertiary==0x19ec)?1:-1];
typedef char layout_P_firstLimit[((unsigned long)&((P*)0)->firstLimit==0x19f0)?1:-1];
typedef char layout_P_secondLimit[((unsigned long)&((P*)0)->secondLimit==0x19f4)?1:-1];
typedef char layout_WORK_correction[((unsigned long)&((WORK*)0)->correction==0x0)?1:-1];
typedef char layout_WORK_position[((unsigned long)&((WORK*)0)->position==0x10)?1:-1];
typedef char layout_WORK_direction[((unsigned long)&((WORK*)0)->direction==0x20)?1:-1];
typedef char layout_WORK_previous[((unsigned long)&((WORK*)0)->previous==0x30)?1:-1];
typedef char layout_WORK_response[((unsigned long)&((WORK*)0)->response==0x40)?1:-1];
typedef char layout_WORK_scalar[((unsigned long)&((WORK*)0)->scalar==0x50)?1:-1];
typedef char layout_WORK_filtered[((unsigned long)&((WORK*)0)->filtered==0x60)?1:-1];
