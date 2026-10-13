typedef int qword __attribute__((mode(TI)));
union U {qword q;float f;};struct M3 {qword a,b,c;};struct S;
extern float D_002C1EC4,D_002C1EC8,D_002C1ECC;
extern qword D_002A2DC0,D_002A2DA0;
extern "C" {
float func_001E8008(S*,float,float);void func_001E6F10(S*,qword*,qword*,float);
float func_0011D448(float,float);qword func_0011E1A0(float,float,float);
void func_001CBBA8(S*,qword*,qword*,float);
}
static inline qword Cross(qword a,qword b){qword r;__asm__("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Sq(qword a){qword r,one;__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a));return r;}
static inline qword Sqrt(qword a){__asm__("vsqrt $Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q":"+j"(a));return a;}
static inline float Float(qword a){float f;__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
static inline qword ToVu(qword a){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(a));return r;}
static inline qword Bc(float f,U &u){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));u.q=q;return q;}
static inline qword Norm(qword v,qword length){qword r;__asm__ volatile("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q":"=j"(r):"j"(length),"j"(v));return r;}
static inline qword Dir(const M3 &m,qword a){__asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z":"+j"(a):"j"(m.a),"j"(m.b),"j"(m.c));return a;}
static inline qword AddScaled(qword a,qword b,qword s){qword r;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(s));return r;}
void func_001CBBA8(S*p,qword*posOut,qword*dirOut,float g){
 U pos;
 M3 basis;
 U scalar,moved,out;
 float x=func_001E8008(p,g,D_002C1EC4);
 func_001E6F10(p,&pos.q,&basis.c,x);
 qword cross=Cross(basis.c,D_002A2DC0);
 qword fallback=D_002A2DA0,length=Sqrt(Sq(cross));
 qword right=ToVu(fallback);
 if(!(Float(length)<0.0001f))right=Norm(cross,length);
 basis.a=Cross(right,basis.c);basis.b=right;
 float r=func_0011D448(-1.0f,1.0f),ar=__builtin_fabsf(r);
 qword local=func_0011E1A0(r*ar*D_002C1EC8,1.0f,0.0f);
 qword dir=Dir(basis,ToVu(local));
 qword cpu;__asm__("qmfc2.ni %0,%1":"=r"(cpu):"j"(dir));
 out.q=dir;moved.q=cpu;
 if(posOut){
  U start;start.q=pos.q;
  float distance=ar*func_0011D448(0.0f,D_002C1ECC);
  *posOut=AddScaled(start.q,moved.q,Bc(distance,scalar));
 }
 if(dirOut)*dirOut=out.q;
}
