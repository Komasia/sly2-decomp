typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct V {float x,y,z;} __attribute__((aligned(16)));
struct HIT {qword pos[2];char pad[0x40];};
struct S {char pad[0xE0];char bsp[8];int count;int padEC;int padF0;qword*vertices;};
extern float D_002A76DC;
void *func_001BF110(void*,qword,int);
qword func_001BFDB0(void*,qword);
int func_001C1700(struct S*,void*,qword,qword,int,void**);
int func_001BC9F0(void*,qword);
qword func_001A6F00(void*,void*,qword);
int func_001C0960(struct S*,qword,qword,int,struct HIT*,int);
void func_0011EE08(qword,qword,qword,qword*,float*,float*);
void func_001C0940(struct S*,qword,qword*,int);
static inline float Z(qword q){qword z;float f;__asm__("pextuw %0,$zero,%1":"=r"(z):"r"(q));__asm__("mtc1 %1,%0":"=f"(f):"r"(z));return f;}
int func_001C0B50(struct S*p,qword point,qword*out){
 void*objects[128];
 union U a,b;
 union {qword q;int i[4];}best;
 struct HIT hits[1];
 union U nearest;
 float distance;
 void*leaf;struct S*poly;
 qword projected;
 int n,i;
 float z,bestDistance;
 leaf=func_001BF110(p->bsp,point,1);
 if(!leaf)return 0;
 projected=func_001BFDB0(leaf,point);poly=0;
 {int j=0;
 n=func_001C1700(p,0,projected,projected,128,objects);
 for(;j<n;j++){if(func_001BC9F0(objects[j],point)){poly=objects[j];break;}}
 }
 if(!poly){*out=projected;return 1;}
 best.i[2]=0;best.i[1]=0;best.i[0]=0;
 bestDistance=D_002A76DC;
 a.q=func_001A6F00(poly,0,poly->vertices[0]);
 z=Z(projected);a.f[2]=z;
 i=1;if(i<poly->count){do{
  int c;qword*h;
  b.q=func_001A6F00(poly,0,poly->vertices[i]);b.f[2]=z;
  c=func_001C0960(p,a.q,b.q,1,hits,2);
  h=&hits[0].pos[1];if(c>0){do{
   func_0011EE08(projected,h[-1],h[0],&nearest.q,0,&distance);
   if(distance<bestDistance){bestDistance=distance;*(qword*)&best=nearest.q;}
   h=(qword*)((char*)h+0x60);
  }while(--c);}
  a=b;i++;
 }while(i<poly->count);}
 func_001C0940(p,*(qword*)&best,out,0);
 return 1;
}
