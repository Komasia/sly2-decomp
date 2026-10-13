typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct HIT {qword a,b;U normal,otherNormal;float t,u;char pad48[0x18];};
struct FRAME {};
extern "C" {
FRAME*func_001AE478(FRAME*);
void func_001AE4A0(FRAME*,int);
struct O;int func_001C5570(void*,O*);
void func_0020FAA0(void*,qword,qword,int(*)(void*,O*),void*,int*,O***);
O*PsoHitTestLineObjects(int,qword,qword,int,O**,HIT*) __asm__("PsoHitTestLineObjects__FiP6VECTORT1iPP2SOP3LSG");
extern char D_003DD490[];
extern qword D_002A2DC0;
int func_001C6DE8(float lo,float hi,float threshold,qword point,int count,O**objects,qword*out);
}

static inline FRAME*CopyFrame(FRAME*p){return p;}
static inline qword Bc(float f){qword q;U s;__asm__("qmtc2 %1,%0":"=j"(q):"r"(f));s.q=q;return s.q;}
static inline qword AddScaled(const qword &p,const qword &axis,qword scale){qword out;__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(out):"j"(p),"j"(axis),"j"(scale));return out;}
int func_001C6DE8(float lo,float hi,float threshold,qword point,int count,O**objects,qword*out){
 HIT hit;
 FRAME frame;FRAME*guard=CopyFrame(&frame);func_001AE478(guard);
 qword h=Bc(hi),l=Bc(lo);
 qword a=AddScaled(point,D_002A2DC0,h);
 qword b=AddScaled(point,D_002A2DC0,l);
 if(!objects)func_0020FAA0(D_003DD490,point,a,func_001C5570,0,&count,&objects);
 if(hi>0){
  if(PsoHitTestLineObjects(0,point,a,count,objects,&hit)&&hit.t==0){
   if(hit.u==1||hit.otherNormal.f[2]<threshold){func_001AE4A0(guard,2);return 0;}
   *out=hit.b;{func_001AE4A0(guard,2);return 1;}
  }
 }
 if(lo<0){
  if(PsoHitTestLineObjects(0,point,b,count,objects,&hit)){
   if(hit.t==0||hit.normal.f[2]<threshold){func_001AE4A0(guard,2);return 0;}
   *out=hit.a;{func_001AE4A0(guard,2);return 1;}
  }
 }
 *out=point;{func_001AE4A0(guard,2);return 1;}
}

#define OFF(t,m) ((int)&((t*)0)->m)
typedef char query_layout_assert[(sizeof(U)==16 && sizeof(HIT)==0x60 && sizeof(FRAME)==1 && OFF(HIT,normal)==0x20 && OFF(HIT,otherNormal)==0x30 && OFF(HIT,t)==0x40 && OFF(HIT,u)==0x44)?1:-1];
