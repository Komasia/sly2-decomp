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
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword ScalarBits(int bits){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(bits));return r;}
static inline qword Scale(qword a,qword s){qword r;__asm__("vmulx.xyzw %0,%1,%2x":"=j"(r):"j"(a),"j"(s));return r;}
static inline qword Squared(qword a){qword d,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a));return d;}
static inline qword Root(qword a){qword r;__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(r):"j"(a));return r;}
static inline qword Unit(qword a){qword r,d=Root(Squared(a));__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(a),"j"(d));return r;}
static inline int DotBits(qword a,qword b){qword d,one;int bits;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a),"j"(b));__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(d));return bits;}
static inline float FloatBits(int bits){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(bits));return f;}
static inline float FloatX(qword a){int bits;__asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(a));return FloatBits(bits);}
static inline qword CrossRetain(qword r,qword a,qword b){__asm__("vopmula.xyz ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"+j"(r):"j"(a),"j"(b));return r;}
static inline float Clamp(float value,float low,float high){if(value<low)return low;else if(high<value)return high;return value;}
static inline float Min(float a,float b){return a<b?a:b;}
static inline float Max(float a,float b){return a>b?a:b;}
static inline float Abs(float f){float r;__asm__("abs.s %0,%1":"=f"(r):"f"(f));return r;}
static inline float Sqrt(float f){float r;__asm__("sqrt.s %0,%1":"=f"(r):"f"(f));return r;}
static inline float Evaluate(POLY*p,float t){return p->a+t*(p->b+t*p->c);}
static inline qword Coordinates(M3*m,qword p){
 qword r=m->r[0].q,a,b,c,one;
 __asm__("vmul.xyzw %1,%0,%5\n\tvmaxw.xyzw %4,$vf0,$vf0w\n\tvmul.xyzw %2,%6,%5\n\tvmul.xyzw %3,%7,%5\n\tvadday.x ACC,%1,%1y\n\tvmaddz.x %0,%4,%1z\n\tvaddax.y ACC,%2,%2x\n\tvmaddz.y %0,%4,%2z\n\tvaddax.z ACC,%3,%3x\n\tvmaddy.z %0,%4,%3y":"+j"(r),"=&j"(a),"=&j"(b),"=&j"(c),"=&j"(one):"j"(p),"j"(m->r[1].q),"j"(m->r[2].q));return r;
}
static inline float XY(qword a){qword d;__asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(d):"j"(a));return FloatX(Root(d));}
static inline qword Pack(float x,float y,float z){qword a,b;__asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0":"=&r"(a),"=&r"(b):"f"(x),"f"(y),"f"(z));return a;}
static inline qword Velocity(P*p){VTE*e=&p->vt[33];return((qword(*)(void*))e->fn)((char*)p+e->delta);}
static inline void*Space(NODE*p){VTE*e=&p->vt[32];return((void*(*)(void*,void*))e->fn)((char*)p+e->delta,0);}
void func_00189618(P*p){
 WORK w;register NODE*selected __asm__("$19")=0;
 w.correction=D_002A2DD0;
 if(!p->primary||!func_0012D058(p->primary))return;
 if(func_001443D8(p)){
  func_0012DA30(p->primary,D_002A2DD0.q);func_0012DA30(p->secondary,D_002A2DD0.q);func_0012DA30(p->tertiary,D_002A2DD0.q);return;
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
     int projectedBits;float parameter,end;
     qword axis,unit;
     w.direction.q=Unit(w.direction.q);
     projectedBits=DotBits(Velocity(p),w.direction.q);
     axis=ScalarBits(projectedBits);w.scalar.q=axis;
     w.previous.q=Scale(w.direction.q,w.scalar.q);
     parameter=p->offset+FloatBits(projectedBits)*D_002BF2D0;
     end=func_001E6648(selected);
     if(selected->cyclic)parameter=func_0011D898(parameter,end);
     else{float first=func_001E6620(selected);if(parameter<first)parameter=first;else if(end<parameter)parameter=end;}
     func_001E6F10(path,0,&w.direction.q,parameter);
     axis=ScalarBits(projectedBits);w.scalar.q=axis;
     unit=Unit(w.direction.q);w.response.q=Scale(unit,w.scalar.q);
     w.correction.q=Sub(w.response.q,w.previous.q);
     if(p->blend){
      float lateral,target,result,left,right,middle;
      qword up=D_002A2DC0.q;
      qword side=Unit(CrossRetain(up,up,w.direction.q));
      w.scalar.q=side;
      lateral=func_0011E290(w.correction.q,w.scalar.q,0,&w.correction.q);
      lateral=Clamp(lateral/D_002BF2D4,-1.0f,1.0f);
      if(p->reverse)lateral=-lateral;
      target=lateral*(2.0f-Abs(lateral));
      result=func_0011D1C0(p->value,p->velocity,target,D_002DDED0.dt,&D_002BF320,&p->velocity);
      left=Max(result,0.0f);right=Max(-result,0.0f);middle=(1.0f-left)-right;
      p->value=result;p->left=left;p->right=right;p->middle=middle;
      func_001384C0(p->blend);
     }
    }
   }
selected_end:

 if(!selected)return;
 w.direction.q=func_0022D348(Space(selected),0,w.position.q);
 w.response.q=Coordinates(&p->basis,w.direction.q);
 {float distance=XY(w.response.q);
 if(distance>0.0001f){
  float fraction=Min(1.0f,distance/D_002BF300);
  float gain=Clamp(Evaluate(&D_002BF310,fraction),D_002BBB60.low,D_002BBB60.high);
  float scale=D_002BF2D8;
  w.previous.f[0]=(w.response.f[0]*scale)*gain/distance;
  w.previous.f[1]=(w.response.f[1]*scale)*gain/distance;
  w.previous.f[2]=D_002BF2DC*Sqrt(1.0f-gain*gain);
 }else{w.previous.i[0]=w.previous.i[1]=w.previous.i[2]=0;}
 }
 {float first=Evaluate(&D_002BF330,p->firstLimit->value),maximum=Evaluate(&D_002BF330,p->secondLimit->value),z=w.previous.f[2];qword output;
  if(z<first&&z<maximum)maximum=z;else if(first<maximum)maximum=first;
  output=Pack(w.previous.f[0],w.previous.f[1],maximum);w.scalar.q=output;
  func_0012DA30(p->primary,w.scalar.q);
 }
 {qword scale=ScalarBits(D_002BF2E0.bits);w.scalar.q=scale;w.filtered.q=Scale(w.previous.q,w.scalar.q);}
 if(p->state==-1){
  func_0012DA30(p->tertiary,w.filtered.q);func_0012DA30(p->secondary,w.filtered.q);
 }else{
  func_0012DA30(p->tertiary,D_002A2DD0.q);func_0012DA30(p->secondary,D_002A2DD0.q);
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
