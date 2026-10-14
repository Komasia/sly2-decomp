#define FIELD_OFFSET(t,m) ((unsigned int)&(((t*)0)->m))
typedef int qword __attribute__((mode(TI)));
struct U{qword q;};
struct SCALAR;
struct VECTOR;
extern "C" SCALAR*func_002564B8(SCALAR*);
extern "C" VECTOR*func_002564C0(VECTOR*);
struct SCALAR{qword q;SCALAR(){(void)func_002564B8(this);}};
struct VECTOR{qword q;VECTOR(){(void)func_002564C0(this);}};
struct POINTS{int count;qword*data;};
struct A{char pad[0x90];POINTS points;};
struct B;
struct W;
struct XP;
struct SURFACE{U plane;char pad10[8];int flags;};
struct EDGE{unsigned short ends[2];};
struct NODE{char pad[0x10];U point;char pad20[0x50-0x20];SURFACE*surface;EDGE*edge;int reverse;NODE*next;};
extern "C" {
 extern float D_002A6AD0;
 void func_001A7C18(W*,A*,B*,qword,qword,int,int,int,XP**,float);
}
static inline qword Load(U*p){qword r;__asm__("lqc2 %0,%1":"=j"(r):"m"(p->q));return r;}
static inline qword Point(qword*p){qword r;__asm__("lqc2 %0,%1":"=j"(r):"m"(*p));return r;}
static inline float FirstDistance(qword normal,qword point){
 SCALAR dot,one;qword d,k;int bits;float f;
 __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddaz.x $ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w":"=&j"(d),"=&j"(k):"j"(normal),"j"(point));
 __asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(d));__asm__("mtc1 %1,%0":"=f"(f):"r"(bits));
 one.q=k;dot.q=d;return f;
}
static inline float OtherDistance(qword normal,qword point){
 SCALAR dot,one;qword k;int bits;register float f __asm__("$f20");
 __asm__("vmul.xyz %0,%2,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddaz.x $ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w":"+j"(point),"=&j"(k):"j"(normal));
 __asm__("qmfc2.ni %0,%1":"=r"(bits):"j"(point));__asm__("mtc1 %1,%0":"=f"(f):"r"(bits));
 one.q=k;dot.q=point;return f;
}
typedef char U_Size[sizeof(U)==16?1:-1];
typedef char SCALAR_Size[sizeof(SCALAR)==16?1:-1];
typedef char VECTOR_Size[sizeof(VECTOR)==16?1:-1];
typedef char POINTS_Size[sizeof(POINTS)==8?1:-1];
typedef char NODE_Size[sizeof(NODE)==96?1:-1];
typedef char A_points_Offset[FIELD_OFFSET(A,points)==144?1:-1];
typedef char POINTS_count_Offset[FIELD_OFFSET(POINTS,count)==0?1:-1];
typedef char POINTS_data_Offset[FIELD_OFFSET(POINTS,data)==4?1:-1];
typedef char SURFACE_plane_Offset[FIELD_OFFSET(SURFACE,plane)==0?1:-1];
typedef char SURFACE_flags_Offset[FIELD_OFFSET(SURFACE,flags)==24?1:-1];
typedef char NODE_point_Offset[FIELD_OFFSET(NODE,point)==16?1:-1];
typedef char NODE_surface_Offset[FIELD_OFFSET(NODE,surface)==80?1:-1];
typedef char NODE_edge_Offset[FIELD_OFFSET(NODE,edge)==84?1:-1];
typedef char NODE_reverse_Offset[FIELD_OFFSET(NODE,reverse)==88?1:-1];
typedef char NODE_next_Offset[FIELD_OFFSET(NODE,next)==92?1:-1];
typedef char EDGE_ends_Offset[FIELD_OFFSET(EDGE,ends)==0?1:-1];
typedef char U_q_Offset[FIELD_OFFSET(U,q)==0?1:-1];
typedef char SCALAR_q_Offset[FIELD_OFFSET(SCALAR,q)==0?1:-1];
typedef char VECTOR_q_Offset[FIELD_OFFSET(VECTOR,q)==0?1:-1];
extern "C" void func_001A87F0(W*w,A*a,B*b,int count,int*indices,NODE**heads,XP**out){
 POINTS*positions=&a->points;NODE*n,*other;float f;
 for(int i=0;i<count;i++){
  qword*points=positions->data;
  int index=indices[i];NODE*head=heads[i];
  qword bestNormal; qword position=points[index];
  SURFACE*best=0;float bestOriginal;
  float bestMinimum=D_002A6AD0;
  for(n=head;n;n=n->next){
   SURFACE*surface=n->surface;
   int flags=surface->flags;qword normal=Load(&surface->plane);
   if(flags&8)continue;surface->flags=flags|8;
   float original=FirstDistance(normal,position);
   float minimum=original;
   for(other=head;other;other=other->next){
    int endpoint=1-other->reverse;
    qword point=Point(&points[other->edge->ends[endpoint]]);
    f=OtherDistance(normal,point);
    if(f<minimum)minimum=f;
   }
   if(bestMinimum<minimum){bestNormal=normal;best=surface;bestMinimum=minimum;bestOriginal=original;}
  }
  for(n=head;n;n=n->next)n->surface->flags&=~8;
  VECTOR normal; normal.q=bestNormal;
  func_001A7C18(w,a,b,position,normal.q,1,(int)&a->points.data[index],(int)best,out,bestOriginal);
  for(other=head;other;other=other->next){
   qword point=Load(&other->point);
   f=OtherDistance(bestNormal,point);
   if(f<bestOriginal){qword emitPoint=other->point.q;VECTOR normal;normal.q=bestNormal;func_001A7C18(w,a,b,emitPoint,normal.q,2,(int)other->edge,(int)best,out,f);}
  }
 }
}
