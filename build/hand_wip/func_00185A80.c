typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];} U;
struct P{int count;char pad4[12];};
extern float D_002A568C;
void func_0011AD30(int,float*,float*,float*,float);
static inline qword*Plane(struct P*p,int i){return(qword*)((char*)p+0x10+(i<<4));}
static inline float Dot(qword a,qword b){qword d,one;float result;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a),"j"(b));__asm__("qmfc2.ni %0,%1":"=r"(result):"j"(d));return result;}
static inline qword Read(qword raw){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(raw));return q;}
static inline void DotWrite(qword*row,qword*column,unsigned int*out){qword a,b,one;unsigned int word;__asm__("lqc2 %0,%1":"=j"(b):"m"(*column));__asm__("lqc2 %0,%1":"=j"(a):"m"(*row));__asm__("vmul.xyz %0,%0,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(a),"=&j"(one):"j"(b));__asm__("qmfc2.ni %0,%1":"=r"(word):"j"(a));__asm__("sw %1,%0":"=m"(*out):"r"(word));}
static inline void RhsWrite(qword vector,qword*plane,float*out){float g=((float*)plane)[3]+Dot(vector,*plane);__asm__("swc1 %1,%0":"=m"(*out):"f"(g));}
static inline int Count(struct P*p){register int count __asm__("$2");__asm__("lw %0,%1":"=r"(count):"m"(p->count));return count;}
qword func_00185A80(void*unused,struct P*p,qword v){
 float matrix[36];float rhs[6] __attribute__((aligned(16)));float weights[6] __attribute__((aligned(16)));U scalar;int i,j,n=Count(p);
 typedef char scratch_layout[(sizeof(matrix)==0x90 && sizeof(rhs)==24 && sizeof(weights)==24 && __alignof__(rhs)==16 && __alignof__(weights)==16)?1:-1];
 qword vector=Read(v);
 if(n!=0){
  unsigned int*cursor=(unsigned int*)matrix;
  for(i=0;i<n;i++){
   for(j=0;j<n;j++){DotWrite(Plane(p,i),Plane(p,j),cursor);++cursor;n=Count(p);}
   n=Count(p);
  }
  {float*cursor=rhs;for(i=0;i<n;i++){RhsWrite(vector,Plane(p,i),cursor);++cursor;n=Count(p);}}
  func_0011AD30(Count(p),matrix,rhs,weights,D_002A568C);
  n=Count(p);for(i=0;i<n;i++){
   qword scale;__asm__("qmtc2.ni %1,%0":"=j"(scale):"r"(*(unsigned int*)&weights[i]));scalar.q=scale;
   __asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(vector):"j"(*Plane(p,i)),"j"(scalar.q));
  }
 }
 return vector;
}

typedef char qword_Size[(sizeof(qword)==16)?1:-1];
typedef char U_Size[(sizeof(U)==16)?1:-1];
typedef char P_header_Size[(sizeof(struct P)==16)?1:-1];
typedef char P_count_Offset[((unsigned)&((struct P*)0)->count==0)?1:-1];
typedef char int_Size[(sizeof(int)==4)?1:-1];
typedef char float_Size[(sizeof(float)==4)?1:-1];
