typedef int qword __attribute__((mode(TI)));
typedef union {qword q;float f;} V;
struct TRI {int index[3];};
struct MESH {qword *velocity,*acceleration;struct TRI *triangles;};
struct P {void *x0;int x4;float maximum;int xC;struct MESH*mesh;char pad14[0x64];int count;qword *positions;int triCount;void *planes;char pad88[0x20];int state;};
void func_00119308(void*,qword,qword,qword);
static inline qword Scalar(float f){qword q;__asm__("qmtc2.ni %1,%0":"=j"(q):"r"(f));return q;}
static inline qword Step(qword a,qword b,qword s){qword r;
__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=&j"(r):"j"(a),"j"(b),"j"(s));return r;}
static inline qword Position(qword p,qword old,qword next,qword half){qword r;
__asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddax.xyzw $ACC,%2,%4x\n\tvmaddx.xyzw %0,%3,%4x":"=&j"(r):"j"(p),"j"(old),"j"(next),"j"(half));return r;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"0"(a),"j"(b));return r;}
static inline float LengthSquared(qword q){qword r,one;float f;
__asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=&j"(r),"=&j"(one):"j"(q));
__asm__("qmfc2.ni %0,%1":"=r"(f):"j"(r));return f;}
void func_001F6EF8(struct P*p,float dt)
{
 V scalar;
 register int vertexIndex __asm__("a2")=0;
 qword *velocity=p->mesh->velocity;
 qword *acceleration=p->mesh->acceleration;register qword *positions __asm__("s4");
 float maximum=0.0f;
 positions=p->positions;
 if(p->count>0){
   qword time=Scalar(dt),half=Scalar(dt*0.5f);
   qword *position=positions;
   do{
     qword old=*velocity,force=*acceleration,point=*position;
     qword next,newpoint;
     float square;
     scalar.q=time;
     next=Step(old,force,scalar.q);
     scalar.q=half;
     newpoint=Position(point,old,next,scalar.q);
     if(p->state!=-1 && 1.0f<LengthSquared(Sub(point,newpoint)))p->state=-1;
     square=LengthSquared(newpoint);
     *position=newpoint;
     *velocity=next;
     if(maximum<square)maximum=square;
   }while(++velocity,++position,++acceleration,++vertexIndex<p->count);
 }
 p->maximum=__builtin_sqrtf(maximum);
 {
   struct TRI*firstTri=p->mesh->triangles;
   char *firstPlane=(char*)p->planes;
   register int planeIndex __asm__("s3")=0;
   if(p->triCount>0){struct TRI*tri=firstTri;char*plane=firstPlane;do{
     func_00119308(plane,positions[tri->index[0]],positions[tri->index[1]],positions[tri->index[2]]);
     plane+=0x20;
   }while(++tri,++planeIndex<p->triCount);}
 }
}
