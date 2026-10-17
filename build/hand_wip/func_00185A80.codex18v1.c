// Project a vector against a set of planes.
typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f[4];} U;
struct P{int count;char pad4[12];};
extern float D_002A568C;
void func_0011AD30(int,float*,float*,float*,float);
static inline qword*Plane(struct P*p,int i){return(qword*)((char*)p+0x10+(i<<4));}
static inline float Dot(qword a,qword b){qword d,one;float result;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(d),"=&j"(one):"j"(a),"j"(b));__asm__("qmfc2.ni %0,%1":"=r"(result):"j"(d));return result;}
static inline qword Read(qword raw){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(raw));return q;}
static inline void DotWrite(qword*row,qword*column,unsigned int*out){qword a,b,one;unsigned int word;__asm__("lqc2 %0,0(%1)":"=j"(b):"r"(column):"memory");__asm__("lqc2 %0,0(%1)":"=j"(a):"r"(row):"memory");__asm__("vmul.xyz %0,%0,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(a),"=&j"(one):"j"(b));__asm__("qmfc2.ni %0,%1":"=r"(word):"j"(a));__asm__("sw %1,0(%0)"::"r"(out),"r"(word):"memory");}
static inline void RhsWrite(qword vector,qword*plane,float*out){float g=((float*)plane)[3]+Dot(vector,*plane);__asm__("swc1 %1,0(%0)"::"r"(out),"f"(g):"memory");}
static inline int Count(struct P*p){register int count __asm__("$2");__asm__("lw %0,%1":"=r"(count):"m"(p->count));return count;}
qword func_00185A80(void*unused,struct P*p,qword v){
 float matrix[36];float rhs[6] __attribute__((aligned(16)));float weights[6] __attribute__((aligned(16)));U scalar;int i,j,initial=Count(p);
 typedef char scratch_layout[(sizeof(matrix)==0x90 && sizeof(rhs)==24 && sizeof(weights)==24 && __alignof__(rhs)==16 && __alignof__(weights)==16)?1:-1];
 qword vector=Read(v);
 if(initial!=0){
  register int n __asm__("$4")=initial;
  unsigned int*cursor=(unsigned int*)matrix;
  typedef char matrix_extent[(sizeof(matrix)==0x90)?1:-1];
  typedef char rhs_extent[(sizeof(rhs)==24 && __alignof__(rhs)==16)?1:-1];
  typedef char weights_extent[(sizeof(weights)==24 && __alignof__(weights)==16)?1:-1];
  typedef char scalar_extent[(sizeof(scalar)==16 && __alignof__(scalar)==16)?1:-1];
  for(i=0;i<n;i++){
   for(j=0;j<n;j++){DotWrite(Plane(p,i),Plane(p,j),cursor);++cursor;n=Count(p);}
   n=Count(p);
  }
  if(n>0){qword left;float*cursor=rhs;__asm__("vmove.xyzw %0,%1":"=j"(left):"j"(vector));for(i=0;i<n;i++){RhsWrite(left,Plane(p,i),cursor);++cursor;n=Count(p);}}
  func_0011AD30(Count(p),matrix,rhs,weights,D_002A568C);
  {int n=Count(p);if(n>0){
   qword scale; qword*plane=Plane(p,0);float*weight=weights;
   do{
    __asm__("qmtc2.ni %1,%0":"=j"(scale):"r"(*(unsigned int*)weight));
    __asm__("vadda.xyzw $ACC,%0,$vf0\n\tvmaddx.xyzw %0,%1,%2x":"+j"(vector):"j"(*plane),"j"(scale));
    ++plane;++weight;
   }while(--n!=0);
   __asm__("sqc2 %1,%0":"=m"(scalar.q):"j"(scale));
  }
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
