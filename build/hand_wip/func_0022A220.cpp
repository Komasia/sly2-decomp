// Clip BSP edge intersections against the vertical source/camera curtain.
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
typedef unsigned short ushort;
union V {qword q;float f[4];};
union F32 {uint bits;float f;};
struct EDGE {ushort first,second,field4,face;EDGE *next;};
struct FACE {V equation;EDGE *first;int field14;int flags;int field1C;};
struct NODE {NODE *negative,*positive;FACE *face;};
struct TREE {int field0,field4,count;NODE *nodes;};
struct O {char pad[0x68];TREE tree;char pad78[0x1C];V *vertices;int field98;FACE *faces;char padA0[0xC8];O *source;char pad16C[0xC];int frame,collided;float height;};
struct CAMERA {char pad[0x90];V position;char padA0[0x404];int frame;};
struct REQ {int bytes,alignment;};
struct MARK {};
struct WORLD;
struct PAIR {V value,one;};
union PHASE {V plane;REQ request;V scalar;};
struct WORK {V points[4],sides[4];PHASE phase;MARK marker;V normal;int count;O **objects;int capacity;FACE **cursor;PAIR evaluations[6];V camera,source,plane,first,second;O ***objectsOut;V temporary,firstBoundary,intersection;};
extern CAMERA D_002DDF40;
extern F32 D_002C4490;
extern V D_002A2DC0;
extern WORLD D_003DD490;
extern "C" {
qword func_001A62E8(O *);
void func_00119308(V *,qword,qword,qword);
void func_00119390(V *,qword,qword);
V *func_002564C0(V *);
V *func_002564B8(V *);
MARK *func_001AE478(MARK *);
void func_001AE4A0(MARK *,int);
void *func_001AE318(const REQ *);
int func_0014F030(void *,O *);
void func_0020FAA0(WORLD *,qword,qword,int (*)(void *,O *),void *,int *,O ***);
int func_00118D08(NODE *,NODE *,int,const V *,int *,FACE ***);
}
static inline qword ToVF(qword q){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(q));return r;}
static inline qword ToCPU(qword q){qword r;__asm__("qmfc2.ni %0,%1":"=r"(r):"j"(q));return r;}
static inline qword ScalarWord(uint bits){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(bits));return r;}
static inline qword Scalar(float f){qword r;__asm__("qmtc2.ni %1,%0":"=j"(r):"r"(f));return r;}
static inline qword VectorHome(V &home,qword value){home.q=value;return home.q;}
static inline qword LoadVF(const V &v){qword r;__asm__("lqc2 %0,%1":"=j"(r):"m"(v));return r;}
static inline qword AddScaled(qword base,qword vector,qword coefficient){qword r;__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x":"=j"(r):"j"(base),"j"(vector),"j"(coefficient));return r;}
static inline qword AddScaledUp(qword base,qword up,qword coefficient){__asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%0,%2x":"+j"(up):"j"(base),"j"(coefficient));return up;}
static inline qword Sub(qword a,qword b){qword r;__asm__("vsub.xyzw %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Minimum(qword a,qword b){__asm__("vmini.xyz %0,%0,%1":"+j"(a):"j"(b));return a;}
static inline qword Maximum(qword a,qword b){qword r;__asm__("vmax.xyz %0,%1,%2":"=j"(r):"j"(a),"j"(b));return r;}
static inline qword Cross(qword a,qword b){__asm__("vopmula.xyz ACC,%0,%1\n\tvopmsub.xyz %0,%1,%0":"+j"(a):"j"(b));return a;}
static inline qword DotV(qword a,qword b){qword r,one;__asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"=j"(r),"=&j"(one):"j"(a),"j"(b));return r;}
static inline qword Sqrt(qword value){__asm__("vsqrt Q,%0x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q":"+j"(value));return value;}
static inline qword Unit(qword v){qword length=Sqrt(DotV(v,v)),r;__asm__("vdiv Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,Q":"=j"(r):"j"(v),"j"(length));return r;}
static inline float X(qword q){float f;int bits;__asm__("qmfc2.ni %1,%2
	mtc1 %1,%0":"=f"(f),"=&r"(bits):"j"(q));return f;}
static inline float Z(qword q){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(q));return f;}
static inline float LengthXY(qword v){qword r;__asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y":"=j"(r):"j"(v));return X(Sqrt(r));}
static inline qword Lerp(qword first,qword second,qword from,qword toward){qword r;__asm__("vmulax.xyzw ACC,%1,%3x\n\tvmaddx.xyzw %0,%2,%4x":"=j"(r):"j"(first),"j"(second),"j"(from),"j"(toward));return r;}
static inline float Distance(PAIR &snapshot,const V &plane,const V &point){
 func_002564B8(&snapshot.value);func_002564B8(&snapshot.one);
 qword normal=LoadVF(plane),position=LoadVF(point);
 __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddaz.x ACC,%1,%0z\n\tvmsubw.x %0,%1,%2w":"=j"(snapshot.value.q),"=&j"(snapshot.one.q):"j"(normal),"j"(position));
 return X(snapshot.value.q);
}
static inline float BoundaryDistance(PAIR &snapshot,const V &plane,const V &point,qword &livePoint){
 func_002564B8(&snapshot.value);func_002564B8(&snapshot.one);
 qword normal=LoadVF(plane),position=LoadVF(point);
 __asm__("vmul.xyz %0,%0,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddaz.x ACC,%1,%0z\n\tvmsubw.x %0,%1,%0w":"=j"(snapshot.value.q),"=&j"(snapshot.one.q):"0"(normal),"j"(position));
 livePoint=position;return X(snapshot.value.q);
}
extern "C" void func_0022A220(O *owner){
 WORK w;
 CAMERA *camera=&D_002DDF40;
 if(owner->frame==camera->frame)return;
 owner->frame=camera->frame;
 w.camera.q=camera->position.q;
 O *source=owner->source;if(!source)source=owner;
 qword sourcePosition=func_001A62E8(source);
 owner->collided=0;owner->height=0.0f;
 w.source.q=sourcePosition;
 qword coefficient=VectorHome(w.phase.scalar,ScalarWord(D_002C4490.bits)),sourceVector=ToVF(sourcePosition),cameraVector=LoadVF(w.camera),up=LoadVF(D_002A2DC0);
 qword cameraTop=AddScaled(cameraVector,up,coefficient),sourceTop=AddScaledUp(sourceVector,up,coefficient);
 w.points[0].q=ToCPU(sourceVector);w.points[2].q=cameraTop;w.points[1].q=sourceTop;w.points[3].q=ToCPU(cameraVector);
 func_00119308(&w.phase.plane,w.camera.q,sourcePosition,ToCPU(sourceTop));
 w.objectsOut=&w.objects;w.plane.q=w.phase.plane.q;
 int i;
 V *sidePlanes=w.sides,*normalCopy=&w.normal;int *objectCount=&w.count;MARK *marker=&w.marker;
 for(i=0;i<4;i++){
  qword edge=Sub(w.points[(i+1)%4].q,w.points[i].q);w.temporary.q=edge;
  func_002564C0(normalCopy);
  qword plane=LoadVF(w.plane),direction=LoadVF(w.temporary);
  qword copied=VectorHome(*normalCopy,plane);
  qword cross=Cross(direction,copied);
  qword normal=Unit(cross);
  func_00119390(sidePlanes+i,normal,w.points[i].q);
 }
 func_001AE478(marker);
 w.phase.request.bytes=0x10000;w.phase.request.alignment=16;
 FACE **faces=(FACE **)func_001AE318(&w.phase.request);
 coefficient=VectorHome(w.phase.scalar,ScalarWord(D_002C4490.bits));
 qword cam=LoadVF(w.camera),position=LoadVF(w.source),upper=AddScaled(Maximum(cam,position),LoadVF(D_002A2DC0),coefficient),lower=Minimum(cam,position);
 func_0020FAA0(&D_003DD490,lower,upper,func_0014F030,0,objectCount,w.objectsOut);
 qword initialDelta=Sub(w.source.q,w.camera.q);
 float best=Z(initialDelta)/LengthXY(initialDelta),initial=best;
 for(i=0;i<w.count;i++){
  O *object=w.objects[i];w.capacity=0x4000;w.cursor=faces;
  int result=func_00118D08(object->tree.nodes,object->tree.nodes+object->tree.count,4,w.points,&w.capacity,&w.cursor);
  switch(result){case 0:func_001AE4A0(marker,2);return;case 1:continue;}
  int count=w.cursor-faces;
  for(int j=0;j<count;j++){
   for(EDGE *edge=faces[j]->first;edge;edge=edge->next){
    if(!(object->faces[edge->face].flags&0x4000))continue;
    w.first.q=object->vertices[edge->first].q;w.second.q=object->vertices[edge->second].q;
    float first=Distance(w.evaluations[0],w.plane,w.first);
    float second=Distance(w.evaluations[1],w.plane,w.second);
    if(0.0f<first&&0.0f<second)continue;
    if(first<0.0f&&second<0.0f)continue;
    float fraction=first/(first-second);
    qword pending=Scalar(fraction);
    qword from=VectorHome(w.phase.scalar,Scalar(1.0f-fraction));
    qword toward=VectorHome(w.phase.scalar,pending);
    w.firstBoundary.q=LoadVF(w.sides[0]);
    w.intersection.q=Lerp(w.first.q,w.second.q,from,toward);
    int inside=0;qword liveIntersection;
    if(BoundaryDistance(w.evaluations[2],w.firstBoundary,w.intersection,liveIntersection)<0.0f){
     w.temporary.q=LoadVF(w.sides[1]);
     if(BoundaryDistance(w.evaluations[3],w.temporary,w.intersection,liveIntersection)<0.0f){
      w.temporary.q=LoadVF(w.sides[2]);
      if(BoundaryDistance(w.evaluations[4],w.temporary,w.intersection,liveIntersection)<0.0f){
       w.temporary.q=LoadVF(w.sides[3]);
       if(BoundaryDistance(w.evaluations[5],w.temporary,w.intersection,liveIntersection)<0.0f)inside=1;
      }
     }
    }
    if(inside){qword delta=Sub(liveIntersection,w.camera.q);float slope=Z(delta)/LengthXY(delta);if(best<slope)best=slope;}
   }
  }
  if(count>0){int remaining=count;FACE **next=faces;do{FACE *face=*next++;face->flags&=~0x4000;}while(--remaining);}
 }
 owner->collided=1;
 owner->height=(best-initial)*LengthXY(Sub(w.camera.q,w.source.q));
 func_001AE4A0(marker,2);
}
