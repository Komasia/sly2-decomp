
typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];} U;
struct SP {qword p;float radius;};
extern float sqrtf(float);
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Cross(qword a,qword b){qword r;__asm__("vopmula.xyz ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"=j"(r):"j"(a),"j"(b));return r;}
static inline float Dot(qword a,qword b){qword d,one;float f;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a),"j"(b));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(d));return f;}
static inline float Len(qword v){qword d,one;float f;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(v));__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(d):"0"(d));__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(d));return f;}
static inline qword UnitLen(qword v,float f){qword l;U u;__asm__("qmtc2.ni %1,%0":"=j"(l):"r"(f));u.q=l;__asm__("vdiv Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%0,Q":"+j"(v):"j"(l));return v;}
static inline qword Unit(qword v){qword d,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(v));__asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"=j"(d):"0"(d));__asm__("vdiv Q,$vf0w,%0x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"+j"(d):"j"(v));return d;}
static inline qword Mix(qword a,qword b,float f,float g){qword x,y,r;U u;__asm__("qmtc2.ni %1,%0":"=j"(x):"r"(f));__asm__("qmtc2.ni %1,%0":"=j"(y):"r"(g));u.q=x;__asm__("vmulax.xyzw ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x":"=j"(r):"j"(a),"j"(b),"j"(x),"j"(y));u.q=y;return r;}
static inline qword AddScaled(qword a,qword b,float f){qword x;U u;__asm__("qmtc2.ni %1,%0":"=j"(x):"r"(f));__asm__("vadda.xyzw ACC,$vf0,%0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(a):"j"(b),"j"(x));u.q=x;return a;}
int func_001A4258(qword pos,float radius,int count,struct SP*points){
 int i;
 i=0;if(i<count){register qword p __asm__("vf3")=pos;do {float sum=radius+points[i].radius; if(Len(Sub(p,points[i].p))<sum)return 1;}while(++i<count);}
 i=1;if(i<count){register qword p __asm__("vf10")=pos;do {
  qword a=points[0].p,b=points[1].p;
  qword d=Sub(p,a),e=Sub(b,a),normal,line;float distance,fraction;
  float ra=points[0].radius,rb=points[1].radius;
  float length=Len(e);
  qword perpendicular=Cross(d,e);
  float s=(ra-rb)/length;
  e=UnitLen(e,length);
  perpendicular=Unit(Cross(e,perpendicular));
  normal=Mix(e,perpendicular,s,sqrtf(1.0f-s*s));
  a=AddScaled(a,normal,ra);
  b=AddScaled(b,normal,rb);
  d=Sub(p,a);
  distance=Dot(d,normal);
  line=Sub(b,a);
  fraction=Dot(d,line)/Dot(line,line);
  if(distance<radius && fraction>=0.0f && fraction<=1.0f)return 1;
 }while(points++,++i<count);}
 return 0;
}
