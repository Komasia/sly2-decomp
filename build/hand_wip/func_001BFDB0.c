typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];} U;
struct T {qword *a,*b,*c;};
extern qword D_002A2DC0;
void func_0011EE08(qword,qword,qword,qword*,float*,float*);
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Cross(qword a,qword b){qword r;__asm__("vopmula.xyz ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1":"=j"(r):"j"(a),"j"(b));return r;}
static inline float Z(qword a){float z;__asm__("qmfc2.ni %0,%1\n\tpextuw %0,$zero,%0":"=r"(z):"j"(a));return z;}
static inline qword AddScaled(qword a,qword b,float g){U u;qword s,r;__asm__("qmtc2.ni %1,%0":"=j"(s):"r"(g));u.q=s;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(a),"j"(b),"j"(u.q));return r;}
static inline qword Read(qword a){qword q;__asm__("qmfc2.ni %0,%1":"=r"(q):"j"(a));return q;}
static inline float ExtractZ(qword q){float z;__asm__("pextuw %0,$zero,%1":"=r"(z):"0"(q));return z;}
static inline float ExtractX(qword q){float x;__asm__("qmfc2.ni %0,%1":"=r"(x):"j"(q));return x;}
static inline qword DotV(qword a,qword b){qword d=a,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"0"(d),"j"(b));return d;}
#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0x10000)->m)-0x10000)
typedef char Offset_0[FIELD_OFFSET(U,q)==0?1:-1];
typedef char Offset_1[FIELD_OFFSET(U,f)==0?1:-1];
typedef char Offset_2[FIELD_OFFSET(struct T,a)==0?1:-1];
typedef char Offset_3[FIELD_OFFSET(struct T,b)==4?1:-1];
typedef char Offset_4[FIELD_OFFSET(struct T,c)==8?1:-1];
typedef char Size_0[sizeof(U)==16?1:-1];
typedef char Size_1[sizeof(struct T)==12?1:-1];
typedef char Size_2[sizeof(qword)==16?1:-1];
typedef char Size_3[sizeof(void*)==4?1:-1];
typedef char Size_4[sizeof(float)==4?1:-1];
qword func_001BFDB0(struct T*t,qword p){
 U result;qword a=*t->a,b=*t->b,c=*t->c;
 qword ab=Sub(b,a);register qword aa __asm__("vf8")=a;register qword cc __asm__("vf7")=c;
 if(0.0f<Z(Cross(Sub(p,a),ab)))func_0011EE08(p,a,b,&result.q,0,0);
 else if(0.0f<Z(Cross(Sub(p,b),Sub(c,b))))func_0011EE08(p,b,c,&result.q,0,0);
 else if(0.0f<Z(Cross(Sub(p,c),Sub(a,c))))func_0011EE08(p,c,a,&result.q,0,0);
 else {qword n=Cross(ab,Sub(cc,aa));qword bits=Read(n);qword dv=DotV(Sub(aa,p),n);float nz=ExtractZ(bits);float dot=ExtractX(dv);float g=dot/nz;result.q=AddScaled(p,D_002A2DC0,g);}
 return result.q;
}
