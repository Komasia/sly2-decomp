typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct HIT {qword a,b;float g20,g24,ny, g2C,g30,g34,nyOther,g3C,t,u;char pad48[0x18];};
class FRAME {public:int data[4];FRAME();~FRAME();};
extern "C" {
FRAME*func_001AE478(FRAME*);
void func_001AE4A0(FRAME*,int);
void func_001C5570();
void func_0020FAA0(void*,qword,qword,void(*)(),void*,int*,void**);
int func_0014CC58(int,qword,qword,int,void*,HIT*);
extern char D_003DD490[];
extern qword D_002A2DC0;
int func_001C6DE8(float lo,float hi,float threshold,qword point,int count,void*objects,qword*out);
}
FRAME::FRAME(){func_001AE478(this);}FRAME::~FRAME(){func_001AE4A0(this,2);}
static inline qword Bc(float f){qword q;U s;__asm__("qmtc2 %1,%0":"=j"(q):"r"(f));s.q=q;return q;}
static inline qword AddScaled(const qword &p,const qword &axis,qword scale){qword out;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(out):"j"(p),"j"(axis),"j"(scale));return out;}
int func_001C6DE8(float lo,float hi,float threshold,qword point,int count,void*objects,qword*out){
 HIT hit;
 FRAME frame;
 qword h=Bc(hi),l=Bc(lo);
 qword a=AddScaled(point,D_002A2DC0,h);
 qword b=AddScaled(point,D_002A2DC0,l);
 if(!objects)func_0020FAA0(D_003DD490,point,a,func_001C5570,0,&count,&objects);
 if(hi>0){
  if(func_0014CC58(0,point,a,count,objects,&hit)&&hit.t==0){
   if(hit.u==1||hit.nyOther<threshold)return 0;
   *out=hit.b;return 1;
  }
 }
 if(lo<0){
  if(func_0014CC58(0,point,b,count,objects,&hit)){
   if(hit.t==0||hit.ny<threshold)return 0;
   *out=hit.a;return 1;
  }
 }
 *out=point;return 1;
}
