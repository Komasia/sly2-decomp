typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M4 {qword a,b,c,d;};
struct VTE {short delta,pad;void(*fn)();};
struct P {char padC[0xC];VTE *vt;char pad10[0xD0];int mode,cyclic,count;float *times,*values;qword *points;};
struct SPACE {qword axis;int mode;};
struct WORK {M4 matrix;qword closest;U scalar;qword start,end,point,filteredDirection,offset;};
extern "C" {
extern float D_002A8138;
qword func_001FA970(SPACE*,qword);
float func_001E63C0(P*,float);
void func_001E6ED8(P*,qword,SPACE*,qword*,qword*,float*,float*,float);
}
static inline qword Load(const qword &a){qword r;__asm__("lqc2 %0,%1":"=j"(r):"m"(a));return r;}
static inline void CopyMatrix(M4 &out,const M4 *in){out.a=Load(in->a);out.b=Load(in->b);out.c=Load(in->c);out.d=Load(in->d);}
static inline qword Point(const M4 &m,qword a){register qword r __asm__("vf6");__asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w":"+j"(r):"j"(m.a),"j"(m.b),"j"(m.c),"j"(m.d),"j"(a));return r;}
static inline qword PointKept(qword carrier,const M4&m,qword a) {
 __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
    :"+j"(carrier):"j"(m.a),"j"(m.b),"j"(m.c),"j"(m.d),"j"(a));
 return carrier;
}
static inline qword PointRow0(const M4&m,qword a) {
 qword r=m.a;
 __asm__("vmulax.xyz $ACC,%0,%4x\n\tvmadday.xyz $ACC,%1,%4y\n\tvmaddaz.xyz $ACC,%2,%4z\n\tvmaddw.xyz %0,%3,$vf0w"
    :"+j"(r):"j"(m.b),"j"(m.c),"j"(m.d),"j"(a));
 return r;
}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword ToVU(qword a){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(a));return r;}
static inline qword Scalar(U &home,float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));home.q=r;return home.q;}
static inline qword Dot(qword a,qword b){qword r,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a),"j"(b));return r;}
static inline qword Root(qword a){__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(a));return a;}
static inline float X(qword a){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
static inline float Length(qword a){return X(Root(Dot(a,a)));}
static inline qword Normalize(qword a){qword length=Root(Dot(a,a)),r;__asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q":"=j"(r):"j"(a),"j"(length));return r;}
static inline qword Lerp(qword a,qword b,qword low,qword high){qword r;__asm__("vmulax.xyzw $ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x":"=j"(r):"j"(a),"j"(b),"j"(low),"j"(high));return r;}
static inline float Zero() { register float value __asm__("$f24");__asm__("mtc1 $zero,%0":"=f"(value));return value; }
static inline float SegmentFraction(qword offset,qword direction){
 register qword a __asm__("vf6")=offset;
 register qword b __asm__("vf3")=direction;
 register float numerator __asm__("$f1"),denominator __asm__("$f0");
 __asm__("vmul.xyz $vf2,%3,%2\n\tvaddw.x $vf1,$vf0,$vf0w\n\tvadday.x $ACC,$vf2,$vf2y\n\tvmaddz.x $vf2,$vf1,$vf2z\n\tvmul.xyz $vf4,%2,%2\n\tvaddw.x %2,$vf0,$vf0w\n\tvadday.x $ACC,$vf4,$vf4y\n\tvmaddz.x $vf4,%2,$vf4z\n\tqmfc2.ni $v0,$vf2\n\tqmfc2.ni $v1,$vf4\n\tmtc1 $v0,%0\n\tmtc1 $v1,%1"
  :"=f"(numerator),"=f"(denominator),"+j"(b):"j"(a):"vf1","vf2","vf4","$2","$3");
 return numerator/denominator;
}
static inline float DisplacementLength(qword displacement){
 register qword phase __asm__("vf1")=displacement;
 register float length __asm__("$f0");
 __asm__("vmul.xyz %1,%1,%1\n\tvaddw.x $vf2,$vf0,$vf0w\n\tvadday.x $ACC,%1,%1y\n\tvmaddz.x %1,$vf2,%1z\n\tvsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %1,$vf0,$Q\n\tqmfc2.ni $v0,%1\n\tmtc1 $v0,%0"
  :"=f"(length),"+j"(phase): :"vf2","$2");
 return length;
}
extern "C" void func_001E6F60(P *p,qword point,SPACE *space,qword *outPosition,qword *outDirection,float *outTime,float *outValue){
 WORK work;work.point=point;
 VTE &v=p->vt[31];CopyMatrix(work.matrix,((M4*(*)(void*))v.fn)((char*)p+v.delta));
 switch(p->mode){
 case 0:{
  work.start=Point(work.matrix,p->points[0]);
  float best=D_002A8138,time=-1.0f;float lowerBound=Zero();
  for(int index=1;index<p->count;index++){
   float fraction;
   {
    register qword endPoint __asm__("vf7");
    register qword pointOffset __asm__("vf6");
    register qword segmentDirection __asm__("vf3");
    __asm__("lqc2 %0,%4\n\tlqc2 $vf1,%5\n\tvsub.xyzw %1,%0,$vf1\n\tlqc2 %2,%6\n\tlqc2 $vf1,0x30(%7)\n\tlqc2 $vf5,0(%7)\n\tlqc2 $vf4,0x10(%7)\n\tlqc2 $vf2,0x20(%7)\n\tvmulax.xyz $ACC,$vf5,%2x\n\tvmadday.xyz $ACC,$vf4,%2y\n\tvmaddaz.xyz $ACC,$vf2,%2z\n\tvmaddw.xyz %0,$vf1,$vf0w\n\tlqc2 $vf1,%5\n\tsqc2 %0,%3\n\tvsub.xyzw %2,%0,$vf1"
      :"=j"(endPoint),"=j"(pointOffset),"=j"(segmentDirection),"=m"(work.end)
      :"m"(work.point),"m"(work.start),"m"(p->points[index]),"r"(&work.matrix),"X"(work.matrix)
      :"vf1","vf2","vf4","vf5");
    if(space){
     qword projectedDirection;
     {
      register qword directionInput __asm__("$5");
      __asm__("qmfc2.ni %0,%1":"=r"(directionInput):"j"(segmentDirection));
      work.offset=pointOffset;
      projectedDirection=func_001FA970(space,directionInput);
     }
     qword projectedOffset;
     {
      register qword restoredOffset __asm__("vf6");
      register qword projected __asm__("vf3");
      __asm__("lqc2 %0,%3\n\tqmtc2.ni %4,%1\n\tsqc2 %1,%2"
       :"=j"(restoredOffset),"=j"(projected),"=m"(work.filteredDirection)
       :"m"(work.offset),"r"(projectedDirection));
      register qword offsetInput __asm__("$5");
      __asm__("qmfc2.ni %0,%1":"=r"(offsetInput):"j"(restoredOffset));
      projectedOffset=func_001FA970(space,offsetInput);
     }
     {
      register qword finalDirection __asm__("vf3");
      register qword finalOffset __asm__("vf6");
      __asm__("lqc2 %0,%2\n\tqmtc2.ni %3,%1":"=j"(finalDirection),"=j"(finalOffset):"m"(work.filteredDirection),"r"(projectedOffset));
      fraction=SegmentFraction(finalOffset,finalDirection);
     }
    }else fraction=SegmentFraction(pointOffset,segmentDirection);
   }
   float complement;
   if(fraction<lowerBound){fraction=0.0f;complement=1.0f;}else if(fraction>1.0f){fraction=1.0f;complement=0.0f;}else complement=1.0f-fraction;
   work.closest=Lerp(work.start,work.end,Scalar(work.scalar,complement),Scalar(work.scalar,fraction));
   qword delta=Sub(work.point,work.closest);
   if(space)delta=ToVU(func_001FA970(space,delta));
   float distance=Length(delta);
   if(distance<best){
    best=distance;time=complement*p->times[index-1]+fraction*p->times[index];
    if(outPosition)*outPosition=work.closest;
    if(outDirection)*outDirection=Normalize(Sub(work.end,work.start));
   }
   work.start=work.end;
  }
  if(outTime)*outTime=time;
  if(outValue)*outValue=func_001E63C0(p,time);
  break;
 }
 case 1:{
  float best=D_002A8138;int closest=-1;
  for(int index=0;index<p->count;index++){
   float distance;
   {
    register qword displacement __asm__("vf1");
    __asm__("lqc2 $vf2,0x20(%3)\n\tlqc2 %0,0x30(%3)\n\tlqc2 $vf3,0(%3)\n\tlqc2 $vf5,0x10(%3)\n\tlqc2 $vf4,%2\n\tvmulax.xyz $ACC,$vf3,$vf4x\n\tvmadday.xyz $ACC,$vf5,$vf4y\n\tvmaddaz.xyz $ACC,$vf2,$vf4z\n\tvmaddw.xyz $vf3,%0,$vf0w\n\tlqc2 $vf2,%1\n\tvsub.xyzw %0,$vf2,$vf3"
     :"=j"(displacement):"m"(work.point),"m"(p->points[index]),"r"(&work.matrix),"X"(work.matrix):"vf2","vf3","vf4","vf5");
    if(space){
     qword filtered=func_001FA970(space,displacement);
     {
      register qword projected __asm__("vf1");
      __asm__("qmtc2.ni %1,%0":"=j"(projected):"r"(filtered));
      distance=DisplacementLength(projected);
     }
    }else distance=DisplacementLength(displacement);
   }
   if(distance<best){best=distance;closest=index;}
  }
  func_001E6ED8(p,work.point,space,outPosition,outDirection,outTime,outValue,p->times[closest]);
  break;
 }
 }
}

#define OFF(t,m) ((unsigned int)&((t*)0)->m)
typedef char nearest_query_layout[(sizeof(void*)==4 && sizeof(qword)==16 && sizeof(U)==16 && sizeof(M4)==0x40 && sizeof(VTE)==8 && sizeof(SPACE)==0x20 && sizeof(WORK)==0xB0 && OFF(VTE,delta)==0 && OFF(VTE,fn)==4 && OFF(M4,a)==0 && OFF(M4,b)==0x10 && OFF(M4,c)==0x20 && OFF(M4,d)==0x30 && OFF(P,vt)==0xC && OFF(P,mode)==0xE0 && OFF(P,cyclic)==0xE4 && OFF(P,count)==0xE8 && OFF(P,times)==0xEC && OFF(P,values)==0xF0 && OFF(P,points)==0xF4 && OFF(SPACE,axis)==0 && OFF(SPACE,mode)==0x10 && OFF(WORK,matrix)==0 && OFF(WORK,closest)==0x40 && OFF(WORK,scalar)==0x50 && OFF(WORK,start)==0x60 && OFF(WORK,end)==0x70 && OFF(WORK,point)==0x80 && OFF(WORK,filteredDirection)==0x90 && OFF(WORK,offset)==0xA0)?1:-1];
